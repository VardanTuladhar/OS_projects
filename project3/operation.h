
#ifndef OPERATION_H
#define OPERATION_H
#include <string>
#include <vector>
using namespace std;
class operation{
	public:
		string Op; 
		int Op_cycles;
		int crit;
		int size, pageid;
		operation(string a, int b, int c);

};
#endif
