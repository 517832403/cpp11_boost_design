#include "msg_engine.h"
#include "AgwMsgEngine.h"

AgwMsgEngine::AgwMsgEngine()
{
	std::cout<<" This is AgwMsgEngine..."<<std::endl;
	m_engine_ = new MessageEngine<int,double>() ;
}

void test()
{
	std::cout<<" This is Test method.."<<std::endl;
}
