/*
 * File:CPUProgramDyn.h
 *Author:Burak AKTEN
 *
 *
 *Created on November 25 in 2016
 *
 *
 */
#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

#include <iostream>
#include <fstream>
#include <string>

namespace DynCPUProgram{

    class CPUProgramDyn{
        
    public:
    	CPUProgramDyn();//default constructor.
    	CPUProgramDyn(int newOption);//call setOption.
        CPUProgramDyn(std::string fName);//calling ReadFile function.
        CPUProgramDyn(const CPUProgramDyn& other);//copyConstructor;
        void setOption(int newOption);//set the option
        void setFileName(std :: string fileName);//sets the file name
        std :: string getFileName();//gets the file name
        int getOption();//gets the value of option
        void ReadFile(std::string fileName);//read the file and store lines.
        void addLine(std :: string line);//add new line into instructions.
        /**********************************************************************/
        CPUProgramDyn& operator=(const CPUProgramDyn rSide);//assignment operator
        CPUProgramDyn operator()(int first , int second);
        std::string& operator[](int lineNumber)const;
        const CPUProgramDyn operator+(std :: string inst);
        const void operator+=(std :: string inst);
        const CPUProgramDyn operator+(CPUProgramDyn& rside);
        bool operator==(CPUProgramDyn& rside)const;
        bool operator<=(CPUProgramDyn& rside)const;
        bool operator>(CPUProgramDyn& rside)const;
        bool operator!=(CPUProgramDyn& rside)const;
        bool operator>=(CPUProgramDyn& rside)const;
        bool operator<(CPUProgramDyn& rside)const;
        CPUProgramDyn& operator--();
        CPUProgramDyn operator--(int);
        friend std::ostream& operator<<(std::ostream& output, const CPUProgramDyn& cProgram);
        /**********************************************************************/
        //return the line that asking for
        std::string& getLine(int lineNumber)const;
        int size()const;//returns the number of line of the file
        /**********************************************************************/
        ~CPUProgramDyn();//desructor to free memory
    private:

    	std :: string* instruction;
    	int capacity;
    	int used;
        int option;
        std :: string nameOfFile;
        void reload();
        //this function makes the capacity of the instruction bigger.
    };
}
    #endif /* CPUPROGRAMDYN_H */
