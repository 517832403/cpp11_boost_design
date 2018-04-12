#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <any>

class IocContainer
{
	public:
		IocContainer(){}
		~IocContainer(){}

		template<class T,typename Depend,typename... Args>
		void Register(const std::string& str_key)
		{
			std::function<T*(Args...)> func = [](Args... args){return new T(new Depend(args...));} ;
			RegisterType(str_key,func) ;
		}

		template<class T,typename... Args>
		T* Resolve(const std::string& str_key,Args... args)
		{
			if(m_create_map_.find(str_key) == m_create_map_.end())
				return nullptr ;
			std::any resolver = m_create_map_[str_key] ;
			std::function<T*(Args...)> func = std::any_cast<std::function<T*(Args...)>>(resolver) ;
			return func(args...) ;
		}

		template<class T,typename... Args>
		std::shared_ptr<T> ResolveShared(const std::string& str_key,Args... args)
		{
			T* t = Resolve<T>(str_key,args...) ;
			return std::shared_ptr<T>(t) ;
		}
	private:
		void RegisterType(const std::string& str_key,std::any constructor)
		{
			if(m_create_map_.find(str_key) != m_create_map_.end())
			{
				throw std::invalid_argument("this key has already exist!") ;
			}
			m_create_map_.emplace(str_key,constructor) ;
		}
		std::unordered_map<std::string,std::any> m_create_map_ ;
};
