/*
 * File:Computer.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on November 25 in 2016
 *
 *
 */
#include "Computer.h"
#include <string>
#include <cstdlib>

using namespace std;

//constructor calls the setter functions 
Computer :: Computer(CPU& cpu,CPUProgramDyn& cpuProg,Memory& memory,int newOption)
				:myMemory(newOption),myCpu(newOption),myCpuProgram(newOption){
	setCPU(cpu);
	setCPUProgram(cpuProg);
	setMemory(memory);
	setOption(newOption);
}
Computer :: Computer(int newOption)
				:myMemory(newOption),myCpu(newOption),myCpuProgram(newOption)
{
	setOption(newOption);
}
//setter functions.
void Computer :: setOption(int newOption){
	if(newOption >= 0 && newOption <= 2)
		option = newOption;
	else{
		cerr << "Undefined option!"<<endl;
		//exit(1);
	}
}
void Computer :: setCPU(CPU& cpu){

	myCpu = cpu;
}
void Computer :: setCPUProgram(CPUProgramDyn& cpuProg){

	myCpuProgram = cpuProg;
}
void Computer :: setMemory(Memory& memory){

	myMemory = memory;
}
//getter function.
int Computer :: getOption(){
	return option;
}
CPU& Computer :: getCPU(){

	return myCpu;
}
CPUProgramDyn& Computer :: getCPUProgram(){

	return myCpuProgram;
}
Memory& Computer :: getMemory() {

	return myMemory;
}
//execute function 
void Computer :: execute(){

	myCpu.setPC(1);
	while(!myCpu.halted()){
		//getting instruction 
        string instruction = myCpuProgram.getLine(myCpu.getPC() - 1);
        //to clear instruction , setting new string for instruction
        myCpu.setInst(instruction);

        //instruction is made clear .
        instruction = myCpu.getInst();

        if(instruction == ""){
        //if instruction can not be executed then the error messages printed
            cerr << "Line : "<< myCpu.getPC();
            cerr << "->Instruction/Syntax Error in the file that is called ";
            cerr << myCpuProgram.getFileName()<<endl;
            // and then exit from the program.
            exit(1);
        }

        if(option==1 || option==2)
            cout <<"*****"<< instruction<<"*****"<<endl;

        if(myCpu.execute(instruction , myMemory)){
        	//print the values of registers and Pc , when the comman is '1'
        	// and instruction is 'hlt'
            if(option==1 || option==2)
                myCpu.print();
            if(option == 2)
            	myMemory.printAll();
            if(myCpu.getPC() - 1 ==myCpuProgram.size()){
            	cout <<"*****"<< instruction<<"*****"<<endl;
            	myCpu.print();
            	myMemory.printAll();
            }
        }  
        else{
        	//if instruction can't be executed then the error messages printed
            cerr << "Line : "<<myCpu.getPC();
            cerr << "->Instruction / Syntax Error in the file that is called ";
            cerr << myCpuProgram.getFileName()<<endl;
            //and then exit from the program.
            exit(1);
        }     
    } 
}
