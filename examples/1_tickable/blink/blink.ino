#include "Blink.h"

Blink led(D0, 1000);

void setup()
{
}

void loop()
{
    led.tick();
}