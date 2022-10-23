#include "state.h"
#include "process.h"
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
//get a process in a state
process state :: get_process(int i)
{
	return this->processes_in[i];
}
//delete process
void state :: delete_process(int i)
{
	this->processes_in.erase(this->processes_in.begin() + i);

}
//put process into a state use for intial input
void state :: insert_process(process a)
	{	
		a.set_state(this->statem);
		this->processes_in.push_back(a);
		this->total_cycle += a.get_total_cycles();
	}
//print the processes in the states
void state :: print_processes_in_state()
{
	for (int i = 0; i < this ->processes_in.size(); i++)
		{
			this -> processes_in[i].display_process();

		}
}
//get total cycles in the state
int state :: get_total_cycles()
{
	return this->total_cycle;
}
//switch a process in the self state to the a state
void state :: swap_states(state a, int i)
{
	//take a process from the self state
	this->insert_process(a.get_process(i));	
	//delete the process from the state
	a.processes_in.clear();	
	//add to the a state

}
//get the number of processes in the state
int state :: get_state_size()
{
	return this->processes_in.size(); 

}
//sort by priority
void state ::priority_schedule()
{
	
	for (int i = 0; i < this->processes_in.size(); i++)
		{
			for (int j = 0; j < this->processes_in.size() - 1; j++)
				{
					if(this->processes_in[j].getpriority() > this->processes_in[j+1].getpriority())
						{
							swap(this->processes_in[j], this->processes_in[j+1]);												
						}
				}
		}


}
void state :: sjf()
{
		for (int i = 0; i < this->processes_in.size(); i++)
		{
			for (int j = 0; j < this->processes_in.size() - 1; j++)
				{
					if(this->processes_in[j].get_total_cycles() > this->processes_in[j+1].get_total_cycles())
						{
							swap(this->processes_in[j], this->processes_in[j+1]);												
						}
				}
		}

}
string state :: get_operation(int i)
{
	return this->processes_in[i].get_currentopname();
}
int state :: get_opcycle(int i)
{
	return this->processes_in[i].get_currentopcycle();
}
void  state :: dec_currentopcycle(int i)
{
	this->total_cycle--; 
	this->processes_in[i].dec_currentopcycle();
}
bool state :: process_done(int i)
{
	if (this->processes_in[i].get_total_cycles() == 0)
	{return true;}
	else
	{return false;}

}
