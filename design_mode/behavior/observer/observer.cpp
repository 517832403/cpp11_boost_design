#include <iostream>
#include <string>
#include <list>
class Observer 
{
	public:
		Observer(){}
		virtual void Update(){}
};
class Subject
{
	public:
		Subject(){}
		void Attach(Observer* observer){observers.push_back(observer);}
		void Remove(Observer* observer){ observers.remove(observer);}
		void Notify()
		{
			std::list<Observer*>::iterator iter = observers.begin();
			for(;iter != observers.end();iter++)
			{
				(*iter)->Update() ;
			}
		}
		virtual void SetStatus(std::string s){m_status = s;}
		virtual std::string GetStatus(){return m_status ;}
	private:
		std::list<Observer*> observers ;		
	protected:
		std::string m_status ;
};

class SubjectImp:public Subject
{
	private:
		std::string m_name ;
	public:
		SubjectImp(std::string name):m_name(name){}
		~SubjectImp(){}
		void SetStatus(std::string name){m_status = "impnotify"+name;}
		std::string GetStatus(){return m_status;}
};


class ObserverImp:public Observer
{
	private:
		std::string m_name ;
		Subject *m_subject ;
	public:
		ObserverImp(std::string name,Subject *subject):m_name(name),m_subject(subject){}
		~ObserverImp(){}
		void Update() override
		{
			std::string status = m_subject->GetStatus() ;
			std::cout<<"update----"<<status<<std::endl;
		}
 };


int main()
{
	Subject *subject = new SubjectImp(std::string("CSDN C++")) ;
	Observer *observer = new ObserverImp(std::string("hoby"),subject);
	subject->Attach(observer) ;
	subject->SetStatus(std::string(" 17 attributes is update.")) ;
	subject->Notify() ;
	delete observer ;
	delete subject ;
	return 0 ;
}




