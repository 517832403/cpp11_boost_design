#include "A.h"
#include "B.h"

int main()
{
	B *b = new B() ;
	A a(b) ;
	a.printB();
	return 0 ;
}
