#ifndef sergomor_WifiMonitor_h
#define sergomor_WifiMonitor_h

#include <Arduino.h>
#include "../utils/Tickable.h"

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

namespace sergomor
{

class WifiMonitor : public Tickable
{
public:
	void tick();

private:
	wl_status_t status = WL_NO_SHIELD;
	uint8_t times_to_connect = 15;
};
}; // namespace sergomor
#endif