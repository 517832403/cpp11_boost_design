#include "mediator.h"

int main()
{
	Mediator *mediator = new HouseMediator() ;
	Person *renter = new Renter() ;
	Person *landlord = new Landlord() ;
	renter->SetMediator(mediator) ;
	landlord->SetMediator(mediator) ;
	mediator->SetA(renter) ;
	mediator->SetB(landlord) ;

	renter->SendMessage("i want rent a house,$1000 per month") ;
	landlord->SendMessage("$1000 per month is low") ;

	delete renter;
	delete landlord ;
	delete mediator;

	return 0 ;
}
