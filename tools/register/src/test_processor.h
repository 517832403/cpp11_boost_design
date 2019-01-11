#ifndef TEST_PROCESSOR_H_
#define TEST_PROCESSOR_H_

#include <string>
#include "message_processor.h"

class TestProcessor : public MessageProcessor<int32_t,std::string,std::string>
{
public:
	int32_t ProcessMessage(int32_t& type,std::string message,std::string source) override;
};


#endif