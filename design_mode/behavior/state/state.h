#ifndef STATE_H_
#define STATE_H_
#include <iostream>
class Tank;
class ISiegeTankState
{
	public:
		ISiegeTankState(Tank *tank):m_tank_(tank){}
		virtual void move()=0 ;
		virtual void attack()=0 ;
	protected:
		void changeState(ISiegeTankState *state) ;
	private:
		Tank *m_tank_ ;
};

class SiegeState:public ISiegeTankState
{
	public:
		SiegeState(Tank *tank):ISiegeTankState(tank){}
		void move() override 
		{
			std::cout<<"siege state cannot move"<<std::endl;
		}

		void attack() override
		{
			std::cout<<"attack 100...."<<std::endl;
		}
};

class TankState:public ISiegeTankState
{
	public:
		TankState(Tank* tank):ISiegeTankState(tank){}
		void move() override
		{
			std::cout<<"tank state,moving"<<std::endl;
		}

		void attack() override
		{
			std::cout<<"attack 10.."<<std::endl;
		}
};

class Tank
{

	public:
		Tank()
		{
		}
		~Tank()
		{
			delete m_siege_state_ ;
			delete m_tank_state_ ;
		}
		void init()
		{
			m_siege_state_ = new SiegeState(this) ;
			m_tank_state_ = new TankState(this) ;
			m_cur_state_ = m_tank_state_ ;
		}
		void attack()
		{
			if(m_cur_state_)
			{
				m_cur_state_->attack() ;
			}
			else
			{
				std::cout<<"unknow state"<<std::endl;
			}
		}
		
		void enterTankState()
		{
			m_cur_state_ = m_tank_state_ ;
			std::cout<<"enter the tank mode state."<<std::endl;
		}

		void enterSiegeState()
		{
			m_cur_state_  = m_siege_state_ ;
			std::cout<<"enter the siege mode state."<<std::endl;
		}

		void move()
		{
			if(m_cur_state_)
			{
				m_cur_state_->move() ;
			}
			else
			{
				std::cout<<"unknow state. cannot move now."<<std::endl;
			}
		}
	private:
		friend class ISiegeTankState ;
		
		void changeState(ISiegeTankState *state)
		{
			m_cur_state_ = state ;
		}

		ISiegeTankState *m_cur_state_ ;
		SiegeState *m_siege_state_ ;
		TankState * m_tank_state_ ;	
};

#endif
