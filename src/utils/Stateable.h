#ifndef sergomor_Stateable_h
#define sergomor_Stateable_h

#include <inttypes.h>

namespace sergomor
{

typedef uint8_t state_t;

class Stateable
{
public:
	state_t stateGet() { return state; }
	virtual void stateSet(state_t new_state) { state = new_state; }

private:
	state_t state;
};
} // namespace sergomor

#endif