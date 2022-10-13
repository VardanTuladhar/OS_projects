#include <iostream>
#include "process.h"
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	//debugging flag
	bool debugging = true;
        //intial user interface	
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
	//list intger buffer of for template
	for (int i = 0; i < templates.size(); i++)
	{
		cout << i+1 <<". " <<templates[i];

	}
	int temp_selection;
	//creating processes
	for (int i = 0; i < templates.size(); i++)
	{
		cout << "Enter template you would like to use for process " << i << ":";
		cin >> temp_selection;
		


	}
	int cycle_count;
	cout << "Please enter how many cycles you would like the simulator to run";
	cin >> cycle_count;

//	OS_sim sim1( template1);
	return 0;

}
