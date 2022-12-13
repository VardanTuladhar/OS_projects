#include <iostream>
#include "process.h"
#include "PCB.h"
#include "OS_functions.h"
#include "frame.h"
#include "core.h"
#include <fstream>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <time.h>

using namespace std;


int main()
{
	int process_count, Template_count, cycle_count;
	bool critflag = false;
	int processflag;
	cout << "Hello and Welcome Vardan's OS simulator with memory management!!!" << endl << "The memory management method is paging" <<endl;
	cout << "Each page will be 4MB and be assigned to main memory or stored in virtual memory" << endl << "This is a two core and two thread per core simualtion";
	cout << "How many processes would you like to create: ";
	cin >> process_count;
	string template1;
	template1 = "Template.txt";
	int temp_num = 1;
	string template_selected;
	vector <process> new_queue1;
	vector <process> new_queue2;
	for (int i = 0; i < process_count; i++)
	{
		process temp_process;
		temp_process.set_process_num(i);
		temp_process.set_operations(template1, i);
		if( i <= (process_count/2))
		{
			new_queue1.push_back(temp_process);
		}
		else
		{
			new_queue2.push_back(temp_process);

		}
	}
	vector <int> priority1, priority2;
	for(int i = 1; i <= new_queue1.size(); i++)
	{
		priority1.push_back(i);

	}
	int pchoice;
	srand(time(NULL));
	int g = 0;
	while(priority1.size() > 0)
	{
	//choose at random an iterarionn of the priority vecto
		pchoice = rand() % + priority1.size();
	//assign chosen number to a process
		new_queue1.at(g).setpriority(priority1[pchoice]);
	//remove that chosen number from vector
		priority1.erase(priority1.begin() + pchoice);
		g++;
	//repeat until size of prority vector is 0
	}
	for(int i = 1; i <= new_queue2.size(); i++)
	{
		priority2.push_back(i);
	}
	g  = 0;
	while(priority2.size() > 0)
	{
	//choose at random an iterarionn of the priority vecto
		pchoice = rand() % + priority2.size();
	//assign chosen number to a process
		new_queue2.at(g).setpriority(priority2[pchoice]);
	//remove that chosen number from vector
		priority2.erase(priority2.begin() + pchoice);
		g++;
	//repeat until size of prority vector is 0
	}
	priority1.clear();
	priority2.clear();
	cout << endl << "Please enter how many cycles you would like the simulator to run: ";
  cin >> cycle_count;
	int scheduling_choice1 = 0;
	int scheduling_choice2 = 0;
	cout << "Core1: " << endl << "What scheduling type will you use: " << endl <<"1. Priority" << endl <<"2. Shortest job first" << endl;
	cin >> scheduling_choice1;
	cout << "Core2: " << endl << "What scheduling type will you use: " << endl <<"1. Priority" << endl <<"2. Shortest job first" << endl;
	cin >> scheduling_choice2;
	bool run = true;
	frame mainmemory[128], virtualmemory[128];
	frame *main1frame = &mainmemory[0];
	frame *main2frame = &mainmemory[65];
	frame *virtual1frame = &virtualmemory[0];
	frame *virtual2frame = &virtualmemory[65];


	core core1(new_queue1);
	core core2(new_queue2);
	int end_choice = 2;
	int core_sel;


	while(run ==true)
	{
		if(end_choice == 2){
			thread t1(&core:: run_core, &core1, main1frame, virtual1frame, cycle_count, "Core 1:", scheduling_choice1, ref(critflag), ref(processflag));
			thread t2(&core :: run_core, &core2, main2frame, virtual2frame, cycle_count, "Core 2:", scheduling_choice2, ref(critflag), ref(processflag));
			t1.join();
			 t2.join();
}
	cout << "Core selection:" << endl;
	cin >> core_sel;
	cout<< "End of simulation options:" <<endl << "1. exit"<<endl << "2. another run"<< endl<< "3. see the state machine" << endl << "4. see the memory"<<endl << "5. see the new state" <<endl;
	cin >> end_choice;
	switch(end_choice)
	{
		case 1:
			run = false;

			break;
		case 2:
			cout << "enter number of cycles: ";
			cin >>cycle_count;
			break;
		case 3:
		if (core_sel == 1)
		{
					cout << "Core1" << endl;
					print_state(core1.get_new_state(), "new");
					print_state(core1.get_ready_state(), "ready");
					print_state(core1.get_running_state(), "running");
					print_state(core1.get_waiting_state(), "waiting");
					print_state(core1.get_terminated_state(), "terminated");
					break;
		}
		else{
			cout << "Core2" << endl;
			print_state(core2.get_new_state(), "new");
			print_state(core2.get_ready_state(), "ready");
			print_state(core2.get_running_state(), "running");
			print_state(core2.get_waiting_state(), "waiting");
			print_state(core2.get_terminated_state(), "terminated");
			break;
		}

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

	}
}
}
