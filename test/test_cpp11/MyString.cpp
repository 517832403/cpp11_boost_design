#include <iostream>
#include <vector>
#include <string.h>
class MyString
{
	private:
		char * m_data ;
		size_t m_len ;
	private:
		void CopyData(const char* data)
		{
			m_data = new char[m_len+1] ;
			memcpy(m_data,data,m_len) ;
			m_data[m_len] = '\0';
		}
	public:
		MyString()
		{
			m_data = NULL ;
			m_len  = 0 ;
			std::cout<<"Default constructor"<<std::endl;
		}
		MyString(const char* p)
		{
			m_len = strlen(p) ;
			CopyData(p) ;
			std::cout<<" Constructor with parameter char*"<<std::endl;
		}
		MyString(const MyString& str)
		{
			m_len = str.m_len ;
			CopyData(str.m_data) ;
			std::cout<<"copy constructor is called."<<std::endl;
		}
		MyString& operator=(const MyString& str)
		{
			if(this != &str)
			{
				m_len = str.m_len ;
				CopyData(str.m_data) ;
				std::cout<<"Copy Assignment is called."<<std::endl;
			}
		}

		MyString(MyString&& str)
		{
			std::cout<<"move constructor is called."<<std::endl;
			m_len = str.m_len ;
			m_data = str.m_data ;
			str.m_data = NULL ;
			str.m_len = 0 ;
		}
		MyString& operator=(MyString&& str)
		{
			if(this != &str)
			{
				std::cout<<"move assignment is called."<<std::endl;
				m_len = str.m_len ;
				m_data = str.m_data ;
				str.m_data = NULL ;
				str.m_len = 0 ;
			}
		}
		virtual ~MyString()
		{
			if(m_data)
			{
				free(m_data) ;
				m_data = NULL ;
			}
		}
};


int main()
{
	MyString a;
	a = MyString("Hello") ;
	std::vector<MyString> vec ;
	vec.push_back(MyString("World")) ;
	return 0 ;
}
