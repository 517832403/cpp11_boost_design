#ifndef SERIAL_PROCESSOR_H_
#define SERIAL_PROCESSOR_H_

#include <unistd.h>
#include <memory>
#include <thread>

#include <boost/asio.hpp>


class SerialProcessor : public std::enable_shared_from_this<SerialProcessor> 
{
public:
	SerialProcessor():m_strand_(GetIoService())
	{}

	template<typename Function>
	void Post(const Function& func)
	{
		auto p = shared_from_this(); // maybe the function contain p 
		m_strand_.post([p,func](){
			func();
		});
	}

	template<typename Function>
	void Dispatch(const Function& func)
	{
		auto p = shared_from_this(); // maybe the function contain p 
		m_strand_.dispatch([p,func](){
			func();
		});
	}	

	template<typename Function>
	void AddTimer(uint32_t seconds,const Function& func)
	{
		auto p = shared_from_this();
		auto timer =std::make_shared<boost::asio::deadline_timer>(GetIoService());
		timer->expires_from_now(boost::posix_time::seconds(seconds));
		timer->async_wait([seconds,timer,func,this,p](const boost::system::error_code& error){
			if (p&& func())
			{
				AddTimer(seconds,func);
			}
		});
	}

	static void AddThread(uint32_t number)
	{
		while(number --)
		{
			new std::thread([](){
				GetIoService().run();
			});
		}
	}

	static void Stop()
	{
		GetIoService().stop();
		while(!GetIoService().stopped())
		{
			usleep(1000);
		}
	}
protected:
	static boost::asio::io_service& GetIoService()
	{
		static boost::asio::io_service ios_;
		static boost::asio::io_service::work *work_ 
			= new boost::asio::io_service::work(ios_);
		(void)work_;
		return ios_;
	}
private:
	boost::asio::io_service::strand m_strand_ ;
};

#endif