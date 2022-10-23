#include "process.h"

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
//set the priority of the process
void process :: setpriority(int a)
{
this->priority = a;
}
//print the:
//process num
//process state
//process operations 
//process number operations cycles
void process:: display_process()
{
			//process number
			cout << "Process "<< this->process_num << endl;
			//process state
			cout << "Process state: "<< this->state << endl;
			cout << "Process priority: " << this->priority << endl; 
			for (int j = 0; j < this-> process_operations.size(); j++)
			{
				cout << "process operation "<< j << " name is " << this-> process_operations[j].Op << endl;
				cout << "process operations " << j << " cycle is " <<this -> process_operations[j].Op_cycles << endl;
			}

}
//get total cycles of a process
int process :: get_total_cycles()	
{
	 return this->total_cycles;
}
//set the state of the process
void process :: set_state(string a)
{
	this->state = a;
}
//get the priority of the process 
int process :: getpriority()
{	
	return this->priority; 	

}
//name of the current operation
string process :: get_currentopname()
{
	return this->process_operations[0].Op;

}
//get the amount of cycles left ina operation
int process :: get_currentopcycle()
{
	return this->process_operations[0].Op_cycles;
}
//decrease the number of cycles in the current operation and the total cycles
void process :: dec_currentopcycle()
{
	this->process_operations[0].Op_cycles--;
	this->total_cycles--;
	if (get_currentopcycle() == 0)
	{
		this->process_operations.erase(process_operations.begin());
	}

}

