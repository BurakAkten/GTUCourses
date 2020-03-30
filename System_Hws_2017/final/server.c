#include <sys/socket.h> //for socket functions
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "inverse.h"


#ifndef PATH_MAX
#define PATH_MAX 256
#endif


typedef struct{
	double **A;
	double *b;
}Matrices;


typedef struct{
	double* x;
}Result;


typedef struct{
	Matrices* data;
	Matrix size;
	double* result;
}Params;

void* connectionWithThread(void* requirements);
int perRequest(int port);
int workerPool(int port ,pthread_t** tid,int* poolSize);
void signalhandling(int sigNum);
void do_server_staff(int socket ,Matrix matrix);
void createMatrix(double** A , double* b , Matrix matrix);
void P1(int socket , Matrix matrix , Matrices* shmData);
void P2(Matrix matrix , Matrices* shmData , double* x);
double P3(Matrices* shmData , Result *shmData2 ,Matrix matrix);
void* psuedo_inverse(void* parameters);
void writeToShm2(double *resultX , Result *shmData2 , int size);
void writeToLog(double** A , double* b , double** x, Matrix size,double e );





int signalNumber = 999;
int sizeofThread = 0;
pthread_t* tid = NULL;
int shmid;
int shmid2;
pid_t pid;


int main(int argc , char **args){

	FILE* temp = NULL;
	int portNumber = 0 , threadPoolSize = 0;;
	int socket  = 0, newSocket = 0, connectSoc = 0;
	pid = getpid();
	

	if(argc != 3){
		fprintf(stdout, "Usage : %s <port #, id> <thpool size, k >\n", args[0]);
		kill(pid , SIGUSR1);
		exit(1);
	}

	signal(SIGINT ,&signalhandling);
	signal(SIGUSR1 ,&signalhandling);

	threadPoolSize = atoi(args[2]);
	portNumber = atoi(args[1]);

	/*if thread pool size is equal to zero then the program works for per-request
	else threadPool will be directly created*/
	if(threadPoolSize == 0){

		if(perRequest(portNumber) < 0){
			kill(pid , SIGUSR1);
			exit(1);
		}

	}
	else{

		tid = (pthread_t*)calloc(threadPoolSize , sizeof(pthread_t));
		if(workerPool(portNumber ,&tid,&threadPoolSize) < 0){
			free(tid);
			kill(pid , SIGUSR1);
			exit(1);
		}
	}

	return 0;
}

int perRequest(int port){

	int socketfd  = 0, newSocket = 0, connectSoc = 0;
	struct sockaddr_in serv_address;
	pthread_t thread;
	int totalClient = 1;

	socketfd = socket(AF_INET , SOCK_STREAM , 0);
	fprintf(stdout, "Socket is created!\n");

	/*clear adress memory*/
	memset(&serv_address, '0', sizeof(serv_address));

	serv_address.sin_family = AF_INET;    
  	serv_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  	serv_address.sin_port = htons(port);

  	/*The socket is binding*/
  	if(bind(socketfd, (struct sockaddr*)&serv_address,sizeof(serv_address)) < 0){
  		fprintf(stderr, "Error on listening!!\n");
  		return -1;
  	}

  	/*Listening the clients*/
  	if(listen(socketfd , 100) < 0 ){
  		fprintf(stderr, "Error on listening!!\n");
  		return -1;
  	}

  	while((newSocket = accept(socketfd , (struct sockaddr*)NULL , NULL))){

  		//printf("Connected!\n");

  		if(pthread_create(&thread , NULL ,  connectionWithThread , &newSocket) < 0){
            perror("Could not create thread!");
            return -1;
        }

        pthread_join(thread , NULL);
        printf("Currently served client numbers : %d\n",totalClient);
        totalClient++;
        
  	}
	return 1;
}

int workerPool(int port ,pthread_t** tid, int* poolSize){

	int socketfd  = 0, newSocket = 0, connectSoc = 0;
	struct sockaddr_in serv_address;
	int i = 0 , size = 0;
	int totalClient = 1;

	socketfd = socket(AF_INET , SOCK_STREAM , 0);
	fprintf(stdout, "Socket is created!\n");

	/*clear adress memory*/
	memset(&serv_address, '0', sizeof(serv_address));

	serv_address.sin_family = AF_INET;    
  	serv_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  	serv_address.sin_port = htons(port);

  	/*The socket is binding*/
  	if(bind(socketfd, (struct sockaddr*)&serv_address,sizeof(serv_address)) < 0){
  		fprintf(stderr, "Error on listening!!\n");
  		return -1;
  	}

  	/*Listening the clients*/
  	if(listen(socketfd , 100) < 0 ){
  		fprintf(stderr, "Error on listening!!\n");
  		return -1;
  	}

  	/*Thread function is called with threadpool*/
  	while((newSocket = accept(socketfd , (struct sockaddr*)NULL , NULL))){

  		/*if threadpool is finished then new place is allocated.*/
  		if(sizeofThread >= *poolSize ){
  			size = *poolSize * 2;
			*tid = (pthread_t*)realloc(*tid , sizeof(pthread_t)*size);
  			*poolSize = size;
  		}

  		//printf("Connected!\n");	
  		if(pthread_create(&(*tid)[sizeofThread] , NULL ,  connectionWithThread , &newSocket) < 0){
            perror("Could not create thread!");
            return -1;
        }

        printf("Currently served client numbers : %d\n",sizeofThread );
        sizeofThread++;
        
  	}
  	return 1;
}

void* connectionWithThread(void* requirements){

	char recvBuff[9];
	int socket = *(int*)requirements;
	Matrix matrix; /*Holds row and col numbers of the matrix*/
	matrix.row = 0;
	matrix.col = 0;

	while((read(socket, &matrix, sizeof(Matrix))) > 0){
		do_server_staff(socket , matrix);
    }
}

void do_server_staff(int socket , Matrix matrix){
	double *resultX , normE;
	int i = 0 , j = 0;
	pid_t child1 , child2 , child3;
	/*for shared memory key to create shm*/
	key_t shmkey = 959595;
	int sizeA = sizeof(double[matrix.row][matrix.col]);
	int sizeB = sizeof(double[matrix.row]);
	int sizeX = sizeof(double[matrix.col]);

	/*Shared memory is created for writing the total into.*/
	shmid = shmget(shmkey,sizeof(Matrices) + sizeA + sizeB,IPC_CREAT | 0600);

	shmid2 = shmget(shmkey + 4 , sizeof(Result)+sizeX , IPC_CREAT | 0600);


	Result* shmData2 = shmat(shmid2 , NULL ,0);

	Matrices* shmData = shmat(shmid , NULL ,0);
	if(shmData == (void*)-1 || shmData2 == (void*)-1){
		kill(pid , SIGUSR1);
		exit(1);
	} 
	resultX = (double*)malloc(sizeof(double)*matrix.col);	

	pthread_mutex_t a = PTHREAD_MUTEX_INITIALIZER;

	/*creating processes*/
	child1 = fork();
	if(getpid() == pid){
		child2 = fork();
		if(getpid() == pid)
			child3 = fork();
	}

	if(child1 == 0){
		pthread_mutex_lock(&a);

		P1(socket , matrix , shmData);

		pthread_mutex_unlock(&a);
		exit(1);
	}
	
	if(child2 == 0){
		pthread_mutex_lock(&a);

		P2(matrix , shmData , resultX);	

		writeToShm2(resultX , shmData2 , matrix.col);

		pthread_mutex_unlock(&a);
		exit(1);
	}
	if(child3 == 0){
		pthread_mutex_lock(&a);

		normE = P3(shmData , shmData2 , matrix);

		pthread_mutex_unlock(&a);
		exit(1);

	}
	if(getpid() == pid)
		free(resultX);
	
	while(wait(NULL) > 0){}
	shmctl(shmid , IPC_RMID , NULL);
	shmctl(shmid2 , IPC_RMID , NULL);

	shmdt(shmData);
	shmdt(shmData2);

}

void P1(int socket , Matrix matrix , Matrices* shmData){

	int i = 0 , j;
	Matrices* temp  = shmData + sizeof(Matrices);
	Matrices* temp2 = temp + sizeof(double) * matrix.row * matrix.col;

	shmData->A = (double**)(shmData + sizeof(Matrices));
	for(i = 0; i < matrix.row ; ++i){
		temp += matrix.col * sizeof(double);
		shmData->A[i] = (double*)temp;
	}

	shmData->b = (double*)(temp2);

	srand(time(NULL));
	createMatrix(shmData->A , shmData->b , matrix);
	
	for ( i = 0; i < matrix.row; ++i){
		for (j = 0; j < matrix.col; ++j){
			write(socket , &shmData->A[i][j] , sizeof(double));		
		}
	}

	for (i = 0; i < matrix.row; ++i){
		write(socket , &shmData->b[i] , sizeof(double));
	}
}

void P2(Matrix matrix , Matrices* shmData , double* x){

	pthread_t tid[3];
	int i ;
	Params parameters;
	parameters.data = shmData;
	parameters.result = x;
	parameters.size = matrix;

	for (i = 0; i < 3; ++i){
		pthread_create(&tid[i] , 0 , psuedo_inverse , &parameters);
		
	}

	for (i = 0; i < 3; ++i){
		pthread_join(tid[i] , NULL);	
	}
	
}
		
double P3(Matrices* shmData , Result *shmData2 ,Matrix matrix){

	double **b , **x , **e , **eT;
	Matrix xS , bS , eS , eTS;
	double **res , ee;
	int i = 0;

	b = (double**)malloc(sizeof(double*)*matrix.row);
	e = (double**)malloc(sizeof(double*)*matrix.row);

	for(int i = 0 ; i < matrix.row ; i++){
		b[i] = (double*)malloc(sizeof(double));
		e[i] = (double*)malloc(sizeof(double));

	}
	x = (double**)malloc(sizeof(double*)*matrix.col);
	for(int i = 0 ; i < matrix.col ; i++)
		x[i] = (double*)malloc(sizeof(double));


	eT = (double**)malloc(sizeof(double*));
	eT[0] = (double*)malloc(sizeof(double)*matrix.row);


	res = (double**)malloc(sizeof(double*));
	res[0] = (double*)malloc(sizeof(double));


	xS.row = matrix.col;
	xS.col = 1;
	bS.row = matrix.row;
	bS.col = 1;

	for (i = 0; i < matrix.row ; ++i){
		b[i][0] = shmData->b[i];
	}

	for (i = 0; i < matrix.col ; ++i){
		x[i][0] = shmData2->x[i];
	}


	eS = matrixMultip(shmData->A , x , e , matrix , xS);

	for(i = 0 ; i < eS.row ; i++){
		e[i][0] = e[i][0] - b[i][0];
	}

	eTS = Tranpose(e , eT , eS);

	matrixMultip(eT , e , res , eTS , eS );

	ee = sqrt(res[0][0]);


	writeToLog(shmData->A,shmData->b , x , matrix , ee);

	for(i = 0; i < matrix.row ; i++)
		free(b[i]);
	free(b);
	for(i = 0; i < matrix.col ; i++)
		free(res[i]);
	free(res);
	for(i = 0; i < matrix.row ; i++)
		free(e[i]);
	free(e);
	/*for(i = 0 ; i < 1 ; i++)
		free(res[i]);*/
	free(res);

	/*free(eT[0]);*/
	free(eT);

	

	return ee;
}

void writeToShm2(double *resultX , Result *shmData2 , int size){

	int i ;
	Result* temp = shmData2 + sizeof(Result);
	shmData2->x = (double*)temp;

	for(i = 0; i < size ; i++)
		shmData2->x[i] = resultX[i];

}

void createMatrix(double** A , double* b , Matrix matrix){
	
	int i = 0 , j;
	int flag = 1;
	srand(time(NULL));
	
	for(i  = 0; i < matrix.row ; i++){

		b[i] = rand() % 100 + 5;

		for (j = 0; j < matrix.col; ++j){
			A[i][j] = rand() % 100 + 5;
		}
	}
}

void signalhandling(int sigNum){
	signalNumber = sigNum;
	int i =0;
	if(signalNumber == SIGINT){
    	
    	if(getpid() != pid){
    		kill(pid , SIGINT);
    		exit(1);
    	}
    	
    	fprintf(stdout, "SIGINT is caught!\n");
    	if(sizeofThread != 0){
    		for(; i < sizeofThread ; i++){
  				pthread_join(tid[i],NULL);
    		}
			free(tid);
    	}
    	exit(1);
    }
    else if(signalNumber == SIGUSR1){
    	fprintf(stdout, "Error with error exit -1!\n");
    	if(sizeofThread != 0){
    		for(; i < sizeofThread ; i++){
  				pthread_join(tid[i],NULL);
    		}
			free(tid);
		}
    	exit(1);
    }
}

void* psuedo_inverse(void* parameters){

	Params params =*(Params*)parameters; 
	//FILE* file;


	double **aT , **b , **res;
	double **inverse , **first , **sec;
	Matrix sizeT , inverseS , sizeB , firstS , secS , xS;
	int i = 0;

	aT = (double**)malloc(sizeof(double*)*params.size.col);
	sec = (double**)malloc(sizeof(double*)*params.size.col);

	for(int i = 0 ; i < params.size.col ; i++){
		aT[i] = (double*)malloc(sizeof(double) * params.size.row);
		sec[i] = (double*)malloc(sizeof(double) * params.size.row);
	}
	
	inverse = (double**)malloc(sizeof(double*)*params.size.col);
	first = (double**)malloc(sizeof(double*)*params.size.col);
	for(int i = 0 ; i < params.size.col ; i++){
		inverse[i] = (double*)malloc(sizeof(double) * params.size.col);
		first[i] = (double*)malloc(sizeof(double) * params.size.col);
	}

	b = (double**)malloc(sizeof(double*)*params.size.row);
	for(int i = 0 ; i < params.size.row ; i++)
		b[i] = (double*)malloc(sizeof(double));

	res = (double**)malloc(sizeof(double*)*params.size.col);
	for(int i = 0 ; i < params.size.col ; i++)
		res[i] = (double*)malloc(sizeof(double));

	sizeT = Tranpose(params.data->A , aT , params.size);


	firstS = matrixMultip(aT , params.data->A  , first ,sizeT, params.size );

	findinverse(first , inverse , firstS);

	secS = matrixMultip(inverse , aT , sec , firstS , sizeT);

	for (i = 0; i < params.size.row ; ++i){
		b[i][0] = params.data->b[i];
	}
	sizeB.row = params.size.row;
	sizeB.col = 1;

	//print_matrix2(b , sizeB);

	xS = matrixMultip(sec , b , res , secS , sizeB);

	for(i = 0 ; i < params.size.col ; i++)
		params.result[i] = res[i][0];

	/*free memory*/
	for(i = 0; i < params.size.col ; i++)
		free(aT[i]);
	free(aT);

	for(i = 0; i < params.size.col ; i++)
		free(sec[i]);
	free(sec);

	for(i = 0; i < params.size.row ; i++)
		free(b[i]);
	free(b);

	for(i = 0; i < params.size.col ; i++)
		free(inverse[i]);
	free(inverse);

	for(i = 0; i < params.size.col ; i++)
		free(first[i]);
	free(first);

	for(i = 0; i < params.size.col ; i++)
		free(res[i]);
	free(res);


}

void writeToLog(double** A , double* b , double** x, Matrix size,double e ){

	char currentPath[PATH_MAX];
	FILE* serverLog;

	int i = 0 , j = 0;

	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		kill(pid , SIGUSR1);
	}


	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , "logs/server/");
	strcat(currentPath ,"server");

	sprintf(currentPath , "%s%ld.log" , currentPath  , pthread_self());

	serverLog = fopen(currentPath , "w");

	fprintf(serverLog , "A = [");

	for(i = 0 ; i < size.row ; i++){
		for( j = 0; j < size.col ; j++){
			fprintf(serverLog, "%.2f ",A[i][j]);
		}
		if(i != size.row - 1 )
			fprintf(serverLog, " ; ");
	}
	

	fprintf(serverLog ,"]\nb = [");


	for(i = 0; i < size.row ; i++){
		fprintf(serverLog, "%.2f ",b[i]);
	}
	fprintf(serverLog ,"]\nx = [");

	for(i = 0; i < size.col ; i++){
		fprintf(serverLog, "%.2f ",x[i][0]);
	}
	fprintf(serverLog ,"]\n|e|= %.2f" , e);

	fclose(serverLog);

}
