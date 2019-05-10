#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <string>
using namespace boost::asio ;
using namespace std;

class client
{
	public:
		typedef client this_type ;
		typedef ip::tcp::endpoint endpoint_type ;
		typedef ip::tcp::socket socket_type ;
		typedef ip::address	address_type ;
		typedef boost::shared_ptr<socket_type> sock_ptr ;
	private:
		io_service m_ios_ ;
		endpoint_type m_ep_ ;
		static bool m_is_deal_;
		boost::shared_ptr<socket_type> sock ;
		
	public:
		client(const std::string& ip,int16_t port):m_ep_(ip::address::from_string(ip),port)
		{
			//start();
			//new boost::thread(run_thread);
		}
		
		void set_endpoint(const std::string& ip,int16_t port)
		{ 
			endpoint_type tmp(ip::address::from_string(ip),port);
			m_ep_ = tmp ;
		}

		static void set_undeal()
		{
			m_is_deal_ = false;
		}
	
		void reset_ios()
		{
			m_ios_.reset();
		}
		static void set_deal()
		{
			m_is_deal_ = true ;
		}

		void run_one()
		{
			while(!m_is_deal_)
			{	
				m_ios_.run_one();
			}
		}
		
		void run_thread()
		{
			new boost::thread(boost::bind(&client::run_one,this));
		}

		void start()
		{
			sock.reset(new socket_type(m_ios_));
			sock->async_connect(m_ep_,boost::bind(&this_type::connect_handler,this,boost::asio::placeholders::error));
		}

		void connect_handler(const boost::system::error_code& ec)
		{
			if(!ec)
			{
				std::cout<<"connect success."<<std::endl;
			}
			else
			{
				std::cout<<"connect failed."<<std::endl;
			}
			m_is_deal_ = true;
		}
};

bool client::m_is_deal_=false; ;

int main(int32_t arg,char** args)
{
	if(arg<3)
	{
		std::cout<<"the wrong arguments"<<std::endl;
		return -1 ;
	}
	client test(args[1],std::stoi(args[2]));
	//test.run_thread();
	test.start();
	test.run_one();
	std::cout<<"out"<<std::endl;
	test.set_undeal();
	test.reset_ios();
	test.set_endpoint(args[1],32001);
	test.start();
	test.run_one();
	std::cout<<"out2"<<std::endl;
	sleep(10);

	return 0 ;
}
