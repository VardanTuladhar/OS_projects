#include <iostream>
#include "process.h"
#include "PCB.h"
#include "OS_functions.h"
#include "frame.h"
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
	bool critflag = false;
	int processflag;
	cout << "Hello and Welcome Vardan's OS simulator with memory management!!!" << endl << "The memory management method is paging" <<endl;
	cout << "Each page will be 4MB and be assigned to main memory or stored in virtual memory" << endl;
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
	int temp_num = 1;
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
		//cout << "Enter template you would like to use for process " << i << ": ";
		//cin >> temp_num;
		template_selected = templates[temp_num-1];
		process temp_process;
		temp_process.set_process_num(i);
		temp_process.set_operations(template_selected, i);
		new_queue.push_back(temp_process);	

	}
	templates.clear();
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
	priority.clear();
	//print_state(new_queue, "new");
	//commit(new_queue, ready_queue);
	//print_state(ready_queue, "ready");
	//print_state(new_queue, "new");	
	cout << endl << "Please enter how many cycles you would like the simulator to run: ";
	cin >> cycle_count;
	
	//Enter the scheduling type you will use
	int scheduling_choice, end_choice;
	int run =1;
	int start_cycle = cycle_count;
	bool inmem;
	int victim = 0;
	//int main_mem, vitual_mem = 512;
	vector <frame> mainmemory(128), virtualmemory(128);

	cout << "What scheduling type will you use: " << endl <<"1. Priority" << endl <<"2. Shortest job first" << endl;
	cin >> scheduling_choice;
	//enter scheduling choice 
		while (run == 1) 
		{
			while( cycle_count > 0)
			{
				//cout << "ready: " <<ready_queue.size() << endl << "running: " << running.size() << endl << "wait_queue: " << wait_queue.size() << endl; 
				if(new_queue.size() != 0)
				{
					//take a the first page of the first process and put into mem page and put it into memory
					//put processs num in
					int frame = 0;	
					int vframe = 0;
					//this is when we initally create the processes at the beginning of the simulation	
					if(cycle_count == start_cycle)
					{
					for(int op = 0; op < 5; op++)
					{
						for(int p = 0; p < process_count; p++)
						{	
							if(frame > 127)
							{
								if (vframe > 127)
								{
									break;
								}
								if(op == 0)
								{		
									virtualmemory.at(vframe).set_frame(new_queue.at(0).get_process_num(), op);
									new_queue.at(0).set_page_table(op, vframe, 0, "Vmem");
									process_swap_states(new_queue, ready_queue, 0,"ready");
								        vframe++;	
								}
								else
								{

								virtualmemory.at(vframe).set_frame(ready_queue.at(p).get_process_num(), op);
								ready_queue.at(p).set_page_table(op, vframe, 0, "Vmem");
								vframe++;
								}
							}
							else
							{
							//cout << j <<endl;
								if(op == 0)
								{		
									mainmemory.at(frame).set_frame(new_queue.at(0).get_process_num(), op);
									new_queue.at(0).set_page_table(op, frame, 1, "Mem");
									process_swap_states(new_queue, ready_queue, 0,"ready");
								        frame++;	
								}
								else
								{
									mainmemory.at(frame).set_frame(ready_queue.at(p).get_process_num(), op);
									ready_queue.at(p).set_page_table(op, frame, 1, "Mem");
								        frame++;	
								}
							}
						}
							
						if(vframe >127)
		
							break;
					}
					}
					else
					{
						/*cout << "Hello" << endl;
						int open_frame = -1;
						for(int o = 0; o < 128; o++)
						{
							if(virtualmemory.at(o).get_process_num() == -1)
							{
								 open_frame = o;
								 break;
							}
						}
						if (open_frame != -1)
						{	
							virtualmemory.at(open_frame).set_frame(new_queue.at(0).get_process_num(), 0);
							new_queue.at(0).set_page_table(0, vframe, 0, "Vmem");
							process_swap_states(new_queue, ready_queue, 0,"ready");								        	
						}*/
								
						
					}
				}
						
				if(running.size() >  0) 
				{
					if(running.at(0).get_operations_size() == 0)
					{
						process_swap_states(running, terminated, 0, "terminated");
						if (ready_queue.size() > 0)
						{
							if (scheduling_choice == 1)
						{
							priority_schedule(ready_queue);	
						}
						else if(scheduling_choice == 2)
						{
							shortest_first(ready_queue);
						}

						}
					}
					else
					{
						if(running.at(0).get_operation_name(0) == "CALCULATE")
						{
							decrementation(running, 0, processflag, critflag, mainmemory);	
						}
						else
						{
							process_swap_states(running, wait_queue, 0, "waiting");
							if (ready_queue.size() > 0)
							{
								if (scheduling_choice == 1)
								{
									priority_schedule(ready_queue);	
								}	
								else if(scheduling_choice == 2)
								{
									shortest_first(ready_queue);
								}

						}

						}
					}
				}
				else
				{
					if (ready_queue.size() > 0)
					{
						if (scheduling_choice == 1)
						{
							priority_schedule(ready_queue);	
						}
						else if(scheduling_choice == 2)
						{
							shortest_first(ready_queue);
						}
						//check that the operation is in memory
						
						process_swap_states(ready_queue, running, 0, "running");
						if(running.at(0).get_operations_size() == 0)
						{
							process_swap_states(running, terminated, 0, "terminated");
							if (scheduling_choice == 1)
							{
								priority_schedule(ready_queue);	
							}	
							else if(scheduling_choice == 2)
							{
								shortest_first(ready_queue);
							}

						}
						else
						{

						if(running.at(0).get_current_op_validbit() == 1)
						
							{
								if(running.at(0).get_operation_name(0) == "CALCULATE")
								{
									decrementation(running, 0, processflag, critflag, mainmemory);	
								}
								else
								{
									process_swap_states(running, wait_queue, 0, "waiting");\
									if (scheduling_choice == 1)
									{
										priority_schedule(ready_queue);	
									}	
									else if(scheduling_choice == 2)
									{
										shortest_first(ready_queue);
									}

								}
							}
						else
							{
								//search the main memory for the a free frame
								int open_frame = -1;
								for(int o = 0; o < 128; o++)
								{
									if(mainmemory.at(o).get_process_num() == -1)
									{
										 open_frame = o;
										break;
									}
								}
								if(open_frame != -1)
								{
								//update the operations page table
								//get the operation page value:q

									int cpage = running.at(0).get_pageid(0);
									int cframe = running.at(0).get_page_frame(cpage);
								//set the page table
									running.at(0).set_page_table(cpage, open_frame, 1, "Mainmem");
									swap(virtualmemory[cframe], mainmemory[open_frame]);
								}
								else
								{
									//victim selection
									int cpage = running.at(0).get_pageid(0);
									int cframe = running.at(0).get_page_frame(cpage);
								//set the page table
									running.at(0).set_page_table(cpage, victim, 1, "Mainmem");
									swap(virtualmemory[cframe], mainmemory[victim]);
									victim++;

								}



							}

						}
					}
				}
				if(wait_queue.size() > 0)
				{
					for(int i =0; i < wait_queue.size(); i++)
					{
						if(wait_queue.at(i).get_operations_size() == 0)
						{
							process_swap_states(wait_queue, ready_queue, i, "ready");
							if (scheduling_choice == 1)
							{
								priority_schedule(ready_queue);	
							}	
							else if(scheduling_choice == 2)
							{
								shortest_first(ready_queue);
							}

						}
						else
						{
							
								if(wait_queue.at(i).get_operation_name(0) == "I/O")
								{
									decrementation(wait_queue, i, processflag, critflag, mainmemory);
								}
								else 
								{
									process_swap_states(wait_queue, ready_queue, i, "ready");
									if (scheduling_choice == 1)
									{
										priority_schedule(ready_queue);	
									}	
									else if(scheduling_choice == 2)
									{
										shortest_first(ready_queue);
									}	

								}
							
							
							


						}
					}
				}

							
							
				cycle_count--;
				}
			cout<< "End of simulation options:" <<endl << "1. exit"<<endl << "2. another run"<< endl<< "3. see the state machine" << endl << "4. see the memory"<<endl << "5. see the new state" <<endl;
			cin >> end_choice;
			switch(end_choice){
				case 1:
					run = 0;
					break;
				case 2:
					cout << "enter number of cycles: ";
					cin >>cycle_count;
					break;
				case 3:
					cout << "cycle: " << cycle_count << endl;
					cout << "criticalflag: " << critflag << "  critcal process:" << processflag << endl;
					print_state(new_queue, "new");
					print_state(ready_queue, "ready");
					print_state(running, "running");
					print_state(wait_queue, "waiting");
					print_state(terminated, "terminated");
					break;
				case 4:
					cout << "Main Memory: \n";
					cout << "Frame:\tProcess: Page:\n";
					cout << "------\t------ -------\n";
					for(int i = 0; i < 128; i++)
					{
						cout << i <<"\t";
						cout<<mainmemory[i].get_process_num()<<"\t";
						cout<<mainmemory[i].get_page_num()<<endl;
					}
					cout << "Virtual Memory: \n";
					cout << "Frame:\tProcess: Page:\n";
					cout << "------\t------ -------\n";
					for(int i = 0; i < 128; i++)
					{
						cout << i <<"\t";
						cout<<virtualmemory[i].get_process_num()<<"\t";
						cout<<virtualmemory[i].get_page_num()<<endl;
					}

					break;
				case 5:
					print_state(new_queue, "new");
					break;



				default:
					run = 0;
					break;
				}
		}
}
