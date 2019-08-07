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
		Serial << "Start WebServer at " << WiFi.localIP() << endl;
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
			Serial << "start DNS Server" << endl;
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
		WifiConfig config;
		AsyncWebParameter *p;
		String anchor("save-error");
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
			UpdaterConfig cfg;
			cfg.load();
			if (!cfg.enable)
			{
				cfg.enable = 1;
				cfg.save();
			}
		}

		if (config.ssid.length() > 0 && config.password.length() > 0 && config.save())
		{
			request->redirect("/#restart");
			delay(500);
			ESP.restart();
		}

		request->redirect("/#" + anchor);
	});

	server->on("/ota", HTTP_POST, [](AsyncWebServerRequest *request) {
		UpdaterConfig config;
		AsyncWebParameter *p;
		String anchor("save-error");
		int params = request->params();

		for (int i = 0; i < params; i++)
		{
			p = request->getParam(i);

			//if (p->name() == "host") config.host = p->value();
			//if (p->name() == "fingerprint") config.fingerprint = p->value();
			if (p->name() == "enable")
				config.enable = p->value().toInt();
		}

		Serial << "enable remote: " << config.enable << endl;

		if (config.save())
		{
			anchor = "save-ok";
		}

		request->redirect("/#" + anchor);
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