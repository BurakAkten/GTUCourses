#include "8080emuCPP.h"
#include "gtuos.h"
//#define DEBG 

using namespace std;

GTUOS :: GTUOS(CPU8080* cpu , int debug , string fileSystem){

	this->Gtu_Cpu = cpu;

	this->debug = debug;

	this->fileSystemFile = fileSystem;

	this->open_file_table = vector<GTU_FILE>();

	binaryFileToTable();

	this->thread_table = vector<Gtu_Thread >();

	Gtu_Thread thread;

	thread_table.push_back(thread);

	this->thread_table[0].thread_state = RUNNING;
	this->thread_table[0].state = *(Gtu_Cpu->state);
	this->thread_table[0].thread_ID = 1; //thread id is index
	this->thread_table[0].starting_time = 0;
	this->thread_table[0].used_cycles = 0;
	this->thread_table[0].addressOfFunc = Gtu_Cpu->state->pc; //beginning
	this->thread_table[0].usable = true; //usable


	this->last_ID = 1;
	this->thread_count = 1;
	this->running_thread_ind = 0;
	this->cycles = 0;
	this->openFileID = 0;
}


void GTUOS:: binaryFileToTable(){
	int size ;
	
	//open the  .dat file  and read into a vector
	const char* name = this->fileSystemFile.c_str();


	systemFile = fopen(name, "r");
	if(systemFile == NULL){
		cerr << "There is no such file ("<<this->fileSystemFile <<")!"<<endl;
		exit(1);
	}

	GTU_FILE new_open_file;
	while(fread(&new_open_file, sizeof(GTU_FILE), 1, systemFile)){
		open_file_table.push_back(new_open_file);
	}

	fclose(systemFile);
	
}

uint64_t GTUOS::handleCall(){

	uint8_t regA = Gtu_Cpu->state->a;
	uint64_t cycleOfCall = 0;

	
	switch(regA){
		case PRINT_B:{

			//cout << "--------PRINT_B--------"<<endl;
			cout <<"Content of Reg B : " <<  (int)(Gtu_Cpu->state->b) <<endl;

			cycleOfCall = PRINT_B_CYCLES;

		}break;
		case PRINT_MEM:{

			//cout << "--------PRINT_MEM--------"<<endl;

			//find the address to get the context
			uint16_t address = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;
			cout << "Content of the memory pointed by Reg A and Reg B: ";
			cout << (int)Gtu_Cpu->memory->at(address)<<endl;

			cycleOfCall = PRINT_MEMB_CYCLES;
		}break;
		case READ_B:{

			//cout << "--------READ_B--------"<<endl;

			int value ;
			cout << "Please enter an integer for reg B in range 0 to 255!: ";
			cin >> value;

			//if the number is bigger than 256 than make the content of the reg B 0.
			Gtu_Cpu->state->b = value >= 0 && value <= 255 ? value : 0 ;

			//then give the info about that.
			if(Gtu_Cpu->state->b == 0)
				cerr << "The register called B is assigned to 0 because of BOUND_ERROR"<<endl;

			//Gtu_Cpu.state->b = value;

			cycleOfCall = READ_B_CYCLES;
		}break;
		case READ_MEM:{

			//cout << "--------READ_MEM--------"<<endl;

			int value ;
			cout << "Please enter an integer for memory adress BC in range 0 to 255!: ";
			cin >> value;

			//find the address to get the context
			uint16_t address = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;
			//if the number is bigger than 256 than make the content of the address(BC) 0.
			Gtu_Cpu->memory->at(address) = value >= 0 && value <= 255 ? value : 0 ;
			
			if(Gtu_Cpu->memory->at(address)== 0)
				cerr << "The memory address BC is assigned to 0 because of BOUND_ERROR"<<endl;
			
			cycleOfCall =  READ_MEM_CYCLES;
		}break;
		case PRINT_STR:{

			//cout << "--------PRINT_STR--------"<<endl;

			uint8_t i =  0;
			//find the address to get the context
			uint16_t address = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;

			cout << "The string from the memory pointed by Reg A and Reg B: ";

			//print the string on the screen
			while(Gtu_Cpu->memory->at((address + i) )!= '\0')
				cout <<Gtu_Cpu->memory->at(address+ i++);
			cout << endl;

			cycleOfCall = PRINT_STR_CYCLES;
		}break;
		case READ_STR:{

			//cout << "--------READ_STR--------"<<endl;			

			string str = " 	";
			cout << "Please enter a string: ";
			cin >> str;


			int size = str.size();
			//find the address to get the context
			uint16_t address = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;

			int i = 0;
			for( ; i < size ; i++)
				Gtu_Cpu->memory->at(address + i) = str[i];
			Gtu_Cpu->memory->at(address+ i) = '\n'; //add newline character
			Gtu_Cpu->memory->at(address+ i) = '\0'; //add null character

			cycleOfCall = READ_STR_CYCLES;
		}break;
		case GET_RND:{

			//cout << "--------GET_RND--------"<<endl;

			uint8_t random = rand() % 256; //get random byte
			Gtu_Cpu->state->b = random;
			
			cout << "Random byte is generated to reg B -> "<< (int)random <<endl;

			cycleOfCall = GET_RND_CYCLES;
		}break;
		case TExit:{
			//cout<<"Texit"<<endl;

			thread_Exit();
			cycleOfCall = TExit_CYCLES;
		}break;
		case TJoin:{
			//cout<<"Tjoin"<<endl;

			thread_Join();
			cycleOfCall = TJoin_CYCLES;
		}break;
		case TYield:{
			//cout<<"Tyield"<<endl;

			thread_Yield();
			cycleOfCall = TYield_CYCLES;
		}break;
		case TCreate:{
			//cout<<"Thcreate"<<endl;
			if(thread_Create() == 0)
				return getCyclesTime();

			cycleOfCall = TCreate_CYCLES;
		}break;
		case FileCreate:{
			string filename = getFileName();

			Gtu_Cpu->state->b = fileCreate(filename);

			cycleOfCall = FileCycles; //change
		}break;
		case FileOpen:{
			string filename = getFileName();

			int fileID =  fileOpen(filename);

			Gtu_Cpu->state->b = fileID;

			cycleOfCall = FileCycles; // change
		}break;
		case FileClose: {
			int fileID =  Gtu_Cpu->state->b;

			Gtu_Cpu->state->b = fileClose(fileID);

			cycleOfCall = FileCycles; 
		}break;
		case FileRead  : {

			int bytesToRead		= Gtu_Cpu->state->d;
			int handleID 		= Gtu_Cpu->state->e;
			uint16_t buffer = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;

			Gtu_Cpu->state->b = fileRead(bytesToRead , handleID , buffer);

			cycleOfCall = FileCycles; // change
		}break;
		case FileWrite: {
			int bytesToRead		= Gtu_Cpu->state->d;
			int handleID 		= Gtu_Cpu->state->e;
			uint16_t buffer = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;

			Gtu_Cpu->state->b = fileWrite(bytesToRead , handleID , buffer);

			cycleOfCall = FileCycles; // change
		}break;
		case FileSeek: {
			uint8_t seekValue = Gtu_Cpu->state->b; //???????
			int handleID  = Gtu_Cpu->state->d;

			Gtu_Cpu->state->b = fileSeek(seekValue , handleID);

			cycleOfCall = FileCycles; 

		}break;
		case DirRead :{

			uint16_t buffer = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;
			int j = 0;
			for (int i = 0; i < open_file_table.size(); ++i)
			{	 
				for (;j < strlen(open_file_table[i].name); ++j)
				{
					Gtu_Cpu->memory->at(buffer + j) = open_file_table[i].name[j];
				}
				Gtu_Cpu->memory->at(buffer + j) = ':';
				for (int k = 0;k < strlen(open_file_table[i].context); ++j , k++)
				{
					Gtu_Cpu->memory->at(buffer + j) = open_file_table[i].context[k];
				}
				Gtu_Cpu->memory->at(buffer + j) = '\n';
			}
			Gtu_Cpu->memory->at(buffer + j) = '\n';
			Gtu_Cpu->memory->at(buffer + j) = '\0';



			cycleOfCall = FileCycles; 
		}break;
		default: cerr << "ERROR! Not system call!" << endl; this->cycles = 0; break;
	}
	Gtu_Cpu->state->a = 0;

	return cycleOfCall;
}


string  GTUOS:: getFileName(){
	//get file name from BC
	string fileName; //holds the filename that in the BC.
	uint8_t i =  0;
	//find the address to get the context
	uint16_t address = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;

	while(Gtu_Cpu->memory->at((address + i) )!= '\0')
		fileName += Gtu_Cpu->memory->at(address+ i++);

	return fileName;
}


int GTUOS :: searchFileInTable(string filename){

	for (int i = 0; i < open_file_table.size(); ++i){
		if(open_file_table[i].name == filename)
			return i;
	}
	return -1;
}



int GTUOS :: fileCreate(string filename){

	GTU_FILE new_open_file;
	
	strcpy(new_open_file.name , filename.c_str());
	strcpy(new_open_file.context , "");
	new_open_file.size = 0;
	new_open_file.isOpen = false;
	new_open_file.filePointerR = 0;
	new_open_file.filePointerW = 0;
	new_open_file.ID = open_file_table.size() + 1;
	new_open_file.fileCreation = this->getCyclesTime();
	new_open_file.lastModification = this->getCyclesTime();
	new_open_file.lastAccess = this->getCyclesTime();

	this->open_file_table.push_back(new_open_file);

	return 1;
}

int GTUOS :: fileOpen(string filename){

	int position = searchFileInTable(filename);

	if(position < 0){

		this->fileCreate(filename);
		open_file_table[open_file_table.size() - 1].isOpen = true;
	}
	else{
		open_file_table[position].isOpen = true;

		open_file_table[position].lastAccess = this->getCyclesTime();
		open_file_table[position].filePointerR = 0;
		open_file_table[position].filePointerW = 0;
	}
	return position > 0 ? open_file_table[position].ID : open_file_table[open_file_table.size() - 1].ID;
}

int GTUOS :: fileSeek(int seekValue , int handleID){


	//cout << "seek " << endl;

	for(int j = 0 ; j < open_file_table.size() ; j++){
		if (open_file_table[j].ID == handleID && open_file_table[j].isOpen){
			open_file_table[j].filePointerR = seekValue;
			open_file_table[j].filePointerW = seekValue;
			break;
		}
		else if (open_file_table[j].ID == handleID && !open_file_table[j].isOpen){
			return 0;//fail
		}
	}
	return 1;
}


int GTUOS :: fileRead(int bytesToRead , int handleID , uint64_t buffer){


	//cout << "read"<<endl;

	char c;
	for(int j = 0 ; j < open_file_table.size() ; j++){
		if (open_file_table[j].ID == handleID && open_file_table[j].isOpen){
			uint8_t i = open_file_table[j].filePointerR;
			int k = 0;
			for (; i < strlen(open_file_table[j].context); ++i , k++){
				
				c = open_file_table[j].context[i];

				Gtu_Cpu->memory->at(buffer + k) = c;	
				Gtu_Cpu->memory->at(buffer + k + 1) = '-';	
				open_file_table[j].filePointerR++;

			}
			Gtu_Cpu->memory->at(buffer + k++) = '\n'; //add newline character
			Gtu_Cpu->memory->at(buffer + k) = '\0'; //add null character

			open_file_table[j].lastAccess = this->getCyclesTime();

			bytesToRead = k ; // if bytesToRead is bigger than 255
			break;
		}
		else if (open_file_table[j].ID == handleID && !open_file_table[j].isOpen){
			return 0;//fail
		}
	}
	return bytesToRead;
}

int GTUOS :: fileWrite(int bytesToRead , int handleID , uint64_t buffer){

	//cout << "write" << endl;


	for(int j = 0 ; j < open_file_table.size() ; j++){
		
		if (open_file_table[j].ID == handleID && open_file_table[j].isOpen){
			uint8_t i = open_file_table[j].filePointerW;
			int k = 0;
			for (; Gtu_Cpu->memory->at((buffer + k) )!= '\0'; ++i , k++){
			
				open_file_table[j].context[open_file_table[j].filePointerW] = Gtu_Cpu->memory->at((buffer + k));
				open_file_table[j].filePointerW++;
				open_file_table[j].size++;

				if(strlen(open_file_table[j].context) == 255){
					bytesToRead = i ;
				}
			}
			open_file_table[j].lastModification = this->getCyclesTime();
			open_file_table[j].lastAccess = this->getCyclesTime();
			bytesToRead = k ;
			break;
		}
		else if (open_file_table[j].ID == handleID && !open_file_table[j].isOpen){
			return 0;//fail
		}
	}
	return bytesToRead;
}


int GTUOS :: fileClose(int fileID){

	//cout << "close" << endl;

	for (int i = 0; i < open_file_table.size(); ++i)
	{	
		if(open_file_table[i].ID == fileID){
			open_file_table[i].isOpen = false;
			return 1;
		}
	}
	return 0;
}

void GTUOS :: printDirInfo(){

	cout <<endl<< "Directory INFO::"<<endl;
	cout << "-------->"<<endl;
	for (int i = 0; i < open_file_table.size(); ++i)
	{
		cout << "Name : "<< open_file_table[i].name<<endl;
		cout << "Context : "<<open_file_table[i].context<<endl;
		cout << "lastModification time as cycle : "<<open_file_table[i].lastModification<<endl;
		cout << "lastAccess time as cycle : "<<open_file_table[i].lastAccess<<endl;
	}

}


void GTUOS :: printFileTableInfo(){
	cout <<endl<< "File Table INFO::"<<endl;
	cout << "-------->"<<endl;
	for (int i = 0; i < open_file_table.size(); ++i)
	{
		cout << "Name : "<< open_file_table[i].name<<endl;
		cout << "Context : "<<open_file_table[i].context<<endl;
		cout << "fd for read : "<<open_file_table[i].filePointerR<<endl;
		cout << "fd for write : "<<open_file_table[i].filePointerW<<endl;
		cout << "ID :"<<open_file_table[i].ID<<endl;
		cout << "Size :"<<strlen(open_file_table[i].context)<<endl;
		cout << "lastModification time as cycle : "<<open_file_table[i].lastModification<<endl;
		cout << "lastAccess time as cycle : "<<open_file_table[i].lastAccess<<endl;
	}
}



uint64_t GTUOS :: getCyclesTime(){
	/*This function return the value of cycles*/
	return this->cycles;
}

bool GTUOS:: writeMemoryToFile(){

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
           	line << setfill('0') << setw(2) << hex <<(int)Gtu_Cpu->memory->at(i * 16 + j) << " ";
        line << endl;

        outStream << line.str(); // write the ss object into the output file.
	}

	outStream.close(); //close the output stream

	return true;

}

uint8_t GTUOS :: thread_Create(){

	if (thread_table.size() > MAX_THREAD_SIZE){
		cout << "You can not create a thread !!"<<endl;
		return 0;
	}

	uint16_t funcAddress = Gtu_Cpu->state->b << 8 | Gtu_Cpu->state->c;

	Gtu_Thread new_thread;
	
	new_thread.thread_state = READY;
	new_thread.thread_ID = ++last_ID;
	new_thread.used_cycles = 0;
	new_thread.addressOfFunc = funcAddress;
	new_thread.usable = true; //usable
	new_thread.starting_time = getCyclesTime();
	new_thread.state.pc = funcAddress;

	thread_table.push_back(new_thread);
	this->thread_count++;
	//contextSwitch(thread_table.size() - 1);
	

	//Gtu_Cpu->state->pc = funcAddress;
	return new_thread.thread_ID;
}

uint8_t GTUOS :: thread_Exit(){

	uint16_t exit_status = Gtu_Cpu->state->b; //ask

	thread_table[running_thread_ind].usable = false;

	uint8_t nextProcess; //holds next process index

	while(!isAllThreadFinish()){
		nextProcess = getAnotherProcID();

		if(nextProcess != running_thread_ind){
			int delete_ = running_thread_ind;

			contextSwitch(nextProcess);

			thread_table.erase(thread_table.begin() + delete_);

			if(this->running_thread_ind > delete_)
				this->running_thread_ind--;

			this->thread_count--;

			break;
		}

	}	
	return exit_status;
}

uint8_t GTUOS :: thread_Join(){

	uint16_t id_to_wait = Gtu_Cpu->state->b;
	//cout <<"ID------------------------------>"<< id_to_wait << endl;
	
	for (uint8_t i = 0; i < thread_count; ++i){
		
		if(thread_table[i].usable && thread_table[i].thread_ID == id_to_wait){
			thread_table[running_thread_ind].thread_state = BLOCKED;
			return 0;
		}
	}

	thread_table[running_thread_ind].thread_state = READY;

	return 0;
}

uint8_t GTUOS :: thread_Yield(){
	uint8_t nextProcess; //holds next process index
	if((nextProcess = getAnotherProcID()) != running_thread_ind)
		contextSwitch(nextProcess);
	return 0;
}


uint64_t GTUOS::execute(){

	uint64_t switch_cycles = 0 , temp_cycles = 0;
	uint8_t nextProcess; //holds next process index


	do{
		temp_cycles = Gtu_Cpu->Emulate8080p(debug);

		if(Gtu_Cpu->isSystemCall())
			temp_cycles += this->handleCall();

		this->cycles += temp_cycles;

		switch_cycles += temp_cycles;

		thread_table[running_thread_ind].used_cycles += switch_cycles;

		Thread_State temp_state = thread_table[running_thread_ind].thread_state;
		//to conrol the quantum time is overed or not
		if((switch_cycles >= QUANTUM_TIME || temp_state == BLOCKED) && !Gtu_Cpu->isHalted()){
			
			//cout << "Cycles1 : " << switch_cycles << endl;

			switch_cycles = switch_cycles % QUANTUM_TIME; //update the switch cycle time
			if((nextProcess = getAnotherProcID()) != running_thread_ind)
				contextSwitch(nextProcess);
			continue;
		}


		//if new thread is halted then it mean its finish its job
		if(Gtu_Cpu->isHalted()){
			thread_table[running_thread_ind].usable = false;

			//get another thread
			if((nextProcess = getAnotherProcID()) != running_thread_ind)
				contextSwitch(nextProcess);
			 
			continue;

		}

		temp_state = thread_table[running_thread_ind].thread_state;
		if((switch_cycles >= QUANTUM_TIME || temp_state == BLOCKED)){
			
			//cout << "Cycles : " << switch_cycles << endl;

			switch_cycles = switch_cycles % QUANTUM_TIME; //update the switch cycle time
			if((nextProcess = getAnotherProcID()) != running_thread_ind)
				contextSwitch(nextProcess);
			
			continue;
		}

	}while(!isAllThreadFinish());

	int size = open_file_table.size();

	//systemFile.open(this->fileSystemFile , ios::binary | ios::out | ios::trunc);

	const char* name = this->fileSystemFile.c_str();

	systemFile = fopen(name , "w");
	
	if (systemFile == NULL)
	{
		cerr << "There is no such file ("<<this->fileSystemFile <<")!"<<endl;
		exit(1);
	}

	for (int i = 0; i < size; ++i)
	{
		GTU_FILE new_open_file = open_file_table[i];

		fwrite (&new_open_file, sizeof(GTU_FILE), 1, systemFile);


	}

	fclose(systemFile);

	if(debug = 1)
		printFileTableInfo();

	printDirInfo();


	return getCyclesTime();
}


void GTUOS :: contextSwitch( uint16_t next_t_ind){

	#ifdef DEBG
		cout << "Context Switch!" << endl ;
	#endif
	if(debug == 2){
		cout << "Context switching occurs between thread_ID : " << running_thread_ind << " and thread_ID : " << next_t_ind << endl;
		cout << "Cycles for first one: " << thread_table[running_thread_ind].used_cycles <<" Cycles for second one: "<<thread_table[next_t_ind].used_cycles<<endl;
	}
	else if(debug == 3){
		for (uint8_t i = 0; i < thread_count; ++i){
		
			cout << "Thread_ID :                                         " << thread_table[i].thread_ID << endl;
			cout <<" Thread_State (READY = 0 , RUNNING = 1 , BLOCKED =2) " << thread_table[i].thread_state << endl;
			cout << "Thread_starting_time                                " << thread_table[i].starting_time << endl;
			cout << "Thread_used_cycles                                  " << thread_table[i].used_cycles << endl;
			cout << "Thread_address_of_function                          " << thread_table[i].addressOfFunc << endl;
		}
	}


	thread_table[running_thread_ind].state = *(Gtu_Cpu->state);
	if (thread_table[running_thread_ind].thread_state != BLOCKED)
    	thread_table[running_thread_ind].thread_state = READY;

    *(Gtu_Cpu->state) = thread_table[next_t_ind].state;
  	thread_table[next_t_ind].thread_state = RUNNING;


  	this->running_thread_ind = next_t_ind; //change running index of thread
}

uint8_t GTUOS::getAnotherProcID() const {

  for (uint8_t i = running_thread_ind + 1; i < thread_count; i++)
    if (thread_table[i].usable && thread_table[i].thread_state == READY) 
      return i;

  // if there is not READY process forward locations
  for (uint8_t i = 0; i < running_thread_ind; i++)
    if (thread_table[i].usable && thread_table[i].thread_state == READY)
      return i;

  // there is just one process
  return running_thread_ind;
}

bool GTUOS :: isAllThreadFinish(){
	//control that all thread is not finished
	for (uint8_t i = 0; i < thread_count; ++i)
		if(thread_table[i].usable)
			return false;

	return true;
}