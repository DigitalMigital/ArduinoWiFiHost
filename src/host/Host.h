#ifndef sergomor_Host_h
#define sergomor_Host_h

#include <Arduino.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include "WebServer.h"
#include "../utils/Stateable.h"
#include "../utils/Tickable.h"
#include "WifiMonitor.h"

namespace sergomor
{

class Host
{
public:
	Host();

	void begin();
	const uint32_t id()
	{
#if defined(ESP32)
		return 111;
#elif defined(ESP8266)
		return ESP.getChipId();
#endif
	}

protected:
	virtual void onConnect() {}
private:
	void acessPoint();

	uint8_t disconnect_count = 4;

#if defined(ESP8266)
	WiFiEventHandler gotIpEventHandler;
	WiFiEventHandler disconnectedHandler;
#endif
};
}; // namespace sergomor
#endif