#include <iostream>

class CaffeineBeverage
{
	public:
		void PrepareReciepe()
		{
			BoilWater() ;
			OnBrew() ;
			PourInCup() ;
			OnAddConiments() ;
		}
		virtual void OnBrew(){}
		virtual void OnAddConiments() {}
		
		void BoilWater()
		{
			std::cout<<"Boil Water"<<std::endl;
		}

		void PourInCup()
		{
			std::cout<<"Pour the coffee to a cup"<<std::endl;
		}
};

class Coffee:public CaffeineBeverage
{
	public:
		void OnBrew() override
		{
			std::cout<<"using the boiling water to pour the coffee "<<std::endl;
		}

		void OnAddConiments() override
		{
			std::cout<<"add sugger and milk"<<std::endl;
		}
};

class Tea:public CaffeineBeverage
{
	public:
		void OnBrew() override
		{
			std::cout<<"using the boiling water to pour the tea"<<std::endl;
		}

		void OnAddConiments() override
		{
			std::cout<<"add lemon"<<std::endl;
		}
};


