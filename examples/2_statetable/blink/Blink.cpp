#include "Blink.h"
#include <Arduino.h>

Blink::Blink(uint8_t _pin, uint8_t _freq): pin(_pin), freq(_freq)
{
	pinMode(pin, OUTPUT);
	stateSet(OFF);
}

void Blink::tick()
{
	if (waiting()) return;

	switch(stateGet()) {
		case OFF:
			digitalWrite(pin, HIGH);
			stateSet(ON);
			break;
		case ON:
			digitalWrite(pin, LOW);
			stateSet(OFF);
	}

	wait(freq);
}