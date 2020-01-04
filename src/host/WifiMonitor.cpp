#include "WifiMonitor.h"
#include "../utils/stream_op.h"
#include <TailEffect.h>

namespace sergomor
{

void WifiMonitor::tick()
{
	static uint8_t times = 0;
	static TailEffect leds;
	leds.tick();

	if (waiting())
		return;

	wl_status_t _status = WiFi.status();

	if (status != _status && _status != WL_CONNECTED)
	{
		leds.begin(CRGB(10, 10, 0), 50, 0);
		debug << "connect to wifi" << endl;
	}

	if (_status != WL_CONNECTED && times_to_connect > times++)
	{
		debug << ".";
	}
	else if (times_to_connect < times)
	{
		debug << endl
			  << "connection failed" << endl;
		times = 0;
		leds.end();
	}

	if (_status == WL_CONNECTED && status != _status)
	{
		debug << "connected to " << WiFi.gatewayIP() << " with " << WiFi.localIP()
			  << endl;
		leds.end();
	}

	status = _status;

	wait(1000);
}

} // namespace sergomor