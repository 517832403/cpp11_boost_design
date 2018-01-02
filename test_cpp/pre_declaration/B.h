#ifndef B_H_
#define B_H_
#include <iostream>
class B
{
	public:
		B(){}

		void IsRunning()
		{
			std::cout<<"is_running:"<<is_running<<std::endl;
		}
	private:
		bool is_running{true};
};

#endif
