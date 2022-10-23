#include <iostream>
#include <string>
#include "state.h"
#include "functions.h"
using namespace std;

void decrement_runs( state rns)
{
//rs--
//if rs <1 
//delete operation
}
void check_waitingqueue(state rns, state wts)
{


}
void add_to_state(state rds, state rns)
{
	rns.insert_process(rds.processes_in[0]);
	rds.processes_in.erase(rds.processes_in.begin());
}
