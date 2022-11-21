#include <iostream>
#include "process.h"
#include "PCB.h"
#include "OS_functions.h"
#include "frame.h"
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
				cout << "page: " << g <<"\tassigned frame: " << a.get_page_frame(g) << "\tvalid bit: " << a.get_valid(g) << endl;
				//cout << "Memory location: " << a.get_mem_loc(g);	
			}
	}

void commit(vector <process> &a, vector <process> &b, int (&main_mem)[127][1], int (&virtual_mem)[127][1])
{
	int frame = 0; 
	int frames_needed = 0;
	int page_per_process = a.at(0).get_operations_size();
	int process_in_state = a.size();
	//calculate frame need
	//for (int i = 0; i < a.size(); i++)
	//{
	//	frames_needed += a.at(i).get_operations_size();
	//}	
	//cout << "frames_needed: "<< frames_needed << endl;	
	//assign a page to a frame then the fram to the page
		
	for(int k = 0;k < page_per_process; k++)
	{
	//so the plan is to have the first page in every process be set to a frame so that they always 
	///go int the ready state however I suppose if someone decides to create 257 process anything greater would
	//still be in the new state
		for(int j = 0; j < process_in_state; j++)
		{
			//set the table in the process to the frame and set the valid bit to 1
			if (k == 0)
			{
				a.at(0).set_page_table(k, frame,1, "main memory");
				main_mem[frame][0] = a.at(0).get_process_num();
				main_mem[frame][1] = k;
				cout << frame << "\t" << main_mem[frame][0] << "\t" << main_mem[frame][1]<<endl;
				process_swap_states(a, b, 0, "ready");
			}
		/*	else
			{
				main_mem[frame][0] = b.at(j).get_process_num();
				main_mem[frame][1] = k;
				b.at(j).set_page_table(k, frame, 1, "main memory");


			}i*/
			frame++;
			if(frame > 128)
				break;		
		}
		if(frame > 128)
			break;

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

void decrementation(vector <process> &a, int i, int &process_num, bool &crit, vector <frame> &mem)
{
	if(a.at(i).get_crit(0) == 1)
	{
		if (crit == true)
		{
		 	if (process_num == a.at(i).get_process_num())
			{
				a.at(i).decrement(crit, mem);
			}		
		}
		else
		{
			crit = true;
			process_num = a.at(i).get_process_num();
			a.at(i).decrement(crit, mem);
		}
	}
	else
	{
		a.at(i).decrement(crit, mem);
	}	
}
