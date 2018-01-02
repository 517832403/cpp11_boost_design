#include "manager.h"



int main()
{
	Manager *general = new GeneralManager(NULL,"general") ;
	Manager *major = new MajorManager(general,"major") ;
	Manager *common = new CommonManager(major,"common") ;

	common->DealWithRequest("D",300) ;
	common->DealWithRequest("E",1200) ;
	common->DealWithRequest("F",3000) ;
	delete common ;
	delete major ;
	delete general ;

	return 0 ;
}
