#include <iostream>
#include <typeinfo>
#define TTPARAM(TT) template<typename> class TT 

template<typename T>
class A
{
public:
	A()
	{
		std::cout<<typeid(T).name()<<std::endl;
	}
private:
	T t ;
};

template<typename T,template<typename> class Type>
class B
{
public:
	B()
	{
		std::cout<<typeid(type).name()<<std::endl;
		std::cout<<typeid(Type<int*>).name()<<std::endl;
	}
private:
	Type<T> type ;
	//T t ;
};


using BB = B<int,A>;
class C
{
	private:
		BB bb ;	
};


int main()
{
	C c ;
	return 0 ;
}
