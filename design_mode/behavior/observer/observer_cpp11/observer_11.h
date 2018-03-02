#include <iostream>
#include <string>
#include <functional>
#include <map>

class NoCopyable
{
	protected:
		NoCopyable() = default ;
		~NoCopyable() = default ;
		NoCopyable(const NoCopyable&) = delete ;
		NoCopyable& operator=(const NoCopyable&) = delete ;
};
template<typename Func>
class Events : public NoCopyable
{
	public:
		Events()
		{}
		~Events(){}

		int Register(const Func& f)
		{
			return Assign(f) ;
		}
		
		void Remove(const int key)
		{
			m_connections_map_.erase(key) ;
		}		

		template<typename... Args>
		void Notify(Args&&... args)
		{
			for(auto& it:m_connections_map_)
			{
				it.second(std::forward<Args>(args)...) ;
			}
		}
	private:
		int Assign(Func&& f)
		{
			int k = m_observerId++ ;
			m_connections_map_.emplace(k,std::forward<Func>(f)) ;
			return k ;
		}
	private:
		int m_observerId{0} ;
		std::map<int,Func> m_connections_map_ ;
};

struct stA
{
	int a,b ;
	void print(int a,int b)
	{
		std::cout<<a<<","<<b<<std::endl;
	}
};

void print(int a,int b)
{
	std::cout<<a<<","<<b<<std::endl;
}




