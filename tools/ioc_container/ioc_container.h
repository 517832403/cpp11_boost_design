#ifndef IOC_CONTAINER_H_
#define IOC_CONTAINER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <any>
#include <exception>
#include <sstream>


class IocContainer // simple ioc container
{
	public:
		IocContainer(){}
		~IocContainer(){}

		template<class T,typename Depend,typename... Args>
		typename std::enable_if<!std::is_base_of<T,Depend>::value>::type RegisterType(const std::string& str_key)
		{
			std::function<T* (Args...)> func = [](Args... args) {
				return new T(new Depend(args...)); } ;
			RegisterType(str_key,func) ;
		}

		template<class T,typename Depend,typename... Args>
		typename std::enable_if<std::is_base_of<T,Depend>::value,void>::type RegisterType(const std::string& str_key)
		{
			std::function<T* (Args...)> func = [](Args... args){
				return new Depend(args...) ;
			} ;
		}
		
		template<class T,typename... Args>
		void RegisterSimple(const std::string& str_key)
		{
			std::function<T* (Args...)> func = [](Args... args){
				return new T(args...) ;
			};
			RegisterType(str_key,func) ;
		}

		template<class T,typename... Args>
		T* Resolve(const std::string& str_key,Args... args)
		{
			auto iter = m_create_map_.find(str_key) ;
			if(iter == m_create_map_.end())
			{
				return nullptr ;
			}

			std::any resolver = iter->second ;
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
		void RegisterType(const std::string& str_key,std::any func)
		{
			if(m_create_map_.count(str_key))
			{
				std::stringstream ss ;
				ss<<str_key+" is exists." ;
				throw std::runtime_error(ss.str()) ;
			}

			m_create_map_.emplace(str_key,func) ;
		}
	private:
		std::unordered_map<std::string,std::any> m_create_map_ ; ///< save the lamda which is creator.
};

#endif



