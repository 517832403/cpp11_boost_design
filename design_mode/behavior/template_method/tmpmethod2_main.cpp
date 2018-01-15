#include "tmpmethod2.h"

int main()
{
	CaffeineBeverage *coffee = new Coffee() ;
	coffee->PrepareReciepe() ;

	CaffeineBeverage *tea  = new Tea() ;
	tea->PrepareReciepe() ;

	delete coffee ;
	delete tea ;
	return 0 ;
}
