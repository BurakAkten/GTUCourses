#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/msg.h>

/*if PATH_MAX is not defined then it is defined to size of the current working directory.*/
#ifndef PATH_MAX
#define PATH_MAX 256
#endif

#define DIRFILE "dir.txt"
#define FILEFILE "file.txt"
#define LINEFILE "line.txt"
#define MILLION 1000000L
#define PERMS (S_IRUSR | S_IWUSR)

/*This structure for found place as row and col*/
typedef struct {
    int col;
    int row;
}foundPlace;

/*This structure for holding parameters for thread function*/
typedef struct{
	char directName[PATH_MAX];
	char innerDirect[PATH_MAX];
	char target[PATH_MAX];
}parameters;

/*The word counts.*/
extern int wordCounts;
/*For semaphore.*/
extern sem_t sem;
/*For handling signals*/
extern int signalNumber;
/*for shared memory id*/
extern int shmid;
/*Message queue key*/
extern key_t mqKey;
/*Message queue id*/
extern int mqId;
extern int result;

/*
 *This function read the file byte by byte. İf this function find
 *the target in the file then print out this on the screen.
 *@param inputName the filename that will be read.
 *@param target the word for seraching in the file.
 *@param inputDirectory the directory of the file.
 *@return the total occurences of the target in the file or -1 for any failure..
 */
void* readCharbyChar(void* args);

/*
 *This function read a directory that is given.
 *@param targetString the word for seraching in the file.
 *@param directoryPath the path of the directory.
 *@param occurencce the file pointer that the total occurences will be writed in.
 */
void readDir( char* targetString , char* directoryPath , pid_t parent , key_t key );

/*
 *This function for writing total occurence to outputfile.
 *@param output the output file
 *@param target the target string to find
 */
int writeToFile(FILE* output , char* target  );

/*
 *This function calculate the count of the files that will be searched.
 *@param directory the name of directory for searching
 */
int numberOfFiles(char* directoryPath , int* max);

/**
 *This function update the temp files.
 *@param name filename
 */
void updateThefile(char* name);

/*
 *This function read file.
 *@param name file name
 */
int readFile(char* name);

/*
 *This fuction prints out results on the screen.
 *@param total the total number of occurences
 */
void writeToConsole( int tot , int max);
/*
*This func. for signal handlig.
*@param sigNum the number of the signal
*/
void signalhandling(int sigNum);

/*
 *This function calculate the total number of the string that is found.
 */
int readTot();

/**
 *This function just reads a directory and return the file numbers
 *@param directoryPath the path of tthe directory
 *@return the file number
 */
int justFilesInDir(char* directoryPath);