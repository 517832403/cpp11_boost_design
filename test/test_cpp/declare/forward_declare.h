#include <memory>
#ifndef FORWARD_DECLARE_H_
#define FORWARD_DECLARE_H_

class A1;

template<typename A>
class A2;

template<typename T1,typename T2>
class A3;



class A4
{
public:
	void test();
private:
	std::shared_ptr< A3<A1,A2<int> > > m;
};

#endif
