
#ifndef MESSAGE_ENGINE_H_
#define MESSAGE_ENGINE_H_

#include <iostream>

template<typename buffer,typename msg>
class MessageEngine
{
public:
	MessageEngine()
	{
		std::cout<<" This is MessageEngine..."<<std::endl;
	}
};


#endif