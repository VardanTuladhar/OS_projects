#include "operation.h"
#include <iostream>
using namespace std;

operation :: operation(string a, int b)
{	
	int random;
	Op = a;
	Op_cycles =  b;	
	srand(b);
	random = rand()%(1-200+1) +1;
	//cout <<random<<endl;
	if (random %3 == 1)
	{
		crit = 1;
	}
	else{crit = 0;}
}
