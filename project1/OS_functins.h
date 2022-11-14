#include <iostream>
#include "process.h"
#include "PCB.h"
#include <vector>
using namespace std;

void shortest_first(vector <process> &a, bool debugging);
void priority_schdule( vector <process> &a, bool debugging);
void print_process(process a);
void print_state(vector <process> a);
void process_swap_states(vector <process> &a, vector <process> &b, int the_process);
