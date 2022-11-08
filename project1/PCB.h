#ifndef PCB_H
#define PCB_H
#include <string>
#include <vector>
#include "process.h"
#include "operation.h"
using namespace std;
class PCB{
	private:
		//state of process
		string process_state;
		//process number
		int process_number;
		//address of the next intruction we start from zero: address = hex(process_number * process.operations.size + 1) 
		int address_instruct;
		//will have all the registers listed in the Register vector then randomly some of those vectors will be put int vectors used
		vector <string> Registers_used;
		//same as register file
		vector <string> open_files;
		//CPU schduling infromation
		//Memory management infromation
		//I/O info
		vector <string> IO;
		//acounting info
		//address of the PCB how?
	public:
		PCB();
		void set_state(string updated_state);

};
#endif
