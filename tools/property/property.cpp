
#include <assert.h>
#include "property.h"
#include "propertyimpl.h"

namespace tools
{
	Property::Property()
	{
		m_propertyimpl_ = new PropertyImpl();
		assert(m_propertyimpl_);
	}

	Property::~Property()
	{
		if( m_propertyimpl_)
		{
			delete m_propertyimpl_;
			m_propertyimpl_ = nullptr ;
		}
	}

	void Property::SetValue(const std::string& key,const std::string& value)
	{
		m_propertyimpl_->SetValue(key,value);
	}

	void Property::SetValue(const std::string& key,const char* value)
	{
		m_propertyimpl_->SetValue(key,value);
	}

	void Property::SetValue(const std::string& key,int32_t value)
	{
		m_propertyimpl_->SetValue(key,value);
	}

	void Property::SetValue(const std::string& key,bool value)
	{
		m_propertyimpl_->SetValue(key,value);
	}

	std::string Property::GetValue(const std::string& key,const std::string& default_value) const
	{
		return m_propertyimpl_->GetValue(key,default_value);
	}

	std::string Property::GetValue(const std::string& key,const char* default_value) const
	{
		return m_propertyimpl_->GetValue(key,std::string(default_value));
	}

	int32_t Property::GetValue(const std::string& key,int32_t default_value) const
	{
		return m_propertyimpl_->GetValue(key,default_value);
	}

	bool Property::GetValue(const std::string& key,bool default_value) const
	{
		return m_propertyimpl_->GetValue(key,default_value);
	}
}// end tools