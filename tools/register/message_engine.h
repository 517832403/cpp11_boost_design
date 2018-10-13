#ifndef MESSAGE_ENGINE_H_
#define MESSAGE_ENGINE_H_
#include <memory>
#include <assert.h>
#include "message_processor.h"

template<typename RegisterType,typename MessageSource,typename Message>
class MessageEngine
{
public:
	using MessageProcessorPtr = std::shared_ptr<MessageProcessor<RegisterType,MessageSource,Message> > ;
public:
	static MessageEngine* GetInstance()
	{
		static MessageEngine* instance = nullptr;
		if(instance == nullptr)
			instance = new MessageEngine();
		assert(instance) ;

		return instance ;
	}

	template<typename Processor>
	class MessageProcessorRegisterHelper
	{
	public:
		MessageProcessorRegisterHelper(RegisterType type)
		{
			MessageEngine<RegisterType,MessageSource,Message>::GetInstance()
				->RegisterProcessor(type,std::make_shared<Processor>());
		}
	};
	
	void RegisterProcessor(const RegisterType& type,MessageProcessorPtr processor)
	{
		m_message_processors_[type] = processor;
	}

	int32_t ProcessBuffer(char* data,uint32_t length,MessageSource& context)
	{
		// decode message 
		RegisterType type=123;
		Message message;
		auto processor = m_message_processors_[type] ;
		if (!processor)
		{
			return -1 ;
		}

		return processor->ProcessMessage(type,message,context);
	}

private:
	std::unordered_map<RegisterType,MessageProcessorPtr> m_message_processors_;
};

#endif