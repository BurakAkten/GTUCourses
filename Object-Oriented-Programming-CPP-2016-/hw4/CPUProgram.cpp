/*
 * File:CPUProgram.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on November 12 in 2016
 *
 *
 */
#include "CPUProgram.h"
#include <cstdlib>
#include <iostream>
using namespace std;

CPUProgram :: CPUProgram() : CPUProgram(0){}

CPUProgram :: CPUProgram(int newOption){
	setOption(newOption);
}

CPUProgram :: CPUProgram(string fName){
	//ReadFile function is being called
    ReadFile(fName);
    setFileName(fName);
}

void CPUProgram :: setFileName(string fileName){
	nameOfFile = fileName;
}
string CPUProgram ::  getFileName(){
	return nameOfFile;
}
void CPUProgram :: setOption(int newOption){
	if(newOption >= 0 && newOption <= 2)
		option = newOption;
	else{
		cerr << "Undefined option!"<<endl;
		exit(1);
	}
}
void CPUProgram :: ReadFile(string fileName){

	setFileName(fileName);

    ifstream cpuFile;
    
    cpuFile.open(fileName);//file is opening
    if(cpuFile.fail()){//if file is not exist error message is printed 
        cerr<<"The file that is called '"<<getFileName()<<"' is not exist!!";
        cerr<<endl;
        //then program finished.
        exit(1);
    }
    string str;
    //file is being read until end of file.
    for(int i = 0 ; !cpuFile.eof() ; ++i){
        getline(cpuFile , str);
        //lines are added in the string vector instruction.
        instruction.push_back(str);
    }
    instruction.pop_back();
    //file is closing
    cpuFile.close();
}
int CPUProgram :: getOption(){
	return option;
}
int CPUProgram :: size()const{
    return instruction.size();//returning the size of the file
}
string CPUProgram :: getLine(int lineNumber)const{
	//when file is not read this part show error message and end it.
    if(size() == 0){
    	cerr << "ERROR!!Could not read any file."<<endl;
    	exit(1);
    }

    //when lineNumber is invalid then exit the program.
	if(lineNumber < 0 || lineNumber > size() - 1){		
		cerr << "ERROR!!Invalid Line number to access!"<<endl;
		exit(1);
	}

    return instruction[lineNumber]; //returning the line of asking
}
/********************************************************************/
string CPUProgram :: operator[] (int lineNumber)const{

	//this function directly call the getLine function with lineNumber
	return getLine(lineNumber);
}
/****************************************************************/
const CPUProgram CPUProgram :: operator+(std :: string inst){
	//if the string is empty then this part show the error message and 
	// return *this CPUProgram.
	if(inst == ""){
		cerr<<"ERROR!!The instruction that you want to add is empty!!"<<endl;
		cerr<<"Adding is fail!"<<endl;
		return *this;
	}
	//if it's not empty then inst is added and then returned.
	CPUProgram temp(option);
	temp = *this;
	temp.instruction.push_back(inst);
	
	return temp;
}
/***************************************************************/
const void CPUProgram :: operator+=(std :: string inst){
	//again if it's empty then show error message then do nothing. 
	if(inst == ""){
		cerr<<"ERROR!!The instruction that you want to add is empty!!";
		cerr<<"Adding is fail!"<<endl<<"Nothing has been added."<<endl;
		return;
	}

	this->instruction.push_back(inst);
}
/****************************************************************/
const CPUProgram& CPUProgram :: operator+(CPUProgram& rside){

	//if rside program has no instruction then error message is shown ,
	// then return *this without adding nothing.
	if(rside.size() == 0){
		cerr << "R-value has no instruction!! Adding is fail!"<<endl;
		cerr << "Nothing has been added."<<endl;
		return *this;
	}
	//if it's not empty then instructions is added from rside to lside.
	//then returned *this(lside).
	for(int i = 0 ; i < rside.size() ; i++)
		*this += rside[i];

	return *this;
}
/****************************************************************/
ostream& operator <<(ostream& output, const CPUProgram& cProgram){

	
	if(cProgram.size() < 0){
		cerr<< "ERROR!! Invalid CPUProgram!!\n";
		exit(1);
	}
	else if(cProgram.size() == 0){
		//if the program han no instruction then returned empty str.
		output << "";
		return output;
	}

	//else returned cprogram line by line.
	for (int i = 0 ; i < cProgram.size(); ++i)
	{
		output << cProgram[i]<<endl;
	}

	return output;
}
/***************************************************************/
//comparasion overloding.
bool CPUProgram :: operator==(CPUProgram& rside)const{
	return (this->size() == rside.size());
}
bool CPUProgram :: operator!=(CPUProgram& rside)const{
	return !(*this == rside);
}

bool CPUProgram :: operator<=(CPUProgram& rside)const{
	return (*this == rside || this->size() < rside.size());
}
bool CPUProgram :: operator>(CPUProgram& rside)const{
	return (!(*this <= rside));
}

bool CPUProgram :: operator>=(CPUProgram& rside)const{
	return (*this == rside || this->size() > rside.size());
}
bool CPUProgram :: operator<(CPUProgram& rside)const{
	return (!(*this >= rside));
}
/***************************************************************/

CPUProgram CPUProgram :: operator-- (int ignore){
	//in this part created a new temp object and deleting a line from
	// *this object then returned temp object.
	CPUProgram temp(option);
	
	temp = *this;

	if(this->size() > 0)
		this->instruction.pop_back();
	else{
		cerr<<"The CPUProgram that tou want to delete a line from";
		cerr<< " is empty!! Deleting Fail!! Nothing has been deleted."<<endl;
		return *this;
	}
	return temp ;
}

CPUProgram& CPUProgram :: operator-- (){
	//in this part directly a line is deleted from *this object then
	// it is returned.

	if(this -> size() > 0)
		this->instruction.pop_back();
	else{
		cerr<<"The CPUProgram that tou want to delete a line from";
		cerr<< " is empty!! Deleting Fail!! Nothing has been deleted."<<endl;
		return *this;
	}

	return *this;
}
/****************************************************************/
CPUProgram CPUProgram :: operator()(int first , int second){

	CPUProgram temp(option);
	//if second index is greater than lines number than returned empty
	// object(temp)
	if(second > size() - 1 || first > size() - 1){
		cerr<<"EROOR! This CPUProgram has at most "<<size()-1<<"lines!"<<endl;
		return temp;
	}

	if(second <= first){
		cerr<<"ERROR!! First index must be smaller than second index";
		cerr<<" for () operator."<<endl;
		return temp;
	}
	//in here , created temporary vector to hold the instruction between the
	// the index of first to second.
	vector<string> v(second - first + 1);
	//fisrt=3 second=10 size of v = 8(second - first + 1)

	for (int i = first , k = 0; i <= second; ++i ,++k)
		v[k] = this->instruction[i];

	temp = *this;
	temp.instruction = v;

	return temp ;
}
/*****************************************************************/
