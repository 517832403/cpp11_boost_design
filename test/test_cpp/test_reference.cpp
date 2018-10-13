#include <iostream>


class A
{
	public:
	int& Add()
	{
		++a ;
		return a ;
	}
	private:
		int a=0 ;	
};

int main()
{
	A tmp ;

	int& b = tmp.Add() ;
       	std::cout<<"b:"<<b<<"a:"<<++tmp.Add()<<tmp.Add()<<std::endl;
	return 0 ;	
}
