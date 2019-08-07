#ifndef sergomor_WebServer_h
#define sergomor_WebServer_h

#include <ESPAsyncWebServer.h>
#include "../utils/Stateable.h"

namespace sergomor
{

class WebServer : public Stateable
{
public:
	class CaptiveRequestHandler : public AsyncWebHandler
	{
	public:
		CaptiveRequestHandler() {}
		virtual ~CaptiveRequestHandler() {}

		bool canHandle(AsyncWebServerRequest *request)
		{
			return true;
		}

		void handleRequest(AsyncWebServerRequest *request);
	};

	WebServer()
	{
		server = new AsyncWebServer(80);
		stateSet(OFF);
	}

	~WebServer()
	{
		delete server;
	}

	void static indexHandle(AsyncWebServerRequest *request);

	void begin();

	enum : state_t
	{
		OFF,
		STARTED
	};

protected:
	virtual void setup();
	AsyncWebServer *webserver() { return server; }

private:
	AsyncWebServer *server;
};
}; // namespace sergomor
#endif