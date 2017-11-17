#include <assert.h>
#include <deque>
#include <list>
#include <mutex>

namespace tool
{

#ifndef MAX_SLAVES
#define MAX_SLAVES	1024

struct SlaveCursor
{
	uint64_t head ;			//the slave head
	uint64_t tail_threshold ;		// the holds
	void *	 context	;		
} ;

typedef int32_t SlaveHandler ;

struct SlaveJoinEvent
{
	SlaveHandler slave ;
	uint64_t	join_index ;
	void * 		context ;
};

const SlaveHandler kInvalidSlaveHandler = -1 ;

struct SCacheStats
{
	uint32_t cache_usage ;
	uint32_t nr_slave_joins ;
	uint32_t nr_slaves ;
};

template<typename DataType>
class Sequential_Cache
{
	public:
		Sequential_Cache(uint64_t nr_max_cache_data = 16*1024*1024,
				uint64_t join_threhold=256)
			:tail_(1),
			head_(1),
			cache_data_(NULL),
			nr_max_cache_data_(nr_max_cache_data),
			join_threhold_(join_threhold),
			nr_slaves_(0)
		{
			tail_threhold_ = 1 ;
			
			is_release_alter_ = false ;
		}

		~Sequetail_Cache()
		{
			
		}

		int32_t Init()
		{
			if(nr_max_cache_data_ == 0)
			{
				std::cout<<"nr_max_cache_data_ is zero"<<std::endl;
				return -1 ;
			}

			cache_data_ = new (std::nothrow) DataType* [nr_max_cache_data_] ;
			if(NULL == cache_data_)
			{
				std::cout<<"new cache_data_ is failed"<<std::endl;
				return -1 ;
			}

			memset(&cache_stats_,0x00,sizeof(cache_stats_)) ;

			return 0 ;

		}


		int32_t Insert(DataType* &user_data,uint64_t &index)
		{
			if(tail_ >= nr_max_cache_data_)
			{
				std::cout<<"the cache is full, insert failed."<<std::endl;
				return -1 ;
			}

			index = tail_ ;
			cache_data_[tail_]  = user_data ;
			++ tail_ ;
			return 0 ;
		}

		int32_t Insert(DataType* &user_data)
		{
			uint64_t index ;
			Insert(user_data,index) ;
		}


		SlaveHandler NewSlave(uint64_t begin_index,void *context)
		{
			if(begin_index == 0)
			{
				return -1 ;
			}
			
			Slavehandler ret_hdl ;
			std::lock_guard<std::mutex> guard(mutex_) ;
			if( ! free_hdl_list_.empty())
			{
				ret_hdl = free_hdl_list_.front() ;
				free_hdl_list_.pop_front() ;
			}
			else
			{
				ret_hdl = nr_slaves_ ;
				if(ret_hdl >= MAX_SLAVES)
				{
					return -1 ;
				}
				++ nr_slaves_ ;
			}

			slave_cursors_[ret_hdl].context = context ;
			slave_cursors_[ret_hdl].head = begin_index ;
			slave_cursors_[ret_hdl].tail_threshold = tail_ ;// ?? may be the head of master
			
			++ cache_stats.nr_slaves ;
			return ret_hdl ;
		}


		void DeleteSlave(Slavehandler hdl)
		{
			std::lock_guard<std::mutex> guard(mutex_) ;
			free_hdl_list_.push(hdl) ;
			--cache_stats_.nr_slaves ;
		}


		template<typename OnJoinEvent>
		DataType * MasterTryNext(uint64_t & index,const OnJoinEvent &event_handler)
		{
			mutex_.lock() ;
			while(!event_queue_.empty())
			{
				SlaveJoinEvent join_event = event_queue_.front() ;
				event_handler(join_event) ;
				++cache_stats_.nr_slave_joins ;	
			}
			mutex_.unlock() ;

			index = head_ ;
			if(HaveData(index,&tail_threhold_))
			{
				++head_ ;
				return cache_data_[index] ;
			}

			return NULL ;
		}

		template<typename OnJoinEvent>
		DataType* MasterNext(uint64_t &index,const OnJoinEvent &event_handler)
		{
			DataType * ret ;
			do
			{
				ret = MasterTryNext(index,event_handler)
				if(ret != NULL)
				{
					return ret ;
				}
				usleep(100) ;
			}while(is_release_alter_) ;
			return NULL ;
		}


		DataType* MasterAt(uint64_t index)
		{
			if(HaveData(index,&tail_threshold_))
			{
				return cache_data_[index] ;
			}

			return NULL ;
		}

		DataType* SlaveNext(SlaveHandler slave,uint64_t &index)
		{
		
			auto & slave_cur = slave_cursor_[slave] ;
			index = slave_cur.head ;
			if(!IsCatchUpWithMaster(slave_cur.head,&slave_cur.tail_threshold))
			{
				++ slave_cur.head ;
				return cache_data_[index] ;
			}

			SignalJoin(slave) ;
			return NULL ;
		}

		DataType* SlaveAt(SlaveHandler slave,uint64_t index)
		{
			if(HaveData(index,&slave_cursor_[slave].slave_threshold))
			{
				return cache_data_[index] ;
			}

			return NULL ;
		}

		void ReleaseRxThread()
		{
			is_release_alert_ = true ;
		}

		void GetStats(SCacheStats &stats)
		{
			stats = cache_stats_ ;
			stats.cache_usage = tail_ * 100Ul /nr_max_cache_data_ ;
		}

	private:

		inline bool HaveData(uint64_t head,uint64_t *tail_threshold)
		{
			if(head < * tail_threshold)
			{
				return true ;
			}

			*tail_threshold = tail_ ;

			if(head < *tail_threshold)
			{
				return true ;
			}

			return false ;
		}

		inline bool IsCatchUpWithMaster(uint64_t head,uint64_t *tail_threshold)
		{
			if(head + join_threshold_ < *tail_threshold)
			{
				return true ;
			}

			*tail_threshold = head_ ;

			if(head + join_threshold_ < *tail_threshold)
			{
				return true ;
			}

			return false ;
		}

		void SignalJoin(SlaveHandler slave)
		{
			std::lock_guard<std::mutex> guard(mutex_) ;
			auto &slave_cur = slave_cursor_[slave] ;
			SlaveJoinEvent event = {slave,slave_cur.head,slave_cur.context} ;
			event_queue.push_back(event) ;
		}

	private:
		uint64_t 		tail_ ;
		uint64_t 		head_ ;
		uint64_t 		tail_threshold_ ;
		bool 	 		is_release_alter_ ;
		std::queue<SlaveJoinEvent>  event_queue_ ;

		SlaveCursor		slave_cursor_[MAX_SLAVES] ;
		DataType ** 		cache_data_ ;
		const uint64_t  	nr_max_cache_data_ ;

		std::mutex		mutex_ ;
		std::list<int32_t> 	free_hdl_list_ ;
		int32_t 		nr_slaves_ ;

		SCacheStats		cache_stats_ ;

};

}

