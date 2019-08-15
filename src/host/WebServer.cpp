#include "WebServer.h"
#include "FS.h"
#include "../utils/stream_op.h"
#include "WifiConfig.h"
#include "UpdaterConfig.h"
#include <DNSServer.h>
#include "html.h"
#include "UpdaterConfig.h"

namespace sergomor
{

void WebServer::CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request)
{
	WebServer::indexHandle(request);
}

void WebServer::begin()
{
	static bool server_started = false;
	if (!server_started)
	{
		setup();
		server->begin();
		stateSet(STARTED);
		debug << "Start WebServer at " << WiFi.localIP() << endl;
		server_started = true;
	}
}

void WebServer::setup()
{
	static DNSServer dnsServer;
	static bool dns_started = false;

	SPIFFS.begin();

	int mode = WiFi.getMode();
	if (mode == WIFI_AP || mode == WIFI_AP_STA)
	{
		if (!dns_started)
		{
			dnsServer.start(53, "*", WiFi.softAPIP());
			debug << "start DNS Server" << endl;
			dns_started = true;
		}
		//server->addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
	}

	server->on("/index.html", HTTP_GET, [this](AsyncWebServerRequest *request) {
		indexHandle(request);
	});

	server->on("/index.html.gz", HTTP_GET, [this](AsyncWebServerRequest *request) {
		indexHandle(request);
	});

	server->on("/style.css.gz", HTTP_GET, [](AsyncWebServerRequest *request) {
		AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/style.css.gz", "text/css");
		response->addHeader("Content-Encoding", "gzip");
		request->send(response);
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

		if (!SPIFFS.exists("/index.html.gz"))
		{
			UpdaterConfig &cfg = UpdaterConfig::instance();
			cfg.load();
			if (!cfg.enable)
			{
				cfg.enable = 1;
				cfg.save();
			}
		}

		if (config.ssid.length() > 0 && config.password.length() > 0 && config.save())
		{
			request->send(200, "text/plain", "WiFi Config Saved. Restarting board...");
			delay(500);
			ESP.restart();
		}

		request->send(200, "text/plain", "WiFi Config Not Saved.");
	});

	server->on("/ota", HTTP_POST, [](AsyncWebServerRequest *request) {
		UpdaterConfig &cfg = UpdaterConfig::instance();
		AsyncWebParameter *p;
		int params = request->params();

		cfg.enable = 0;

		for (int i = 0; i < params; i++)
		{
			p = request->getParam(i);

			//if (p->name() == "host") config.host = p->value();
			//if (p->name() == "fingerprint") config.fingerprint = p->value();
			if (p->name() == "enable")
				cfg.enable = p->value().toInt();
		}

		debug << "enable remote: " << cfg.enable << endl;

		cfg.save();

		request->send(200, "text/plain", "OTA Config Saved.");
	});
}

void WebServer::indexHandle(AsyncWebServerRequest *request)
{
	SPIFFS.begin();

	if (!SPIFFS.exists("/index.html.gz"))
	{
		request->send_P(200, "text/html", index_html);
		return;
	}

	AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.html.gz", "text/html");
	response->addHeader("Content-Encoding", "gzip");
	request->send(response);
}
} // namespace sergomor