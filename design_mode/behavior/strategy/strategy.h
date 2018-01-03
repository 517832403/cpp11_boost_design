#ifndef STRATEGY_H_
#define STRATEGY_H_
#include <iostream>

class WeaponBehavior
{

	public:
		virtual void  useWeapon() = 0 ;
};

class AK47 : public WeaponBehavior
{

	public:
		void useWeapon() override
		{
			std::cout<<"Use AK47 to shoot"<<std::endl;
		}
};

class Knife:public WeaponBehavior
{

	public:
		void useWeapon() override
		{
			std::cout<<"Use knife to kill"<<std::endl;
		}
};

class Character
{
	public:
		Character()
		{
			weapon = NULL ;
		}
		void SetWeapon(WeaponBehavior *w)
		{
			this->weapon = w ;
		}
		virtual void fight() = 0 ;
	
	protected:
		WeaponBehavior *weapon ;	
};

class King :public Character
{

	public:
		void fight() override
		{
			std::cout<<"The King:";
			if(weapon == NULL)
			{
				std::cout<<" you don't have a weapon,please set Weapon"<<std::endl;
			}
			else
			{
				weapon->useWeapon() ;
			}
		}
};

#endif
