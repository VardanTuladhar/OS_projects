#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include "operation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;
class process{
	private:
		string state;
		int process_num, total_cycles;
		int priority;	
	public:
		int get_process_num();		
		vector <operation> process_operations;
		process(string templat, int a);
		void setpriority(int a);
		void display_process();
		int get_total_cycles();
		void set_state (string a);
		int getpriority();
		string get_currentopname();
		int get_currentopcycle();
		void dec_currentopcycle(bool &crit);
		bool current_op_crit();
};
#endif
