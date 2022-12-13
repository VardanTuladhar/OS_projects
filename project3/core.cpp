#include "core.h"
#include "OS_functions.h"
#include <thread>
using namespace std;

core :: core(vector <process> &new_process)
{
	new_queue = new_process;
}
void core :: run_core( frame *main, frame *virt, int cc, string core, int scheduling_choice, bool &critflag, int &processflag)
{
	bool run = true;
	int victim = 0;
	int frame_count = 0;
	int vframe_count = 0;
	frame *mainstart = main;
	frame *virtstart = virt;
	int numprocess = new_queue.size();
	int start, tempcount, end_choice ;
	start = cc;
	tempcount = cc;

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
				while(vframe_count < 64)
				{
					if(virt->get_page_num() == -1)//check it a frame is open
					{
						if(this->new_queue.size() > 0)
						{
						//insert first operation into free frame
						virt->set_frame(this->new_queue.at(0).get_process_num(), 0);
						//set the page table to that frame
						this->new_queue.at(0).set_page_table(0, vframe_count, 0, "vMem");
						//add the process to the ready queue

							this->swap_states(this->new_queue, this->ready_queue, 0, "Ready");

						}
						else
						{
							break;
						}
					}
					vframe_count++;
					virt = virtstart+vframe_count;
				}

			}
		}
		//if
		if(this->running.size() >  1)
                                {
                                        if(this->running.at(0).get_operations_size() == 0 || this->running.at(1).get_operations_size() == 0 )
                                        {
																					if(this->running.at(0).get_operations_size() == 0)
																					{
                              							process_swap_states(this->running, this->terminated, 0, "terminated");
																					}
																					if(this->running.at(1).get_operations_size() == 0)
																					{
                              							process_swap_states(this->running, this->terminated, 1, "terminated");
																					}

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
																					int valid1 = this->running.at(0).get_current_op_validbit();
																					int valid2 = this->running.at(0).get_current_op_validbit();
																					cout << "Valid 1:" << valid1 << endl;
																					cout << "Valid 2:" << valid2 << endl;
																					if(valid1  == 1 && valid2 == 1)
																						{

																					if(this->running.at(0).get_operation_name(0) == "CALCULATE"&&this->running.at(1).get_operation_name(0) == "CALCULATE")
																					{
																						thread run1(decrementation, ref(this->running), 0, ref(processflag), ref(critflag), mainstart);
																						thread run2(decrementation, ref(this->running), 1, ref(processflag), ref(critflag), mainstart);
																						run1.join();
																						run2.join();
																					}
																					else
																					{
																						if(this->running.at(0).get_operation_name(0) == "CALCULATE" && this->running.at(1).get_operation_name(0) != "CALCULATE" && this->ready_queue.size() > 0)
																						{
																						process_swap_states(this->running, this->wait_queue, 1, "waiting");
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
																					if(this->running.at(0).get_operation_name(0) != "CALCULATE" && this->running.at(1).get_operation_name(0) == "CALCULATE" && this->ready_queue.size() > 0)
																					{
																					process_swap_states(this->running, this->wait_queue, 0, "waiting");
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
																				if(this->running.at(0).get_operation_name(0) != "CALCULATE" && this->running.at(1).get_operation_name(0) != "CALCULATE" & this->ready_queue.size() > 1)
																				{
																				process_swap_states(this->running, this->wait_queue, 0, "waiting");
																				process_swap_states(this->running, this->wait_queue, 1, "waiting");
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
																				}
																				else{
																					if (valid1 == 0)
																					{
																					main = mainstart;
																					int open_frame1 = -1;
																					for(int o = 0; o < 128; o++)
																					{
																						if(main->get_process_num() == -1)
																						{
																							 open_frame1 = o;
																							break;
																						}
																						main = mainstart +o;
																					}
																					if(open_frame1 != -1)
																					{
																					//update the operations page table
																					//get the operation page value:q

																						int cpage = running.at(0).get_pageid(0);
																						int cframe = running.at(0).get_page_frame(cpage);
																					//set the page table
																						running.at(0).set_page_table(cpage, open_frame1, 1, "Mainmem");
																							main = mainstart +open_frame1;
																						main->set_frame(running.at(0).get_process_num(), cpage);
																					}
																					else
																					{
																						//victim selection
																						int cpage = running.at(0).get_pageid(0);
																						int cframe = running.at(0).get_page_frame(cpage);
																					//set the page table
																						running.at(0).set_page_table(cpage, victim, 1, "Mainmem");
																						main = mainstart +victim;
																						main->set_frame(running.at(0).get_process_num(), cpage);
																						victim++;
																					}
																					}
																					if (valid2 == 0)
																					{
																					main = mainstart;
																					int open_frame2 = -1;
																					for(int o = 0; o < 128; o++)
																					{
																						if(main->get_process_num() == -1)
																						{
																							 open_frame2 = o;
																							break;
																						}
																						main = mainstart +o;
																					}
																					if(open_frame2 != -1)
																					{
																					//update the operations page table
																					//get the operation page value:q

																						int cpage = running.at(1).get_pageid(0);
																						int cframe = running.at(1).get_page_frame(cpage);
																					//set the page table
																						running.at(1).set_page_table(cpage, open_frame2, 1, "Mainmem");
																							main = mainstart + open_frame2;
																						main->set_frame(running.at(1).get_process_num(), cpage);
																					}
																					else
																					{
																						//victim selection
																						int cpage = running.at(1).get_pageid(0);
																						int cframe = running.at(1).get_page_frame(cpage);
																					//set the page table
																						running.at(1).set_page_table(cpage, victim, 1, "Mainmem");
																						main = mainstart +victim;
																						main->set_frame(running.at(1).get_process_num(), cpage);
																						victim++;
																					}
																					}

																				}
																				}

																}
					else
																{
																	if (this->ready_queue.size() > 1)
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
																	if(this->running.size() == 1 && this->ready_queue.size() > 0){
																	process_swap_states(this->ready_queue, this->running, 0, "running");
																	}
																	if (this->running.size() == 0 && this->ready_queue.size() > 1) {
																		process_swap_states(this->ready_queue, this->running, 0, "running");
																		process_swap_states(this->ready_queue, this->running, 0, "running");
																	}
																	if(this->running.at(0).get_operations_size() == 0 || this->running.at(1).get_operations_size() == 0 )
																	{
																		if(this->running.at(0).get_operations_size() == 0)
																		{
																			process_swap_states(this->running, this->terminated, 0, "terminated");
																		}
																		if(this->running.at(1).get_operations_size() == 0)
																		{
																			process_swap_states(this->running, this->terminated, 1, "terminated");
																		}

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
																	int valid1 = this->running.at(0).get_current_op_validbit();
																	int valid2 = this->running.at(0).get_current_op_validbit();
																	cout << "Valid 1:" << valid1 << endl;
																	cout << "Valid 2:" << valid2 << endl;
																	if(valid1  == 1 && valid2 == 1)
																		{
																			if(this->running.at(0).get_operation_name(0) == "CALCULATE" && this->running.at(1).get_operation_name(0) == "CALCULATE")
																			{
																				thread run1(decrementation, ref(this->running), 0, ref(processflag), ref(critflag), mainstart);
																				thread run2(decrementation, ref(this->running), 1, ref(processflag), ref(critflag), mainstart);
																				run1.join();
																				run2.join();
																			}

																			else
																			{
																				if(this->running.at(0).get_operation_name(0) == "CALCULATE" && this->running.at(1).get_operation_name(0) != "CALCULATE" && this->ready_queue.size() > 0)
																				{
																				process_swap_states(this->running, this->wait_queue, 1, "waiting");
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
																			if(this->running.at(0).get_operation_name(0) != "CALCULATE" && this->running.at(1).get_operation_name(0) == "CALCULATE" && this->ready_queue.size() > 0)
																			{
																				process_swap_states(this->running, this->wait_queue, 0, "waiting");
																				if (scheduling_choice == 1)
																				{
																					priority_schedule(this->ready_queue);
																				}
																				else if (scheduling_choice == 2)
																				{
																					shortest_first(this->ready_queue);
																				}
																					process_swap_states(this->ready_queue, this->running, 0, "running");
																		}
																				if(this->running.at(0).get_operation_name(0) != "CALCULATE" && this->running.at(1).get_operation_name(0) != "CALCULATE" && this->ready_queue.size() > 1)
																				{
																					process_swap_states(this->running, this->wait_queue, 0, "waiting");
																					process_swap_states(this->running, this->wait_queue, 1, "waiting");
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
																		}
																		else
																			{
																				//search the main memory for the a free frame
																				if (valid1 == 0)
																				{
																				main = mainstart;
																				int open_frame1 = -1;
																				for(int o = 0; o < 128; o++)
																				{
																					if(main->get_process_num() == -1)
																					{
																						main = mainstart +o;
																						 open_frame1 = o;
																						break;
																					}
																					main = mainstart +o;
																				}
																				if(open_frame1 != -1)
																				{
																				//update the operations page table
																				//get the operation page value:q

																					int cpage = running.at(0).get_pageid(0);
																					int cframe = running.at(0).get_page_frame(cpage);
																				//set the page table
																					running.at(0).set_page_table(cpage, open_frame1, 1, "Mainmem");
																						main = mainstart +open_frame1;
																					main->set_frame(running.at(0).get_process_num(), cpage);
																				}
																				else
																				{
																					//victim selection
																					int cpage = running.at(0).get_pageid(0);
																					int cframe = running.at(0).get_page_frame(cpage);
																				//set the page table
																					running.at(0).set_page_table(cpage, victim, 1, "Mainmem");
																					main = mainstart +victim;
																					main->set_frame(running.at(0).get_process_num(), cpage);
																					victim++;
																				}
																				}
																				if (valid2 == 0)
																				{
																				main = mainstart;
																				int open_frame2 = -1;
																				for(int o = 0; o < 128; o++)
																				{
																					if(main->get_process_num() == -1)
																					{
																						main = mainstart +o;
																						 open_frame2 = o;
																						break;
																					}
																					main = mainstart +o;
																				}
																				if(open_frame2 != -1)
																				{
																				//update the operations page table
																				//get the operation page value:q

																					int cpage = running.at(1).get_pageid(0);
																					int cframe = running.at(1).get_page_frame(cpage);
																				//set the page table
																					running.at(1).set_page_table(cpage, open_frame2, 1, "Mainmem");
																						main = mainstart + open_frame2;
																					main->set_frame(running.at(1).get_process_num(), cpage);
																				}
																				else
																				{
																					//victim selection
																					int cpage = running.at(1).get_pageid(0);
																					int cframe = running.at(1).get_page_frame(cpage);
																				//set the page table
																					running.at(1).set_page_table(cpage, victim, 1, "Mainmem");
																					main->set_frame(running.at(1).get_process_num(), cpage);
																					victim++;
																				}
																				}
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
																					int valid1 = this->wait_queue.at(i).get_current_op_validbit();

																					cout << "Valid 1:" << valid1 << endl;
																					if(valid1  == 1)
																						{
																							decrementation(this->wait_queue, i, processflag, critflag, mainstart);
																						}
																						else
																						{
																							main = mainstart;
																							int open_frame1 = -1;
																							for(int o = 0; o < 128; o++)
																							{

																								if(main->get_process_num() == -1)
																								{
																									main = mainstart +o;
																									 open_frame1 = o;
																									break;
																								}
																								main = mainstart +o;
																							}
																							if(open_frame1 != -1)
																							{
																							//update the operations page table
																							//get the operation page value:q

																								int cpage = wait_queue.at(i).get_pageid(0);
																								int cframe = wait_queue.at(i).get_page_frame(cpage);
																							//set the page table
																								running.at(0).set_page_table(cpage, open_frame1, 1, "Mainmem");
																								main->set_frame(wait_queue.at(i).get_process_num(), cpage);
																						}
																				}
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
