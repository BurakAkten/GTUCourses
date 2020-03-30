/*
 * File:CPUProgram.h
 *Author:Burak AKTEN
 *
 *
 *Created on November 12 in 2016
 *
 *
 */
#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class CPUProgram{
    
public:
	CPUProgram();//default constructor.
	CPUProgram(int newOption);//call setOption.
    CPUProgram(std::string fName);//calling ReadFile function.
    void setOption(int newOption);//set the option
    void setFileName(std :: string fileName);//sets the file name
    std :: string getFileName();//gets the file name
    int getOption();//gets the value of option
    void ReadFile(std::string fileName);//read the file and store lines.
    /***********************************************************************/
    CPUProgram operator()(int first , int second);
    std::string operator[](int lineNumber)const;
    const CPUProgram operator+(std :: string inst);
    const void operator+=(std :: string inst);
    const CPUProgram& operator+(CPUProgram& rside);
    bool operator==(CPUProgram& rside)const;
    bool operator<=(CPUProgram& rside)const;
    bool operator>(CPUProgram& rside)const;
    bool operator!=(CPUProgram& rside)const;
    bool operator>=(CPUProgram& rside)const;
    bool operator<(CPUProgram& rside)const;
    CPUProgram& operator--();
    CPUProgram operator--(int);
    friend std::ostream& operator<<(std::ostream& output, const CPUProgram& cProgram);
    /**************************************************************************/
    //getline function works according to PC. Thus if user wants the 0. 
	//line this function will show error message and end the program.
    std::string getLine(int lineNumber)const;//return the line that asking for
    int size()const;//returns the number of line of the file
private:
    std::vector<std::string> instruction;//to store instruction lines.
    int option;
    std :: string nameOfFile;
};

#endif /* CPUPROGRAM_H */

