#include<string>
#include<functional>
#include<memory>
#include<map>
#include<iostream>


const int MaxObjectNum  = 10 ;

template<typename T>
class ObjectPool
{
	template<typename... Args>
	using Constructor = std::function<std::shared_ptr<T>(Args...)> ;

	public:
		template<typename... Args>
		void Init(size_t num,Args&&... args)
		{
			if(m_need_stop_)
				return ;
			if(num<= 0 || num > MaxObjectNum)
				throw std::logic_error("object num out of range.") ;

			auto constructName = typeid(Constructor<Args...>).name() ;
			for(size_t i = 0 ;i< num ; i++)
			{
				std::cout<<constructName<<std::endl;
				m_object_map_.emplace(constructName,
						std::shared_ptr<T>(new T(std::forward<Args>(args)...),
							[this,constructName](T* p)
							{
								if(m_need_stop_)
									delete p ;
								else
									m_object_map_.emplace(std::move(constructName),std::shared_ptr<T>(p)) ;
							}
						)) ;							
			}
		}

		void Stop()
		{
			m_need_stop_ = true ;
		}
		template<typename... Args>
		std::shared_ptr<T> Get()
		{
			if(m_need_stop_)
				return nullptr ;
			std::string constructName = typeid(Constructor<Args...>).name() ;
			auto range = m_object_map_.equal_range(constructName) ;
			for( auto iter = range.first; iter != range.second ;++iter)
			{
				auto ptr = iter->second ;
				m_object_map_.erase(iter) ;
				return ptr ;
			}
			return nullptr ;
		}

	private:
		std::multimap<std::string,std::shared_ptr<T>> m_object_map_ ;
		bool m_need_stop_{false} ;
};
