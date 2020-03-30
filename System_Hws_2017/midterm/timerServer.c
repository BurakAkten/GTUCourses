#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#define FIFO_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define MILLION 1000000L
#define SERVERPIDFILE "pid"
#define SERVERLOG "TimeServer.log"

#ifndef _POSIX_C_SOURCE 
#define _POSIX_C_SOURCE
#endif

/*if PATH_MAX is not defined then it is defined to size of the current working directory.*/
#ifndef PATH_MAX
#define PATH_MAX 256
#endif


/*
*This function create a invertible matrix
*/
double createInvertibleMat(double **matrix , int size);
/*
*This function calculate the determinant of a matrix
*it is referenced a little from 
*http://bilgisayarkavramlari.sadievrenseker.com/2012/05/01/matrisin-determinanti-matrix-determinant/ 
*/
double determinantOfMat(double **matrix , int size);
void print(double **matrix , int size );
/*
*This func. for signal handlig.
*/
void signalhandling(int sigNum);
/*
*This funvtiom is making the main part. S.t. handling signals , creatin matrix reading from  and writing to fifo...
*/
void TimeServer(double** matrix , int size , const char* mainpipename , double msec);
/*
*This function writing the client pid det of matrix ant the time of generating the matrix to a log file.
*/
void writeToLog(double det , double time , time_t pid);
/*
*This function writing the message to the log file when ctrl+c is caught.
*/
void writeToLogMessage(char* message);


/*global signal number*/
int signalNumber;
/*control*/
int ctrl = 0;
/*clientpid*/
pid_t client = 0;

int main(int argc, char const *argv[])
{	

	FILE* tempFile;
	/*for the invertible matrix*/
	double **invertibleMatrix;
	/*The size of the matrix*/
	int size;
	/*counter and control flag*/
	int i ;
	/*To be accessed by each process*/
	int fifoFd;
	/*For mainfifo*/
	int mainfifo;
	/*server pid*/
	pid_t serverPid;
	/*for waiting*/
	double Sec;
	char currentPath[PATH_MAX];

	/*Controlling for command line arguments. İf this format is wrong then error message
     *is printed out.
     */
    if(argc != 4){  	
   		fprintf(stderr, "Usage: %s <ticks in msec> <n> <mainpipename>\n", argv[0]);
		return -1;
    }
	
	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		exit(0);
	}
	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , "logs/");
	strcat(currentPath ,SERVERLOG);

	remove(currentPath);
    remove(argv[3]);
    /******************************************************************************/

    /*main fifo is opening*/
    if(mkfifo(argv[3], FIFO_PERMS) < 0){
		perror("Error on making fifo!!");
		return -1;
	}

	serverPid = getpid();
	size = 2 * atoi(argv[2]);

    /******************************************************************************/
	/*openinn the temp file to write size and server pid*/
	if((tempFile = fopen(SERVERPIDFILE , "w+"))==NULL)
		fprintf(stderr,"Error on opening file!\n");

	fprintf(tempFile, "%ld %d",(long)serverPid , size);

	fclose(tempFile);
    /******************************************************************************/

	Sec = atof(argv[1]) / pow(10 , 3);

 	/******************************************************************************/
    /*Taking place from memory */
    invertibleMatrix= (double**)malloc(sizeof(double*) * size);
    for (i = 0; i < size; ++i)
    	invertibleMatrix[i] = (double*)malloc(sizeof(double) * size);
     /******************************************************************************/

    /*calling the timeserver function*/
	TimeServer(invertibleMatrix , size , argv[3] , Sec);    

	/******************************************************************************/
	/*free the memory*/
    for (i = 0; i < size; ++i)
    	free(invertibleMatrix[i]);
    free(invertibleMatrix);

    /*Unlike the fifo*/
	if(unlink(argv[3]) < 0){
		perror("Error on unlinking !!");
		return -1;
	}
	close(mainfifo);

	remove(SERVERPIDFILE);
	
	if(ctrl == 1){
		kill(client,SIGINT);
	}


    /******************************************************************************/
	fprintf(stdout, "%s\n","End of the server!" );

	return 0;
}

void TimeServer(double** matrix , int size ,const char* mainpipename, double sec){

	
	int flag = 1;
	int i , j ;
	/*determiant of the matrix*/
	double det;
	/*hold the the value that the fork returned.*/
	pid_t child ;

	/*clientfifo*/
	int fifoFd , mainfifo;
	/*holds pid*/
	pid_t pid;
	/*for handling the signals*/
	struct sigaction handle;
	/*for holding the name of the clientfifo*/
	char clientName[50];
	/*To calculate the time of the matrix is generated*/
	long timedif;
	struct timeval end;
	struct timeval start;

    /*setting the signalhadding function for handeling the signals.*/
	handle.sa_handler = &signalhandling;

	handle.sa_flags = 0;
	
	/*The signal set is making empty. after add adding two signals for handling*/
	sigemptyset(&handle.sa_mask);

    if (sigaction(SIGINT, &handle, NULL) == -1) 
        perror("Error on handling SIGINT"); 
    
    if (sigaction(SIGUSR2, &handle, NULL) == -1) 
        perror("Error on handling SIGUSR1"); 
    
    while(flag){

    	if(sigprocmask(SIG_BLOCK , &handle.sa_mask , NULL) == -1){
    		fprintf(stderr, "%s\n","Error on blocking signal!" );
    		return;
    	}
    	/*sleeping for signal*/
    	sleep(sec);

    	if(sigprocmask(SIG_UNBLOCK , &handle.sa_mask , NULL) == -1){
    		fprintf(stderr, "%s\n","Error on unblocking signal!" );
    		return;
    	}

		/************************************************************************/

    	if(signalNumber == SIGINT){

    		/*the signal SIGINT is caught.*/
    		writeToLogMessage("The signal Ctrl+C is caught!\n");
    		ctrl = 1;
    		flag = 0;
    	}
    	else if(SIGUSR2 == signalNumber){

    		fprintf(stdout, "%s\n","Signal was caught from client!" );

    		/*reading the pid of the client*/
			while((mainfifo = open(mainpipename , O_RDONLY)) < 0);

			/*client pid is being read from the client mainfifo */
			read(mainfifo , &client , sizeof(pid_t));

			sprintf(clientName , "fifo%ld" , (long)client);

			/*The client fifo is opening for writing the matrix*/
			while((fifoFd = open(clientName , O_WRONLY)) < 0);
    		
    		child = fork();

    		if(child < 0)
    			perror("Error on fork!");	
    		else if(child == 0){
    			srand(time(NULL));

    			/*calculating time*/
    			if (gettimeofday(&start, NULL)) {
					fprintf(stderr, "Failed to get start time\n");
					return ;
				}
    			det = createInvertibleMat(matrix,size);

    			if (gettimeofday(&end, NULL)) {
					fprintf(stderr, "Failed to get end time\n");
					return ;
				}

				timedif = MILLION*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

    			/*writing to the fifo*/
    			for(i = 0 ; i < size ; i++)
    				for(j = 0 ; j < size ; j++){
    					double value = matrix[i][j];
    					if (write(fifoFd, &value, sizeof(double)) < 0)
							exit(EXIT_FAILURE);
    				}
    			/*wiring to the log file.*/
    			writeToLog(det ,  (double)timedif/1000.0 , client);
    			
    			exit(0);
    		}
    		else if(child > 0){
    			while(wait(NULL) > 0 );
    			signalNumber = -99;
    		}
    	}
    	else{
    		fprintf(stdout,"Waiting for signal!\n ");
    		sleep(1);
    	}
    }
}

double createInvertibleMat(double **matrix , int size){
	
	/*for loop control*/
	int i , j , flag = 1;
	/*temporary matrix for creating invertible matrix*/
	double **tempMat;
	/*determiant of the matrix*/
	double det;
	/*for fill the big matrix*/
	int count = 1;

	/*taking place from memory for temporary matrix*/
	tempMat = (double**)malloc(sizeof(double*) * (size / 2));
    for (i = 0; i < size / 2; ++i){
    	tempMat[i] = (double*)malloc(sizeof(double) * (size / 2));
    }

    /*for creating random number*/
	srand(time(NULL));

	/*The general loop for creating random invertible matrix.*/
	while(flag){

		/*this loop create random matrix*/
		for(i = 0 ; i < size / 2 ; i++){
			for(j  = 0 ; j < size / 2 ; j++){

				tempMat[i][j] = rand() % 100;	
			}
		}

		/*This if control the matrix is invertible or not. if it is invertible than matrix is initialized*/
		if(determinantOfMat(tempMat , size / 2) != 0){
			if(count == 1){
				for(i = 0; i < size / 2 ; i++)
					for(j = 0 ; j < size / 2 ; j++)
						matrix[i][j] = tempMat[i][j];
				count++;
			}
			else if(count == 2){
				for(i = 0; i < size / 2 ; i++)
					for(j = 0 ; j < size / 2 ; j++)
						matrix[i][j + (size / 2)] = tempMat[i][j];
				count++;

			}
			else if(count == 3){
				for(i = 0; i < size / 2 ; i++)
					for(j = 0 ; j < size / 2 ; j++)
						matrix[i + (size / 2)][j] = tempMat[i][j];
				count++;

			}
			else if(count == 4){
				for(i = 0; i < size / 2 ; i++)
					for(j = 0 ; j < size / 2 ; j++)
						matrix[i + (size / 2)][j + (size / 2)] = tempMat[i][j];
				count++;
			}

			if(count > 4)
				flag = 0;
		}

	}
	det = determinantOfMat(matrix , size);
	/*free the memory*/
    for (i = 0; i < size / 2; ++i){
    	free(tempMat[i]);
    }
    free(tempMat);
    return det;
}

double determinantOfMat(double **matrix , int size){
	/*the result*/
	double determinant = 0.0;
	/*for the smaller matrix that is for calling the recursive matrix.*/
	double **smallMatrix;
	/*Counter.*/
	int i , j , k , l;
	/*Two base case condition*/
	if(size == 1)
		determinant += matrix[0][0];
	else if(size == 2)
		determinant += matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	else{	

		/*The ecursive part is working here.*/
		for(i = 0 ; i < size ; i++){	
			
			/*tking place from the memory for the small matrix*/
			smallMatrix = (double**)malloc(sizeof(double*) * size );
	    	for (k = 0; k < size; ++k)
	    		smallMatrix[k] = (double*)malloc(sizeof(double) * size );

	    	/*Then the matrix is making small*/
	    	for (j = 1; j < size ; ++j){
	    		for(l = 0; l < size ; l++){
	    			if(l > i)
	    				smallMatrix[j - 1][l - 1] = matrix[j][l];
	    			else
	    				smallMatrix[j - 1][l] = matrix[j][l];
	    		}
	    	}
	    	/*calculating the determinant recursivly*/
	    	determinant += matrix[0][i] * pow(-1 , i) * determinantOfMat(smallMatrix , size - 1);
		    /*free the memory*/
	    	for (i = 0; i < size; ++i)
	    		free(smallMatrix[i]);
	    	free(smallMatrix);

	    }
	}
	return determinant;
}

void print(double **matrix , int size){
	/*int size = sizeof(matrix) / sizeof(double);*/
	int i , j ;

	for(i = 0; i < size ; i++){
		for(j = 0 ; j < size ; j++)
			printf("%.2f ",matrix[i][j]);
		printf("\n");
	}
}

void signalhandling(int sigNum){

	signalNumber = sigNum;

}

void writeToLog(double det , double time , time_t pid){


	FILE* serverLog;
	char currentPath[PATH_MAX];
	
	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		exit(0);
	}

	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , "logs/");
	strcat(currentPath ,SERVERLOG);


	serverLog = fopen(currentPath , "a+");
	fprintf(serverLog, "Client Pid : %ld - Time - : %.4f - Determinant : %.2f\n",(long)pid , time,det );

	fclose(serverLog);

}

void writeToLogMessage(char* message){
	FILE* serverLog;
	char currentPath[PATH_MAX];
	
	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		exit(0);
	}

	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , "logs/");
	strcat(currentPath ,SERVERLOG);


	serverLog = fopen(currentPath , "a+");
	fprintf(serverLog, "%s",message );

	fclose(serverLog);
}