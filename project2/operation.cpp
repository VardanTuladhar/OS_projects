#include "operation.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
using namespace std;

operation :: operation(string a, int b)
{
	Op = a;
	Op_cycles = b;	
	srand(time(NULL)+b);
	int crit_choice = rand();
	if (crit_choice % 2 == 0)
		{
			crit = 0;
		}
	else
		{
			crit = 1;
		}
	size = 4;
	


}
