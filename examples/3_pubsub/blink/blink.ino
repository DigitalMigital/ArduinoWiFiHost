#include "Blink.h"
#include "Led.h"

Blink publisher(LED_BUILTIN, 1000);
Led subscriber_one(6);
Led subscriber_two(7);

void setup()
{
	subscriber_one.subscribe(&publisher);
	subscriber_two.subscribe(&publisher);
}

void loop()
{
	publisher.tick();
}