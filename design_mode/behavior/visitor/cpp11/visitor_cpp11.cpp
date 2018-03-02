#include "visitor_cpp11.h"
int main()
{
	PrintVisitor vis ;
	stA a ;
	a.val = 9 ;
	stB b ;
	b.val = 9.12;
	Base *base = &a ;
	base->Accept(vis) ;
	base = &b ;
	base->Accept(vis) ;
	return 0 ;
}

