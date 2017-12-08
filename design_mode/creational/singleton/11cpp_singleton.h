#include <stdexcept>
#include <utility>

template<typename T>
class Singleton
{
	public:
		template<typename... Args>
		static T* Instance(Args&&... args)
		{
			if(m_pInstance_ == nullptr)
			{
				m_pInstance_ = new T(std::forward<Args>(args)...) ;
			}
			return m_pInstance_ ;
		}

		static T* GetInstance()
		{
			if(m_pInstance_ == nullptr)
			{
				throw std::logic_error("the instance is not init,please initialize the instance first") ;
			}
			return m_pInstance_ ;
		}

		static void DestoryInstance()
		{
			if(m_pInstance_ == nullptr) 
				return ;
			delete m_pInstance_ ;
			m_pInstance_ = nullptr ;
		}


	
	private:
		static T* m_pInstance_ ;
};

template<typename T>
T* Singleton<T>::m_pInstance_ = nullptr ;

