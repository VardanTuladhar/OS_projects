#include <iostream>
#include "process.h"
#include "PCB.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;
void shortest_first( vector <process> &a, bool debugging)
	{

		for (int i = 0; i < a.size(); i++)
			{
				for (int j = 0; j < a.size() - 1; j++)
						{
							if(a[j].total_cycles > a[j+1].total_cycles)
							{
								swap(a[j], a[j+1]); 

							}
							
						}

				}	
			
			if(debugging == true)
			{
				for (int i = 0; i < a.size(); i++)
					{
						//process number
						cout << "Process "<< a[i].process_num << endl;
						//process state
						cout << "Process state: "<< a[i].state << endl;
						cout << "Total Cycle Count: " <<a[i].total_cycles << endl;
						for (int j = 0; j < a[i].process_operations.size(); j++)
						{
							cout << "process operation "<< j << " name is " << a[i].process_operations[j].Op << endl;
							cout << "process operations " << j << " cycle is " << a[i].process_operations[j].Op_cycles << endl;
	
						}
			
					}
			}
	}	
void priority_schdule( vector <process> &a, bool debugging)
	{	
	vector <int> priority;
	for(int i = 1; i <= a.size(); i++)
			{
				priority.push_back(i);		

			}
			int pchoice;
			srand(time(NULL));
			int g = 0;
			while(priority.size() > 0)
			{
			//choose at random an iterarionn of the priority vecto
			pchoice = rand() % + priority.size(); 
			//assign chosen number to a process 
			a[g].setpriority(priority[pchoice]);			
			//remove that chosen number from vector
			priority.erase(priority.begin() + pchoice);
			g++;
			//repeat until size of prority vector is 0
			}
			//bubble sort based on process priority
			for (int i = 0; i < a.size(); i++)
				{
					for (int j = 0; j < a.size() - 1; j++)
						{
							if(a[j].priority > a[j+1].priority)
							{
								swap(a[j], a[j+1]); 

							}
							
						}
				}
		if(debugging == true)
			{
				for (int i = 0; i < a.size(); i++)
					{
						//process number
						cout << "Process "<< a[i].process_num << endl;
						//process state
						cout << "Process state: "<< a[i].state << endl;
						cout << "Priority: " << a[i].priority << endl;
						for (int j = 0; j < a[i].process_operations.size(); j++)
						{
							cout << "process operation "<< j << " name is " << a[i].process_operations[j].Op << endl;
							cout << "process operations " << j << " cycle is " << a[i].process_operations[j].Op_cycles << endl;
	
						}
			
					}
			}	


	}
void print_process(process a)
	{
		cout << "Process: "<< a.process_num << endl;
	        cout << "____________________________"<< endl;
		cout << "Process total cycles: " << a.total_cycles << endl;
		for (int g = 0; g < a.process_operations.size(); g++)
			{
				cout << "process operation "<< g << " name is " << a.process_operations[g].Op << endl;
				cout << "process operations " << g << " cycle is " << a.process_operations[g].Op_cycles << endl;	
			}
			

	}
			
int main()
{
	//debugging flag
	bool debugging = false;
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
	int temp_num;
	string template_selected;
	vector <process> new_queue;
	vector <process> ready_queue;
	vector <process> wait_queue;
	vector <process> running;
	vector <process> terminated;
	//creating processes and process vector
	for (int i = 0; i < process_count; i++)
	{
		cout << "Enter template you would like to use for process " << i << ": ";
		cin >> temp_num;
		template_selection = templates[temp_num-1];
		process temp_process();
		temp_process.set_process_num(i);
		temp_process.set_operations(template_selected)
		new_queue.push_back(temp_process);	

	}
	if(debugging == true)
	{
		for (int i = 0; i < process_count; i++)
		{
			//process number
			cout << "Process "<< processes[i].process_num << endl;
			//process state
			cout << "Process state: "<< processes[i].state << endl;
			for (int j = 0; j < processes[i].process_operations.size(); j++)
			{
				cout << "process operation "<< j << " name is " << processes[i].process_operations[j].Op << endl;
				cout << "process operations " << j << " cycle is " << processes[i].process_operations[j].Op_cycles << endl;
			}
			
		}
	}
	//Enter the number of cycles you would like the sim to run	
	cout << endl << "Please enter how many cycles you would like the simulator to run: ";
	cin >> cycle_count;
	//Enter the scheduling type you will use
	int scheduling_choice;
	cout << "What scheduling type will you use: " << endl <<"1. Priority" << endl <<"2. Shortest job first" << endl;
	cin >> scheduling_choice;
	//enter scheduling choice 
	while (1)
		{
		if (scheduling_choice == 1)
			{	
				break;
			}	
		else if( scheduling_choice == 2)

			{
				break;
			}
		else
			{
			cout << "You did not pick an apropraite answer please pick again: ";
		       	cin >> scheduling_choice;	
			}	
	
		}
	int current_process, current_operation = 0;
	if (debugging == false)
		{
			cout << "Hello" <<endl;
		}
	//vector <PCB> PCBofprocess;
	//set_PCB
	//for(int i = 0; i < processes.size(); i++)
	//	{
	//		PCB new_PCB(processes[i]);
	//		PCBofprocess.push_back(new_PCB);	
	//	}

	//establish ready and waiting quque
	int v, l = 0;
	vector <process> readyqueue;
	vector <process> waitingqueue;	
	for (int k = 0; k < processes.size(); k++)
		{
			readyqueue.push_back(processes[k]);
		}
	print_process(readyqueue[v]);

	//	if (readyqueue[i].state == "ready")
	//		{	
	//			if (scheduling_choice == 1)
	//				{	
	//					//create vector that will contain priority numbers
	//					priority_schdule( readyqueue, debugging);
	//	
	//				}	
	//			else if( scheduling_choice == 2)
	//				{
						//reorder based on shortest job
						//create a total cycle attribute of the process
						//bubble sort algorithm
	//					shortest_first(readyqueue, debugging);
	//		
	//				}
	//				
	//			processes[i].state == "running";
	//	   		PCBofprocess[i].update_state(processes[i]);

	//		}
		
	//		cout << "program is finished";

}
