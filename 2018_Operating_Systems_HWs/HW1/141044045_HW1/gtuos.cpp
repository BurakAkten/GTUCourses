#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "8080emuCPP.h"
#include "gtuos.h"

using namespace std;

GTUOS :: GTUOS(){
	/*constructor initialize cycles to 0*/
	this->cycles = 0;
}

uint64_t GTUOS::handleCall(const CPU8080 & cpu){

	uint8_t regA = cpu.state->a;
	
	switch(regA){
		case PRINT_B  :{

			//cout << "--------PRINT_B--------"<<endl;
			cout <<"Content of Reg B : " <<  (int)(cpu.state->b) <<endl;

			this->cycles = PRINT_B_CYCLES;

		} break;
		case PRINT_MEM: {

			//cout << "--------PRINT_MEM--------"<<endl;

			//find the address to get the context
			uint16_t address = cpu.state->b << 8 | cpu.state->c;
			cout << "Content of the memory pointed by Reg A and Reg B: ";
			cout << (int)cpu.memory->at(address)<<endl;

			this->cycles = PRINT_MEMB_CYCLES;

		}break;
		case READ_B   : {

			//cout << "--------READ_B--------"<<endl;

			int value ;
			cout << "Please enter an integer for reg B in range 0 to 255!: ";
			cin >> value;

			//if the number is bigger than 256 than make the content of the reg B 0.
			cpu.state->b = value >= 0 && value <= 255 ? value : 0 ;

			//then give the info about that.
			if(cpu.state->b == 0)
				cerr << "The register called B is assigned to 0 because of BOUND_ERROR"<<endl;

			//cpu.state->b = value;

			this->cycles = READ_B_CYCLES;

		} break;
		case READ_MEM : {

			//cout << "--------READ_MEM--------"<<endl;

			int value ;
			cout << "Please enter an integer for memory adress BC in range 0 to 255!: ";
			cin >> value;

			//find the address to get the context
			uint16_t address = cpu.state->b << 8 | cpu.state->c;
			//if the number is bigger than 256 than make the content of the address(BC) 0.
			cpu.memory->at(address) = value >= 0 && value <= 255 ? value : 0 ;
			
			if(cpu.memory->at(address)== 0)
				cerr << "The memory address BC is assigned to 0 because of BOUND_ERROR"<<endl;
			
			this->cycles =  READ_MEM_CYCLES;

		} break;
		case PRINT_STR:{

			//cout << "--------PRINT_STR--------"<<endl;

			uint8_t i =  0;
			//find the address to get the context
			uint16_t address = cpu.state->b << 8 | cpu.state->c;

			cout << "The string from the memory pointed by Reg A and Reg B: ";

			//print the string on the screen
			while(cpu.memory->at((address + i) )!= '\0')
				cout <<cpu.memory->at(address+ i++);
			cout << endl;

			this->cycles = PRINT_STR_CYCLES;

		}  break;
		case READ_STR : {

			//cout << "--------READ_STR--------"<<endl;			

			string str = " 	";
			cout << "Please enter a string: ";
			cin >> str;


			int size = str.size();
			//find the address to get the context
			uint16_t address = cpu.state->b << 8 | cpu.state->c;

			int i = 0;
			for( ; i < size ; i++)
				cpu.memory->at(address + i) = str[i];
			cpu.memory->at(address+ i) = '\n'; //add newline character
			cpu.memory->at(address+ i) = '\0'; //add null character

			this->cycles = READ_STR_CYCLES;

		} break;
		case GET_RND  : {

			//cout << "--------GET_RND--------"<<endl;

			uint8_t random = rand() % 256; //get random byte
			cpu.state->b = random;
			
			cout << "Random byte is generated to reg B -> "<< (int)random <<endl;

			this->cycles = GET_RND_CYCLES;

		}break;

		default: cerr << "ERROR! Not system call!" << endl;  this->cycles = 0 ; break;
	}
	return getCyclesTime();
}

uint64_t GTUOS :: getCyclesTime(){
	/*This function return the value of cycles*/
	return this->cycles;
}

bool GTUOS:: writeMemoryToFile(const CPU8080 & cpu ){

	ofstream outStream; // create outstream object to write to the file
	outStream.open("exe.mem"); // open the file that is called "exe.mem"

	if(!outStream.is_open()){ //if this file couldn't open than return false.
		outStream.close();
		return false;
	}

	for (uint16_t i=0; i<0x1000; i++)
	{
		stringstream line; // this object represent each line to be printed the output file.

		//calculate the address and write into the ss object
		line << "0x" << setfill('0') << setw(5) << hex << i * 16 << " "; 
		
		//put the values from the address into the ss object 
		for(int j=0;j<0x10;++j) 
           	line << setfill('0') << setw(2) << hex <<(int)cpu.memory->at(i * 16 + j) << " ";
        line << endl;

        outStream << line.str(); // write the ss object into the output file.
	}

	outStream.close(); //close the output stream

	return true;

}
