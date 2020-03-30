/*
 * File:Computer.h
 *Author:Burak AKTEN
 *
 *
 *Created on November 25 in 2016
 *
 *
 */
#ifndef Computer_H
#define Computer_H

#include <string>
#include "CPU.h"
#include "CPUProgramDyn.h"
#include "Memory.h"

using namespace DynCPUProgram;

class Computer{

public:    
    Computer(CPU& cpu , CPUProgramDyn& cpuProg , Memory& memory , int newOption);
    Computer(int newOption);
    void execute();
    //setter and getter function for myCPu,myCpuProgram,myMemory,option
    void setOption(int newOption);//set the option
    int getOption();//gets the value of option
    void setCPU(CPU& cpu);
    void setCPUProgram(CPUProgramDyn& cpuProg);
    void setMemory(Memory& memory);
    CPU& getCPU();
    CPUProgramDyn& getCPUProgram();
    Memory& getMemory();

private:
	//member variables
	CPU myCpu;
	CPUProgramDyn myCpuProgram;
	Memory myMemory;
	int option;

};

#endif /* Computer_H */

