#include "requirements.h"
void readDir( char* targetString , char* directoryPath  , int fd , int i){

	/*These variable for calculation of total occurence of the string.*/
	int total = 0 ;
	/*For local file discriptor*/
	int localFd = 0;
	DIR* directory ;
	struct dirent* direntp;
	/*for pid number*/
    unsigned int child = 1;
    /*for innerdirectory.*/
    char innerDir[PATH_MAX];
    /*For pipe field. It is global for being reacheable for each child.*/
	int fields[2];
	/*temp variable for total*/
	int totalFromPipe = 0;
	/*for fifo file name*/
	char name[12];


    /*Opening the directory.*/
	if((directory = opendir(directoryPath)) == NULL){
		perror("Error on openning directory!");
		return;
	}

	/*reading the directory.*/
	direntp = readdir(directory);
	if(direntp == NULL) {
		return;
	}
	/*this loop is working just for parent process till direntp become NULL.*/
	do{
		/*İnner directory is modified*/
		strcpy(innerDir , directoryPath);
		strcat(innerDir , "/");
		strcat(innerDir , direntp->d_name );

		/*In this part , everything in the directory is read by one by. For every file new process
		is created.*/
		if(strcmp(direntp->d_name ,  ".") != 0 && strcmp(direntp->d_name ,  "..") != 0 ){

			if(child < 0){
				perror("Error when forking!");
			}

			if(directoryOrNot(innerDir) == 0  ){
				/*pipe is created*/
    			if(pipe(fields) == -1){
					perror("Failed to create the pipe!");
					exit(EXIT_FAILURE);
				}		

				child = fork();

				/*child staff reading files and finding the occurences.*/
				if(child == 0){

					total = readCharbyChar(direntp->d_name , innerDir , targetString);
					if(total == -1){
						return;
					}

					if(total != 0 && child == 0){
						while(wait(NULL) > 0);
						writeToPipe(fields, total);
						exit(0);	
					}					
				}

				if(child > 0){
					totalFromPipe = readFromPipe(fields);
					writeToFifo(totalFromPipe , fd);		
				}
			}
			else if (directoryOrNot(innerDir) == 1){
				
				sprintf(name , "fifo%d" , i);

				if(mkfifo(name  , FIFO_PERMS) < 0){
					perror("Error on making fifo!!");
					exit(EXIT_FAILURE);
				}

				if((localFd = open(name , O_RDWR|O_NONBLOCK)) < 0){
					perror("Error on opening fifo!!");
					exit(EXIT_FAILURE);
				}

								
				child = fork();
				/*child reading inner folder recursivly. */	
				
				if(child == 0){
					readDir(targetString , innerDir , localFd , ++i);
					readFromFdtoOtherFd(localFd , fd);
				}
				else if(child > 0){
					while(wait(NULL) > 0);
					if(unlink(name) < 0){
						perror("Error on unlinking !!");
						exit(EXIT_FAILURE);
					}
				}
			}
		}
	}while((direntp = readdir(directory)) != NULL && child > 0);	

	while(wait(NULL) > 0);
	/*Closing the directory*/
	while ((closedir(directory) == -1) && (errno == EINTR));

}
void readFromFdtoOtherFd(int first , int second){
	int temp = 0, total = 0 , readByte = -1;
	
	/*reading value from filr discriptor*/
	while((readByte = read(first , &temp , sizeof(int))) > 0)
		total += temp;

	/*If readByte lower than zero than exit.*/
	if(readByte > 0){
		perror("Error on reading pipe !");
		exit(EXIT_FAILURE);
	}

	writeToFifo(total , second);
}

int readFromPipe(int fields[2]){

	int temp = 0 , total = 0 , readByte;

	/*closing file discriptor that writes*/
	close(fields[1]);

	/*reading value from filr discriptor*/
	while((readByte = read(fields[0] , &temp , sizeof(int))) > 0)
		total += temp;

	/*If readByte lower than zero than exit.*/
	if(readByte > 0){
		perror("Error on reading pipe !");
		exit(EXIT_FAILURE);
	}
	/*closing reading*/
	close(fields[0]);
	return total;
}
void writeToPipe(int fields[2] , int total){
	
	/*closing file discriptor that reads*/
	close(fields[0]);

	/*writit to pipe*/
	if(write(fields[1] , &total , sizeof(total)) < 0){
		perror("Error on writing to pipe!!");
		exit(EXIT_FAILURE);
	}
	/*closing file discriptor that writes*/
	close(fields[1]);
}
void writeToFifo(int total , int fd){	
	
	if (write(fd, &total, sizeof(int)) < 0)
		exit(EXIT_FAILURE);

}
void writeToFile(FILE* output , char* target ,  int fd ){
	
	int temp = 0, total = 0 , readByte = -1;

	/*reading value from filr discriptor*/
	while((readByte = read(fd , &temp , sizeof(int))) > 0)
		total += temp;
	
	/*If readByte lower than zero than exit.*/
	if(readByte > 0){
		perror("Error on reading pipe !");
		exit(EXIT_FAILURE);
	}

	/*opening output file to writing total.*/
	output = fopen("log.log" , "a+");

	/*Writing total occcurence*/
	fprintf(output, "%d , %s were found in total!\n", total ,target);

	/*closing files.*/
	fclose(output);
}
int readCharbyChar(char* inputName , char* inputDirectory,  char* target){
    /*The character that is read from file.*/
    char character;
    /*For controlling the reading*/
    int col = 1,     currentRow = 1 , foundByte = 0 ,newline = 0 ;
    /*for controlling loops*/
    int flag = 1, flag2 = 1 ;
    /*counter*/
    int count = 0 , i = 1;
    /*The place that target is found.*/
    foundPlace found;
    /*File pointer for reading and writing*/
    FILE* input;
    FILE* output;
    /*the size of target string*/
    int targetSize = strlen(target);

    /*Opening the file that is in the path.*/
    char* dir = inputDirectory;

    if((input= fopen(dir , "r")) == NULL){
    	perror("Error on reading file!");
    	return -1;
    }
	
	/*This file for writing the occurence places.*/    
    output = fopen("log.log" , "a+");

    /*This loop read byte by byte the file till end of file. */
    for(character=fgetc(input); character != EOF && flag2 ;character=fgetc(input),col++){     
        /*control that the first character and the character that is read are same 
         *if they are then keep going to read.
         */
        if(character == target[0]){   
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
            while(target[i] != '\0' && flag && character != EOF){
                   
                character = fgetc(input);
                col++;

                if(character == target[i])
                    i++;
                else if(character == ' ' || character == '\t' || character == '\n')
                {}
                else if (character != target[i]){
                    flag = 0;
                }
                    
                if(i >= targetSize){
                	
                    fprintf(output,"%s : [%d , %d] %s first character found.\n",inputName,found.row,found.col , target);
                    count++;
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
    return count;
}

int directoryOrNot(char* directoryPath){

	/*For the path status*/
	struct stat pathStatus;

	/*controlling is being made.*/
	if (stat(directoryPath, &pathStatus) == -1)
		return 0;

	else
		return S_ISDIR(pathStatus.st_mode);
}
