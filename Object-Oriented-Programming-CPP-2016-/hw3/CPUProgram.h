/*
 * File:CPUProgram.h
 *Author:Burak AKTEN
 *
 *
 *Created on October 24 in 2016
 *
 *
 */
#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <vector>
#include <fstream>
#include <string>

class CPUProgram{
    
public:
    CPUProgram(std::string fName);//calling ReadFile functions.
    void ReadFile(std::string fileName);//read the file and store lines.
    std::string getLine(int lineNumber)const;//return the line that asking for
    int size()const;//returns the number of line of the file
private:
    std::vector<std::string> instruction;//to store instruction lines.
    int sizeOfFile ;
};

#endif /* CPUPROGRAM_H */

