#include "WebServer.h"
#include "FS.h"
#include "../utils/stream_op.h"
#include "WifiConfig.h"
#include "html.h"

namespace sergomor
{

void WebServer::begin()
{
	SPIFFS.begin();
	server->begin();
}

WebServer::WebServer()
{
	static AsyncWebServer s(80);
	server = &s;
	server->on("/index.html", HTTP_GET, [this](AsyncWebServerRequest *request) {
		indexHandle(request);
	});

	server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
		indexHandle(request);
	});

	server->on("/wifi", HTTP_POST, [](AsyncWebServerRequest *request) {
		WifiConfig &config = WifiConfig::instance();
		AsyncWebParameter *p;
		int params = request->params();

		for (int i = 0; i < params; i++)
		{
			p = request->getParam(i);

			if (p->name() == "ssid")
				config.ssid = p->value();
			if (p->name() == "pass")
				config.password = p->value();
		}

		if (config.ssid.length() > 0 && config.password.length() > 0 && config.save())
		{
			request->send(200, "text/plain", "WiFi Config Saved. Restarting board...");
			delay(500);
			ESP.restart();
		}

		request->send(200, "text/plain", "WiFi Config Not Saved.");
	});
}

void WebServer::indexHandle(AsyncWebServerRequest *request)
{
	request->send_P(200, "text/html", index_html);
	return;
}
} // namespace sergomor