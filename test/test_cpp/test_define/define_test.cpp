#include <iostream>

#include <string>
#include <assert.h>

#define FixedPointValue \
	std::string str("luojian") ;\
	std::string str1("luojian1") ;\
	std::string str2("luojian2") ;\
	std::string str3("luojian3") ;

#define MAX 100000
#define Integer int64_t

class Tmp
{
	public:
		int i = 0 ;
		virtual ~Tmp(){}
};
class Derived : public Tmp
{
	public:
		double d = 1.0f ;
};

Tmp *g_tmp = nullptr;

#define PLUGIN(D,ep_name) do { \
	std::string str(""#ep_name) ; \
	D* d = dynamic_cast<D*>(g_tmp); \
	assert(d!=nullptr);\
	std::cout<<str<< d->d<< d->i<<std::endl;\
} while(false)


struct SpxInteger
{
	SpxInteger(Integer i)
	{
		val_ = i ;
	}
	Integer val_ ;
};

int main()
{
	FixedPointValue ;
	std::cout<<str<<str1<<str2<<str3<<std::endl;
	
	int64_t diff = 'a' * MAX;
	std::cout<<diff<<std::endl;
	
	g_tmp = new Derived;

	Integer i = diff ;
	std::cout<<"Integer:"<<i<<std::endl;
	SpxInteger val((int8_t)12) ;
	std::cout<<"SpxInteger:"<<val.val_<<std::endl;
	PLUGIN(Derived,test);
	return 0 ;
}
