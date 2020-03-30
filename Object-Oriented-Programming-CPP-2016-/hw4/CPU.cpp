/*
 * File:CPU.cpp
 *Author:Burak AKTEN
 *
 *
 *Created on November 12 in 2016
 *
 *
 */

#include "CPU.h"
#include "Memory.h"
#include <iostream>
#include <string>

using namespace std;
//Constructors
CPU :: CPU() : CPU(0){
	//when user create object without any parameters.
}
CPU :: CPU(int newOption){
	setOption(newOption);
	setPC(1);
	setRegisters(0,0,0,0,0);
}
CPU :: CPU(int r1,int r2,int r3,int r4,int r5,int pc){
    setRegisters(r1,r2,r3,r4,r5);
    setPC(pc);
}
//setters
void CPU :: setOption(int newOption){
	if(newOption >= 0 && newOption <= 2)
		option = newOption;
	else{
		cerr << "Undefined option!"<<endl;
		exit(1);
	}
}
void CPU :: setRegisters(int r1,int r2,int r3,int r4,int r5){
	//setting the registers
    reg[0] = r1;
    reg[1] = r2;
    reg[2] = r3;
    reg[3] = r4;
    reg[4] = r5;
}
void CPU :: setPC(int pc){//sets the program counter

	PC = pc;
}
void CPU ::  setInst(string myInst){

    inst = myInst;
}
//getter functions.
int CPU :: getOption(){
	return option;
}
int CPU :: getPC()const{
    return PC;
}
int CPU :: getReg(int index)const{
    return reg[index];
}
//////////////////////////////////////////////////////////////////////////
void CPU :: print()const{//prints registers and PC on the screen.
    
    cout << "CPU Register Values :"<<endl;
	for (int i = 0; i < SIZE; ++i)
	{
		cout << "["<<i<<"] -> "<<getReg(i)<<" ";
	}
	cout <<endl<< "CPU PC Value : "<<endl<<getPC()<<endl;
}
bool CPU :: halted()const{
	//returns the value of flag.
	return flag;
}
string CPU :: getInst(){
	//this function clean the string thaht is called myInst and return the 
	//clean string.

    string txt = "" , txt2 = "" ;
    //if instruction has space or spaces from the beginning and end, 
    // the function will remove them.
    eraseSpace(inst);
    
  	//it's the first 3 letters in the instruction after fixed.
    txt = inst.substr(0 , 3);
    //it's the string that come after first 3 letters.
    txt2 = &inst[3];
     
    //making the letters in txt and txt2 upper-case
    makeUpper(txt);
    makeUpper(txt2);

    if(txt2 != ""){
    	eraseSpace(txt2);
    	if(txt == "HLT" && txt2[0] == ';')
    	//if txt2 begins with ';' its mean this string is comment.
    		txt2 = "";
    	else if(txt2[0]!='R' && !(txt2[0]>='0'&&txt2[0]<='9')&&txt2[0]!= '#')
    	//this part control if there is any character different from them after
    	//first three letters then if there is it returns empty string.
    		return "";
    }
    //str is the all string to be returned.
    string str = txt , tempStr = txt2;
    txt = "";
    txt2 = "";

    if(tempStr != "")//in there , sub-string is found , if tempStr isn't empty.
    	findSubStr(txt ,txt2 , tempStr);

    //returns the instruction clearly.
    if(str == "HLT" && txt != "")// if str is HLT and txt isn't empty returns ""
    	return "";
    else if(txt == "" && txt2 == "" && str == "HLT")
    	return str;
    else if(txt2 != "" && txt != "")
        return str + " " + txt + "," + txt2;
    else if(txt != "" && txt2 == "" && (str == "JMP" || str == "PRN"))
    	return str + " " + txt;
    return "";   
     
}
bool CPU ::execute(string instruction , Memory& myMemory){
	//intruction is executed here.

	flag = false;

    string mov="MOV",jmp="JMP" , sub="SUB" , add="ADD" , prn="PRN" ,hlt="HLT";
    string  Jpn = "JPN" ,txt , txt2 ; // for substrings from instruction.
    
    //to clear instruction , setting new string for instruction
    setInst(instruction);
    
    //instruction is made clear .
    instruction = getInst();
    
    if(instruction == ""){
        //if this parts works , it's mean this function was called
        //directly.
        //Because the controlling of invalid instruction is made in
        // the execute function of computer class.
        cerr << "ERROR!! Invalid Instruction!"<<endl;
        exit(1);
    }
    //first 3 letters to compare for which function must be called
    txt = instruction.substr(0 , 3);
    //the string after first three elements for what program have to do.
    // for example, if txt = mov , txt2 = r1 ,r2 , then the function call
    // move and do its staff.
    txt2 = &instruction[3];
    
    //to execute the instruction,txt is controlling for which one must be done
    //(mov or jmp or....) then PC is updated if instruction can be executed.
    if(txt == mov){
        if(move(txt2 , myMemory))
            setPC(PC + 1);
        else
            return false;
    }
    else if(txt == jmp || txt == Jpn){

        if(!jump(txt2 , txt))
            return false;
    }
    else if(txt == sub || txt == add){
        int minusOrPlus = (txt == add ? 1 : -1); 
        if(subOrAdd(txt2 , minusOrPlus , myMemory))
            setPC(PC + 1);
        else 
            return false;
    }
    else if(txt == prn){
        if(prnt(txt2 , myMemory))
            setPC(PC + 1);
        else
            return false;
    }
    else if(txt == hlt){
        halt();
        setPC(PC + 1);
    }
    else 
    	return false;
    return true;
}
namespace{
	void eraseSpace(string& str){  
		//first loop finds the spaces from the beginning and erase it
		//until no space.
		//second loop finds again spaces but in this time from the end.
	    int index = str.find_first_of(' ');
	    while(index == 0 && str.size() > 0){
			str.erase(index , 1);
	    	index = str.find_first_of(' ');
	    }
	    
	    index = str.find_last_of(' ');
	    while(index == (str.size() - 1) && str.size() > 0){
	    	str.erase(index , 1);
	    	index = str.find_last_of(' ');
	    }
	    /////////////////////////////////////////////////////
	    //This part does same thing for TAB(	)
		index = str.find_first_of('	');
	    while(index == 0 && str.size() > 0){
			str.erase(index , 1);
	    	index = str.find_first_of('	');
	    }
	    
	    index = str.find_last_of('	');
	    while(index == (str.size() - 1) && str.size() > 0){
	    	str.erase(index , 1);
	    	index = str.find_last_of('	');
	    }
	}
	void makeUpper(string& txt){
	    // this function make all the letter in the txt string upper-case
	    for(int i = 0 ; i < txt.size() ; ++i)
	        if(txt[i] >= 'a' && txt[i] <= 'z')
	            txt[i] -= 'a' - 'A';
	}
	void findSubStr( string& txt , string& txt2, string str){
	    
	    txt = "";
	    txt2 = "";
	    // firstly make the strings that is given empty.

	    int index = str.find_first_of(',');
	    if(index >= 0){//control of comma 
	        txt = str.substr(0 , index);

	        int index2 = str.find_first_of(';');

	        if(index2 >= 0)//control of semi colon
	            txt2 = str.substr(index + 1 , index2 - (index + 1));
	        else
	            txt2 = str.substr(index + 1 , str.size() - (index + 1));
			// erase the unneeded spaces from the beginning and the end.
	        eraseSpace(txt2);
	    }
	    else{//control of semi colon
	        index = str.find_first_of(';');

	        if(index > 0)
	            txt = str.substr(0 , index);
	        else
	            txt = str.substr(0 , str.size());
	    }
	    eraseSpace(txt);
	}   
	bool isAllNumber(string txt){
	    //this function control if the all the character in the string
	    // is number and if it is return true.
	    bool ctrl = true;
	    for(int i = 0 ; i < txt.size(); ++i)
	        if(!(txt[i] >= '0' && txt[i] <= '9'))
	            ctrl = false;
	    return ctrl;
	}
	bool controlTxt(string txt , string str[]){
		//this function searc the txt in the str[] and if it finds , 
		//returns true.
	    for(int i = 0; i < SIZE ; ++i)
	        if(txt == str[i])
	            return true;
	    return false;
	} 
	int convertStrToInt(string str){
		//len represents the length of the str
	    int len = str.length() , sum = 0;
	    int temp = len;

	    //in the fisrt loop , every index is converted to integer 
	    //and in the second loop , sum is updated for each number.
	    //after pow.
	    for(int i = 0 ; i < len; ++i ,--temp){
	        int pow = 1 ;
	        for(int j = 1 ; j <= temp - 1 ; j++ )
	            pow *= 10;
	        sum += (str[i] - 48) * pow;
	    }
	    return sum;
	}
}
bool CPU :: subOrAdd(string str,int value,Memory& myMemory){
  
    string strReg[] = {"R1","R2","R3","R4","R5"};
    string txt = "" , txt2 = "";
  
    findSubStr(txt ,txt2 , str);

    //after call the findSubStr, this function make its staff
    // according to rules.
    // if value is minus one , then function make subruction,
    // otherwise addition.

    //if txt2 is number and txt is register
    if(isAllNumber(txt2) && controlTxt(txt , strReg )){
        
    	for(int i = 0 ; i < SIZE ; ++i)
            if(txt == strReg[i])
       		reg[i] = reg[i] + (value) * convertStrToInt(txt2);
    }
    else if(controlTxt(txt , strReg ) && controlTxt(txt2, strReg )){
   		//if txt and txt2 are both register.
    	for(int i = 0 ; i < SIZE ; ++i)
            for(int j = 0 ; j < SIZE ; ++j)
    			if(txt == strReg[i] && txt2 == strReg[j])
                    reg[i] = reg[i] + (value) * reg[j];
    }
    else if(controlTxt(txt,strReg) && txt2[0]=='#' && isAllNumber(&txt2[1])){
    	//if txt is a register and  txt2 is accessibe memory location,
    	// then this part will be run.
    	if(convertStrToInt(&txt2[1]) >= myMemory.getSize())
    		return false;

    	for(int i = 0 ; i < SIZE ; ++i)
    		if(txt == strReg[i])
            	reg[i] +=(value)*myMemory.getMem(convertStrToInt(&txt2[1]));	
    }
    else 
        return false;
    return true;
}
bool CPU :: move(string str , Memory& myMemory){
    string strReg[] = {"R1","R2","R3","R4","R5"};
    string txt = "" , txt2 = "";
  
    findSubStr(txt ,txt2 , str);

    //this function make its satff like subOrAdd function.
 	// use the same tecnique.
    if(isAllNumber(txt2) && controlTxt(txt , strReg ) ){
 		//constant to register
        for(int i = 0 ; i < SIZE ; ++i)
            if(txt == strReg[i])
                reg[i] = convertStrToInt(txt2);
    }
    else if(controlTxt(txt , strReg ) && controlTxt(txt2, strReg)){
    	//register to register
    	for(int i = 0 ; i < SIZE ; ++i)
            for(int j = 0 ; j < SIZE ; ++j)
    		if(txt == strReg[i] && txt2 == strReg[j])
                    reg[j] = reg[i];
    }
    else if(controlTxt(txt,strReg) && txt2[0]=='#' && isAllNumber(&txt2[1])){
    	//register to memory
    	if(convertStrToInt(&txt2[1]) >= myMemory.getSize())
    		return false;

    	for(int i = 0 ; i < SIZE ; ++i)
    		if(txt == strReg[i])
    			myMemory.setMem(convertStrToInt(&txt2[1]) , reg[i]);
    }
    else if(controlTxt(txt2,strReg) && txt[0]=='#' && isAllNumber(&txt[1])){
    	//memory to register
    	if(convertStrToInt(&txt[1]) >= myMemory.getSize())
    		return false;

   		for(int i = 0 ; i < SIZE ; ++i)
        	if(txt2 == strReg[i])
     			reg[i] = myMemory.getMem(convertStrToInt(&txt[1]));
    }
    else if(isAllNumber(txt2) && txt[0]=='#' && isAllNumber(&txt[1])){
    	//constant to memory
    	if(convertStrToInt(&txt[1]) >= myMemory.getSize())
    		return false;
    	myMemory.setMem(convertStrToInt(&txt[1]) , convertStrToInt(txt2));
    }
    else
        return false;
    return true;
}  
bool CPU :: prnt(string str , Memory& myMemory){

    string strReg[] = {"R1","R2","R3","R4","R5"};
    string txt = "" , txt2 = "";
    
    findSubStr(txt ,txt2 , str);

    //this function prints on the screen a value of a register
    // or a constant in string txt2 or the value in a memory

    //if txt2 is empty it returns false.
    if(txt2 != "")
        return false;
    else if(isAllNumber(txt))//if txt is a number
        cout << " <" <<convertStrToInt(txt)<< "> "<<endl ;
    else if(controlTxt(txt , strReg)){//if txt is a register
        
    	for(int i = 0; i < SIZE ; ++i)
            if(txt == strReg[i])
                cout << "<"<<reg[i] << ">"<<endl;
    }
    else if(txt[0] == '#' && isAllNumber(&txt[1])){
    	//if txt represents a memory location.
    	if(convertStrToInt(&txt[1]) >= myMemory.getSize())
    		return false;

    	cout << "<"<<myMemory.getMem(convertStrToInt(&txt[1]))<<">"<<endl;  
    }
    else
        return false;
    return true;
}
bool CPU :: jump(string str , string str2){
    string strReg[] = {"R1","R2","R3","R4","R5"};
    int currentLine = PC ;
    string txt = "" , txt2 = "";
    
    findSubStr(txt ,txt2 , str);
    //İf txt2 is empty then it must be number and txt must be register.
    if(txt2 != "" && isAllNumber(txt2) && controlTxt(txt , strReg)){

        int line = convertStrToInt(txt2); 
     	
     	//if str2 is JMP then calls the jump2 otherwise jpn 
     	// with the parameter txt. Then jumpVal will be 
     	// initialized.
        int jumpVal = (str2 == "JMP") ? jump2(txt) : jpn(txt);

        //PC is getting updated to line or PC + 1
        PC = ((jumpVal) ? line : PC + 1); 
    }
    else if(txt2 == "" && isAllNumber(txt)){
        //if txt2 is empty then txt must be number to jump.
        int line = convertStrToInt(txt);
        if(line > currentLine || line < currentLine)
           setPC(line);
        else
            setPC(PC + 1);
    }
    else
        return false;
    return true;
}
int CPU :: jump2(string txt){
	//If txt represents a register , and if the register is zero
	// then function returns 1.
    string strReg[] = {"R1","R2","R3","R4","R5"};
    bool ctrl = false;

    for(int i = 0 ; i < SIZE; ++i){
    	if(txt == strReg[i] && reg[i] == 0)
    		ctrl = true;
    }
    if(ctrl)
    	return 1;
    return 0;
}
int CPU :: jpn(string txt){
	//If txt represents a register , and if the register is zero or 
	//smaller than zero,
	//then function returns 1.
    string strReg[] = {"R1","R2","R3","R4","R5"};
    bool ctrl = false;

    for(int i = 0 ; i < SIZE ; ++i){
    	if(txt == strReg[i] && reg[i] <= 0)
    		ctrl = true;
    }
    if(ctrl)
    	return 1;
    return 0;
}
void CPU :: halt(){
    
    flag = true;
}
