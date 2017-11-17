#include "sequetial_cache.hpp"

#include <thread>
#include <mutex>
#include <sys/types.h>
#include <stdint.h>
#include <iostream>

struct AppData
{
	uint64_t cache_seq ;
	uint64_t counter ;
}

std::mutex g_mutex ;
const uint64_t simulate_conn_error_at = 100000 * 5 ;
const uint64_t simulate_eos_flag = -1ul ;


static void Write(std::queue<AppData*> &channel, AppData *app_data)
{
	std::lock_guard<std::mutex> guard(g_mutex);

	channel.push_back(app_data) ;

	usleep(1) ;

	return  ;
}

static AppData* Read(std::queue<AppData*> &channel)
{

	AppData * ret = NULL ;
	std::lock_guard<std::mutex> guard(g_mutex) ;
	if(channel.empty())
	{
		return NULL ;
	}
	ret = channel.front() ;
	channel.pop_front() ;
	return ret ;
}

bool is_server_by_master = true ;

void MasterThread(tool::Sequetial_Cache<AppData> *cache,std::queue<AppData*> &channel)
{
	uint64_t app_data_seq = 0 ;
	while(true)
	{
		AppData* app_data = cache->MasterNext(app_data_seq,[cache,channel](tool::SlaveJoinEvent& join_event){
				std::cout<<"join event.joint_index:"<<join_event.joint_index<<std::endl;
				{
					std::lock_guard<std::mutex> guard(g_mutex)
					is_server_by_master = true ;
				}		
				uint64_t txw_tail = cache->MasterLastIndex() ;
				uint64_t merge_break_index  = join_event.join_index -1 ;
				while((++merge_break_index <= txw_tail)// read the threhold data
				{
					AppData *data = cache->MasterAt(merge_break_index) ;
					assert(data != NULL) ;
					data->cache_seq = merge_break_index ;
					Write(channel,data) ;
				}
				// do the other things ;
				}) ;

		if( !app_data)
		{
			break ;
		}

		app_data->cache_seq = app_data_seq ;

		if(app_data->cache_seq == simulate_conn_error_at)
		{
			AppData* eos = new AppData() ;
			eos->cache_seq = simulate_eos_flag ;
			Write(channel,eos) ;
			std::lock_guard<std::mutex> guard(g_mutex) ;
			is_server_by_master = false ;
		}

		if(!is_server_by_master))
		{
			is_server_by_master = true ;
			continue ;
		}

		Write(channel,app_data) ;

	}
}


void SlaveThreadMain(uint64_t break_point,tool::Sequetial_Cache<AppData> *cache,std::queue<AppData*> &channel)
{
	auto slave_hdl = cache->NewSlave(break_point,NULL) ;

	uint64_t counter = 0 ;
	while(true)
	{
		AppData * app_data = cache->SlaveNext(slave_hdl,counter);
		if(app_data == NULL)
		{
			break ;
		}

		app_data->cache_seq = counter ;

		Write(channel,app_data) ;
	}

	cache->DeleteSlave(slave_hdl) ;
}

void ClientThreadMain(tool::Sequetial_Cache<AppData> *cache,std::queue<AppData*> &chennal)
{
	uint64_t counter = 0 ;

	while(true)
	{
		++counter ;
		auto *app_data = Read(channel) ;
		if(app_data == NULL)
		{
			return ;
		}

		if(app_data->cache_seq == simulate_eos_flag)
		{
			std::thread(std::bind(SlaveThreadMain,counter,cache,channel)) ;
			delete app_data ;
			--counter ;
			continue ;
		}

		assert(app_data->counter == app_data_cache_seq) ;
		assert(app_data->counter == counter) ;
		delete app_data ;
	}
}



int main()
{
	tool::Sequetial_Cache<AppData> cache ;
	cache.Init() ;

	std::queue<AppData*> channel ;

	std::thread master = std::thread(std::bind(MasterThread,&cache,channel)) ;
	std::thread client = std::thread(std::bind(ClientThreadMain,&cache,channel));

	uint64_t counter = 0 ;
	while(true)
	{
		AppData *data = new AppData() ;
		data->counter = ++counter ;
		data->cache_seq = 0 ;
		cache.Insert(data) ;

		usleep(10) ;
	}

	cache.ReleaseRxThread() ;

	return 0 ;	
}



