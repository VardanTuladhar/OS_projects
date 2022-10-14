#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <vector>
#include "operation.h"
using namespace std;
class process{
	public:

		string state;
		int process_num;
		vector <operation> process_operations;
		process(string templat, int a);

};
#endif
