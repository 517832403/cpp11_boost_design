#ifndef PROPERTYIMPL_H_
#define PROPERTYIMPL_H_

#include <map>
#include <boost/any.hpp>


namespace tools
{
	class PropertyImpl
	{
	public:
		PropertyImpl(){}
		~PropertyImpl(){}

		template<typename T>
		void SetValue(const std::string& key,const T& value)
		{
			m_values_[key] = value;
		}

		void SetValue(const std::string& key,const char* value)
		{
			SetValue(key,std::string(value));
		}

		template<typename T>
		T GetValue(const std::string& key,const T& default_value)
		{
			auto it = m_values_.find(key);
			if ( (it != m_values_.end()) && (it->second.type() == typeid(T)) )
			{
				return boost::any_cast<T>(it->second) ;
			}
			return default_value ;
		}

		std::string GetValue(const std::string& key,const char* default_value)
		{
			return GetValue(key,std::string(default_value));
		}

	private:
		std::map<std::string,boost::any> m_values_ ;
	};
} // end namespace tools

#endif