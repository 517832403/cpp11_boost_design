#include <iostream>
#include <string>
#include <map>
class Memento
{
	public:
		Memento(){}
		Memento(int activity,int attack,int defense)
			:m_activity_(activity),m_attack_(attack),m_defense_(defense){}

		Memento& operator=(const Memento &memento)
		{
			m_activity_ = memento.m_activity_ ;
			m_attack_ = memento.m_attack_;
			m_defense_ = memento.m_defense_ ;
			return *this ;
		}

		int m_activity_ ;
		int m_attack_ ;
		int m_defense_ ;
	
};

class GameRole
{
	public:
		GameRole():m_activity_(100),m_attack_(100),m_defense_(100){}
		Memento Save()
		{
			Memento memento(m_activity_,m_attack_,m_defense_);
			return memento ;
		}

		void Load(const Memento& memento)
		{
			m_activity_ = memento.m_activity_ ;
			m_attack_ = memento.m_attack_ ;
			m_defense_  = memento.m_defense_ ;
		}

		void Show()
		{
			std::cout<<"activity:"<<m_activity_<<" attack:"<<m_attack_<<" defense:"<<m_defense_<<std::endl;
		}

		void Attacked(int substract)
		{
			m_activity_-=substract ;
			if(m_activity_<0)
			{
				m_activity_ = 0 ;
				std::cout<<"die"<<std::endl;
			}
		}
	private:
		int m_activity_ ;
		int m_attack_ ;
		int m_defense_ ;
};


class Caretake
{
	public:
		Caretake(){}
		bool Save(const int state,const Memento memento) 
		{
			auto rlt = m_mapMemento_.insert(std::make_pair(state,memento)) ;
			return rlt.second ;
		}

		Memento Load(const int state)
		{
			return m_mapMemento_[state] ;
		
		}

	private:
		std::map<int,Memento> m_mapMemento_ ;
};
