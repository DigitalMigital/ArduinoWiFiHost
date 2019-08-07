#include "Blink.h"
#include <Arduino.h>

Blink::Blink(uint8_t _pin, uint16_t _freq)
    : pin(_pin)
    , freq(_freq)
{
    pinMode(pin, OUTPUT);
}

void Blink::tick()
{
    static uint8_t state = LOW;
    if (waiting())
        return;

    digitalWrite(pin, state = state == LOW ? HIGH : LOW);

    wait(freq);
}