#include <iostream>
#include <cstdlib>
#include <memory>
using namespace std;


class A : public std::enable_shared_from_this<A>
{
	public:
		A(){}
		~A()
		{ 
			std::cout<<i<<std::endl;
			this->shared_from_this();
			std::cout<<"is over"<<std::endl;
		}
	private:
		int i{23} ;	
};

int main()
{
	std::shared_ptr<A> a(new A);
	a->shared_from_this();
	std::cout<<a<<std::endl;
	
	getchar() ;
	return 0 ;
}

