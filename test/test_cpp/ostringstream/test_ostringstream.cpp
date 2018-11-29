#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <sstream>
class ABC
{
	public:
	ABC()
	{a=1,b=2,c=3;}
	int a;
	int b;
	int c;
};

class Handler
{
public:
	virtual void OnMessage(const std::shared_ptr<ABC>& abc)=0;
};

class DFHandler:public Handler
{
	public:
	virtual void OnMessage(const std::shared_ptr<ABC>& abc)
	{
		std::cout<<"DFHandler a:"<<abc->a<< " b:"<<abc->b<<std::endl;
		std::swap(abc->a,abc->b);
	}
};

class KHHandler:public DFHandler
{
	public:
	virtual void OnMessage(const std::shared_ptr<ABC>& abc)
	{
		DFHandler::OnMessage(abc);
		std::cout<<"KHHandler,a:"<<abc->a<<" b:"<<abc->b<<std::endl;
	}
};

int main()
{
	double positive = 4.015 ;
	double negative = -4.015;

	std::ostringstream ostring ;
	ostring << std::setprecision(2)<<std::fixed<<positive <<" -"<<-negative;
	std::cout<<ostring.str()<<std::endl;
	printf("%.2lf %.2lf\n",positive,negative);

	auto p = new KHHandler();
	auto abc = std::make_shared<ABC>();
	p->OnMessage(abc);
	return 0 ;
}
