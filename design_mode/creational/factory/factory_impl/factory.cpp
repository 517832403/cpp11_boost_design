#include <iostream>
#include "factory.h"


class Base
{
	public:
		using FuncNo = std::string ;
	protected:
		template<typename Derived>
		using TmplRegister = RegisterInFactory<Base,Derived,FuncNo> ;
	public:
		virtual void print(){std::cout<<"base"<<std::endl;}
		int base{12} ;
};

class DerivedImpl:public Base
{
	public:
		typedef TmplRegister<DerivedImpl> SelfRegister ;
		static const SelfRegister kSelfRegister;	
	public:
		void print() override {std::cout<<"derived"<<std::endl;}
		int derived{13} ;
};


const DerivedImpl::SelfRegister DerivedImpl::kSelfRegister("17") ;


int main()
{
	auto obj = GenericFactory<Base>::GetInstance().Create("17") ;	
	obj->print();
	return 0 ;
}
