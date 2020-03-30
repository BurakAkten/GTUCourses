#include "requiredIncs.h"

int main(int argc , char** argv){

	//////////////////////////////////////////////////////////////////////////
	//command line parameters
	
	//Controlling the command line errors.
	/////////////// Kind of Errors///////////////
	///////less or more than 3 parameters////////
	///////different option from (0,1,2)/////////
	if(argc < 3 || argc > 3){
		cerr<<"Command Line Error!";
		cerr<<"(More or less than three arguments)"<<endl;
		return -1;
	}
	string tempOp = argv[2];
	if(tempOp.size() > 1 || !(argv[2][0] >= '0' && argv[2][0] <= '2')){
		cerr<<"Command Line Error!";
		cerr<<"(Invalid Option!)"<<endl;
		return -1;
	}
	
	string fileName = argv[1];
	int option = (argv[2][0] - 48);
	
	Memory myMemory(option);
	CPU myCPU(option);
	CPUProgram myCPUProgram(option);

	myCPUProgram.ReadFile(fileName);

	Computer myComputer1(myCPU, myCPUProgram, myMemory , option);
	Computer myComputer2(option);

	myComputer2.setCPU( myComputer1.getCPU() );

	myComputer2.setCPUProgram(myComputer1.getCPUProgram() );

	myComputer2.setMemory(myComputer1.getMemory() );

	myComputer2.execute();
	
	
	return 0;
}
