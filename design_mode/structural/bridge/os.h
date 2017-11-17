#include <iostream>
using namespace std;


class OS
{
	public:
		virtual void InstallOSImpl() {} ;
} ;

class LinuxOS:public OS
{
	public:
		void InstallOSImpl()
		{
			cout<<"install linux os"<<endl;
		}
} ;

class WindowOS:public OS
{
	public:
		void InstallOSImpl()
		{
			cout<<"install windows os"<<endl;
		}
};

class UnixOS:public OS
{
	public:
		void InstallOSImpl()
		{
			cout<<"install unix os"<<endl;
		}
};
