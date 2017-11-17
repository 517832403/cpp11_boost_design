#include <iostream>

class prototype
{
public:
	prototype(){}
	virtual ~prototype(){}
	virtual prototype* clone()=0 ;
	virtual void print() = 0 ;
};
class ConcrePrototype:public prototype
{
	
	public:
		ConcrePrototype()
		{ 
			m_ = 11 ;
			data_ = new int(12) ;
		}
		
		ConcrePrototype(const ConcrePrototype &rhs)
		{
			m_  = rhs.m_ ;
			data_ = new int(*(rhs.data_)) ;
		}

		virtual ~ConcrePrototype()
		{
			delete data_ ;
			data_ = nullptr ;
		}
		
		virtual prototype* clone()
		{
			return new ConcrePrototype(*this) ;
		}
		
		virtual void print()
		{
			std::cout<<m_<<"data_:"<<*data_<<std::endl;
			return ;
		}
		
	private:
		int m_ ;
		int* data_ ;
};


int main()
{
	prototype* proto_a = new ConcrePrototype() ;
	prototype* proto_b = proto_a->clone() ;
	proto_a->print() ;
	proto_b->print() ;
	delete proto_a ;
	proto_a = nullptr ;
	delete proto_b ;
	proto_b = nullptr ;
	return 0 ;
}



