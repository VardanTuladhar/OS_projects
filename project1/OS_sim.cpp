#include "OS_sim.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
OS_sim :: OS_sim(string template1)
{
	string myText; 
	ifstream temp(template1);
	while (getline( temp, myText)){
	cout << myText<< endl;
	}

}

