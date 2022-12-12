#ifndef COREH
#define COREH
#include <iostream>
#include "process.h"
#include "PCB.h"
#include "OS_functions.h"
#include "frame.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
using namespace std;
class core{
	private:
		vector <process> new_queue;
		vector <process> ready_queue;
		vector <process> wait_queue;
		vector <process> running;
		vector <process> terminated;

	public:
		core(vector <process> &new_process);
		void run_core(frame *main, frame *virt,int cc, string core , int schedule);  
		vector <process> get_new_state();
		vector <process> get_ready_state();
		vector <process> get_running_state();
		vector <process> get_waiting_state();
		vector <process> get_terminated_state();
		void swap_states(vector <process> &a, vector <process> &b, int the_process, string state);



};
#endif
