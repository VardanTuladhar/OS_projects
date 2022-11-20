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
//      	this->ThePCB->set_process_num(a);	
}
void process ::set_operations(string temp, int j)
{
	string Op_name;
	int mincycle, maxcycle, cycles,i, ttemp_cycles = 0;
	string firstline;
	ifstream utemplate(temp, ios::in);
	getline(utemplate, firstline);
	while (utemplate >>Op_name >> mincycle >> maxcycle)
	{
		srand (time(NULL)+j);
		cycles = rand() % (maxcycle - mincycle +1) + mincycle;
		operation pro_op(Op_name, cycles);
		pro_op.pageid = i;
		this->process_operations.push_back(pro_op);
		this->total_cycles += cycles;
		this->total_size += pro_op.size;
		i++;		
	}
	for (int i = 0; i < this->process_operations.size(); i++)
	{
		vector<int> page;
		for (int j =0; j < 2; j++)
		{
			page.push_back(0);	
		}
		this->page_table.push_back(page);
		//this->memory_location.push_back("Secondary Mem");
	}

}	
void process :: setpriority(int a)
{
	this->priority = a;
	//this->ThePCB->set_priority_num(a);
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
int process :: get_crit(int a)
{
	return this->process_operations.at(a).crit;
}
void process :: decrement(bool &a)
{
	this->process_operations.at(0).Op_cycles--;
	this->total_cycles--;
	if(this->get_operation_cycles(0) <= 0)
		{
			if(a == true && this->get_crit(0) == 1)
				{
					a = false;
				}
			this->process_operations.erase(process_operations.begin());
		}
}
void process :: set_page_table(int page, int frame, int valid, string mem)
{
	this->page_table[page][0] = frame;
	this->page_table[page][1] = valid;
//	this->memory_location.at(page) = mem;
}
int process :: get_page_frame(int page)
{
	return this->page_table[page][0];
}
int process :: get_valid(int page)
{
	return this->page_table[page][1];
}
//string get_mem_loc(int page)
//{
//	return this->memory_location.at(page);
//}
