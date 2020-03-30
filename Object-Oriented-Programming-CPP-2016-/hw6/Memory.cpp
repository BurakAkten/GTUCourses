/*
 * File:Memory.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on November 25 in 2016
 *
 *
 */
#include "Memory.h"
#include <iostream>
#include <cstdlib>//for using the exit() function

using namespace std;

Memory :: Memory() : Memory(0)
{}

Memory :: Memory (int myOption){
	//initialize each memory index to zero by callin set function
	for(int i = 0; i < MEMORY_SIZE ; ++i)
		setMem(i , 0);
	setOption(myOption);
}
//setter function
void Memory :: setOption(int newOption){
	if(newOption >= 0 && newOption <= 2)
		option = newOption;
	else{
		cerr << "Undefined option!"<<endl;
		exit(1);
	}
}
void Memory :: setMem(int index , int value){
	//if the index isn't accessible then exit from the program.
	if(!testIndex(index)){
		cerr<<"(FATAL ERROR!)Unaccessible index in Memory!"<<endl;
		exit(1);
	}
	memory[index] = value;
}
//getter  function
int Memory :: getOption(){
	return option;
}
int Memory :: getMem(int index)const{
	return memory[index];
}
//prints all the memory index
void Memory :: printAll()const{
	cout<<"Memory Values : "<<endl;
	for(int i = 0 ; i < MEMORY_SIZE ; ++i)
		cout << "[" << i << "] -> " << getMem(i) <<" ";   
	cout <<endl;
}
//gets the memory size
int Memory :: getSize()const{
	return MEMORY_SIZE;
}
//test given index if it is accessible or not.
bool Memory :: testIndex(int index)const{
	if(index >= MEMORY_SIZE)
		return false;
	return true;
}