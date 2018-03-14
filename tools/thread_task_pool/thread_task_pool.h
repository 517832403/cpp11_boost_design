#include <list>
#include <thread>
#include <functional>
#include <atomic>
#include "../syncque/syncqueue.h"

const int MaxTaskCount = 100 ;

class ThreadPool
{
	public:
		using Task = std::function<void()> ;
		ThreadPool(int32_t numberThreads = std::thread::hardware_concurrency()):m_queue_(MaxTaskCount)
		{
			Start(numberThreads) ;
		}

		~ThreadPool()
		{
			Stop() ;
		}

		void Stop()
		{
			std::call_once(m_flag_,[this]{StopThreadGroup();}) ;
		}
		
		void AddTask(Task&& task)
		{
			m_queue_.Put(std::forward<Task>(task)) ;
		}

		void AddTask(Task& task)
		{
			m_queue_.Put(task) ;
		}

	private:
		void Start(int32_t numberThreads)
		{
			m_running_ = true ;
			
			for(int32_t i = 0 ;i< numberThreads ; ++i)
			{
				m_threadgroup_.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread,this)) ;
			}
		}

		void RunInThread()
		{
			while(m_running_)
			{
				Task task ;
				m_queue_.Take(task) ;

					if(!m_running_)
						return ;

					task() ;
			}
		}

		void StopThreadGroup()
		{
			m_queue_.Stop() ;
			m_running_ = false ;

			for(auto thread:m_threadgroup_)
			{
				if(thread)
					thread->join() ;
			}

			m_threadgroup_.clear() ;
		}

	private:
		std::once_flag m_flag_ ;
		std::atomic<bool> m_running_{true} ;
		SyncQueue<Task> m_queue_ ;
		std::list<std::shared_ptr<std::thread>> m_threadgroup_ ;
};

