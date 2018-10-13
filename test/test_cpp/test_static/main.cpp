#include "static.h"
#include "static_1.h"

int main()
{

	Derived* d = new Derived ;
	d->print();
	delete d ;
	d = nullptr ;
	Derived1* d1 = new Derived1 ;
	d1->print() ;
	delete d1 ;
	d1 = nullptr ;
	InternalTmp internalTmp ;
	ExternalTmp externalTmp ;
	TMP tmp ;
	
	std::cout<<tmp.luojian<<std::endl;
	std::cout<<InternalTmp::GetInstance()<<std::endl;
	std::cout<<ExternalTmp::GetInstance()<<std::endl;
	std::cout<<&InternalTmpN::name<<std::endl;
	std::cout<<&ExternalTmpN::name<<std::endl;
	return 0 ;
}
