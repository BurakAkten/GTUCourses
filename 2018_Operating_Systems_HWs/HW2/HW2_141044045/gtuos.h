#ifndef H_GTUOS
#define H_GTUOS

#include <vector>
#include "8080emuCPP.h"

//functions
#define PRINT_B    1
#define PRINT_MEM  2
#define READ_B     3
#define READ_MEM   4
#define PRINT_STR  5
#define READ_STR   6
#define GET_RND    7
#define TExit      8
#define TJoin	   9
#define TYield	   10
#define TCreate    11

//cycles
#define PRINT_B_CYCLES    10
#define PRINT_MEMB_CYCLES 10
#define READ_B_CYCLES     10
#define READ_MEM_CYCLES   10
#define PRINT_STR_CYCLES  100
#define READ_STR_CYCLES   100
#define GET_RND_CYCLES    5
#define TExit_CYCLES 	  50
#define TJoin_CYCLES  	  40
#define TYield_CYCLES	  40
#define TCreate_CYCLES	  80


#define MAX_THREAD_SIZE   10
#define QUANTUM_TIME 	  100



//thread states
typedef enum {	
	READY = 0,
	RUNNING = 1,
	BLOCKED = 2

}Thread_State;
 

using namespace std;


typedef struct Thread{

	bool usable;                 //if false that mean it has not fnish the job

	Thread_State thread_state; 	 //state of the thread ready , blocked , running

	State8080 state;			 //for cpu registers
	
	uint16_t thread_ID; 		 //thread id
	
	uint64_t starting_time; 	 //starting time of the thread
	
	uint64_t used_cycles; 		 //cycles that the thread used so far
		
	uint64_t addressOfFunc; 	 //address of thethread function
	//empty stack space
}Gtu_Thread;



class GTUOS{
	public:
		GTUOS(CPU8080* cpu , int debug);
		uint64_t handleCall();
		bool writeMemoryToFile();
		uint64_t execute();
		
	private:
		CPU8080* Gtu_Cpu;
		uint64_t cycles;
		vector<Gtu_Thread> thread_table;
		int debug;
		int thread_count;
		uint16_t running_thread_ind;
		uint16_t last_ID;
		////////////////////////
		void contextSwitch( uint16_t next_t_ind);
		uint8_t getAnotherProcID()const;

		bool isAllThreadFinish();
		uint64_t getCyclesTime();
		uint8_t thread_Create();
		uint8_t thread_Exit();
		uint8_t thread_Join();
		uint8_t thread_Yield();

		
};



#endif
