#ifndef STATIC_H_
#define STATIC_H_

#include<iostream>
#include<string>

class Base
{

	public:
		static const std::string name ;
		static const int32_t name2=123 ;
		//static int32_t name1 = 1;
};
const std::string Base::name="luojian" ; 


class Derived : public Base
{
	public:
		void print()
		{
			std::cout<<name<<std::endl;
		}
};


template<typename type,int a=0>
class Tmp
{
	public:
		Tmp()
		{
			instance = this ;
			std::cout<<"construct:"<<instance<<std::endl;
		}
		static Tmp<type,a>* GetInstance()
		{
			return instance ;
		}	
		static std::string name ;
		static Tmp<type,a>* instance ;
};

template<typename type,int a>
std::string Tmp<type,a>::name="luojian" ;
template<typename type,int a>
Tmp<type,a>* Tmp<type,a>::instance(nullptr) ;

class TMP:public Tmp<int,1>
{
	public:
		int32_t luojian ;
};

using Internal = uint32_t ;
using External = uint32_t ;
using InternalTmp = Tmp<Internal,1> ;
using ExternalTmp = Tmp<External,2> ;
// InternalTmp ExternalTmp is not the same type.



template<typename type>
class TmpN
{
	public:
		static std::string name ;
};
template<typename type>
std::string TmpN<type>::name="luojian n" ;

//InternalTmpN ExternalTmpN is the same type.
using InternalTmpN = TmpN<Internal>;
using ExternalTmpN = TmpN<Internal>;


#endif



