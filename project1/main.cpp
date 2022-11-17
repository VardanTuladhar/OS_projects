#include <iostream>
#include "process.h"
#include "PCB.h"g
#include "OS_functions.h"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

			
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
	vector <PCB> process_PCB;
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
		template_selected = templates[temp_num-1];
		process temp_process;
		temp_process.set_process_num(i);
		temp_process.set_operations(template_selected, i);
		new_queue.push_back(temp_process);	

	}
	vector <int> priority;
	for(int i = 1; i <= new_queue.size(); i++)
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
		new_queue.at(g).setpriority(priority[pchoice]);			
	//remove that chosen number from vector
		priority.erase(priority.begin() + pchoice);
		g++;
	//repeat until size of prority vector is 0
	}
	//print_state(new_queue, "new");
	//commit(new_queue, ready_queue);
	//print_state(ready_queue, "ready");
	//print_state(new_queue, "new");	
	cout << endl << "Please enter how many cycles you would like the simulator to run: ";
	cin >> cycle_count;
	//Enter the scheduling type you will use
	int scheduling_choice, end_choice;
	int run =1;
	cout << "What scheduling type will you use: " << endl <<"1. Priority" << endl <<"2. Shortest job first" << endl;
	cin >> scheduling_choice;
	//enter scheduling choice 
		while (run == 1) 
		{
			while( cycle_count > 0)
				{
					if(new_queue.size() != 0)
					{
						commit(new_queue, ready_queue);
					}
					if(running.size() == 0) 
						{
						if(ready_queue.size() > 0)
						{	
							while (1)
								{
									if (scheduling_choice == 1)
										{
											priority_schdule(ready_queue);	
											break;
										}	
									else if( scheduling_choice == 2)

										{
											shortest_first(ready_queue);	
											break;
										}
									else
										{
											cout << "You did not pick an apropraite answer please pick again: ";
		       									cin >> scheduling_choice;	
										}	
	
								}
							
							process_swap_states(ready_queue, running, 0, "running");
						}
						}
					else
						{
							if(running.at(0).get_operations_size() > 0)
								{
									if(running.at(0).get_operation_name(0) == "CALCULATE")
										{
											running.at(0).decrement();
										}
									else
										{
											process_swap_states(running, wait_queue, 0, "waiting");
											if (scheduling_choice == 1)
												{
													priority_schdule(ready_queue);	
												}	
											else if( scheduling_choice == 2)

												{
													shortest_first(ready_queue);	
												}

										}	
								}
							else
								{
									process_swap_states(running, terminated,0, "terminated" );
								}

						}
					if(wait_queue.size() > 0)
						{
							for(int i = 0; i < wait_queue.size(); i++)
								{
								if(wait_queue.at(i).get_operations_size() == 0)
										{
											process_swap_states(wait_queue, ready_queue, i, "ready");
												if (scheduling_choice == 1)
													{
														priority_schdule(ready_queue);	
													}	
												else if( scheduling_choice == 2);
													{
														shortest_first(ready_queue);	
													}
										}

									if(wait_queue.at(i).get_operation_name(0) == "I/O")
										{
											wait_queue.at(i).decrement();
										}
									

									else
										{
											process_swap_states(wait_queue, ready_queue, i, "ready");
											if (scheduling_choice == 1)
												{
													priority_schdule(ready_queue);	
												}	
											else if( scheduling_choice == 2)

												{
													shortest_first(ready_queue);	
												}


										}
								}
						}

				cout << "cycle: " << cycle_count << endl;
				print_state(new_queue, "new");
				print_state(ready_queue, "ready");
				print_state(running, "running");
				print_state(wait_queue, "waiting");
				print_state(terminated, "terminated");
				cycle_count--;
				}
			cout<< "End of simulation options:" <<endl << "1. exit"<<endl << "2. another run"<< endl;
			cin >> end_choice;
			switch(end_choice){
				case 1:
					run = 0;
					break;
				case 2:
					cout << "enter number of cycles: ";
					cin >>cycle_count;
					break;
				default:
					run = 0;
					break;
				}
		}
}
