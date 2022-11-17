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
      	this->ThePCB->set_process_num(a);	
}
void process ::set_operations(string temp, int j)
{
	string Op_name;
	int mincycle, maxcycle, cycles, ttemp_cycles = 0;
	string firstline;
	srand (time(NULL)+j);
	ifstream utemplate(temp, ios::in);
	getline(utemplate, firstline);
	while (utemplate >>Op_name >> mincycle >> maxcycle)
	{
		cycles = rand() % (maxcycle - mincycle +1) + mincycle;
		operation pro_op(Op_name, cycles);
		this->process_operations.push_back(pro_op);
		this->total_cycles += cycles;		
	}

}	
void process :: setpriority(int a)
{
	this->priority = a;
	this->ThePCB->set_priority_num(a);
}
void process :: set_state(string updated_state)
{
	this->state = updated_state;
}
int process :: get_priority()
{
 	return this->priority; 
}
string process :: get_state()
{
	return this->state;
}
int process :: get_process_num()
{
	return this->process_num;
}
int process :: get_total_cycles()
{
	return this->total_cycles;
}
int process :: get_operations_size()
{
	return this->process_operations.size();
}
string process :: get_operation_name(int a)
{
	return this->process_operations.at(a).Op;
}
int process :: get_operation_cycles(int a)
{
	return this->process_operations.at(a).Op_cycles;
}
void process :: decrement()
{
	this->process_operations.at(0).Op_cycles--;
	this->total_cycles--;
	if(this->get_operation_cycles(0) <= 0)
		{
			this->process_operations.erase(process_operations.begin());
		}
}
