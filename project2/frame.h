#ifndef FRAME_H
#define FRAME_H
#include <iostream>
using namespace std;
class frame{
	private:
		int process_num;
		int page_num;
	public:
		frame();
		void set_frame(int process, int page);
		int get_process_num();
		int get_page_num();
};
#endif
		
