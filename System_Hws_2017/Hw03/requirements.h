#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

/*if PATH_MAX is not defined then it is defined to size of the current working directory.*/
#ifndef PATH_MAX
#define PATH_MAX 256
#endif

#define FIFO_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FIFONAME "myFifo"

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
void readDir( char* targetString , char* directoryPath , int fd , int i);

/*
 *FOR THİS FUNCTİON THE COURSE BOOK BECOME A REFERRENCE FOR ME.
 *This function control the path is directory or not.
 *@return 1 if it is directory otherwise 0.
 */
int directoryOrNot(char* directoryPath);

/*
 *This function for writing total occurence to outputfile.
 *@param output the output file
 *@param target the target string to find
 *@param fields the file discriptors
 */
void writeToFile(FILE* output , char* target , int fd );

/*
 *This function write sth to pipe.
 *@param fields the file dicriptors.
 *@param total the variable to write.
 */
void writeToPipe(int fields[2] , int total);

/*
 *This function write the  total to fifo.
 *@param total The value for writing to fifo
 *@param fd the file discriptor
 */
void writeToFifo(int total , int fd);

/*
 *This function read from pipe
 *@param fields the file discriptors
 *@return the value of value that is read from pipe
 */
int readFromPipe(int field[2]);

/*
 *This function read values from a file discriptor to another. 
 *@param first the first file discriptor.
 *@param second the second file discriptor.
 */
void readFromFdtoOtherFd(int first , int second);



