#ifndef ATOMIC_H_
#define ATOMIC_H_

#include <stdint.h>
#include <assert.h>

#ifndef NAMESPACE
#ifndef LIB
#define NAMESPACE tool_lib
#else
#define NAMESPACE tool
#endif
#endif


namespace NAMESPACE
{
class Atomic
{
	public:
		using RefType = uint32_t ;
		
		Atomic()
		{
			m_reference_ = new RefType ;
			assert(m_reference) ;
			*m_reference_ = 1 ;
		}

		Atomic(const Atomic& atomic)
		{
			m_reference_ = atomic.m_reference_ ;
			__sync_fetch_and_add(m_reference_,1);
		}

		Atomic operator=(const Atomic& atomic)
		{
			if(&atomic != this)
			{
				Reset() ;
				m_reference_ = atomic.m_reference_ ;
			       	__sync_fetch_and_add(m_reference_,1);	
			}

			return *this ;
		}

		~Atomic()
		{
			Reset();
		}

		void Reset()
		{
			if(*m_reference_ == 0)
			{
				delete m_reference_ ;
			}
			else
			{
				__sync_fetch_and_sub(m_reference_,1) ;
			}
		}

		RetType reference()
		{
			return *m_reference_ ;
		}

	private:
		RefType* m_reference_ = nullptr ;
};

}

#endif
