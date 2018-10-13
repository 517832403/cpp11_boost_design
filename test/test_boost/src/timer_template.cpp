#include <boost/asio/steady_timer.hpp>
#include <boost/date_time.hpp>
#include <functional>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/asio.hpp>
class a_timer
{
	public:
		template<typename F>
		a_timer(boost::asio::io_service &ios,int x,F func):
			f(func),count_max(x),count(0),
			m_timer(ios)
		{
			m_timer.async_wait(boost::bind(&a_timer::call_func,this,boost::asio::placeholders::error));
		}
		void call_func(const boost::system::error_code &ec)
		{
			if(count >= count_max)
				return ;
			++count ;
			f() ;
			m_timer.expires_from_now(std::chrono::milliseconds(500));
			m_timer.async_wait(boost::bind(&a_timer::call_func,this,boost::asio::placeholders::error));
		}
	private:
		int count,count_max ;
		std::function<void ()> f ;
		boost::asio::steady_timer m_timer ;
};

void print1()
{
	std::cout<<"hello asio"<<std::endl;
}
void print2()
{
	std::cout<<"hello boost"<<std::endl;
}
int main()
{
	boost::asio::io_service ios ;
	a_timer at1(ios,5,print1) ;
	a_timer at2(ios,5,print2) ;
	ios.run() ;
}
