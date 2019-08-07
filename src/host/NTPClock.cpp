#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include "NTPClock.h"

namespace sergomor
{

IPAddress NTPClock::timeServerIP = IPAddress();
const char *NTPClock::ntpServerName = "time.nist.gov";
uint32_t NTPClock::epoch = 0;
uint32_t NTPClock::local_time = 0;

bool NTPClock::begin()
{
	WiFi.hostByName(ntpServerName, timeServerIP);
	Serial.println("Resolve NTP Server");
	Serial.print("NTP server IP: ");
	Serial.println(timeServerIP);
	return sync();
}

bool NTPClock::sync()
{
	WiFiUDP udp;
	udp.begin(2390);
	uint8_t packetBuffer[48];
	Serial.println("sending NTP packet...");
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, 48);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011; // LI, Version, Mode
	packetBuffer[1] = 0;		  // Stratum, or type of clock
	packetBuffer[2] = 6;		  // Polling Interval
	packetBuffer[3] = 0xEC;		  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	udp.beginPacket(timeServerIP, 123); //NTP requests are to port 123
	udp.write(packetBuffer, 48);
	udp.endPacket();
	delay(1000);

	uint16_t cb = udp.parsePacket();
	if (!cb)
	{
		Serial.println("no packet yet");
		return false;
	}
	else
	{
		Serial.print("packet received, length=");
		Serial.println(cb);
		// We've received a packet, read the data from it
		udp.read(packetBuffer, 48); // read the packet into the buffer

		//the timestamp starts at byte 40 of the received packet and is four bytes,
		// or two words, long. First, esxtract the two words:

		uint32_t highWord = word(packetBuffer[40], packetBuffer[41]);
		uint32_t lowWord = word(packetBuffer[42], packetBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		uint32_t secsSince1900 = highWord << 16 | lowWord;
		epoch = secsSince1900 - 2208988800UL;
		local_time = millis() / 1000;
		Serial.print("GMT Time: ");
		Serial.println(epoch);
		return true;
	}
}

uint32_t NTPClock::time()
{
	return local_time ? (millis() / 1000 - local_time + epoch) : local_time;
}

}; // namespace sergomor
