#ifndef sergomor_WebServer_h
#define sergomor_WebServer_h

#include <ESPAsyncWebServer.h>

namespace sergomor
{

class WebServer
{
public:
	WebServer();
	void static indexHandle(AsyncWebServerRequest *request);
	void begin();

protected:

private:
	AsyncWebServer* server;
};
}; // namespace sergomor
#endif