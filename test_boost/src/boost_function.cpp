#include <boost/function.hpp>
#include <iostream>
#include <cassert>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
int f(int a,int b)
{
	return b+a ;
}

struct demo_class
{
	typedef int result_type ;
	typedef boost::function<void(int&)> func_t ;

	func_t func ;
	int n{10} ;

	template<typename CallBack>
	void accept(CallBack f)
	{
		func = f ;
	}

	void run()
	{
		func(n) ;
		std::cout<<n<<std::endl;
	}

	int add(int a,int b) 
	{
		return a+b ;
	}
	int operator()(int x) const
	{
		return x*x ;
	}
};


void call_back(int &i )
{
	std::cout<< "call_back_func"<<std::endl;
	i *= 2 ;
	std::cout<< i<< std::endl;
}


class call_back_obj
{

	private:
		int x ;
	public :
		call_back_obj(int i):x(i){}
		void operator()(int i)
		{
			std::cout<<"call_back_obj"<< i*x++ <<std::endl;
		}
};

int main()
{
	boost::function<int (int,int)> func ;
	assert(!func) ;
	func = f ;
	if(func)
		std::cout<<func(10,20)<<std::endl;
	func = 0 ; // likes func.clear()
	assert(func.empty()) ;
	
	boost::function<int (demo_class&,int,int)> func1 ;
	func1 = boost::bind(&demo_class::add,_1,_2,_3) ;
	demo_class dc ;
	std::cout<<func1(dc,10,20)<<std::endl;
	
	func = boost::bind(&demo_class::add,&dc,_1,_2) ;
	std::cout<<func(10,20)<<std::endl;

	boost::function<int(int)> func2 ;
	func2 = boost::cref(dc) ;
	std::cout<<func2(10)<<std::endl;
	
	std::function<int (int,int)> funcstd;
	funcstd = std::bind(&demo_class::add,&dc,std::placeholders::_1,std::placeholders::_2) ;
	std::cout<<funcstd(10,20)<<std::endl;
		

	dc.accept(call_back) ;
	dc.run() ;



	call_back_obj cbo(2) ;
	dc.accept(boost::ref(cbo)) ;
	dc.run();
	dc.run() ;

	return 0 ;
}
