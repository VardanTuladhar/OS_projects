#include <string>
#include <vector>
#include "process.h"
#include "operation.h"
#include "PCB.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
PCB :: PCB(process a)
	{
		vector <string> Registers = {"$v0", "$v1", "$a0","a1", "$t0", "$t1", "$t2","t3", "$t4", "$t5", "$t6","t7", "$t8", "$t9", "$t10","s1", "s0" };
		vector <string> Possible_files_open = {"file.txt", "file1.txt"};
		vector <string> PIO = {"mouse", "keyboard", "camera"};
		process_state = a.state;
		process_number = a.process_num;
		srand(time(NULL));
		int num_regu, num_openf, num_IO;
		num_regu = rand()% + Registers.size();
		num_openf = rand() % + Possible_files_open.size();
		num_IO = rand() % + PIO.size();
		int reg_choice,file_choice, IO_choice;
		for(int i = 0; i < num_regu; i++)
			{
				reg_choice = rand() % + Registers.size();
				Registers_used.push_back(Registers[reg_choice]);
				Registers.erase(Registers.begin() +reg_choice);	
			}
		for(int i = 0; i < num_openf; i++)
			{
				file_choice = rand() % + Possible_files_open.size();
				open_files.push_back(Possible_files_open[file_choice]);
				Possible_files_open.erase(open_files.begin() +file_choice);	
			}
		for(int i = 0; i < num_IO; i++)
			{
				IO_choice = rand() % + PIO.size();
				IO.push_back(PIO[IO_choice]);
				PIO.erase(open_files.begin() +IO_choice);	
			}
	
	}
void PCB :: update_state(process a)
	{
		process_state = a.state;
	}
