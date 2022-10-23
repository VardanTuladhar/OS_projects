
#ifndef OPERATION_H
#define OPERATION_H
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
class operation{
	public:
		string Op;
		int Op_cycles;
		int crit;
		operation(string a, int b);

};
#endif
