/*
 * File:main.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on October 24 in 2016
 *
 *
 */
#include <iostream>
#include <string>
#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

int main(int argc, char** argv) {
    
    CPUProgram myProg(argv[1]);
    CPU myCpu(0 ,0 , 0, 0 , 0 , 1);
    string command = argv[2];

    while(!myCpu.halted()){
        string instruction = myProg.getLine(myCpu.getPC());
        
        //when the comman is '1' and instruction is 'hlt' , this part works to  
        // clean instruction to write on the screen.
        myCpu.setInst(instruction);
        //instruction is updating after cleaning.
        instruction = myCpu.getInst();
 		
        
        if(myCpu.getPC() > myProg.size()){
          	cerr << "PC can not represents unaccessible line!"<<endl;
          	return -1;
        }

        if(instruction == ""){
        	//if instruction can not be executed then the error messages printed
            cerr << "Line : "<<myCpu.getPC();
            cerr << "->Instruction / Syntax Error in the file that is called ";
            cerr << argv[1]<<endl;
            // and then returns -1.
            return -1;
        }

        if(command == "1" || myCpu.getPC() == myProg.size())
            cout << instruction<<endl;

        if(myCpu.execute(instruction)){
        	//print the values of registers and Pc , when the comman is '1'
        	// and instruction is 'hlt'
            if(command == "1" || myCpu.getPC() == myProg.size() + 1)
                myCpu.print();
        }  
        else{
        	//if instruction can not be executed then the error messages printed
            cerr << "Line : "<<myCpu.getPC();
            cerr << "->Instruction / Syntax Error in the file that is called ";
            cerr << argv[1]<<endl;
            // and then returns -1.
            return -1;
        }       
    } 
    return 0;
}
