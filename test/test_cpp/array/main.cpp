#include <iostream>
struct A
{
	A(int a){}
	//A(const int a){}
};
int main()
{
	const char arr[]="abcdef" ;
	std::cout<<"arr[3]:"<<arr[3]<<" 3[arr]:"<<3[arr]<<std::endl;
	return 0 ;
}
