#include "strategy.h"


int main()
{

	WeaponBehavior *ak47 = new AK47() ;
	WeaponBehavior *knife = new Knife() ;

	Character *king = new King() ;
	king->fight() ;
	

	king->SetWeapon(ak47);
	king->fight() ;

	king->SetWeapon(knife) ;
	king->fight();
	delete king ;
	delete knife ;
	delete ak47 ;
	return 0 ;
}

