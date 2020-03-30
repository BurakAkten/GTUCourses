#include "requirements.h"

int main(int argc , char* argv[]){
	
	/*It holds the total occurences of the word.*/
	int total = 0 ;
	/*For holding current working directory.*/
	char currentPath[PATH_MAX];
	/*File pointers.*/
	FILE* output;
	/*For parent pid*/
	unsigned int pid = getpid();
	/*To be accessed by each process*/
	int fifoFd;
	/*for file counter*/
	int i = 0;

	/*Controlling command line parameters*/
	if(argc != 3){
		fprintf(stderr, "Usage : %s targetString  <dirName>\n",argv[0]);
		return -1;
	}

	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		return -1;
	}

	if(mkfifo(FIFONAME  , FIFO_PERMS) < 0){
		perror("Error on making fifo!!");
		return -1;
	}

	if((fifoFd = open(FIFONAME , O_RDWR|O_NONBLOCK)) < 0){
		perror("Error on opening fifo!!");
		exit(EXIT_FAILURE);
	}

	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , argv[2]);

	/*Calling the function that reads the directory.*/
	readDir(argv[1] , currentPath , fifoFd , i);


	/*Here , parent reads the fields[0] , then making sum of them then 
	write the total occurence on the .log file.*/
	while(wait(NULL) > 0);
	if(pid == getpid()){
		writeToFile(output , argv[1] , fifoFd);
		if(unlink(FIFONAME) < 0){
			perror("Error on unlinking !!");
			return -1;
		}
	}
	close(fifoFd);
	return 0;
}
