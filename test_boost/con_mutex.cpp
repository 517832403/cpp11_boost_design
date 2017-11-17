#include <stack>
#include <boost/thread.hpp>
#include <iostream>

boost::mutex io_mu ;
class buffer
{
private:
	boost::mutex mu ;
	boost::condition_variable_any con_put ;
	boost::condition_variable_any con_get ;
	std::stack<int> stk ;
	int un_read,capacity ;
	inline bool is_full()
	{
		return un_read == capacity ;
	}
	inline bool is_empty()
	{
		return un_read == 0 ;
	}

public:
	buffer(size_t n):un_read(0),capacity(n){}
	void put(int x)
	{
		{
			boost::mutex::scoped_lock lock(mu) ;
			while(is_full())
			{
				{
					boost::mutex::scoped_lock lock(io_mu) ;
					std::cout<<"full waiting..."<<std::endl;
				}

				con_put.wait(mu) ;
			}

			stk.push(x) ;
			++un_read ;
		}
		con_get.notify_one() ;
	}

	void get(int &x)
	{
		{
			boost::mutex::scoped_lock lock(mu) ;
			while(is_empty())
			{
				{
					boost::mutex::scoped_lock lock(io_mu) ;
					std::cout<<"empty waiting...."<<std::endl;
				}
				con_get.wait(mu) ;
			}
			--un_read ;
			x = stk.top() ;
			stk.pop() ;
		}
		con_put.notify_one() ;
	}
};

buffer buf(5) ;

void producer(int n)
{
	for(int i = 0 ; i<n ; i++)
	{
		{
		
			boost::mutex::scoped_lock lock(io_mu) ;
			std::cout<<"put:"<<i<<std::endl;
		}
		buf.put(i) ;
	}
}


void consumer(int n)
{
	int x ;
	for(int i = 0 ; i < n ; i++)
	{
		buf.get(x) ;
		boost::mutex::scoped_lock lock(io_mu) ;
		std::cout<<"get "<<x<<std::endl;
	}
}


int main()

{
	boost::thread t1(producer,20) ;
	boost::thread t2(consumer,10) ;
	boost::thread t3(consumer,10) ;

	t1.join() ;
	t2.join() ;
	t3.join() ;
	return 0 ;
}



