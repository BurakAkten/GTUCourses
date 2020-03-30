/*
 * File:Computer.h
 *Author:Burak AKTEN
 *
 *
 *Created on November 12 in 2016
 *
 *
 */
#ifndef Computer_H
#define Computer_H

#include <string>
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

class Computer{

public:    
    Computer(CPU& cpu , CPUProgram& cpuProg , Memory& memory , int newOption);
    Computer(int newOption);
    void execute();
    //setter and getter function for myCPu,myCpuProgram,myMemory,option
    void setOption(int newOption);//set the option
    int getOption();//gets the value of option
    void setCPU(CPU& cpu);
    void setCPUProgram(CPUProgram& cpuProg);
    void setMemory(Memory& memory);
    CPU& getCPU();
    CPUProgram& getCPUProgram();
    Memory& getMemory();

private:
	//member variables
	CPU myCpu;
	CPUProgram myCpuProgram;
	Memory myMemory;
	int option;

};

#endif /* Computer_H */

