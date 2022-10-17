#include <iostream>
#include "process.h"
#include <fstream>
#include <vector>
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
	vector <process> processes;
	//creating processes and process vector
	for (int i = 0; i < process_count; i++)
	{
		cout << "Enter template you would like to use for process " << i << ": ";
		cin >> temp_selection;
		string template_selection = templates[temp_selection-1];
		process temp_process(template_selection, i);
		processes.push_back(temp_process);	

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
	cout << "What scheduling type will you use: " << endl <<"1. First come first serve" << endl <<"2. Shortest job first" << endl;
	cin >> scheduling_choice;
	//enter create 
	while (1)
		{
		if (scheduling_choice == 1)
			{	
			//reoder based on first come first server
			
			break;
			}	
		else if( scheduling_choice == 2)
			{
			//reorder based on shortest job
			//create a total cycle attribute of the process
			
			//bubble sort algorithm
			for (int i = 0; i < processes.size(); i++)
				{
					for (int j = 0; j < processes.size() - 1; j++)
						{
							if(processes[j].total_cycles > processes[j+1].total_cycles)
							{
								swap(processes[j], processes[j+1]); 

							}
							
						}

				}	
			
			if(debugging == true)
			{
				for (int i = 0; i < process_count; i++)
					{
						//process number
						cout << "Process "<< processes[i].process_num << endl;
						//process state
						cout << "Process state: "<< processes[i].state << endl;
						cout << "Total Cycle Count: " << processes[i].total_cycles << endl;
						for (int j = 0; j < processes[i].process_operations.size(); j++)
						{
							cout << "process operation "<< j << " name is " << processes[i].process_operations[j].Op << endl;
							cout << "process operations " << j << " cycle is " << processes[i].process_operations[j].Op_cycles << endl;
	
						}
			
					}
			}	
			break;
			}
		else
			{
			cout << "You did not pick an apropraite answer please pick again: ";
		       	cin >> scheduling_choice;	
			}	
	
		}
	int current_process, current_operation = 0;
	while (processes.size() > 0 && cycle_count > 0)
		{
		
		//1. change state of process 
		//a. check the  
		if (processes[current_process].state == "new")

			{
				processes[current_process].state = "ready"

			}
		




		}	

	return 0;

}
