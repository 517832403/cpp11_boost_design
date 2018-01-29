#include <iostream>
#include <functional>
#include <string>
#include <deque>
#include <thread>

using namespace std;
class Tool
{
	public:
		Tool(){}
		~Tool(){}
		void print()
		{
			while(!dq.empty())
			{
				auto f = dq.front() ;
				f() ;
				dq.pop_front() ;
			}
		}

		template<typename T>
		void SetData(T t,std::function<std::string(const T&)> f,std::function<void(T)> Free=nullptr)
		{
			dq.push_back([=](){
					string str = f(t) ;
					std::cout<<"Record Data:"<<str<<std::endl;
					if(Free != nullptr)
					{
						Free(t) ;
					}
					}) ;
		}

	private:
		std::deque<std::function<void ()> > dq ;
};

int main()
{
	Tool tool ;
	int i = 0 ;

	auto f = [](const int &i){ return to_string(i) ;} ;
	
	std::function<std::string(const int&)> func = f ;

	tool.SetData(1,func) ;

	std::function<std::string(const double &)> func2 = [](const double& d){ return to_string(d);};

	tool.SetData(2.0,func2) ;

	tool.print() ;

	return 0 ;
}
