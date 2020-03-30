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
#include <sys/time.h>
#include <math.h>
#define MILLION 1000000L




#ifndef PATH_MAX
#define PATH_MAX 256
#endif


typedef struct{
	int row;
	int col;
}Matrix;

void* connectionWithThread(void* requirements);
void do_client_staff(int socket , Matrix matrix);
void signalhandling(int sigNum);
void writeToLog(double** A , double* b , Matrix size);
void writeToMainLog(double nanoTime , int tisSize , pid_t pid , double* timeT);



Matrix arr;
int  portNum;
sem_t sem;
pid_t pid;
int signalNumber = 999;
int clientsNum = 0;
pthread_t* tid;
double* timeT;
double **A , *b ;
int controlFree = 0;
int count = 0;
long timedif;


int main(int argc , char** args){

	int i = 0;
	/*To calculate the time of the matrix is generated*/
	long timedif2;
	struct timeval end;
	struct timeval start;
	long value;
	void* status = 0;

	portNum = 0;
  	arr.row = 0;
  	arr.col = 0;

	if(argc != 5){
		fprintf(stdout, "Usage : %s <#of columns of A, m> <#of rows of A, p> <#of clients, q> <port # , id>\n", args[0]);
		kill(pid , SIGUSR1);
		exit(1);
	}

	signal(SIGINT ,&signalhandling);
	signal(SIGUSR1 ,&signalhandling);

	pid = getpid();
	arr.col = atoi(args[1]);
	arr.row = atoi(args[2]);
	clientsNum = atoi(args[3]);
	portNum = atoi(args[4]);

	/*For thread id*/
	tid = (pthread_t*)malloc(sizeof(pthread_t) * clientsNum);
	/*time*/
	timeT = (double*)malloc(sizeof(double)*clientsNum);

	/*calculating time*/
    if (gettimeofday(&start, NULL)) {
		fprintf(stderr, "Failed to get start time\n");
		kill(pid , SIGUSR1);
	}
	sem_init(&sem, 0 , 1);
  	for(i = 0; i < clientsNum ; i++){
		pthread_create(&tid[i] , 0 , connectionWithThread , &i);
	}

	for (i = 0; i < clientsNum; ++i){
		pthread_join(tid[i] , &status);
		value = (long)status;
		timeT[i] = value;	
	}

	if (gettimeofday(&end, NULL)) {
		fprintf(stderr, "Failed to get end time\n");
		kill(pid , SIGUSR1);
	}

	timedif2 = MILLION*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	writeToMainLog((double)timedif2 / 1000.0 , clientsNum  , getpid() , timeT);


	sem_destroy(&sem);
	free(tid);
	free(timeT);
	clientsNum = 0;
	return 0;	
}

void* connectionWithThread(void* requirements){
	sem_wait(&sem);
	struct sockaddr_in soc_address;
  	int socketfd = 0 , i = 0 ;


  	/*To calculate the time of the matrix is generated*/
	struct timeval end;
	struct timeval start;

	/*calculating time*/
    if (gettimeofday(&start, NULL)) {
		fprintf(stderr, "Failed to get start time\n");
		kill(pid , SIGUSR1);
	}

	A = (double**)malloc(arr.row * sizeof(double*));
	for(; i < arr.row ; i++)
		A[i] = (double*)malloc(arr.col * sizeof(double)); 

	b = (double*)malloc(arr.row * sizeof(double));
	
	//x = (double*)malloc(arr.col * sizeof(double));
	
	socketfd = socket(AF_INET , SOCK_STREAM , 0);
	
	memset(&soc_address, '0', sizeof(soc_address));

	soc_address.sin_family = AF_INET;    
  	soc_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  	soc_address.sin_port = htons(portNum);

	if(connect(socketfd, (struct sockaddr *)&soc_address, sizeof(soc_address))<0){
      printf("Error on connecting server\n");
      kill(pid , SIGUSR1);
      exit(1);
    }
    write(socketfd , &arr , sizeof(arr) );    
    do_client_staff(socketfd , arr);

    close(socketfd);

    if (gettimeofday(&end, NULL)) {
		fprintf(stderr, "Failed to get end time\n");
		kill(pid , SIGUSR1);
	}

	timedif = MILLION*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	timedif = timedif / 1000.0;

	sem_post(&sem); 
	return (long*)timedif;
}

void do_client_staff(int socket , Matrix matrix){
	
	double value = 0.0;
	int i = 0 , j = 0, count = 0;
	double normE;
	i = 0;
	j = 0;
    
	while(count < matrix.row * matrix.col){
		read(socket, &value, sizeof(double));
		A[i][j] = value;
		j++;
		if(j % matrix.col == 0){
			i++;
			j = 0;
		}
		count++;
	}

	for(i = 0 ; i < matrix.row ; i++){
		read(socket , &value, sizeof(double));
		b[i] = value;
	}

	/*for(i = 0 ; i < matrix.col ; i++){
		read(socket , &value, sizeof(double));
		x[i] = value;
	}
	
	while(read(socket , &normE , sizeof(double)) > 0)
		printf("%f\n",normE );*/

	writeToLog(A ,b , matrix);

	for(i = 0; i < matrix.row ; i++)
		free(A[i]);
	free(A);
	free(b);
	controlFree = 1;
}

void signalhandling(int sigNum){
	signalNumber = sigNum;
	int i =0;
	if(signalNumber == SIGINT){
    	fprintf(stdout, "SIGINT is caught!\n");
    	if(clientsNum != 0){
			free(tid);
			free(timeT);

    	}
    	if(controlFree == 0){
    		for(i = 0; i < arr.row ; i++)
				free(A[i]);
			free(A);
			free(b);
			//free(x);
    	}	
    	exit(1);
    }
    else if(signalNumber == SIGUSR1){
    	fprintf(stdout, "Error with error exit -1!\n");

    	if(clientsNum != 0){
			free(tid);
			free(timeT);

		}
		if(controlFree == 0){
    		for(i = 0; i < arr.row ; i++)
				free(A[i]);
			free(A);
			free(b);
			//free(x);
    	}
    	exit(1);
    }
}


void writeToLog(double** A , double* b , Matrix size){
	char currentPath[PATH_MAX];
	FILE* clientLog;

	int i = 0 , j = 0;

	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		kill(pid , SIGUSR1);
	}


	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , "logs/clients/client/");
	strcat(currentPath ,"client");

	sprintf(currentPath , "%s%d%ld.log" , currentPath , count++ , pthread_self());

	clientLog = fopen(currentPath , "w");

	fprintf(clientLog , "A = [");
	fflush(clientLog);
	

	for(i = 0 ; i < size.row ; i++){
		for( j = 0; j < size.col ; j++){
			fprintf(clientLog, "%.2f ",A[i][j]);
			fflush(clientLog);

		}
		if(i != size.row - 1 )
			fprintf(clientLog, " ; ");
		fflush(clientLog);

	}
	

	fprintf(clientLog ,"]\nb = [");
	fflush(clientLog);



	for(i = 0; i < size.row ; i++){
		fprintf(clientLog, "%.2f ",b[i]);
		fflush(clientLog);

	}
	fprintf(clientLog ,"]\n");
	fflush(clientLog);

	fclose(clientLog);

}
void writeToMainLog(double nanoTime , int tisSize , pid_t pid, double* timeT){
	
	FILE* clientLog;
	char currentPath[PATH_MAX];
	int i = 0;
	double mean = 0.0;
	double statndartDev = 0.0;
	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		kill(pid , SIGUSR1);
	}

	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , "logs/clients/");
	strcat(currentPath ,"clients");

	sprintf(currentPath , "%s%d.log" , currentPath , pid);


	clientLog = fopen(currentPath , "w");

	mean = nanoTime / tisSize;

	for(i = 0 ; i < tisSize ; i++){
		statndartDev += (pow(timeT[i] - mean , 2)); 
	}

	statndartDev = sqrt(statndartDev / (tisSize-1) );

	fprintf(clientLog , "Mean = %f \n" , mean);
	fflush(clientLog);
	fprintf(clientLog , "Standart Deviation = %f \n" , statndartDev);
	fflush(clientLog);

	fclose(clientLog);

}