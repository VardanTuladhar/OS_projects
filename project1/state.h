#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <vector>
#include "process.h"
using namespace std;
class state{
	private:
		string statem;
		int max_size ;
		int total_cycle;
	public:
		process get_process(int i);
		vector <process> processes_in;
		void delete_process(int i);
		state(int set_max_size, string set_state);
		void insert_process(process a);
		void print_processes_in_state();
		int get_total_cycles();
		void swap_states( state a, int i);
		int get_state_size();
		void priority_schedule();
		void sjf();
		string get_operation(int i);
		int get_opcycle(int i);
		void dec_currentopcycle(int i);
		bool process_done(int i);
};
#endif
