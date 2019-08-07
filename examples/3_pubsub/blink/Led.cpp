#include "Led.h"
#include "Blink.h"
#include <Arduino.h>

Led::Led(uint8_t _pin): pin(_pin)
{
	pinMode(pin, OUTPUT);
}

void Led::onState(Publisher* p)
{
	switch (p->stateGet()) {
		case Blink::ON:
			digitalWrite(pin, LOW);
			break;
		case Blink::OFF:
			digitalWrite(pin, HIGH);
	}
}