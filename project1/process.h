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
		vector <operation> process_operations;
	public:
		//set the process up
		process();
		//set operations
		void set_operations(string temp);
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



	     };	
#endif
