#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <vector>
#include "operation.h"
#include "PCB.h"
using namespace std;
class process{
	private:
		int process_num, total_cycles;
		int priority;
		int child_processes;
		string state;	
	//	PCB *ThePCB;
		//vector <string> memory_location;
		vector <operation> process_operations;
		int total_size;
		vector<vector<int>> page_table;
	public:
		//set the process up
		process();
		//set PCB
		void set_PCB(PCB &a);
		//set operations
		void set_operations(string temp, int j);
		//set process number
		void set_process_num(int a);
		//set the priority
		void setpriority(int a);
		//get the priority
		int get_priority();
		//get the state
		string get_state();
		//set the state
		void set_state(string updated_state);
		//get the process num
		int get_process_num();
		//get the total cycles 
		int get_total_cycles();
		//operation vector size
		int get_operations_size();
		//get current operation name
		string get_operation_name(int a);
		//get the current operations cycles
		int get_operation_cycles(int a);
		int get_crit(int a);
		//decrement the processes current cylce
		void decrement(bool &a);
		//set the page table
		void set_page_table(int page, int frame, int valid, string mem);
		//get the page
		int get_page_frame(int page);
		//get the valid bit
		int get_valid(int page);
		//string get_mem_loc(int page);


	     };	
#endif
