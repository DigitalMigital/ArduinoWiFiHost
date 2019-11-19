#ifndef visicount_NTPClock_h
#define visicount_NTPClock_h

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

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