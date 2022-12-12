#ifndef PAGELINE_H
#define PAGELINE_H
#include <iostream>
#include "frame.h"
class pageline{
	private:
		int valid;
		frame *f;
	
	public:
		pageline();
		void set_page(int svalid, frame *fr);
		int get_frame_prnum();
		int get_frame_panum();
		int get_valid();	

};





#endif
