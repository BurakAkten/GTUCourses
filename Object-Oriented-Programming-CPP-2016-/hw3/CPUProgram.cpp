/*
 * File:CPUProgram.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on October 24 in 2016
 *
 *
 */
#include "CPUProgram.h"
#include <cstdlib>
#include <iostream>
using namespace std;

CPUProgram :: CPUProgram(string fName){
	//ReadFile function is being called
    ReadFile(fName);
}
void CPUProgram :: ReadFile(string fileName){

    ifstream cpuFile;
    
    cpuFile.open(fileName);//file is opening
    if(cpuFile.fail()){//if file is not exist error message is printed 
        cerr<<"The file that is called '"<<fileName<<"' is not exist!!"<<endl;
        //then program finished.
        exit(1);
    }
    
    string str;
    //file is being read until end of file.
    for(int i = 0 ; !cpuFile.eof() ; ++i){
        getline(cpuFile , str);
        //lines are added in the string vector instruction.
        instruction.push_back(str);
        sizeOfFile = i;//size of file updating
    }
    //file is closing
    cpuFile.close();
} 
int CPUProgram :: size()const{
    return sizeOfFile;//returning the size of the file
}
string CPUProgram :: getLine(int lineNumber)const{
    
    return instruction[lineNumber - 1]; //returning the line of asking
}

