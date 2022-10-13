#include "process.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

process :: process( string templa)
{
	string Op_name;
	int mincycle, maxcycle;
	string firstline;
	ifstream utemplate(templa, ios::in);
	getline(utemplate, firstline);
	while (utemplate >>Op_name >> mincycle >> maxcycle)
	{
		Op.pushback(Op_name);	
			

	}






}
