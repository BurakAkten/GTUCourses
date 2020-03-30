#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"	


using namespace std;



	// This is just a sample main function, you should rewrite this file to handle problems 
	// with new multitasking and virtual memory additions.
int main (int argc, char**argv)
{	
	srand(time(NULL));
	
	if (argc != 4){
		std::cerr << "Usage: prog exeFile fileSystem.dat debugOption\n";
		exit(1); 
	}
	int DEBUG = atoi(argv[3]);
	string fileSystem = argv[2];


	uint64_t totalExecutionCycles = 0;


	memory mem;
	CPU8080 theCPU(&mem);
	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);

	GTUOS	theOS(&theCPU , DEBUG , fileSystem);


	totalExecutionCycles = theOS.execute();

	//print out the total cycles on the screen
	cout << "Total number of cycles used by program execution is : " << totalExecutionCycles << endl;

	//write the memory to file
	if(!theOS.writeMemoryToFile()){
		cerr << "The outfile that is called" <<"could not opened!"<<endl;
		return -1;
	}



	return 0;
}

