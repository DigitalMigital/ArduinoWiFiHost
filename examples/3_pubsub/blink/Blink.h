#ifndef Blink_h
#define Blink_h

#include <ArduinoWiFiHost.h>

using namespace sergomor;

class Blink: public Tickable, public Publisher
{
public:
	Blink(uint8_t, uint8_t);
	virtual void tick();

	enum:state_t {
		OFF,
		ON
	};

private:
	uint8_t pin;
	uint8_t freq;
};

#endif