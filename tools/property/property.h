
#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace tools
{
class PropertyImpl ;
//using StringVector = std::vector<std::string>;
//using IntIntMap = std::map<uint32_t,uint32_t> ;

class Property
{
public:
	Property();
	
	~Property();

	void SetValue(const std::string& key,const std::string& value);

	void SetValue(const std::string& key,const char* value) ;

	void SetValue(const std::string& key,int32_t value);

	void SetValue(const std::string& key,bool value);

	//void SetValue(const std::string& key,const StringVector& value);

	//void SetValue(const Std::string& key,const IntIntMap& value);

	std::string GetValue(const std::string& key,const std::string& default_value) const;

	std::string GetValue(const std::string& key,const char* default_value) const ;

	int32_t GetValue(const std::string& key,int32_t default_value) const ;

	bool GetValue(const std::string& key,bool default_value) const ;


private:
	PropertyImpl* m_propertyimpl_ ;
};

}// end tools

#endif