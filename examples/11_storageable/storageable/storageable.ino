#include <ArduinoWiFiHost.h>

using namespace sergomor;

constexpr char filename[] = "person";
struct Person: public Storageable<Person, filename>
{
	String name;
	uint8_t age;

	size_t length(){ return name.length() + 1 + sizeof(age); }
	virtual OStreambuff& output(OStreambuff& os){ return os << name << age; }
	virtual IStreambuff& input(IStreambuff& is){ return is >> name >> age; }
};

Person a, b;
uint8_t buff[200];

void setup()
{
	Serial.begin(115200);
	delay(200);

	a.name = "Sara";
	a.age = 20;

	a.save();

	b.load();

	Serial << b.name << " " << b.age << endl;

}

void loop()
{
}