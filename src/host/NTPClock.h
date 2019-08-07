#ifndef visicount_NTPClock_h
#define visicount_NTPClock_h

#include <ESP8266WiFi.h>

namespace sergomor
{

class NTPClock
{
private:
	static IPAddress timeServerIP;
	static const char *ntpServerName;
	static uint32_t epoch;
	static uint32_t local_time;

public:
	bool static begin();
	bool static sync();
	uint32_t static time();
};
}; // namespace sergomor
#endif