#include "Memento.h"

int main()
{
	Caretake caretake ;
	GameRole game_role ;
	game_role.Show() ;

	caretake.Save(0,game_role.Save()) ;
	game_role.Attacked(10) ;
	game_role.Show() ;

	game_role.Load(caretake.Load(0)) ;
	game_role.Show() ;
	return 0 ;
}
