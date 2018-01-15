#include <iostream>
#include <vector>

class RoastCook
{

	public:
		void MakeMutton() {std::cout<<"make mutton"<<std::endl;}
		void MakeChickenWing() { std::cout<<"make chicken wing"<<std::endl;}
};

class Command
{
	public:
		Command(RoastCook *roast_cook){m_roast_cook_ = roast_cook;}
		virtual void ExecCmd() = 0 ;
	protected:
		RoastCook *m_roast_cook_ ;
};

class MakeMuttonCmd:public Command
{

	public:
		MakeMuttonCmd(RoastCook *roast_cook):Command(roast_cook){}
		void ExecCmd(){ m_roast_cook_->MakeMutton() ;}	
};

class MakeChickenWingCmd:public Command
{
	public:
		MakeChickenWingCmd(RoastCook *roast_cook):Command(roast_cook){}
		void ExecCmd(){ m_roast_cook_->MakeChickenWing() ;}
};

class Waiter
{
	public:
		void SetCmd(Command *cmd)
		{
			m_command_vec_.push_back(cmd) ;
			std::cout<<"add new command"<<std::endl;
		}

		void Notify()
		{
			std::vector<Command*>::iterator iter ;
			for(iter  = m_command_vec_.begin();iter != m_command_vec_.end();iter++)
			{
				(*iter)->ExecCmd() ;
			}
		}
	protected:
		std::vector<Command*> m_command_vec_ ;
};
