#include <iostream>
struct B
{
	long long l;
};
//#pragma pack(1)
struct A
{

	//long long l ;
	//char a1;
	//short s1;
	int a ;
	B bb ;
	char b[] ;
};
//#pragma pack()

int main()
{

	std::cout<<sizeof(A)<<std::endl;
	return 0 ;
}
