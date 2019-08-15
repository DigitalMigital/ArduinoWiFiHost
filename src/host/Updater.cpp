#include "Updater.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include "../utils/stream_op.h"
#include "UpdaterConfig.h"
#include <ArduinoJson.h>

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
	UpdaterConfig &config = UpdaterConfig::instance();
	config.load();

	if (!config.host.length())
		config.host = githubusercontent_host;

	debug << "Update enable: " << config.enable << endl;

	if (!config.enable)
		return;

	if (!SPIFFS.begin())
	{
		debug << "SPIFFS Mount Failed" << endl;
		return;
	}

	WiFiClient *stream;
	HTTPClient http;
	File file;
	int httpCode;
	uint8_t buf[128];
	size_t len;
	String path("/");
	JsonArray files;
	size_t num_files = 0;
	int got_files = 0;
	String webfile;

	debug << "web files version: " << config.webfiles_version << endl;

	// load manifest
	http.begin(config.host + webserver_path + "manifest.json", githubusercontent_fingerprint);
	httpCode = http.GET();
	if (httpCode > 0 && httpCode < 400)
	{
		stream = http.getStreamPtr();
		len = http.getSize();
		stream->readBytes(buf, len);

		buf[len + 1] = NULL;
		StaticJsonDocument<100> doc;
		if (!deserializeJson(doc, buf))
		{
			debug << "manifest version: " << (const char *)doc["version"] << endl;
			if (strlen((const char *)doc["version"]) && config.webfiles_version != (const char *)doc["version"])
			{
				files = doc["files"];
				num_files = files.size();
			}
		}
	}
	http.end();

	if (!num_files)
		return;

	for (int i = 0; i < num_files; i++)
	{
		webfile = String((const char *)files[i]);
		http.begin(config.host + webserver_path + webfile, githubusercontent_fingerprint);
		httpCode = http.GET();
		debug << "read: " << config.host + webserver_path + webfile << " with code: " << httpCode << endl;
		if (httpCode > 0 && httpCode < 400)
		{
			stream = http.getStreamPtr();
			file = SPIFFS.open(path + webfile, "w");
			debug << "open file: " << path + webfile << " res:" << (bool)file << endl;
			if ((bool)file)
			{
				len = http.getSize();
				debug << "write " << webfile << " to fs " << len << " bytes" << endl;
				while (http.connected() && (len > 0))
				{
					len = stream->readBytes(buf, 127);
					file.write(buf, len);
				}
				debug << endl;
				file.close();
				got_files++;
			}
		}
		http.end();
	}

	if (got_files == num_files)
	{
		config.version = doc["version"];
		//config.save();
		devug <<
	}
}
} // namespace sergomor