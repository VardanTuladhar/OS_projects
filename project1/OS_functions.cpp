#include <iostream>
#include "process.h"
#include "PCB.h"
#include "OS_functions.h"
#include <vector>
using namespace std;

void shortest_first( vector <process> &a)
	{

		for (int i = 0; i < a.size(); i++)
			{
				for (int j = 0; j < a.size() - 1; j++)
						{
							if(a.at(j).get_total_cycles() > a.at(j+1).get_total_cycles())
							{
								swap(a.at(j), a.at(j+1)); 

							}
							
						}

				}	
			
			
	}	

void priority_schedule( vector <process> &a)
	{	

			for (int i = 0; i < a.size(); i++)
				{
					for (int j = 0; j < a.size() - 1; j++)
						{
							if(a.at(j).get_priority() > a.at(j+1).get_priority())
							{
								swap(a.at(j), a.at(j+1)); 

							}
							
						}
				}


	}
void print_process(process a)
	{
		cout << endl << "Process: "<< a.get_process_num() << endl;
	        cout << "____________________________"<< endl;
		cout << "process priority: " << a.get_priority() << endl;
		cout << "Process total cycles: " << a.get_total_cycles() << endl;
		cout << "Process state: " << a.get_state() << endl;
		for (int g = 0; g < a.get_operations_size(); g++)
			{
				cout << "process operation "<< g << " name is " << a.get_operation_name(g) << endl;
				cout << "process operations " << g << " cycle is " << a.get_operation_cycles(g) << endl;
				cout << "crit: " << a.get_crit(g) <<endl;	
			}
	}

void commit(vector <process> &a, vector <process> &b)
{
	b = a;
	a.clear();
	string ready = "ready";
	for (int i = 0; i < b.size(); i++)
			{
				b.at(i).set_state(ready);
			
			}

	
}
void print_state(vector <process> a, string state)
{
cout << "state: " << state << endl;
cout << "_________________________________" <<endl;
for (int i = 0;  i < a.size(); i++)
	{
		print_process(a.at(i));
	}
cout << endl;
}
void process_swap_states(vector <process> &a, vector <process> &b, int the_process, string state)
{

	b.push_back(a.at(the_process));
	a.erase(a.begin()+the_process);
	b.at(b.size() -1).set_state(state);
}

void decrementation(vector <process> &a, int i, int &process_num, bool &crit)
{
	if(a.at(i).get_crit(0) == 1)
	{
		if (crit == true)
		{
		 	if (process_num == a.at(i).get_process_num())
			{
				a.at(i).decrement(crit);
			}		
		}
		else
		{
			crit = true;
			process_num = a.at(i).get_process_num();
			a.at(i).decrement(crit);
		}
	}
	else
	{
		a.at(i).decrement(crit);
	}	
		

	
	
}
