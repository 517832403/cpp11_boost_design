#include <iostream>
#include <boost/smart_ptr.hpp>
class self_shared:
	public std::enable_shared_from_this<self_shared>
{
public:
	self_shared(int n):n_(n){}
	void print()
	{
		std::cout<< "self_shared:"<< n_<<std::endl;
	}
	void setN(int n)
	{
		n_ = n ;
	}
private:
	int n_ ;	
};

int main()
{
	std::shared_ptr<self_shared> sp = std::make_shared<self_shared>(324) ;
	sp->print() ;
	std::shared_ptr<self_shared> p = sp->shared_from_this() ;
	p->setN(1000) ;
	p->print() ;
	return 0 ;
}
