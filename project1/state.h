#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <vector>
#include "process.h"
using namespace std;
class state{
	public:
		vector <process> processes_in;
		string statem;
		int max_size ;
		int total_cycle;
		state(int set_max_size, string set_state);
		void insert_process(process a);

};
#endif
