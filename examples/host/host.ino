#include <ArduinoWiFiHost.h>

sergomor::Host h;

void setup()
{
    Serial.begin(115200);
    delay(200);
    Serial << endl
           << "booting" << endl;
    h.begin();

    SPIFFS.begin();

  FSInfo fs_info;
  SPIFFS.info(fs_info);
  printf("SPIFFS: %lu of %lu bytes used.\n",
         fs_info.usedBytes, fs_info.totalBytes);
}

void loop()
{
    h.tick();
}
