#include <iostream>
#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
class rw_data
{
	private :
		int m_x_ ;
		boost::shared_mutex rw_mu ;
	public:
		rw_data():m_x_(0){}
		void write()
		{
			boost::unique_lock<boost::shared_mutex> ul(rw_mu) ;
			++ m_x_ ;
		}

		void read(int *x)
		{
			boost::shared_lock<boost::shared_mutex> ul(rw_mu) ;
			*x = m_x_ ;
		}
};


boost::mutex io_mu ;

void writer(rw_data &d)
{
	for(int i = 0 ;i< 5;i++)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(10));
		d.write() ;
	}
}

void reader(rw_data &d)
{
	int x  ;
	for(int i = 0 ;i<20 ;i++)
	{
		boost::this_thread::sleep(boost::posix_time::millisec(5));
		d.read(&x) ;
		{		
			io_mu.lock();
			std::cout<<"reader:"<<x<< " threadID:"<<boost::this_thread::get_id()<<std::endl;
			io_mu.unlock() ;
		}
	}
}


int main()

{

	rw_data d ;
	boost::thread_group pool ;
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(reader,boost::ref(d)));
	pool.create_thread(boost::bind(writer,boost::ref(d)));
	pool.create_thread(boost::bind(writer,boost::ref(d)));
	
	pool.join_all() ;
	return 0 ;
}
