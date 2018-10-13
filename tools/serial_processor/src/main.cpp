#include "serial_processor.h"
#include <iostream>
int main()
{
	SerialProcessor::AddThread(1);

	auto serail_processor = std::make_shared<SerialProcessor>();
	serail_processor->Post([](){std::cout<<"this is SerialProcessor..."<<std::endl;});
	std::cout<<"sleep..."<<std::endl;
	usleep(1000);
	std::cout<<"wake up..."<<std::endl;
	SerialProcessor::Stop();
	return 0 ;
}