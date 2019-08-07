#include "Blink.h"

Blink led_one(LED_BUILTIN, 1000);
Blink led_two(6, 500);

void setup()
{
}

void loop()
{
	led_one.tick();
	led_two.tick();
}