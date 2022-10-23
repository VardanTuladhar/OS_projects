#include <iostream>
#include "process.h"
#include "functions.h"
#include "state.h"
#include "PCB.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
	//debugging flag
	bool debugging = true;
        //intial user interface	
	int process_count, Template_count, cycle_count;
	cout << "Hello and Welcome Vardan's OS simulator!!!" << endl;
	cout << "How many processes would you like to create: ";
	cin >> process_count;
	if (debugging == true)
	{
		cout << process_count<< endl;
	}
	cout << "How many templates are you loading in: ";
	cin >> Template_count;
	if (debugging == true)
	{
		cout << Template_count << endl;
	}
	vector <string> templates;
	string template1;
	for (int i = 0; i < Template_count; i++)
	{
		cout << "Please enter the txt files for the template: "<< endl;
		cin >> template1;
		templates.push_back(template1);
		if (debugging == true)
		{
			cout << templates[i] << endl;
		}
	
	}
	//list intger buffer of for template
	for (int i = 0; i < templates.size(); i++)
	{
	cout << i+1 <<". " <<templates[i] << endl;

	}
	int temp_selection;
	state new_state(30, "new");
	//creating processes and process vector
	for ( int i = 0; i < process_count; i++)
	{
		cout << "Enter template you would like to use for process " << i << ": ";
		cin >> temp_selection;
		string template_selection = templates[temp_selection-1];
		process temp_process(template_selection, i);
		new_state.insert_process(temp_process);	

	} 
	vector <int> priorities;
	for (int i= 1; i <= new_state.get_state_size(); i++)
	       	{
			priorities.push_back(i);
		}	
	int pchoice;
	srand(time(NULL));
	int g = 0;
	while (priorities.size() > 0)
	{
		pchoice = rand()% + priorities.size();
		new_state.processes_in[g].setpriority(priorities[pchoice]);		
		priorities.erase(priorities.begin() +pchoice);
		g++;
	}
	if(debugging == true)
	{
		new_state.print_processes_in_state();
		cout << new_state.get_total_cycles()<< endl;
	}
	//Enter the number of cycles you would like the sim to run	
	cout << endl << "Please enter how many cycles you would like the simulator to run: ";
	cin >> cycle_count;
	//Enter the scheduling type you will use
	int scheduler;
	int TCN = new_state.get_total_cycles();
	state ready(30, "ready");
	state running(1, "run");
	state waiting(30, "wait");
	state terminate(30, "terminate");
	for(int i = 0; i < new_state.get_state_size(); i++)
	{
		ready.swap_states(new_state, i);
	}
	if (debugging  == true)
		{
			cout << "--------------NEW---------------------------"<<endl;
			new_state.print_processes_in_state();
			//cout << running.get_total_cycles()<< endl;
			cout << "--------------READY----------------------------"<<endl;
			ready.print_processes_in_state();
		}
	
	cout << "Enter scheduling choice "<< endl << "1. priority\n2. shorts job first" << endl;
	cin >> scheduler;
//--End of intial paramenters---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	while(TCN >= 0 && cycle_count >= 0)
		{
			//if nothing is running and something is ready schedule and move
			if( running.get_state_size() < 1 && ready.get_state_size() > 0)
			{	
				//schedule ready state
					if(scheduler == 1)
						{
							ready.priority_schedule();
							if (debugging  == false)
								{
									ready.print_processes_in_state();
									cout << ready.get_total_cycles()<< endl;
								}				
						}
					else if (scheduler == 2)
						{
							ready.sjf();
							if (debugging  == false)
								{
									ready.print_processes_in_state();
									cout << ready.get_total_cycles()<< endl;
								}
						}
					else
						{
							cout << "error please select appropriate choice" << endl;
							cout << "Enter scheduling choice "<< endl << "1. priority\n2. shorts job first" << endl;
							cin >> scheduler;
						}
				
					//take from ready to running
					running.swap_states(ready, 0);
					if (debugging  == true)
						{
							cout << "--------------Running---------------------------"<<endl;
							running.print_processes_in_state();
							cout << running.get_total_cycles()<< endl;
							cout << "-------------Ready-----------------------------"<<endl;
							ready.print_processes_in_state();
							//cout << ready.get_total_cycles()<< endl;

						}

			
				//running.dec_currentopcycle(0);	
			}
			//if there is something that running
			
			if (running.get_state_size() > 0)
				{
					//check if we are still running a calc
					if (running.get_operation(0) == "CALCULATE")
					{	
						running.dec_currentopcycle(0);
					}
					else
					{
						//move to waiting state
						waiting.swap_states(running,0); 
						if(scheduler == 1)
							{
								ready.priority_schedule();			
							}
						else if (scheduler == 2)
							{
								ready.sjf();
							}
					
					}
					/*if (running.processes_in[0].process_operations.empty() == true)
					{
						terminate.insert_process(running.processes_in[0]);
						running.processes_in.erase(running.processes_in.begin());
						if(scheduler == 1)
							{
								ready.priority_schedule();			
							}
						else if (scheduler == 2)
							{
								ready.sjf();
							}

					}*/					
					

						
				}

			//then check whether their is anything waiting and decrement if their is
			if (waiting.get_state_size() > 0)
			{
				for (int i = 0; i < waiting.get_state_size();i++)
					{
						/*if (waiting.processes_in[i].process_operations.empty() == true)
						{
							ready.insert_process(waiting.processes_in[i]);
							waiting.processes_in.erase(waiting.processes_in.begin() + i);
						}*/

						//if the current operation is I/O we'll decrement
						if(waiting.get_operation(i) == "I/O")
						{
							waiting.dec_currentopcycle(i);
						}
						else
						{
							if(scheduler == 1)
							{
								ready.priority_schedule();			
							}
							else if (scheduler == 2)
							{
								ready.sjf();
							}
							ready.swap_states(waiting, i);
						}

					}

			}



						if (debugging  == true)
				{
					cout << "--------------Running---------------------------"<<endl;
					running.print_processes_in_state();
					//cout << running.get_total_cycles()<< endl;
					cout << "-------------Ready-----------------------------"<<endl;
					ready.print_processes_in_state();
					//cout << ready.get_total_cycles()<< endl;
					cout << "--------------Waiting---------------------------"<<endl;
					waiting.print_processes_in_state();
					cout << waiting.get_total_cycles()<< endl;
					cout << "-------------Terminated-----------------------------"<<endl;
					terminate.print_processes_in_state();
					//cout << terminate.get_total_cycles()<< endl;
				}

			TCN--;
			cycle_count--;
			cout << "TCN: " << TCN <<endl << "input: " <<cycle_count << endl;

		}
	cout << "program is finished";
	return 0;

}
