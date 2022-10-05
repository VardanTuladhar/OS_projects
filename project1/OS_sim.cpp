#include "OS_sim.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
OS_sim :: OS_sim(string template1)
{
	vector <string> Op_names;
        vector <int> maxcycles;
	vector <int> mincycles;
	int mincycle, maxcycle;
	string Op_name;
	string firstline;	
	ifstream temp(template1, ios:: in);
	getline(temp, firstline);
	while(temp >>  Op_name >> mincycle >> maxcycle){
		Op_names.push_back(Op_name);
       		mincycles.push_back(mincycle);
 		maxcycles.push_back(maxcycle);
	}
	cout << Op_names[0]<< endl;	


}

