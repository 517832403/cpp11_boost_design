#include <iostream>
#include <cstdlib>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


using namespace boost ;
using namespace std ;

boost::asio::io_service ios_ ;
boost::asio::strand     strand2_(ios_) ;
boost::asio::strand     strand_(ios_) ;
std::mutex m_mutex ;


void print(int id)
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000)) ;
	static int count = 0 ;
	{
		std::lock_guard<std::mutex> guard(m_mutex) ;
		cout<<this_thread::get_id()<<"id:"<<boost::lexical_cast<std::string>(id)<<endl;
		cout<<this_thread::get_id()<<"cout:"<<boost::lexical_cast<std::string>(++count)<<endl;
	}
}

void IORunOne()
{
	while(true)
	ios_.run() ;
}
void IORunTwo()
{
	while(true)
	ios_.run() ;
}

void IORunThree()
{
	while(true)
		ios_.run() ;
}

void IORunFour()
{
	while(true)
		ios_.run() ;
}

void StrandPrintOne()
{
	strand_.post(boost::bind(print,1)) ;
	strand2_.post(boost::bind(print,5));
}

void StrandPrintTwo()
{
	strand_.post(boost::bind(print,2)) ;
	strand2_.post(boost::bind(print,6));
}

void StrandPrintThree()
{
	strand_.dispatch(boost::bind(print,3));
	strand2_.dispatch(boost::bind(print,7));
}

void StrandPrintFour()
{
	strand_.post(boost::bind(print,4));
	strand2_.post(boost::bind(print,8));
}

void ServicePrintOne()
{
	ios_.post(boost::bind(print,5)) ;
}

void ServicePrintTwo()
{
	ios_.post(boost::bind(print,6));
}

void ServicePrintThree()
{
	ios_.post(boost::bind(print,7));
}

void TestService()
{
	boost::thread t1(IORunOne) ;
	boost::thread t2(IORunTwo) ;
	boost::thread t3(IORunThree) ;
	boost::thread t4(IORunFour) ;

	boost::thread tt1(ServicePrintOne);
	boost::thread tt2(ServicePrintTwo);
	boost::thread tt3(ServicePrintThree);
	tt1.join() ;
	tt2.join() ;
	tt3.join() ;

	ios_.run() ;
}

void TestStrand()
{
	boost::thread ios1(IORunOne) ;
	boost::thread ios2(IORunTwo) ;

	boost::thread tt1(StrandPrintOne) ;
	boost::thread tt2(StrandPrintTwo) ;
	boost::thread tt3(StrandPrintThree) ;
	boost::thread tt4(StrandPrintFour) ;
	
	//ios_.run() ;
	tt1.join() ;
	tt2.join() ;
	tt3.join() ;
	tt4.join() ;

	//ios_.run() ;
}

int main()
{
	TestStrand() ;
	cout<<"----------------service----------------"<<endl;
	//TestService() ;
	getchar() ;
	return 0 ;
}

