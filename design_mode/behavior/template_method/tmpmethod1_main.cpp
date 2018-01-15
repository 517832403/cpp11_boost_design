#include "tmpmethod1.h"

int main()
{
	std::cout<<"want to junk a cup of coffe.."<<std::endl;
	Coffee c ;
	c.PrepareReciepe() ;
	std::cout<<std::endl;
	std::cout<<"wang to junk a cup of tea..."<<std::endl;
	Tea t ;
	t.PrepareReciepe() ;
	return 0 ;
}
