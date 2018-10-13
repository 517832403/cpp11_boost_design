
#ifndef REGISTER_FACTORY_H_
#define REGISTER_FACTORY_H_

#include<unordered_map>

template<typename RegisterType,typename MessageSource,typename Message>
class MessageProcessor
{
public:
	virtual int32_t ProcessMessage(RegisterType& type,Message message,MessageSource source)
	{
		return 0 ;
	}
};


#define REGISTER_MESSAGE_PROCESSOR(MsgEngine,message_type,MsgProcessor) \
	static MsgEngine::MessageProcessorRegisterHelper<MsgProcessor> \
		_register(message_type);


#endif