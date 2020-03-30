/*
 * File:Memory.h
 *Author:Burak AKTEN
 *
 *
 *Created on November 25 in 2016
 *
 *
 */

#ifndef Memory_H
#define Memory_H

const int  MEMORY_SIZE = 50;

class Memory{

public:
    Memory(int newOption);//call the setMem(int) and setOption()
    Memory();//default constructor
    void setMem(int index , int value);//set the given index to the value.
    void setOption(int newOption);//set the option
    int getOption();//gets the value of option
    int getMem(int index)const;//gets the value in the index.
    int getSize()const;//getter function for the size of memory
    void printAll()const;//print all the memory.
private:
    //member variables
    bool testIndex(int index)const;
    unsigned int memory[MEMORY_SIZE];
    int option;
};

#endif /* Memory_H */

