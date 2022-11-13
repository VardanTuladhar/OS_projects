#include "process.h"
#include "operation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

process :: process()
{
	
	state = "new";
	process_num = 0;
	total_cycles = 0;	
}
void process :: set_process_num(int a)
{
	this->process_num = a; 
}
void process ::set_operations(string temp)
{
	string Op_name;
	int mincycle, maxcycle, cycles, ttemp_cycles = 0;
	string firstline;
	srand (time(NULL));
	ifstream utemplate(temp, ios::in);
	getline(utemplate, firstline);
	while (utemplate >>Op_name >> mincycle >> maxcycle)
	{
		
		cycles = rand() % (maxcycle - mincycle +1) + mincycle;
		operation pro_op(Op_name, cycles);
		this->process_operations.push_back(pro_op);
		ttemp_cycles += cycles;		

	}

}	
void process :: setpriority(int a)
{
	this->priority = a;
}
