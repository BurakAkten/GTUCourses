/*
 * File:CPU.h
 *Author:Burak AKTEN
 *
 *
 *Created on October 24 in 2016
 *
 *
 */
#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>

class CPU{
public:
    CPU(int r1,int r2,int r3,int r4,int r5,int pc);//this const. call the set.
    CPU();//it calls the settter functions
    void setRegisters(int r1,int r2,int r3,int r4,int r5);//set the reg arr 
    void setPC(int pc);//sets the pc
    void setInst(std :: string myInst);//set the instruction 
    void print()const;//prints registers and pc
    bool halted()const;//return true if the instruction is 'HLT'
    bool execute(std:: string instruction);//execute the instructions
    std :: string getInst();//get the instruction after clean it.
    //other getter functions.
    int getPC()const;
    int getR1()const;
    int getR2()const;
    int getR3()const;
    int getR4()const;
    int getR5()const;
private:
    bool move(std::string str);//if move is possible returns true
    bool jump(std::string str);//if jump is possible returns true
    //if txt is one of registers and the register is zero , then returns 1.
    int jump2(std::string txt); 
    bool prnt(std::string txt);//if print is possible returns true
    void halt();//make flag true.
    bool subOrAdd(std::string str,int value);//if suboradd possible return true
    void eraseSpace(std::string& str);//erase the spaces from the str
    void makeUpper(std::string& txt);//make all letter capital
    bool isAllNumber(std::string txt)const;//if txt is number completely true.
    int convertStrToInt(std::string str);//convert the string to int.
    //control the txt if it is equal to one of string in str[] 
    bool controlTxt(std::string txt ,std:: string str[])const;
    // make the sub strings 
    void findSubStr(std::string& txt ,std:: string& txt2, std::string str);
    bool flag = false;//to finish the loop in main function.
    int reg[5];//store the values of registers
	const int size = 5; //size of reg.
    int PC;//program counter (line of file.)
    std :: string inst; //instruction
};

#endif /* CPU_H */

