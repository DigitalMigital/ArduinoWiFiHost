#ifndef Blink_h
#define Blink_h

#include <ArduinoWiFiHost.h>

class Blink: public sergomor::Tickable
{
public:
	Blink(uint8_t, uint16_t);
	virtual void tick();

private:
	uint8_t pin;
	uint16_t freq;
};

#endif