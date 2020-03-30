#include "requirements.h"

void readDir(char* targetString , char* directoryPath , pid_t parent , key_t key){
	
	/*These variable for calculation of total occurence of the string.*/
	void* status = 0  ;
	DIR* directory ;
	struct dirent* direntp;
	/*for pid number*/
    unsigned int child = 1;
    /*for innerdirectory.*/
    char innerDir[PATH_MAX];
	/*parameters*/
	parameters params;
	int j = 0 , tIndex = -1 , size = 0;
	int tempFile;	
	/*For thread id*/
	pthread_t *tid;
	int total1;

    /*Opening the directory.*/
	if((directory = opendir(directoryPath)) == NULL){
		kill(parent , SIGUSR1);
		return;
	}

	/*Shared memory is created for writing the total into.*/
	shmid = shmget(key,sizeof(int),IPC_CREAT | 0600);


	/*Taking place from memory for the thread ids*/
	size = justFilesInDir(directoryPath);
	tid = (pthread_t*)malloc(size * sizeof(pthread_t));

	
	/*reading the directory.*/
	direntp = readdir(directory);
	if(direntp == NULL) {
		kill(parent , SIGUSR1);
		return;
	}	
	updateThefile(DIRFILE);
	sem_init(&sem , 0 ,1);


	/*Then it makes attachable*/
	int* shmData = shmat(shmid , NULL , 0);
	if(shmData == (int*)-1){
		kill(parent , SIGUSR1);
		return;
	} 
	*shmData = 0;

	/*this loop is working just for parent process till direntp become NULL.*/
	do{
		
		/*İnner directory is modified*/
		strcpy(innerDir , directoryPath);
		strcat(innerDir , "/");
		strcat(innerDir , direntp->d_name );

		/*In this part , everything in the directory is read by one by. For every file new process
		is created.*/
		if(strcmp(direntp->d_name ,  ".") != 0 && strcmp(direntp->d_name ,  "..") != 0 ){
			
			if(direntp->d_type==DT_REG && direntp->d_name[strlen(direntp->d_name) - 1] != '~' ){	
				
				updateThefile(FILEFILE);
				sem_wait(&sem);
 				strcpy(params.directName , "");
				strcpy(params.innerDirect, "");
				strcpy(params.target , "");

				strcpy(params.directName , direntp->d_name);
				strcpy(params.innerDirect, innerDir);
				strcpy(params.target , targetString);

				tIndex++;
				
				pthread_create(&tid[tIndex] , 0 , readCharbyChar , &params);

			}
			else if (direntp->d_type==DT_DIR){
				
				child = fork();
				/*child reading inner folder recursivly. */
				if(child == 0){
					readDir(targetString , innerDir  , parent ,(++key + 1));
					exit(0);
				}else
					key++;
			}
		}

	}while((direntp = readdir(directory)) != NULL && child > 0);	
	while(wait(NULL) > 0);

	for(j = 0 ; tIndex != -1 && j < size; j++){
		pthread_join(tid[j] , NULL);
	}
	if(*shmData != 0){	
		msgsnd(mqId,shmData, sizeof(int),0);	
	}

	shmctl(shmid , IPC_RMID , NULL);

	
	/*Closing the directory*/
	while ((closedir(directory) == -1) && (errno == EINTR));
	sem_destroy(&sem);
	free(tid);

}

int writeToFile(FILE* output , char* target){
	
	/*opening output file to writing total.*/
	int res = readTot();
	
	output = fopen("log.txt" , "a+");

	/*Writing total occcurence*/
	fprintf(output, "%d , %s were found in total!\n", res ,target);

	/*closing files.*/
	fclose(output);
	return res;
}
void* readCharbyChar(void* args){
	char buffer[1024];
	wordCounts = 0;
    /*The character that is read from file.*/
    char character;
    /*For controlling the reading*/
    int col = 1,     currentRow = 1 , foundByte = 0 ,newline = 0 ;
    /*for controlling loops*/
    int flag = 1, flag2 = 1 ;
    int *error ;
    /*counter*/
    int i = 1;
    /*The place that target is found.*/
    foundPlace found;
    /*File pointer for reading and writing*/
    FILE* input;
    FILE* output;
    /*the size of target string*/
    parameters *params = (parameters*)args;

    int targetSize = strlen(params->target);

    /*Opening the file that is in the path.*/
    char* dir = params->innerDirect;

    if((input= fopen(dir , "r")) == NULL){
    	*error = -1;
    	return (int*)error;
    }

    while(fgets(buffer , 1024 , input) != '\0')
    	updateThefile(LINEFILE);

    fseek(input , 0 , SEEK_SET);

	/*This file for writing the occurence places.*/    
    output = fopen("log.txt" , "a+");
    /*This loop read byte by byte the file till end of file. */
    for(character=fgetc(input); character != EOF && flag2 ;character=fgetc(input),col++){     
        /*control that the first character and the character that is read are same 
         *if they are then keep going to read.
         */
        if(character == params->target[0]){   
            /*initilazing the found place */       
            found.col = col;
            found.row = currentRow;
            foundByte = ftell(input) - 1;
            /*initilazing the control variable.*/
            flag = 1;
            i=1;
            /*In this while loop , the file still is reading but the space and tab ignored. And
             * when newline character is read then row updated(+1)
             */
            while(params->target[i] != '\0' && flag && character != EOF){
                   
                character = fgetc(input);
                col++;

                if(character == params->target[i])
                    i++;
                else if(character == ' ' || character == '\t' || character == '\n')
                {}
                else if (character != params->target[i]){
                    flag = 0;
                }
                    
                if(i >= targetSize){
                	
                    fprintf(output,"ProcessID : %ld - ThreadID : %ld -> %s : [%d , %d] %s first character found.\n"
                    	,(long)getpid(),(long)pthread_self(),params->directName,found.row,found.col , params->target);
                    wordCounts++;
                }
            }
            /*going back to the found place from the file. and updating the column.*/
            fseek(input ,foundByte + 1, SEEK_SET);
            col = found.col ;
        }
        else if (character == '\n'){
        	newline += 1;
            col = 0;
        }
        else if (character == EOF){
            flag2 = 0;
        }

        /*row is updated.*/
        if(newline != 0){
            currentRow += newline ;
            newline = 0;
        }
    }
    fclose(input);
    fclose(output);
    
    if (wordCounts != 0){
	    /*The shared memory again is attachable*/
	    int *shmData = shmat(shmid,NULL,0);
	    /*Total is updated */
		(*shmData) += wordCounts;
		/*Detach the shared memory*/
		//shmdt(shmData);
    }

    sem_post(&sem);
    //return ((int*)wordCounts);
}
int numberOfFiles(char* directoryPath , int* max){
	DIR* directory ;
	char innerDir[PATH_MAX];
	struct dirent* direntp;
	int count = 0;
	int filecount = 0;

	/*Opening the directory.*/
	if((directory = opendir(directoryPath)) == NULL){
		return -1;
	}
	/*Calculating the number of files recursively to create thread pool.*/
	while ((direntp = readdir(directory)) != NULL){
        
        if(direntp->d_type==DT_DIR && strcmp(direntp->d_name,".") != 0 && strcmp(direntp->d_name,"..") != 0){ 

            strcpy(innerDir,directoryPath);
           	strcat(innerDir,"/");
            strcat(innerDir,direntp->d_name);

            /*if it is directory then call the same function with new path*/
            count += numberOfFiles(innerDir , max);
        }
        else if(direntp->d_type==DT_REG && direntp->d_name[strlen(direntp->d_name) - 1] != '~'){
        	/*if it is file count is decremented*/
        	count++;
        	filecount++;
        }
        if(filecount > *max)
            *max = filecount;
    }
    /*closing directory*/
    closedir(directory);
    return count;
}

int justFilesInDir(char* directoryPath){
	DIR* directory ;
	char innerDir[PATH_MAX];
	struct dirent* direntp;
	int count = 0;
	int filecount = 0;

	/*Opening the directory.*/
	if((directory = opendir(directoryPath)) == NULL){
		return -1;
	}
	/*Calculating the number of files recursively to create thread pool.*/
	while ((direntp = readdir(directory)) != NULL){
        
		if(direntp->d_type==DT_REG && direntp->d_name[strlen(direntp->d_name) - 1] != '~'){
        	/*if it is file count is decremented*/
        	count++;
        }
    }
    /*closing directory*/
    closedir(directory);
    return count;
}
void updateThefile(char* name){
	int value = 1;
	FILE* file;
	file = fopen(name , "a+");

	fprintf(file, "%d\n", value);
	fclose(file);
}
int readFile(char* name){
	int value = 0 , sum = 0;
	FILE* file;
	file = fopen(name , "a+");

	while((value =fgetc(file)) != EOF){
		if(value != '\n')
			sum+= (int)(value - '0');
	}
	fclose(file);
	return sum;
}
void writeToConsole(int tot , int max){
	int dircNum = readFile(DIRFILE) , i;
	fprintf(stdout, "Total number of string found              : %d\n",tot );
	fprintf(stdout, "Total number of directories searched      : %d\n",dircNum);
	fprintf(stdout, "Total number of files searched            : %d\n",readFile(FILEFILE));
	fprintf(stdout, "Total number of lines searched            : %d\n",readFile(LINEFILE) );
	fprintf(stdout, "Total number of cascade threads created   : %d\n", max);
	fprintf(stdout, "Total number of searchs threads created   : %d\n",readFile(FILEFILE));
	fprintf(stdout, "Max # of threads running concurrently is not calculated.\n");	
	fprintf(stdout, "Total number of Shared Memories created   : %d\n",dircNum);
	fprintf(stdout, "Created shared memories sizes =>          : " );
	for( i = 0 ; i < dircNum ; i++){
		fprintf(stdout, "%lu" ,sizeof(int));
		if(i != dircNum - 1)
			fprintf(stdout, ",");
		else
			fprintf(stdout, "\n");

	}

	remove(DIRFILE);
	remove(FILEFILE);
	remove(LINEFILE);
}
void signalhandling(int sigNum){signalNumber = sigNum;}

int readTot(){

	int asd = 0 , j = 0;
	
	int toplam = 0 , readfl =  readFile(DIRFILE);
	int* arr;

	arr = (int*)malloc(readfl * sizeof(int));
	
	static int x = 0;			
	while(msgrcv(mqId , &x , sizeof(int) , 0 ,  O_NONBLOCK ) > 0 && asd < readfl){
			arr[asd] = x;
			asd++;
	}

	while(j < asd && j < readfl){
		toplam += arr[j];
		//printf("aaa : %d\n", toplam );
		j++;
	}

	free(arr);
	//msgctl(mqId, IPC_RMID, NULL);
	return toplam;
	
}