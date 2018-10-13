#include <iostream>

class A
{
	public:
		void test()
		{
			int c = 11;
			auto f = [=](){
				//c = 12 ;
				a = 13;
				b = 123.4f;
				std::cout<<"c:"<<c<<" a:"<<a<<" b:"<<b<<std::endl;
			} ;

			f();
			a = 123;
			b = 123.01f ;
			std::cout<<"a:"<<a<<"b:"<<b<<std::endl;
		}
		int a{12};
		double b{12.01f};
};


int main()
{
	A a;
	a.test();
	return 0 ;
}
