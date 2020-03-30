#include "requirements.h"

int wordCounts = 0;
sem_t sem;
int signalNumber = 999;
int shmid;
int mqId;
key_t mqKey = 9595;
int result = 0;


int main(int argc , char* argv[]){
	
	char message[50];
	/*For holding current working directory.*/
	char currentPath[PATH_MAX];
	/*File pointers.*/
	FILE* output;
	/*For parent pid*/
	pid_t pid = getpid();
	/*for file counter*/
	int i = 0 , flag = 1;
	/*To calculate the time of the matrix is generated*/

	long timedif;
	struct timeval end;
	struct timeval start;
	/*To find max cascade threads*/
	int max = 0;
	/*for shared memory key to create shm*/
	key_t shmkey = 959595;


	/*calculating time*/
    if (gettimeofday(&start, NULL)) {
		fprintf(stderr, "Failed to get start time\n");
		kill(pid , SIGUSR1);
	}

	signal(SIGINT ,&signalhandling);
	signal(SIGUSR1 ,&signalhandling);
	signal(SIGUSR2 ,&signalhandling);
	signal(SIGABRT ,&signalhandling);

	/*if file exist than remove the file.*/
	remove("log.txt");
	remove(DIRFILE);
	remove(FILEFILE);
	remove(LINEFILE);

	/*Controlling command line parameters*/
	if(argc != 3){
		fprintf(stderr, "Usage : %s targetString <dirName>  \n",argv[0]);
		kill(pid , SIGUSR1);
		flag = 0;
	}

	/*Creating message queue*/
	if ((mqId = msgget(mqKey, PERMS | IPC_CREAT)) == -1){
		fprintf(stderr,"Failed to create message queue!\n");
		kill(pid , SIGUSR1);
		flag = 0;
	}

	/*Getting the path of the current working directory. If failed then error message sended.*/
	if (getcwd(currentPath, PATH_MAX) == NULL) {
		perror("To get current working directory is faild!");
		kill(pid , SIGUSR1);
		flag = 0;
	}

	if(flag){
		/*Adding the the directory name to currentPath*/
		strcat(currentPath , "/");
		strcat(currentPath , argv[2]);

		if((i = numberOfFiles(currentPath , &max)) < 0)
			kill(pid , SIGUSR1);

		//tid = (pthread_t*)malloc(i * sizeof(pthread_t));

		/*Calling the function that reads the directory.*/
		readDir(argv[1] , currentPath ,pid ,shmkey);

		/*Here , parent reads the fields[0] , then making sum of them then 
		write the total occurence on the .log file.*/
		while(wait(NULL) > 0);
		if(pid == getpid()){

			
			writeToConsole(writeToFile(output , argv[1]),max);
		}
		else exit(0);
	}

	if (gettimeofday(&end, NULL)) {
		fprintf(stderr, "Failed to get end time\n");
		kill(pid , SIGUSR1);
	}

	/*Signal handling*/
    if(signalNumber == SIGINT){
    	strcpy(message , "SIGINT is caught!");
		fprintf(stdout, "Exit condtion : %s\n" , message);

    }
    else if(signalNumber == SIGUSR1){
    	strcpy(message , "Error with error exit -1!");
		fprintf(stdout, "Exit condtion : %s\n" , message);

    }
    else if(signalNumber == SIGUSR2){
    	strcpy(message , "SIGUSR2 is caught!");
		fprintf(stdout, "Exit condtion : %s\n" , message);
    }
    else if(signalNumber == SIGABRT){
    	strcpy(message , "SIGABRT is caught!");
		fprintf(stdout, "Exit condtion : %s\n" , message);
    }
    else if(signalNumber == 999){
    	strcpy(message , "Normal!");
    	fprintf(stdout, "Exit condtion : %s\n" , message);
    }

	timedif = MILLION*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

	fprintf(stdout ,"Total run time : %ld miliseconds.\n",timedif);

	msgctl(mqId, IPC_RMID, NULL);


	return 0;
}
