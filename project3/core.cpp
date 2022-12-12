#include "core.h"
#include "OS_functions.h"
#include <thread>
using namespace std;

core :: core(vector <process> &new_process)
{
	new_queue = new_process;
}
void core :: run_core( frame *main, frame *virt, int cc, string core, int scheduling_choice)
{
	bool run = true;
	bool critflag = false;
	int frame_count = 0;
	frame *mainstart = main;
	frame *virtstart = virt;
	int numprocess = new_queue.size();
	int start, tempcount, end_choice ;
	start = cc;
	tempcount = cc;
	while (run == true)
	{
	while( tempcount > 0)
	{
		if (this->new_queue.size() > 0)
		{
			if( tempcount == start)
			{

				while(frame_count < 65)
				{
					if(main->get_page_num() == -1)//check it a frame is open
					{
						if(this->new_queue.size() > 0)
						{
						//insert first operation into free frame
						main->set_frame(this->new_queue.at(0).get_process_num(), 0);
						//set the page table to that frame
						this->new_queue.at(0).set_page_table(0, frame_count, 1, "Mem");
						//add the process to the ready queue

							this->swap_states(this->new_queue, this->ready_queue, 0, "Ready");

						}
						else
						{
							break;
						}
					}
					frame_count++;
					main = mainstart+frame_count;

				}

			}
		}
		//if
		if(this->running.size() >  0)
                                {
                                        if(this->running.at(0).get_operations_size() == 0)
                                        {
                                                process_swap_states(this->running, this->terminated, 0, "terminated");
                                                if (this->ready_queue.size() > 0)
                                                {
                                                        if (scheduling_choice == 1)
                                                {
                                                        priority_schedule(this->ready_queue);
                                                }
                                                else if(scheduling_choice == 2)
                                                {
                                                        shortest_first(this->ready_queue);
                                                }

                                                }
                                        }
																				else
																				{
																					if(this->running.at(0).get_operation_name(0) == "CALCULATE")
																					{
																						//decrementation(running, 0, processflag, critflag, mainmemory);
																					}
																					else
																					{
																						process_swap_states(this->running, this->wait_queue, 0, "waiting");
																						if (this->ready_queue.size() > 0)
																						{
																							if (scheduling_choice == 1)
																							{
																								priority_schedule(this->ready_queue);
																							}
																							else if(scheduling_choice == 2)
																							{
																								shortest_first(this->ready_queue);
																							}
																						}

																					}
																				}

																}
					else
																{
																	if (this->ready_queue.size() > 0)
																	{
																		if (scheduling_choice == 1)
																		{
																			priority_schedule(this->ready_queue);
																		}
																		else if(scheduling_choice == 2)
																		{
																			shortest_first(this->ready_queue);
																		}
																	}
																	process_swap_states(this->ready_queue, this->running, 0, "running");
																	if(this->running.at(0).get_operations_size() == 0)
																	{
																		process_swap_states(this->running, this->terminated, 0, "terminated");
																		if (scheduling_choice == 1)
																		{
																			priority_schedule(this->ready_queue);
																		}
																		else if(scheduling_choice == 2)
																		{
																			shortest_first(this->ready_queue);
																		}

																	}
																	else
																	{
																	int valid = this->running.at(0).get_current_op_validbit();
																	if(valid  == 1)

																		{
																			if(this->running.at(0).get_operation_name(0) == "CALCULATE")
																			{

																			}
																			else
																			{
																				process_swap_states(this->running, this->wait_queue, 0, "waiting");\
																				if (scheduling_choice == 1)
																				{
																					priority_schedule(this->ready_queue);
																				}
																				else if(scheduling_choice == 2)
																				{
																					shortest_first(this->ready_queue);
																				}
																				process_swap_states(this->ready_queue, this->running, 0, "running");

																			}
																		}
																		else
																			{/*
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

																				}*/
																			}
																	}
																}

																if(this->wait_queue.size() > 0)
																{
																	for(int i =0; i < this->wait_queue.size(); i++)
																	{
																		if(this->wait_queue.at(i).get_operations_size() == 0)
																		{
																			process_swap_states(this->wait_queue, this->ready_queue, i, "ready");
																			if (scheduling_choice == 1)
																			{
																				priority_schedule(this->ready_queue);
																			}
																			else if(scheduling_choice == 2)
																			{
																				shortest_first(this->ready_queue);
																			}

																		}
																		else
																		{

																				if(this->wait_queue.at(i).get_operation_name(0) == "I/O")
																				{
																					//decrementation(this->wait_queue, i, processflag, critflag, mainmemory);
																				}
																				else
																				{
																					process_swap_states(this->wait_queue, this->ready_queue, i, "ready");
																					if (scheduling_choice == 1)
																					{
																						priority_schedule(this->ready_queue);
																					}
																					else if(scheduling_choice == 2)
																					{
																						shortest_first(this->ready_queue);
																					}

																				}
																		}
																	}
																}


tempcount--;
}



cout << core << endl;
cout<< "End of simulation options:" <<endl << "1. exit"<<endl << "2. another run"<< endl<< "3. see the state machine" << endl << "4. see the memory"<<endl << "5. see the new state" <<endl;
cin >> end_choice;
switch(end_choice)
{
	case 1:
		run = false;

		break;
	case 2:
		cout << "enter number of cycles: ";
		cin >>cc;
		break;
	case 3:
				cout << core << endl;
				print_state(this->get_new_state(), "new");
				print_state(this->get_ready_state(), "ready");
				print_state(this->get_running_state(), "running");
				print_state(this->get_waiting_state(), "waiting");
				print_state(this->get_terminated_state(), "terminated");
				break;

	case 4:
		main = mainstart;
		virt = virtstart;
		cout << "Main Memory: \n";
		cout << "Frame:\tProcess: Page:\n";
		cout << "------\t------ -------\n";
		for(int i = 0; i < 128; i++)
		{
			cout << i <<"\t";
			cout<<main->get_process_num()<<"\t";
			cout<<main->get_page_num()<<endl;
			main = mainstart +i;
		}
		cout << "Virtual Memory: \n";
		cout << "Frame:\tProcess: Page:\n";
		cout << "------\t------ -------\n";
		for(int i = 0; i < 128; i++)
		{
			cout << i <<"\t";
			cout<<virt->get_process_num()<<"\t";
			cout<<virt->get_page_num()<<endl;
			virt = virtstart +i;
		}

			break;

}
}

}
vector <process> core :: get_new_state()
{
 return this->new_queue;
}
vector <process> core :: get_ready_state()
{
 return this->ready_queue;
}
vector <process> core :: get_running_state()
{
 return this->running;
}
vector <process> core :: get_waiting_state()
{
 return this->wait_queue;
}
vector <process> core :: get_terminated_state()
{
 return this->terminated;
}
void core :: swap_states(vector <process>&a, vector <process> &b, int the_process, string state)
{
	b.push_back(a.at(the_process));
	a.erase(a.begin()+the_process);
	b.at(b.size() -1).set_state(state);
}
