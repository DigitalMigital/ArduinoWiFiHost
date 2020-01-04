#include "Host.h"
#include "Updater.h"
#include "../utils/stream_op.h"
#include "NTPClock.h"
#include "WifiConfig.h"
#include "WebServer.h"

namespace sergomor
{

Host::Host()
{
	// setup wifi events
#if defined(ESP32)

	WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info) {
		debug << endl
			  << "Station connected, IP: " << WiFi.localIP() << endl;
	},
				 WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);

#elif defined(ESP8266)

	gotIpEventHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP &event) {
		debug << endl
			  << "Station connected, IP: " << WiFi.localIP() << endl;
		this->onConnect();
	});

	disconnectedHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected &event) {
		debug << endl
			  << "Station disconnected" << " " << disconnect_count << endl;

		if (--disconnect_count == 0) {
			WiFi.disconnect();
			// setup AP mode
			acessPoint();
		}
	});

#endif

}

void Host::acessPoint()
{
	static WebServer s;
	WiFi.mode(WIFI_AP);
	IPAddress netMsk(255, 255, 255, 0);
	IPAddress apIP(192, 168, 72, 1);
	WiFi.softAPConfig(apIP, apIP, netMsk);
	WiFi.softAP("ESP-000");
	delay(500);
	s.begin();
}

void Host::begin()
{
	WifiConfig &config = WifiConfig::instance();
	config.load();

	WiFi.mode(WIFI_STA);

	if (!config.ssid.length())
	{
		config.ssid = "badseed";
		config.password = "nopassword";
	}
	WiFi.begin(config.ssid.c_str(), config.password.c_str());
	debug << "begin WiFi: " << config.ssid << endl;
}

} // namespace sergomor