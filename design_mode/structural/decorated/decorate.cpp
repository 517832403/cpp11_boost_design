#include <iostream>
#include <string>

class Phone
{
	public:
		Phone(){}
		virtual ~Phone(){}
		virtual void ShowDecorated() =0 ;
};
class IPhone:public Phone
{
	public:
		IPhone(std::string name){name_ = name ;}
		virtual ~IPhone()
		{
			std::cout<<"delete IPhone"<<std::endl;
		}
		virtual void ShowDecorated()
		{
			std::cout<<name_<<"'s decorate"<<std::endl;
		}
	private:
		std::string name_ ;
};


class Decorated:public Phone
{
	public:
		Decorated(Phone* phone):phone_(phone){}
		~Decorated(){}
		virtual void ShowDecorated()
		{
			phone_->ShowDecorated() ;
		}

	private:
		Phone *phone_ ;
};

class Decorated_A:public Decorated
{
	public:
		Decorated_A(Phone *phone):Decorated(phone){}
		~Decorated_A(){}
		virtual void ShowDecorated()
		{
			Decorated::ShowDecorated() ;
			ShowDecorated_A() ;
		}
		void ShowDecorated_A()
		{
			std::cout<<"decorated A"<<std::endl;
		}
};
class Decorated_B:public Decorated
{
	public:
		Decorated_B(Phone *phone):Decorated(phone){}
		~Decorated_B(){}
		void ShowDecorated_B()
		{
			std::cout<<"decorated B"<<std::endl;
		}

		virtual void ShowDecorated()
		{
			Decorated::ShowDecorated() ;
			ShowDecorated_B() ;
		}
};

int main()
{
	Phone *iPhone = new IPhone("iphone") ;
	Decorated_A *pa = new Decorated_A(iPhone) ;
	Decorated_B *p = new Decorated_B(pa) ;
	
	p->ShowDecorated() ;

	delete p ;
	p = nullptr ;
	
	delete pa ;
	pa = nullptr ;

	delete iPhone ;
	iPhone = nullptr ;

	return 0 ;
}
