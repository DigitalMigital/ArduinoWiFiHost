#include "Host.h"
#include "Updater.h"
#include "../utils/stream_op.h"
#include "NTPClock.h"
#include "WifiConfig.h"

namespace sergomor
{

Host::Host()
{
	// setup wifi events
#if defined(ESP32)

	WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info) {
		debug << endl
			  << "Station connected, IP: " << WiFi.localIP() << endl;
		stateSet(BEGIN_UPDATE);
	},
				 WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);

#elif defined(ESP8266)

	gotIpEventHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP &event) {
		debug << endl
			  << "Station connected, IP: " << WiFi.localIP() << endl;
		stateSet(BEGIN_UPDATE);
	});

	disconnectedHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected &event) {
		debug << endl
			  << "Station disconnected" << endl;
		//stateSet(BEGIN_WEB_SERVER);
	});

#endif

	stateSet(OFF);
}

void Host::begin()
{
	WifiConfig config;
	config.load();

	WiFi.mode(WIFI_AP_STA);

	String ssid("eps8266-" + ESP.getChipId());
	//if (config.ap_ssid.length())
	//	ssid = config.ap_ssid;
	Serial << "AP SSID: " << ssid << endl;

	IPAddress netMsk(255, 255, 255, 0);
	IPAddress apIP(192, 168, 72, 1);
	//if (config.ap_ipaddress.length())
	//	apIP.fromString(config.ap_ipaddress);

	WiFi.softAPConfig(apIP, apIP, netMsk);
	WiFi.softAP(ssid.c_str());
	delay(500);
	Serial << "AP IP: " << WiFi.softAPIP() << endl;

	if (!config.ssid.length())
	{
		config.ssid = "badseed";
		config.password = "nopassword";
	}
	WiFi.begin(config.ssid.c_str(), config.password.c_str());
}

void Host::tick()
{
	wifi_monitor.tick();

	//Serial << WiFi.status() << endl;

	if (WiFi.status() == WL_DISCONNECTED) // WL_CONNECT_FAILED
		webserver->begin();

	switch (stateGet())
	{

	case BEGIN_UPDATE:
		Updater::begin();
		if (webserver != nullptr)
			stateSet(BEGIN_WEB_SERVER);
		break;

	case BEGIN_WEB_SERVER:
		webserver->begin();
		stateSet(READY);
		break;
	}
}
} // namespace sergomor