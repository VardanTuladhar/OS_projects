#include "state.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

state :: state(int set_max_size, string set_state)
	{
		statem = set_state;
		max_size = set_max_size;
		total_cycle = 0;

	}
void state :: insert_process(process a)
	{
		int temp = 0;
		temp = a.total_cycles;
		processes_in.push_back(a);
		total_cycle += a.total_cycles;



	}
