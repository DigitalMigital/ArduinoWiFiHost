#ifndef sergomor_Tickable_h
#define sergomor_Tickable_h

#include <Arduino.h>
#include <inttypes.h>

namespace sergomor
{

class Tickable
{
public:
	virtual void tick() = 0;

	void wait(uint32_t mls) { time = mls + millis(); }
	inline bool waiting() { return time > millis(); }

private:
	uint32_t time = 0;
};
}; // namespace sergomor

#endif