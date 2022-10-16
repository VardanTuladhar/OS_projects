#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <vector>
#include "operation.h"
using namespace std;
class process{
	public:

		string state;
		int process_num, total_cycles;
		int priority;	
		vector <operation> process_operations;
		process(string templat, int a);
		void setpriority(int a);	
};
#endif
