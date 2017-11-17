#include <iostream>
#include <vector>
class Productor
{
	public:
		std::vector<int> m_vector_ ;
};

class Builder
{
	public:
		Builder(){}
		virtual ~Builder(){}
		virtual void BuildPartA()=0 ;
		virtual void BuildPartB()=0 ;
		virtual void print() = 0 ;	
};

class Director
{
	public:
		Director(Builder *builder):m_builder_(builder){}
		~Director()
		{
			delete m_builder_ ;
		}
		void Construct()
		{
			m_builder_->BuildPartA() ;
			m_builder_->BuildPartB() ;
		}
	private:
		Builder * m_builder_ ;

};

class ConcreBuilder:public Builder
{
	public:
		ConcreBuilder()
		{
			m_productor_  = new Productor;
		}

		~ConcreBuilder()
		{
			delete m_productor_ ;
		}

		void BuildPartA()
		{
			m_productor_->m_vector_.push_back(12) ;
			std::cout<<"construct Part A"<<std::endl;
		}

		void BuildPartB()
		{
			m_productor_->m_vector_.push_back(13) ;
			std::cout<<"construct Part B"<<std::endl;
		}

		void print()
		{
			std::vector<int>::iterator pos ;
			for(pos = m_productor_->m_vector_.begin();pos != m_productor_->m_vector_.end();++pos)
				std::cout<< *pos << std::endl;
			return ;
		}

		Productor& GetResult()
		{
			return *m_productor_ ;
		}
	private:
		Productor *m_productor_ ;
};

int main()
{
	ConcreBuilder *builder = new ConcreBuilder() ;
	Director *director = new Director(builder) ;
	director->Construct() ;
	Productor productor = builder->GetResult() ;
	builder->print() ;

	delete director ;
	
	std::cout<<"over"<<std::endl;
	return 0 ;
}

