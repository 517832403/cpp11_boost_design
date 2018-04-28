#include <iostream>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/impl/write.hpp>

using boost::asio::deadline_timer;
using boost::asio::ip::tcp;
using boost::asio::streambuf ;
using boost::asio::io_service ;

class Client
{
public:
	Client(io_service &ioservice):stopped_(false),socket_(ioservice),deadline_timer_(ioservice),heart_beat_(ioservice){}

	void Start(tcp::resolver::iterator endpoint_iter)
	{
		StartConnect(endpoint_iter) ;
		deadline_timer_.async_wait(boost::bind(&Client::CheckDeadline,this));
	}

private:
	void Stop()
	{
		stopped_ = true ;
		boost::system::error_code ignore_ec ;
		socket_.close(ignore_ec) ;
		deadline_timer_.cancel() ;
		heart_beat_.cancel() ;
	}

	void StartConnect(tcp::resolver::iterator endpoint_iter)
	{
		if(endpoint_iter != tcp::resolver::iterator())
		{
			std::cout<< "trying" << endpoint_iter->endpoint()<<"....\n";

			deadline_timer_.expires_from_now(boost::posix_time::seconds(60));

			socket_.async_connect(endpoint_iter->endpoint(),boost::bind(&Client::HandleConnect,this,boost::asio::placeholders::error,endpoint_iter));
		}
		else
		{
			Stop() ;
		}
	}

	void HandleConnect(const boost::system::error_code& ec,tcp::resolver::iterator endpoint_iter)
	{
		if(stopped_)
			return ;
		if(!socket_.is_open())
		{
			std::cout<<"Connect is dismiss"<<std::endl;
			StartConnect(++endpoint_iter) ;
		}
		else if(ec)
		{
			std::cout<<"connect is error:"<<ec.message()<<"\n";
			socket_.close() ;
			StartConnect(++endpoint_iter) ;
		}
		else
		{
			std::cout<<"Connect to "<<endpoint_iter->endpoint()<<"\n" ;
			StartRead() ;
			StartWrite() ;
		}
	}
	
	void StartRead()
	{
		deadline_timer_.expires_from_now(boost::posix_time::seconds(30));

		boost::asio::async_read_until(socket_,input_buf_,'\n',boost::bind(&Client::HandleRead,this,boost::asio::placeholders::error)) ;
	}
		
	void HandleRead(const boost::system::error_code& ec)
	{
		if(stopped_)
			return ;
		if(!ec)
		{
			std::string line ;
			std::istream is(&input_buf_) ;
			std::getline(is,line) ;
			if(!line.empty())
			{
				std::cout<<"received:"<<line<<"\n";
			}

			StartRead() ;// continue to read
		}
		else
		{
			std::cout<<"Error on receive:"<<ec.message()<<"\n";
			Stop() ;
		}
	}

	// the heart_beat
	void StartWrite()
	{
		if(stopped_)
			return ;
		boost::asio::async_write(socket_,boost::asio::buffer("\n",1),boost::bind(&Client::HandleWrite,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
	}

	void HandleWrite(const boost::system::error_code& ec,std::size_t bytes_transferred)
	{
		if(stopped_)
			return ;
		if(!ec)
		{
			heart_beat_.expires_from_now(boost::posix_time::seconds(10));

			heart_beat_.async_wait(boost::bind(&Client::StartWrite,this));
		}
		else
		{
			std::cout<<"Error on heart beat:"<<ec.message()<<"\n";
			Stop() ;
		}
	}

	void CheckDeadline()
	{
		if(stopped_)
			return ;
		// expired
		if(deadline_timer_.expires_at() <= deadline_timer::traits_type::now())
		{
			socket_.close() ;

			deadline_timer_.expires_at(boost::posix_time::pos_infin);// never active
		}

		deadline_timer_.async_wait(boost::bind(&Client::CheckDeadline,this));
	}

private:
	bool stopped_ ;
	tcp::socket socket_ ;
	streambuf input_buf_ ;
	deadline_timer deadline_timer_ ;
	deadline_timer heart_beat_ ;
};


int main()
{
	try{
	io_service ioservice ;
	tcp::resolver r(ioservice) ;
	Client c(ioservice) ;
	c.Start(r.resolve(tcp::resolver::query("127.0.0.1","8080"))) ;
	ioservice.run() ;
	}
	catch(std::exception &e)
	{
		std::cerr<<"Exception:"<< e.what()<<"\n";
	}

	return 0 ;

}


