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
		PCB *ThePCB;
		vector <operation> process_operations;
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
		//decrement the processes current cylce
		void decrement();




	     };	
#endif
