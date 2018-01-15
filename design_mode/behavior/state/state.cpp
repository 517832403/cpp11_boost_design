#include "state.h"

void ISiegeTankState::changeState(ISiegeTankState *state)
{
	m_tank_->changeState(state) ;
}

