#include <iostream>
#include "process.h"
#include "PCB.h"
#include <vector>
using namespace std;

void shortest_first(vector <process> &a);
void priority_schedule( vector <process> &a);
void commit(vector <process> &a, vector <process> &b);
void print_process(process a);
void print_state(vector <process> a, string state);
void process_swap_states(vector <process> &a, vector <process> &b, int the_process, string state);
void decrementation( vector <process> &a, int i, int &process_num, bool &crit);
