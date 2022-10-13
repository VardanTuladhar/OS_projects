#include <iostream>
//#include "OS_sim.h"
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	bool debugging = true; 
	int process_count, Template_count;
	cout << "Hello and Welcome Vardan's OS simulator!!!" << endl;
	cout << "How many processes would you like to create:";
	cin >> process_count;
	if (debugging == true)
	{
		cout << process_count<< endl;
	}
	cout << "How many templates are you loading in:";
	cin >> Template_count;
	if (debugging == true)
	{
		cout << Template_count << endl;
	}
	vector <string> templates;
	string template1;
	for (int i = 0; i < Template_count; i++)
	{
		cout << "Please enter the txt files for the template"<< endl;
		cin >> template1;
		templates.push_back(template1);
		if (debugging == true)
		{
			cout << templates[i] << endl;
		}

	
	}
//	OS_sim sim1( template1);
	return 0;

}
