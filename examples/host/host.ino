#include <ArduinoWiFiHost.h>

sergomor::Host h;

void setup()
{
    Serial.begin(115200);
    delay(200);
    Serial << endl
           << "booting" << endl;

    h.begin();

}

void loop()
{
    
}
