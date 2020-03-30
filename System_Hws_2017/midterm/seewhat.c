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

#define FIFO_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SERVERPIDFILE "pid"
#define SEEWHATLOG "seeWhat.log"
#define TEMPFILE1 "temp1"
#define TEMPFILE2 "temp2"
#define TEMPFILE3 "temp3"


/*if PATH_MAX is not defined then it is defined to size of the current working directory.*/
#ifndef PATH_MAX
#define PATH_MAX 256
#endif


void print(double **matrix , int size);
/*
*This function fill the matrix by reading fifo.
*/
void fillTheMatrix(double** matrix , int size , int fifofd);
/*
*This function read the matrix size and server pid from temp file. 
*/
void readSizeAndServerPid(FILE* tempServer , int* serverPid , int* size );
/*
*This func. for signal handlig.
*/
void signalhandling(int sigNum);
/*
*This function calculate the determinant of a matrix
*it is referenced a little from 
*http://bilgisayarkavramlari.sadievrenseker.com/2012/05/01/matrisin-determinanti-matrix-determinant/ 
*/
double determinantOfMat(double **matrix , int size);
/*
*This function writing the message to the log file when ctrl+c is caught.
*/
void writeToLogMessage(char* message);
/*
*This function find the inverse of a matrix.
*it is referenced a little from 
*http://bilgisayarkavramlari.sadievrenseker.com/2012/05/01/matrisin-determinanti-matrix-determinant/
*/
void findinverse(double** matrix , double** inverse , int size);
/*Find the shifted inverse matrix det.*/
double shiftedInverse(double** matrix ,int size);
/*Write the matrix the temp file.*/
void writetotemp(char* name , double** matrix , int size);
/*This function write to the log file 3 matrices as matlab format.*/
void writeToLog(int count , int size);
/*This function calculate the convolution matrix
*it is referenced a little from  http://songho.ca/dsp/convolution/convolution.html
*/
double convolution(double** matrix , int size);


/*global signal number*/
int sig ;


int main(int argc, char const *argv[]){	
	/*for temp file.*/
	FILE* tempFile;
	/*For fifos*/
	int mainfifo , fifofd;
	/*for pids*/
	pid_t  pid ,serverPid;
	/*holdinf the matrix that is read from fifo.*/
	double **matrix;
	/*client fifo name*/
	char clientName[50];
	/*matrix size*/
	int size;
	/*counter*/
	int i , count = 0;
	int flag = 1;
	/*child pid*/
	pid_t child1 , child2;
	/*result1*/
	double result1 ;


	/*Controlling for command line arguments. İf this format is wrong then error message
     *is printed out.
     */
    if(argc != 2){
       	fprintf(stderr, "Usage: %s <mainpipename>\n", argv[0]);
		return -1;
    }
	/******************************************************************************/
	remove(TEMPFILE1);
	remove(TEMPFILE2);
	remove(TEMPFILE3);
	/******************************************************************************/

    /*getting client pid and creating client fifo name.*/
    pid  = getpid();
    sprintf(clientName , "fifo%ld" ,(long) pid);

    /*creating fifo for client and then opening this fifo*/
	if(mkfifo(clientName  , FIFO_PERMS) < 0){	
		perror("Error on making fifo!!");
		return -1;
	}
	/******************************************************************************/

	/*Temp file is opening for reading the matrix size and server pid*/
	if((tempFile = fopen(SERVERPIDFILE , "r"))==NULL){
		fprintf(stderr,"Error on opening file!\n");
		exit(1);
	}
	readSizeAndServerPid(tempFile , &serverPid , &size);
	fclose(tempFile);
	/******************************************************************************/

	/*Takeing place from memory */
	matrix= (double**)malloc(sizeof(double*) * size);
	for (i = 0; i < size; ++i)
	 	matrix[i] = (double*)malloc(sizeof(double) * size);
	
	
	signal(SIGINT , signalhandling);
	
	while(flag){

		/******************************************************************************/	
		/*opening the main fifo with write mode*/
		while((mainfifo = open(argv[1] , O_RDWR)) < 0);

		/*this client pid is written to the client server fifo*/
		if(write(mainfifo, &pid, sizeof(pid_t)) < 0){
			perror("Error:");
			exit(EXIT_FAILURE);
		}
		/******************************************************************************/
		kill(serverPid , SIGUSR2);
		fprintf(stdout, "%s\n","Signal is sended!" );
		sleep(1);
		/******************************************************************************/
		while((fifofd = open(clientName , O_RDWR)) < 0);

	    /******************************************************************************/
	    /*filling the matrix by reading from client fifo.*/
		fillTheMatrix(matrix , size , fifofd );
		writetotemp(TEMPFILE1 , matrix , size);
		child1 = fork();

		if(child1 == 0){
			result1 = shiftedInverse(matrix , size);
			
			writetotemp(TEMPFILE2 , matrix ,size);
			exit(0);
			/*write to the log*/
		}
		else if(child1 > 0){
			/*create second child*/
			child2 = fork();
			if(child2 == 0){
				result1 = convolution(matrix , size);
				writetotemp(TEMPFILE3 , matrix , size);
				exit(0);
			}
		}

	    /******************************************************************************/

		if(sig == SIGINT){
			fprintf(stdout, "%s\n","The signal Ctrl+C is caught!\n" );
			kill(serverPid , SIGINT);
			flag = 0 ;
		}
		while(wait(NULL) > 0);
		writeToLog(count , size);

		count++;
	}

	/*Unlike the fifo*/
	if(unlink(clientName) < 0){
		perror("Error on unlinking !!");
		return -1;
	}
	close(fifofd);
	remove(TEMPFILE1);
	remove(TEMPFILE2);
	remove(TEMPFILE3);

	/*free the memory*/
	for (i = 0; i < size; ++i)
	    free(matrix[i]);
	free(matrix);
	fprintf(stdout,"end of client\n");

	return 0;
} 

void readSizeAndServerPid(FILE* tempServer , pid_t* serverPid , int* size ){
	int pid ;
	int matrixSize;
	/*size and server pid reading from temp file */
	fscanf(tempServer , "%d" , &pid );
	fscanf(tempServer , "%d" , &matrixSize );
	
	*serverPid = (pid_t)pid;
	*size = matrixSize;
}

void fillTheMatrix(double** matrix , int size , int fifofd){

	double value;
	int i , j ;

	/*reading matrix from fifo*/
	for(i = 0 ; i < size ; i++){
		for (j = 0; j < size; ++j){
			read(fifofd , &value , sizeof(double));
			matrix[i][j] = value;
		}
	}
	//print(matrix , size);
}

void print(double **matrix , int size){
	/*int size = sizeof(matrix) / sizeof(double);*/
	int i , j ;

	for(i = 0; i < size ; i++){
		for(j = 0 ; j < size ; j++)
			printf("%.2f ",matrix[i][j]);
		printf("\n");
	}
	printf("/************************************/\n");
}

void signalhandling(int sigNum){
	sleep(1);
	sig = sigNum;
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
void findinverse(double** matrix , double** inverse , int size){

	int i , j , k ;
	double x , y;

	/*Creating I matrix*/
	for(i = 0 ; i < size ; i++){
		for(j = 0 ; j < size ; j++){
			if(i != j)
				inverse[i][j] = 0;
			else
				inverse[i][j] = 1;
		}
	}
	
	/*Start to make matrix I then we have inverse matrix*/
	for (i = 0; i < size; ++i){
		x = matrix[i][i];
		for (j = 0; j < size; ++j){
			matrix[i][j] = matrix[i][j] / x;
			inverse[i][j] = inverse[i][j] / x;
		}

		for(k = 0 ; k < size ; k++){
			if(k != i ){
				y = matrix[k][i];
				for(j = 0 ; j < size ; j++){
					matrix[k][j] = matrix[k][j] - (matrix[i][j] * y);
					inverse[k][j] = inverse[k][j] - (inverse[i][j] * y);
				}
			}
		}
	}
}

double shiftedInverse(double** matrix ,int size){

	/*for loop control*/
	int i , j ;
	/*temp matrix*/
	double **tempMat  , **inverse ;
	/*result*/
	double result = determinantOfMat(matrix , size);

	/*taking place from memory for temporary matrix*/
	tempMat = (double**)malloc(sizeof(double*) * (size / 2));
	inverse= (double**)malloc(sizeof(double*) * (size / 2));
    for (i = 0; i < size / 2; ++i){
    	tempMat[i] = (double*)malloc(sizeof(double) * (size / 2));
    	inverse[i] = (double*)malloc(sizeof(double) * (size / 2));

    }
	
	/******************************************************************************/

    /*First part is changeing here with the inverse of first nxn matrix in the general matrix*/
    for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			tempMat[i][j] = matrix[i][j] ;

	findinverse(tempMat , inverse , size / 2);

	for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			matrix[i][j] = inverse[i][j] ;

	/******************************************************************************/
	/*Second part is changeing here with the inverse of Second nxn matrix in the general matrix*/
	for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			 tempMat[i][j] = matrix[i][j + (size / 2)] ;

	findinverse(tempMat , inverse , size / 2);


	for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			matrix[i][j + (size / 2)]  = inverse[i][j] ;

	/******************************************************************************/
	/*Third part is changeing here with the inverse of Third nxn matrix in the general matrix*/
	for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			 tempMat[i][j] = matrix[i + (size / 2)][j] ;

	findinverse(tempMat , inverse , size / 2);


	for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			matrix[i + (size / 2)][j]  = inverse[i][j] ;

	/******************************************************************************/
	/*Fouth part is changeing here with the inverse of Fouth nxn matrix in the general matrix*/
	for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			 tempMat[i][j] = matrix[i + (size / 2)][j + (size / 2)] ;

	findinverse(tempMat , inverse , size / 2);


	for(i = 0; i < size / 2 ; i++)
		for(j = 0 ; j < size / 2 ; j++)
			matrix[i + (size / 2)][j + (size / 2)]  = inverse[i][j] ;


	/******************************************************************************/


	result -= determinantOfMat(matrix , size);


    /*free the memory*/
    for (i = 0; i < size / 2; ++i){
    	free(tempMat[i]);
    	free(inverse[i]);
    }
    free(tempMat);
    free(inverse);

    return result;
}


void writetotemp(char* name , double** matrix , int size){

	FILE* temp;
	int i , j;
	
	temp = fopen(name , "w");

	for(i = 0; i < size ; i++){
		for(j = 0 ; j < size ; j++)
			fprintf(temp,"%.2f ",matrix[i][j]);
	}

	fclose(temp);
}


void writeToLog(int count , int size){
	FILE* clientLog;
	FILE* temp1;
	FILE* temp2;
	FILE* temp3;
	char currentPath[PATH_MAX];
	int i ,j ; 
	double value;
	
	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		exit(0);
	}

	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , "logs/");
	strcat(currentPath ,"seeWhat");
	sprintf(currentPath , "%s%d%ld.log" , currentPath , count , (long)getpid());


	clientLog = fopen(currentPath , "w");

	/*for the original matrix*/
	fprintf(clientLog , "Original = [");

	temp1 = fopen(TEMPFILE1 , "r");
	for(i = 0 ; i < size*size ; i++){

		fscanf(temp1 , "%lf" , &value);
		fprintf(clientLog, "%.2f ",value );
		if(i == size - 1)
			fprintf(clientLog, ";");
	}
	fclose(temp1);
	fprintf(clientLog , "]\nShifted One = [");

	/*for the shifted matrix*/
	temp2 = fopen(TEMPFILE2 , "r");
	for(i = 0 ; i < size*size ; i++){
		
		fscanf(temp2 , "%lf" , &value);
		fprintf(clientLog, "%.2f ",value );
		if(i == size - 1)
			fprintf(clientLog, ";");
	}
	fclose(temp2);
	fprintf(clientLog , "]\nConvolution One = [");

	/*for the convolution matrix*/
	temp3 = fopen(TEMPFILE3 , "r");
	for(i = 0 ; i < size*size ; i++){
		
		fscanf(temp3 , "%lf" , &value);
		fprintf(clientLog, "%.2f ",value );
		if(i == size - 1)
			fprintf(clientLog, ";");
	}
	fclose(temp3);
	fprintf(clientLog , "]\n");

	fclose(clientLog);
}

double convolution(double** matrix , int size){

	/*counters*/
	int i,j,m,n,mm,nn;
	/*center*/
	int kerX = 3/2 , kerY = 3/2;
	/*row and cols*/
	int row , col;
	/*kernel matrix*/
	int kernel[3][3];
	/*output matrix*/
	double **out;
	/*result*/
	double result;

	/*Taking place from memory */
    out= (double**)malloc(sizeof(double*) * size);
    for (i = 0; i < size; ++i)
    	out[i] = (double*)malloc(sizeof(double) * size);

	/*creating 3x3 kernel matrix*/
	for(i = 0 ; i < 3 ; i++){
		for(j = 0; j < 3 ; j++){
			if(i == 1 && j == 1)
				kernel[i][j] = 1;
			else
				kernel[i][j] = 0;
		}
	}

	/*Convolution part*/
	for(i = 0 ; i < size ; i++){
		for(j = 0 ; j < size ; j++){
			for(m = 0 ; m < 3 ; m++){
				mm = 3 - 1 - m ;
				for(n = 0; n < 3 ; n++){
					nn = 3 - 1 - n;

					row = i + m - kerY;
					col = j + n - kerX;


					if(row >= 0 && row < size && col >= 0 && col < size)
						out[i][j] += matrix[row][col]*kernel[mm][nn]; 
				}
			}
		}
	}

	result = determinantOfMat(matrix , size) - determinantOfMat(out , size);

	for(i = 0; i < size ; i++){
		for(j = 0 ; j < size ; j++)
			matrix[i][j] = out[i][j];
		
	}
	/*free the memory*/
    for (i = 0; i < size; ++i)
    	free(out[i]);
    free(out);
    return result;
}