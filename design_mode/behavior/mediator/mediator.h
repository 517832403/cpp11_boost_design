#include <iostream>
#include <string>

class Mediator ;
class Person
{
	protected:
		Mediator *m_mediator_ ;
	public:
		virtual void SetMediator(Mediator *mediator){} 
		virtual void SendMessage(std::string message) {}
		virtual void GetMessage(std::string message){}
};

class Mediator
{
	public:
		virtual void send(std::string message,Person *person){}
		virtual void SetA(Person *a) {}
		virtual void SetB(Person *b) {}
};


class Renter : public Person
{
	public:
		void SetMediator(Mediator *mediator) override
		{
			m_mediator_ = mediator ;
		}

		void SendMessage(std::string message) override
		{
			m_mediator_->send(message,this) ;
		}

		void GetMessage(std::string message) override
		{
			std::cout<<"renter recv the message:"<<message<<std::endl;
		}
};

class Landlord :public Person
{
	public:
		void SetMediator(Mediator *mediator) override
		{
			m_mediator_ = mediator ;
		}

		void SendMessage(std::string message) override
		{
			m_mediator_->send(message,this) ;
		}

		void GetMessage(std::string message) override
		{
			std::cout<<"The landlord recv the message:"<<message<<std::endl;
		}
};

class HouseMediator :public Mediator
{
	public:
		HouseMediator():m_a_(0),m_b_(0){}
		void SetA(Person *a) override
		{
			m_a_ = a ;
		}
		void SetB(Person *b) override
		{
			m_b_ = b ;
		}

		void send(std::string message,Person *person) override
		{
			if(person == m_a_)
			{
				m_b_->GetMessage(message) ;
			}
			else
			{
				m_a_->GetMessage(message) ;
			}
		}
	private:
		Person *m_a_ ;//renter
		Person *m_b_ ;//landlord
};


