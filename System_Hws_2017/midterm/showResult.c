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

int main(int argc, char const *argv[])
{
	/*Controlling for command line arguments. İf this format is wrong then error message
     *is printed out.
     */
    if(argc != 0){
       	fprintf(stderr, "Usage: %s\n", argv[0]);
		return -1;
    }

	return 0;
}