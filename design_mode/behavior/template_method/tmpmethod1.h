#include <iostream>

template<typename T>
class CaffeineBeverage
{
	public:
		void PrepareReciepe()
		{
			BoilWater() ;
			Brew() ;
			PourInCup() ;
			AddCondiments() ;
		}

		void BoilWater()
		{
			std::cout<<"boil water"<<std::endl;
		}

		void Brew()
		{
			(static_cast<T*>(this))->Brew() ;
		}

		void PourInCup()
		{
			std::cout<<"pour the coffee to cup"<<std::endl;
		}

		void AddCondiments()
		{
			(static_cast<T*>(this))->AddConiments() ;
		}
};

class Coffee :public CaffeineBeverage<Coffee>
{
	public:
		void Brew()
		{
			std::cout<<"make coffee"<<std::endl;
		}

		void AddConiments()
		{
			std::cout<<"add sugger and milk"<<std::endl;
		}
};

class Tea:public CaffeineBeverage<Tea>
{
	public:
		void Brew()
		{
			std::cout<<"make tea"<<std::endl;
		}
		void AddConiments()
		{
			std::cout<<"add lemon juice"<<std::endl;
		}
};
