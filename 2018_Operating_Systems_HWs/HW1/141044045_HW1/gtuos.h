#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"

#define PRINT_B    1
#define PRINT_MEM  2
#define READ_B     3
#define READ_MEM   4
#define PRINT_STR  5
#define READ_STR   6
#define GET_RND    7


#define PRINT_B_CYCLES    10
#define PRINT_MEMB_CYCLES 10
#define READ_B_CYCLES     10
#define READ_MEM_CYCLES   10
#define PRINT_STR_CYCLES  100
#define READ_STR_CYCLES   100
#define GET_RND_CYCLES    5

class GTUOS{
	public:
		GTUOS();
		uint64_t handleCall(const CPU8080 & cpu);
		bool writeMemoryToFile(const CPU8080 & cpu);
		

	private:
		uint64_t getCyclesTime();
		uint64_t cycles;
};

#endif
