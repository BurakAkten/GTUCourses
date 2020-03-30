#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

/*if PATH_MAX is not defined then it is defined to size of the current working directory.*/
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

/*This structure for found place as row and col*/
typedef struct {
    int col;
    int row;
}foundPlace;

/*
 *This function read the file byte by byte. İf this function find
 *the target in the file then print out this on the screen.
 *@param inputName the filename that will be read.
 *@param target the word for seraching in the file.
 *@param inputDirectory the directory of the file.
 *@return the total occurences of the target in the file or -1 for any failure..
 */
int readCharbyChar(char* inputName , char* inputDirectory,  char* target);

/*
 *This function read a directory that is given.
 *@param targetString the word for seraching in the file.
 *@param directoryPath the path of the directory.
 *@param occurencce the file pointer that the total occurences will be writed in.
 */
void readDir( char* targetString , char* directoryPath , FILE* occurencce);

/*
 *FOR THİS FUNCTİON THE COURSE BOOK BECOME A REFERRENCE FOR ME.
 *This function control the path is directory or not.
 *@return 1 if it is directory otherwise 0.
 */
int directoryOrNot(char* directoryPath);


int main(int argc , char* argv[]){
	
	/*It holds the total occurences of the word.*/
	int total = 0 ;
	/*For read from file.*/
	char i;
	/*For holding current working directory.*/
	char currentPath[PATH_MAX];
	/*File pointers.*/
	FILE* totalFile;
	FILE* output;
	/*For parent pid*/
	unsigned int pid = getpid();

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

	/*Adding the the directory name to currentPath*/
	strcat(currentPath , "/");
	strcat(currentPath , argv[2]);

	/*Openning the file that each process writes the total occurence in */
	totalFile = fopen("total.txt" , "a+");
	
	/*Calling the function that reads the directory.*/
	readDir(argv[1] ,currentPath,  totalFile);
	
	/*Closing the file after writing is done.*/
	fclose(totalFile);

	/*Here , parent reads the totalFile , then making sum of them then write the total occurence on the .log file.*/
	if(pid == getpid()){	

		totalFile = fopen("total.txt" , "r");
		
		/*Making calculation for total occurence*/
		for(i = getc(totalFile);i != EOF;i = getc(totalFile))
			if(i != '\n')
				total += (int)(i - 48) ;
				
		output = fopen("log.log" , "a+");
		/*Writing total occcurence*/
		fprintf(output, "%d , %s were found in total!\n", total , argv[1]);

		/*closing files.*/
		fclose(totalFile);
		fclose(output);
	}
	
	return 0;
}

void readDir( char* targetString , char* directoryPath , FILE* occurencce){


	/*These variable for calculation of total occurence of the string.*/
	int total = 0  , returnvalue = 0;
	/*size of the inner dirrectory*/
	int size = strlen(directoryPath);

	DIR* directory ;
	struct dirent* direntp;
	/*for pid number*/
    unsigned int child = 1;
    /*for innerdirectory.*/
    char innerDir[PATH_MAX];


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

			child = fork();


			if(directoryOrNot(innerDir) == 0  ){
				/*child staff reading files and finding the occurences.*/
				if(child == 0){

					returnvalue = readCharbyChar(direntp->d_name , innerDir , targetString);
					if(returnvalue == -1){
						return;
					}
					total += returnvalue;
					break;
				}
			}
			else if (directoryOrNot(innerDir) == 1){
				/*child reading inner folder recursivly. */

				if(child == 0){
					readDir(targetString , innerDir , occurencce);
					break;
				}
			}
		}
	}while((direntp = readdir(directory)) != NULL && child > 0);	
	
	/*Total occurences are printed on the file by each child. After they are come same place.
	then finising the child process.*/
	while(wait(NULL) > 0);
	if(child == 0 && total != 0){
		fprintf(occurencce, "%d\n", total);
		exit(0);
	}
	/*Closing the directory*/
	while ((closedir(directory) == -1) && (errno == EINTR));
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
