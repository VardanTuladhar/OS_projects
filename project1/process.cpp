#include "process.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

process :: process( string templa)
{
	string Op_name
	int mincycle, maxcycle, cycles;
	string firstline;
	srand (time(NULL));
	ifstream utemplate(templa, ios::in);
	getline(utemplate, firstline);
	while (utemplate >>Op_name >> mincycle >> maxcycle)
	{
		
		cycles = rand() % (maxcycle - mincycle +1) + mincycle;
		operation pro_op(Op_name, cycles);
		process_operations.pushback(pro_op);
			

	}






}
