#include <string>
#include <vector>
#include "process.h"
#include "operation.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
PCB :: PCB(process a)
	{
		vector <string> Registers = {"$v0", "$v1", "$a0","a1", "$t0", "$t1", "$t2","t3", "$t4", "$t5", "$t6","t7", "$t8", "$t9", "$t10","s1", "s0" };
		vector <string> Possible_files_open = {"file.txt", "file1.txt"}
		vector <string> PIO = {"mouse", "keyboard", "camera"}
		process_state = a.state;
		process_number = a.num;
		address_instruct = &a.operation[1];		
		srand(time(NULL));
		int num_regu, num_openf, num_IO;
		num_regu = rand()% + Registers.size();
		num_openf = rand() % + Possible_files_open.size();
		num_IO = rand() % + PIO.size();
		for(int i = 0; i < num_regu; i++)
			{
				
			}









	}
