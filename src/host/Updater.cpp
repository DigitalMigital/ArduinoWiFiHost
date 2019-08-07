#include "Updater.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include "../utils/stream_op.h"
#include "UpdaterConfig.h"

namespace sergomor
{

const char *Updater::webserver_path = "/files/webserver/";
const char *Updater::binary_path = "/files/binary/";
const char *const Updater::web_files[] = {"index.html.gz", "style.css.gz"};

void Updater::begin()
{
	updateWebServerFiles();
}

void Updater::updateWebServerFiles()
{
	UpdaterConfig config;
	config.load();

	if (!config.host.length())
		config.host = githubusercontent_host;

	Serial << "Update enable: " << config.enable << endl;

	if (!config.enable)
		return;

	if (!SPIFFS.begin())
	{
		Serial << "SPIFFS Mount Failed" << endl;
		return;
	}

	WiFiClient *stream;
	HTTPClient http;
	File file;
	int httpCode;
	uint8_t buf[128];
	size_t len;
	String path("/");

	for (int i = 0; i < NUM_WEB_FILES; i++)
	{
		http.begin(config.host + webserver_path + web_files[i], githubusercontent_fingerprint);
		httpCode = http.GET();
		Serial << "read: " << config.host + webserver_path + web_files[i] << " with code: " << httpCode << endl;
		if (httpCode > 0 && httpCode < 400)
		{
			stream = http.getStreamPtr();
			file = SPIFFS.open(path + web_files[i], "w");
			Serial << "open file: " << path + web_files[i] << " res:" << (bool)file << endl;
			if ((bool)file)
			{
				len = http.getSize();
				printf("write %s to fs %lu bytes\n", web_files[i], len);
				while (http.connected() && (len > 0))
				{
					len = stream->readBytes(buf, 127);
					file.write(buf, len);
				}
				Serial << endl;
				file.close();
			}
			http.end();
		}
	}
}
} // namespace sergomor