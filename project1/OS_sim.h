#ifndef OS_SIM_H
#define OS_SIM_H
#include <string>
#include <vector>

using namespace std;
class OS_sim{
	private:
	 vector <string> Op_names;
	 vector <int> mincycles; 
	 vector <int> maxcycles;
	public:
		OS_sim(string template1);
		create_process( vector <string> Op_names, vector <int> mincycles, vector <int> );

};
#endif
