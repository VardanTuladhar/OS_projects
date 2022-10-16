#include "process.h"
#include "operation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

process :: process(string templa, int a)
{
	string Op_name;
	int mincycle, maxcycle, cycles, ttemp_cycles = 0;
	string firstline;
	srand (time(NULL));
	ifstream utemplate(templa, ios::in);
	getline(utemplate, firstline);
	while (utemplate >>Op_name >> mincycle >> maxcycle)
	{
		
		cycles = rand() % (maxcycle - mincycle +1) + mincycle;
		operation pro_op(Op_name, cycles);
		process_operations.push_back(pro_op);
		ttemp_cycles += cycles;		

	}
	state = "new";
	process_num = a;
	total_cycles = ttemp_cycles;
	priority = 1;
	
}
void process :: setpriority(int a)
{

priority = a;


}
