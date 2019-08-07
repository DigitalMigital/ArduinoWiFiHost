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

class Host : public Stateable, public Tickable
{
public:
	Host();

	virtual void tick();
	virtual void stateSet(state_t new_state)
	{
		Stateable::stateSet(new_state);
		onState(stateGet());
	}
	virtual void onState(state_t){};
	void webServerSet(WebServer *server) { webserver = server; }

	void begin();
	const uint64_t id() { return ESP.getChipId(); }
	void setup();

	enum : state_t
	{
		OFF,
		ON,
		BEGIN_UPDATE,
		BEGIN_WEB_SERVER,
		READY,

		LAST // for child states
	};

protected:
	WebServer *webserver = nullptr;

private:
	WifiMonitor wifi_monitor;

#if defined(ESP8266)
	WiFiEventHandler gotIpEventHandler;
	WiFiEventHandler disconnectedHandler;
#endif
};
}; // namespace sergomor
#endif