#include "message_engine.h"

int main()
{
	const std::string str("123");
	std::string source("123456");
	MessageEngine<int32_t,std::string,std::string>::GetInstance()
		->ProcessBuffer(const_cast<char*>(str.c_str()),str.length(),source);
	return 0 ;
}