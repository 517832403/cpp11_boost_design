#include <iostream>
#include <boost/timer.hpp>
using namespace std;

int main()
{
	boost::timer t ;
	cout <<"max timespan:"<< t.elapsed_max()/3600<<"h"<<endl;
	cout <<"min timespan:"<< t.elapsed_min() <<"s"<<endl;
	
	return 0 ;
}
