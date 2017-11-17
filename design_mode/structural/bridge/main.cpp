#include "computer.h"


int main()
{
	OS *linux = new LinuxOS() ;
	OS *unix = new UnixOS();
	Computer *dell = new Dell() ;
	dell->InstallOS(linux) ;
	dell->InstallOS(unix) ;
	return 0 ;
}


