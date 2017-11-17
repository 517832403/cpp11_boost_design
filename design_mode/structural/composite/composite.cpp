#include <iostream>
#include <string>
#include <list>

class Company
{
	public:
		Company(std::string name){m_name_ = name ;}
		virtual ~Company(){}
		virtual void Add(Company *company){}
		virtual void Show(int depth){}
	protected:
		std::string m_name_ ;
};


class ConcreteCompany:public Company
{
	public:
		ConcreteCompany(std::string name):Company(name){}
		~ConcreteCompany(){}
		void Add(Company* pcompany){ m_list.push_back(pcompany);}
		void Show(int depth)
		{
			for(int i = 0 ;i< depth;i++)
			{
				std::cout<<"-" ;
			}
			std::cout<<m_name_<<std::endl;
			std::list<Company*>::iterator iter = m_list.begin() ;
			for(;iter!=m_list.end();++iter)
			{
				(*iter)->Show(depth+2) ;
			}
		}
	private:
		std::list<Company *> m_list ;
};



class FinanceDepartment:public Company
{
	public:
		FinanceDepartment(std::string name):Company(name){}
		 ~FinanceDepartment(){}
		void Show(int depth)
		{
			for(int i=0;i<depth;i++)
				std::cout<<"-";
			std::cout<<m_name_<<std::endl;
		}
};


class HRDepartment:public Company
{
	public:
		HRDepartment(std::string name):Company(name){}
		~HRDepartment(){}
		void Show(int depth)
		{
			
			for(int i=0;i<depth;i++)
				std::cout<<"-";
			std::cout<<m_name_<<std::endl;
		}
};
int main()
{
	Company *root = new ConcreteCompany("root") ;
	Company *root_finance = new FinanceDepartment("root_Finance") ;
	Company *root_hr = new HRDepartment("root_HR") ;
	root->Add(root_finance) ;
	root->Add(root_hr) ;

	Company *root_child1 = new ConcreteCompany("child_1");
	Company *child1_finance = new FinanceDepartment("child1_finance") ;
	Company *child1_hr = new HRDepartment("child1_hr") ;
	root_child1->Add(child1_finance) ;
	root_child1->Add(child1_hr) ;
	root->Add(root_child1) ;

	Company *root_child2 = new ConcreteCompany("child_2");
	Company *child2_finance = new FinanceDepartment("child2_finance") ;
	Company *child2_hr = new HRDepartment("child2_hr") ;
	
	root_child2->Add(child2_finance) ;
	root_child2->Add(child2_hr) ;
	root->Add(root_child2) ;

	root->Show(0) ;

	//release the ptr
	
	delete child2_hr;
	delete child2_finance ;
	delete root_child2 ;
	delete child1_hr ;
	delete child1_finance ;
	delete root_child1 ;
	delete root_hr ;
	delete root_finance ;
	delete root ;

	return 0 ;
}
