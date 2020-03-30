/*
 * File:CPUProgramDyn.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on November 25 in 2016
 *
 *
 */
#include "CPUProgramDyn.h"
#include <cstdlib>
#include <iostream>
using namespace std;

namespace DynCPUProgram{

	CPUProgramDyn :: CPUProgramDyn() : CPUProgramDyn(0){}

	CPUProgramDyn :: CPUProgramDyn(int newOption)
								:used(0),capacity(0),option(newOption) {
		//this constructor sets the first value of used , capacity and option.
		instruction = new string[capacity];
	}

	CPUProgramDyn :: CPUProgramDyn(string fName) 
						: nameOfFile(fName),used(0),capacity(0){
		//ReadFile function is being called
	    ReadFile(fName);
	}
	CPUProgramDyn :: CPUProgramDyn(const CPUProgramDyn& other)
	:capacity(other.capacity),used(other.used){
		//copy constructor.Copy every line in instruction to other's instructions.
		//And initialize the capacity and used to other's capacity and used.
		instruction = new string[capacity];
		for (int i = 0; i < used; ++i)
			instruction[i] = other.instruction[i];
	}
	CPUProgramDyn :: ~CPUProgramDyn(){
		//destructor free the memory for instruction
		delete [] instruction;
	}
	void CPUProgramDyn :: addLine(std :: string line){

		//this function first controls if used is bigger than or equal to 
		//capacity. if it is call the reload function for take more place 
		//from memory.
		if(used >= capacity)
			reload();
		//then adds the new line to instruction .
		instruction[used] = line;
		used++;
	}
	void CPUProgramDyn :: reload(){
		//this function makes capacity more than previous and takes place
		// from memory again
		capacity += 10;
		string* newArray = new string[capacity];

		//then initializes every index in instruction to newArray.
		for(int i = 0 ; i < used ; ++i)
			newArray[i] = instruction[i];
		//free old memory
		delete [] instruction;

		instruction = newArray;	
	}
	void CPUProgramDyn :: setFileName(string fileName){
		nameOfFile = fileName;
	}
	string CPUProgramDyn ::  getFileName(){
		return nameOfFile;
	}
	void CPUProgramDyn :: setOption(int newOption){

		if(newOption >= 0 && newOption <= 2)
			option = newOption;
		else{
			cerr << "Undefined option!!"<<endl;
			//exit(1);
		}
	}
	void CPUProgramDyn :: ReadFile(string fileName){

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
	        //lines are added in the string instruction.
	        
	        addLine(str);
	    }
	    used--;
	    //file is closing
	    cpuFile.close();
	}
	int CPUProgramDyn :: getOption(){
		return option;
	}
	int CPUProgramDyn :: size()const{
	    return used;//returning the size of the file
	}
	string& CPUProgramDyn :: getLine(int lineNumber)const{
		//when file is not read this part show error message and end it.
	    if(size() == 0){
	    	cerr << "ERROR!! This object is empty! There is no line!"<<endl;
	    	exit(1);
	    }

	    //when lineNumber is invalid then exit the program.
		if(lineNumber < 0 || lineNumber > size() - 1){		
			cerr << "ERROR!!Invalid Line number to access!"<<endl;
			cerr << "Last line was returned!!"<<endl;
			return instruction[size() - 1];
			//exit(1);
		}

	    return instruction[lineNumber]; //returning the line of asking
	}
	/********************************************************************/
	CPUProgramDyn&  CPUProgramDyn :: operator=(const CPUProgramDyn rSide){
		
		//the assignment operator overloading make deep copy for *this and 
		//rSide
		if(used != rSide.used && capacity != rSide.capacity){
			delete [] instruction;
			capacity = rSide.capacity;
			used = rSide.used;
			instruction = new string[capacity];
		}
		
		for(int i = 0; i < used ; ++i)
			instruction[i] = rSide.instruction[i];
			
		return *this; 
	}
	/*******************************************************************/
	string& CPUProgramDyn :: operator[] (int lineNumber)const{

		//this function directly call the getLine function with lineNumber
		return getLine(lineNumber);
	}
	/****************************************************************/
	const CPUProgramDyn CPUProgramDyn :: operator+(std :: string inst){
		//if the string is empty then this part show the error message and 
		// return *this CPUProgramDyn.
		if(inst == ""){
			cerr<<"ERROR!!The instruction that you want to add is empty!!\n";
			cerr<<"Adding is fail! Returned old objectc without any adding!\n";
			return CPUProgramDyn(0);
		}
		//if it's not empty then inst is added and then returned.

		CPUProgramDyn temp;
		temp = *this;

		temp.addLine(inst);

		return temp;
	}
	/***************************************************************/
	const void CPUProgramDyn :: operator+=(std :: string inst){
		//again if it's empty then show error message then do nothing. 
		if(inst == ""){
			cerr<<"ERROR!!The instruction that you want to add is empty!!";
			cerr<<"Adding is fail!"<<endl<<"Nothing has been added."<<endl;
			cerr<<"Last line still same as old one ->"<<endl;
			return;
		}

		addLine(inst);
	}
	/****************************************************************/
	const CPUProgramDyn CPUProgramDyn :: operator+(CPUProgramDyn& rside){

		//if both *this and rside have no line then it returns empty object.
		//if just rside has no line then it returns *this.
		//if just *this has no line then it returns rside. 
		if(rside.size() == 0 && size() == 0){
			cerr<<"This two objects have no instruction!Adding is fail!"<<endl;
			return CPUProgramDyn(0);
		}
		else if(rside.size() == 0 && size() > 0)
			return *this;
		else if(rside.size() > 0 && size() == 0)
			return rside;
		//if both have lines then the lines of rside are added to *this.
		CPUProgramDyn temp;
		temp = *this;
		for(int i = 0 ; i < rside.size() ; i++)
			temp += rside[i];

		return temp;
	}
	/****************************************************************/
	ostream& operator <<(ostream& output, const CPUProgramDyn& cProgram){

		
		if(cProgram.size() < 0){
			cerr<< "ERROR!! Invalid CPUProgramDyn!!\n";
			//exit(1);
		}
		else if(cProgram.size() == 0){
			//if the program han no instruction then returned empty str.
			output << "";
			return output;
		}

		//else returned cprogram line by line.
		for (int i = 0 ; i < cProgram.size(); ++i)
		{
			output << cProgram[i];
			if(i < cProgram.size() -1)
				output << endl;
		}

		return output;
	}
	/***************************************************************/
	//comparasion overloding.
	bool CPUProgramDyn :: operator==(CPUProgramDyn& rside)const{
		return (this->size() == rside.size());
	}
	bool CPUProgramDyn :: operator!=(CPUProgramDyn& rside)const{
		return !(*this == rside);
	}

	bool CPUProgramDyn :: operator<=(CPUProgramDyn& rside)const{
		return (*this == rside || this->size() < rside.size());
	}
	bool CPUProgramDyn :: operator>(CPUProgramDyn& rside)const{
		return (!(*this <= rside));
	}

	bool CPUProgramDyn :: operator>=(CPUProgramDyn& rside)const{
		return (*this == rside || this->size() > rside.size());
	}
	bool CPUProgramDyn :: operator<(CPUProgramDyn& rside)const{
		return (!(*this >= rside));
	}
	/***************************************************************/

	CPUProgramDyn CPUProgramDyn :: operator-- (int ignore){
		//in this part created a new temp object and deleting a line from
		// *this object then returned temp object.
		CPUProgramDyn temp;
		
		temp = *this;

		if(this->size() > 0)
			this->used--;
		else{
			cerr<<"The CPUProgramDyn that you want to delete a line from";
			cerr<< " is empty!! Deleting Fail!! Nothing has been deleted."<<endl;
			return *this;
		}
		return temp ;
	}

	CPUProgramDyn& CPUProgramDyn :: operator-- (){
		//in this part directly a line is deleted from *this object then
		// it is returned.

		if(this -> size() > 0)
			this->used--;
		else{
			cerr<<"The CPUProgramDyn that tou want to delete a line from";
			cerr<< " is empty!! Deleting Fail!! Nothing has been deleted."<<endl;
			return *this;
		}

		return *this;
	}
	/****************************************************************/
	CPUProgramDyn CPUProgramDyn :: operator()(int first , int second){

		CPUProgramDyn temp;
		//if second index is greater than lines number than returned empty
		// object(temp)
		if(second > size() -1 || first > size() -1 || second < 0 || first < 0){
			cerr<<"EROOR!Unaccessible range !!\n";
			return temp;
		}

		if(second <= first){
			cerr<<"ERROR!! First index must be smaller than second index";
			cerr<<" for () operator."<<endl;
			return temp;
		}
		//in here , created temporary vector to hold the instruction between the
		// the index of first to second.
		for (int i = first; i <= second; ++i)
			temp.addLine(this->instruction[i]);

		return temp ;
	}
	/*****************************************************************/
}
