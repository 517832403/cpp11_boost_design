#include <iostream>
#include "state.h"

int main()
{
	Tank *tank = new Tank() ;
	tank->init() ;
	tank->attack() ;
	tank->enterSiegeState() ;
	tank->attack() ;
	tank->move() ;

	tank->enterTankState() ;
	tank->attack() ;
	tank->move() ;

	delete tank ;
	return 0 ;
}
