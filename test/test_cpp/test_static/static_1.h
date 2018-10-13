#include "static.h"

class Derived1 : public Base
{
	public:
		void print()
		{
			std::cout<<"Derived1:"<<name<<std::endl;
		}
} ;
