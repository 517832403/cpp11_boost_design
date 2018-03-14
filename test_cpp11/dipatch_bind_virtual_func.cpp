#include <iostream>
#include <functional>
/*
 * 验证绑定虚函数时的调用问题
 * */
struct Base
{
	Base()
	{
		m_func_ = std::bind(&Base::DoClose,this) ;
	}
	virtual void DoClose()
	{
		std::cout<<"base DoClose"<<std::endl;
	}
	void Close()
	{
		m_func_() ;
	}

	typedef std::function<void()> Func ;
	Func m_func_ ;
};

struct D :public Base
{
	void DoClose() override
	{
		std::cout<<"D DoClose"<<std::endl;
	}
};

int main()
{
	Base *p_base = new D() ;
	p_base->Close() ;
	delete p_base ;
	return 0 ;
}
