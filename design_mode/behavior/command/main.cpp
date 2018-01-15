#include "command.h"

int main()
{
	RoastCook *p_roast_cook = new RoastCook() ;
	Command *cmd1 = new MakeMuttonCmd(p_roast_cook) ;
	Command *cmd2 = new MakeChickenWingCmd(p_roast_cook) ;

	Waiter *waiter = new Waiter() ;
	waiter->SetCmd(cmd1) ;
	waiter->SetCmd(cmd2) ;
	waiter->Notify() ;
	delete waiter ;
	delete cmd2 ;
	delete cmd1 ;
	delete p_roast_cook ;
	
	return 0 ;
}
