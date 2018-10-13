#include "test_processor.h"
#include "message_engine.h"
#include <iostream>

using MessageEngineIntStrStr = MessageEngine<int32_t,std::string,std::string>; 

REGISTER_MESSAGE_PROCESSOR(MessageEngineIntStrStr,123,TestProcessor);

int32_t TestProcessor::ProcessMessage(int32_t& type,std::string message,std::string source)
{
	std::cout<<"This is Test Processor."<<std::endl;
	return 0 ;
}