#ifndef AGW_MESSAGE_ENGINE_H_
#define AGW_MESSAGE_ENGINE_H_
#include <iostream>

template<typename buf,typename msg>
class MessageEngine;


class AgwMsgEngine
{
public:

	//using engine = ;
	AgwMsgEngine();

	void test() {

	};

private:
	MessageEngine<int,double> *m_engine_ ;
};

#endif