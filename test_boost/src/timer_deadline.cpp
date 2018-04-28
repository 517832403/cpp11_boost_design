#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

using namespace boost::asio ;

int main()
{
	io_service ios ;
	deadline_timer t(ios,boost::posix_time::seconds(2)) ;
	std::cout<<t.expires_at()<<std::endl;

	t.wait() ;
	std::cout<<"helloc asio:"<<std::endl;
	//time_t t = time() ;
	std::cout<<boost::posix_time::second_clock::universal_time()<<std::endl;
	return 0 ;
}
