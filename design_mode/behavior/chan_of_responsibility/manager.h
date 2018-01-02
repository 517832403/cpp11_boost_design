#ifndef MANAGER_H_
#define MANAGER_H_
#include <iostream>
#include <string>

class Manager
{
	public:
		Manager(Manager *manager,std::string name):mp_manager_(manager),m_name_(name){}
		virtual void DealWithRequest(std::string name,int num){}
	protected:
		Manager *mp_manager_ ;
		std::string m_name_ ;
};

class CommonManager:public Manager
{
	public:
		CommonManager(Manager* manager,std::string name):Manager(manager,name){}
		void DealWithRequest(std::string name,int num ) override
		{
			if(num < 500)
			{
				std::cout<<"common manager:"<<m_name_<<" add money:"<<num<<" for "<<name<<std::endl;
			}
			else
			{
				//std::cout<<"common manager cannot deal it"<<std::endl;
				mp_manager_->DealWithRequest(name,num) ;
			}
		}
};


class MajorManager:public Manager
{
	public:
		MajorManager(Manager* manager,std::string name):Manager(manager,name){}
		void DealWithRequest(std::string name,int num) override
		{
			if(num < 3000)
			{
				std::cout<<"Major manager:"<<m_name_<<" add money:"<<num<<" for "<<name<<std::endl;
			}
			else
			{
				//std::cout<<"Major manager cannot deal it"<<std::endl;
				mp_manager_->DealWithRequest(name,num) ;
			}
		}
};


class GeneralManager:public Manager
{
	public:
		GeneralManager(Manager* manager,std::string name):Manager(manager,name){}
		void DealWithRequest(std::string name,int num) override
		{
			std::cout<<"General manager:"<<m_name_<<"add money:"<<num<<" for "<<name<<std::endl;
		}
};

#endif
