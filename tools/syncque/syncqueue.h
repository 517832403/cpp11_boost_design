#ifndef SYNC_QUEUE_H_
#define SYNC_QUEUE_H_

#include<list>
#include<mutex>
#include<thread>
#include<condition_variable>
#include<iostream>

using namespace std;

template<typename T>
class SyncQueue
{
	public:
		SyncQueue(size_t max_size):m_max_size_(max_size),m_need_stop_(false)
		{
		}

		bool Put(const T& x)
		{
			return Add(x) ;
		}

		bool Put(T&& x)
		{
			return Add(std::forward<T>(x)) ;
		}

		bool Take(std::list<T> & list)
		{
			std::unique_lock<std::mutex> locker(m_mutex_) ;
			m_not_empty_.wait(locker,[this]{return m_need_stop_ || NotEmpty();}) ;

			if(m_need_stop_)
				return false ;
			list = std::move(m_queue_) ;
			return true ;
		}

		bool Take(T& t)
		{
			std::unique_lock<std::mutex> locker(m_mutex_) ;
			m_not_empty_.wait(locker,[this]{return m_need_stop_ || NotEmpty();}) ;

			if(m_need_stop_)
				return false ;
			t = m_queue_.front() ;
			m_queue_.pop_front() ;
			m_not_full_.notify_one() ;
			return true ;
		}

		void Stop()
		{
			{
				std::lock_guard<std::mutex> locker(m_mutex_) ;
				m_need_stop_ = true ;
			}

			m_not_full_.notify_all() ;
			m_not_empty_.notify_all() ;
		}


		bool Empty()
		{
			std::lock_guard<std::mutex> locker(m_mutex_) ;
			return m_queue_.empty() ;
		}


		bool Full()
		{
			std::lock_guard<std::mutex> locker(m_mutex_) ;
			return m_queue_.size() == m_max_size_ ;
		}

		size_t Size()
		{
			std::lock_guard<std::mutex> locker(m_mutex_) ;
			return m_queue_.size() ;
		}

		size_t Count()
		{
			return m_queue_.size() ;
		}
	private:
		bool NotEmpty() const
		{
			bool empty = m_queue_.empty() ;
			if(empty)
				std::cout<<"Is empty need to wait...:"<<this_thread::get_id()<<std::endl;
			return !empty ;
		}

		bool NotFull() const 
		{
			bool full = m_queue_.size() >= m_max_size_ ;
			if(full)
				std::cout<<"Is Full need to wait.."<<std::endl;
			return !full ;
		}
		
		template<typename F>
		bool Add(F&& x)
		{
			std::unique_lock<std::mutex> locker(m_mutex_) ;
			m_not_full_.wait(locker,[this]{return m_need_stop_ || NotFull();}) ;
			if(m_need_stop_)
				return false ;
			m_queue_.push_back(x) ;
			m_not_empty_.notify_one() ;
			return true ;
		}

	private:
		std::list<T> m_queue_;
		std::mutex m_mutex_ ;
		std::condition_variable m_not_empty_ ;
		std::condition_variable m_not_full_ ;
		uint32_t m_max_size_ ;
		bool m_need_stop_ ;
};
#endif
