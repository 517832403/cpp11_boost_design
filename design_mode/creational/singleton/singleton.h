#include <iostream>
#include <string.h>



class Singleton
{
	public:
		static Singleton* GetInstance(const char* name) ;
		
		virtual void show(){ std::cout<<"Singleton"<<std::endl;} 

		Singleton(){}
	private:
		static Singleton *m_singleton_ ;
};

class SingletonA:public Singleton
{
	friend class Singleton ;

	public:
		void show() { std::cout<<"A"<<std::endl;}
	private:
		SingletonA(){}
};

class SingletonB:public Singleton
{
	friend class Singleton ;
	public:
		void show(){std::cout<<"B"<<std::endl;}

	private:
		SingletonB(){}
};

