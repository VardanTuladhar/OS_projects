#include "frame.h"
#include <iostream>
using namespace std;

frame :: frame()
{
	this->process_num = -1;
	this->page_num = -1;
}
void frame :: set_frame(int process, int page)
{
	this->process_num = process;
	this->page_num = page;
}
int frame :: get_process_num()
{
	return this->process_num;
}
int frame :: get_page_num()
{
	return this->page_num;
}
