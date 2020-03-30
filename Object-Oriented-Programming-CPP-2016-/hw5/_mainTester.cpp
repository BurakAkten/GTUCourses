/*
 * File:CPUProgram.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on November 12 in 2016
 *
 *
 */
#include "requiredIncs.h"

int main(int argc, char** argv){
	////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	
	//Testing class CPUProgram
	
	//op []
	CPUProgram myCPUProgram(option);
	myCPUProgram.ReadFile(filename);

	cout << "***********************************************"<<endl;

	cout << myCPUProgram[0] << endl;
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	cout << "***********************************************"<<endl;

	//op +
	cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size() - 1]) << endl;
	
	cout << "***********************************************"<<endl;

	//op +=
	myCPUProgram += "MOV R2, #50";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	cout << "***********************************************"<<endl;

	//op + <<
	CPUProgram myOtherCPUProgram(option);
	myOtherCPUProgram.ReadFile(filename);
	cout << (myCPUProgram + myOtherCPUProgram) << endl;
	
	cout << "***********************************************"<<endl;

	//op COMP --

	cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	
	--myOtherCPUProgram;
	
	cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	

	cout << "***********************************************"<<endl;

	//op ()
	cout << myCPUProgram(5,10) << endl;
	

	cout << "***********************************************"<<endl;

	//error check
	myCPUProgram += "";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	cout << myCPUProgram[myCPUProgram.size()] << endl;

		
	cout << "***********************************************"<<endl;
	//////////////////////////////////////////////////////////////////////////

	return 0;
}
