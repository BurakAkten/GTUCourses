#include "requirements.h"

int tidCount = 0;
long long int wordCounts = 0;
sem_t sem;
int signalNumber = 999;

int main(int argc , char* argv[]){
	
	char message[50];
	/*It holds the total occurences of the word.*/
	int total = 0 ;
	/*For holding current working directory.*/
	char currentPath[PATH_MAX];
	/*File pointers.*/
	FILE* output;
	/*For parent pid*/
	pid_t pid = getpid();
	/*for file counter*/
	int i = 0;
	/*For thread id*/
	pthread_t *tid;
	/*To calculate the time of the matrix is generated*/
	long timedif;
	struct timeval end;
	struct timeval start;
	/*To find max cascade threads*/
	int max = 0;

	/*calculating time*/
    if (gettimeofday(&start, NULL)) {
		fprintf(stderr, "Failed to get start time\n");
		kill(pid , SIGUSR1);
	}

	signal(SIGINT ,&signalhandling);
	signal(SIGUSR1 ,&signalhandling);
	signal(SIGUSR2 ,&signalhandling);


	/*if file exist than remove the file.*/
	remove("log.txt");
	remove(DIRFILE);
	remove(FILEFILE);
	remove(LINEFILE);

	/*Controlling command line parameters*/
	if(argc != 3){
		fprintf(stderr, "Usage : %s <dirName> targetString \n",argv[0]);
		kill(pid , SIGUSR1);
	}

	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		kill(pid , SIGUSR1);
	}

	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , argv[2]);

	if((i = numberOfFiles(currentPath , &max)) < 0)
		kill(pid , SIGUSR1);

	tid = (pthread_t*)malloc(i * sizeof(pthread_t));


	/*Calling the function that reads the directory.*/
	readDir(argv[1] , currentPath , tid , 0 ,pid);

	/*Here , parent reads the fields[0] , then making sum of them then 
	write the total occurence on the .log file.*/
	while(wait(NULL) > 0);
	if(pid == getpid()){
		total = writeToFile(output , argv[1]);
		writeToConsole(total , max);
	}
	else exit(0);
	free(tid);
	if (gettimeofday(&end, NULL)) {
		fprintf(stderr, "Failed to get end time\n");
		kill(pid , SIGUSR1);
	}

	/*Signal handling*/
    if(signalNumber == SIGINT)
    	strcpy(message , "SIGINT is caught!");
    else if(signalNumber == SIGUSR1)
    	strcpy(message , "Error with error exit -1!");
    else if(signalNumber == SIGUSR2)
    	strcpy(message , "SIGUSR2 is caught!");
    else if(signalNumber == 999)
    	strcpy(message , "Normal!");

	timedif = MILLION*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

	fprintf(stdout ,"Total run time : %ld miliseconds.\n",timedif);
	fprintf(stdout, "Exit condtion : %s\n" , message);

	return 0;
}
