#include "singleton.h"

Singleton* Singleton::m_singleton_ = nullptr ;

Singleton * Singleton::GetInstance(const char *name)
{
	        if(m_singleton_ == nullptr)
		 {
		 	 if(strcmp(name,"SingletonA")==0)
			 {
				 m_singleton_ = new SingletonA ;
				 
		 	 }
			 else if(strcmp(name,"SingletonB")==0)
			 {    
				 m_singleton_ = new SingletonB;     
			 }
			 else
			 {
			       	m_singleton_ = new Singleton ;
			 }
		}
		return m_singleton_ ;
}
int main()
{
	Singleton * st = Singleton::GetInstance("SingletonA");
	st->show() ;
	return 0 ;
}
