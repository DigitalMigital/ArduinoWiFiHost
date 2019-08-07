#include <ArduinoWiFiHost.h>

using namespace sergomor;

struct Person
{
	String name;
	uint8_t age;
};

Person* a;
Person b;
uint8_t buff[200];

void setup()
{
	Serial.begin(115200);
	delay(200);

	a = new Person();

	a->name = "Sara";
	a->age = 20;

	DataStream s(buff, 200);
	s << *a;

	s >> b;

	Serial << b.name << " " << b.age << endl;

}

void loop()
{
}