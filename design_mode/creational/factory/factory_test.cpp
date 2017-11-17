/*
 * @brief  factory method
 * @author luojian
 * */

#include <iostream>
#include <map>
#include <boost/functional/factory.hpp>
#include <boost/function.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/core/noncopyable.hpp>

template <typename ClassBase,typename type_id>
class Factory : public boost::noncopyable
{
	public:
		typedef boost::function<ClassBase*()> CreatorType ;
	
		static void Register(const type_id &id,const CreatorType &creator)
		{
			GetInstance()->RegisterProduct(id,creator) ;
		}

		static ClassBase* Create(const type_id& id)
		{
			return GetInstance()->DoCreate(id) ;
		}

	private:
		static Factory<ClassBase,type_id>* GetInstance()
		{
			static Factory<ClassBase,type_id> instance ;
			return &instance ;
		}

		void RegisterProduct(const type_id &id,const CreatorType& creator)
		{
			RegisterInfo info ;
			info.creator = creator ;
			product_dict_[id] = info ;
		}

		void Clear()
		{
			product_dict_.clear() ;
		}

		ClassBase* DoCreate(const type_id& id)
		{
			BOOST_AUTO(iter,product_dict_.find(id)) ;
			if(iter != product_dict_.end())
				return iter->second.creator() ;
			else
				return NULL ;
		}

	private:
		Factory(){} 
		struct RegisterInfo
		{
			CreatorType creator ;
		};

		std::map<type_id,RegisterInfo> product_dict_ ;

};

template<typename ClassBase,typename ClassDerived,typename type_id>
class ClassRegister
{
	public:
		explicit ClassRegister(const type_id& id)
		{
			Factory<ClassBase,type_id>::Register(id,boost::factory<ClassDerived*>());
		}
};


class A
{
	public:
		virtual void show(){ std::cout<<"A"<<std::endl;}
};

class B :public A
{
	public:
		virtual void show() { std::cout<<"B"<<std::endl;}
};

#define REGISTER_MSG_UTIL(cls,packet_no) \
	static ClassRegister<A,cls,long> cls##Register(packet_no) ;

#define CREATE_MSG_UTIL(type) Factory<A,long>::Create(type) ;




int main()
{
	REGISTER_MSG_UTIL(B,1) ;
	A * a = CREATE_MSG_UTIL(1) ;
	a->show() ;
	return 0 ;
}
