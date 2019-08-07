#ifndef Led_h
#define Led_h

#include <ArduinoWiFiHost.h>

using namespace sergomor;

class Led: public Subscriber
{
public:
	Led(uint8_t);
	virtual void onState(Publisher*);

private:
	uint8_t pin;
};

#endif