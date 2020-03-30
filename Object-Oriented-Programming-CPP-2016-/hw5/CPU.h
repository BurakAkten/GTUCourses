/*
 * File:CPU.h
 *Author:Burak AKTEN
 *
 *
 *Created on November 12 in 2016
 *
 *
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>

const int SIZE = 5;

class Memory;//to use memory object

class CPU{

public:
	
    CPU(int r1,int r2,int r3,int r4,int r5,int pc);//this const call the set
    CPU(int newOption);//this const. calls the setOPtion().
    CPU();// default constructor calls the CPU(int) with value '0'
    void setOption(int newOption);//set the option
    int getOption();//gets the value of option
    void setRegisters(int r1,int r2,int r3,int r4,int r5);//set the reg arr 
    void setPC(int pc);//sets the pc
    void setInst(std :: string myInst);//set the instruction 
    void print()const;//prints registers and pc
    bool halted()const;//return true if the instruction is 'HLT'
    //execute the instructions
    bool execute(std:: string instruction , Memory& myMemory);
    std :: string getInst();//get the instruction after clean it.
    //other getter functions.
    int getPC()const;
    int getReg(int index)const;

private:
	//if move is possible returns true
    bool move(std::string str,Memory& myMemory);
    //if jump is possible returns true
    bool jump(std::string str , std :: string str2);
    //if txt is one of registers and the register is zero , then returns 1.
    int jump2(std::string txt);
    int jpn(std::string txt);
    //if print is possible returns true 
    bool prnt(std::string txt , Memory& myMemory);
    void halt();//make flag true.
    //if suboradd possible return true
    bool subOrAdd(std::string str,int value , Memory& myMemory);

    bool flag;//to finish the loop in main function.
    int reg[SIZE];//store the values of registers
    int PC;//program counter (line of file.)
    std :: string inst; //instruction
    int option;
};

namespace {
	void eraseSpace(std::string& str);//erase the spaces from the str
    void makeUpper(std::string& txt);//make all letter capital 
    // make the sub strings 
    void findSubStr(std::string& txt ,std::string& txt2, std::string str);
    //control the txt if it is equal to one of string in str[] 
    bool controlTxt(std::string txt ,std:: string str[]);
    bool isAllNumber(std::string txt);//if txt is number completely true.
    int convertStrToInt(std::string str);//convert the string to int.
}

#endif /* CPU_H */

