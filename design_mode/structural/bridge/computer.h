

#include <iostream>
#include "os.h"
using namespace std ;


class Computer
{
	public:
		virtual void InstallOS(OS *os){}
};

class Dell:public Computer
{
	public:
		void InstallOS(OS *os)
		{
			dellInstall() ;
			os->InstallOSImpl() ;
		}
	private:
		void dellInstall()
		{
			cout<<"dell install os..."<<endl;
		}
};

class Apple:public Computer
{
	public:
		void InstallOS(OS *os)
		{
			appleInstall() ;
			os->InstallOSImpl() ;
		}
	private:
		void appleInstall()
		{
			cout<<"apple install os..."<<endl;
		}
};


