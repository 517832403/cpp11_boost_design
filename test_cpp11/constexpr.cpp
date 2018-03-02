#include <iostream>


class Circle
{
	public:
		constexpr Circle(int x,int y,int radius):x_(x),y_(y),radius_(radius){}
		constexpr double getArea() 
		{
			return radius_ * radius_ * 3.14 ;
		}
	private:
		int x_ ;
		int y_ ;
		int radius_ ;
};

constexpr int f(int n)
{
	return n > 0 ? n*f(n-1) :1 ;
}

int main()
{
	f(10) ;
	int i=0 ;
	f(i) ;

	constexpr Circle c(1,1,10) ;
	auto area = c.getArea() ;

	return 0 ;
}
