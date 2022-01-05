#include <Arduino.h>
#include "data-pusher.cpp"
#include "co2-sensor.cpp"
#include "connect-to-wifi.cpp"
#include "neopixel-control.cpp"

Co2Sensor co2;
DataPusher dataPusher;
NeoPixelControl pixelMatrix;

class LedCo2Service {
public:

    int readingInverval;
    int brightness;

    const char *ssid;
    const char *password;

    const char *scriptId;

    boolean dataPushEnabled = false;

    LedCo2Service (int readingInverval, int brightness) {
        this->readingInverval = readingInverval;
        this->brightness = brightness;
    }

    LedCo2Service (int readingInverval, int brightness, const char *ssid, const char *password, const char *scriptId) {
        this->readingInverval = readingInverval;
        this->brightness = brightness;

        this->ssid = ssid;
        this->password = password;

        this->scriptId = scriptId;
        dataPushEnabled = true;
    }

    void setup() {

        pixelMatrix.setup(this->brightness);

        co2.setup();

        if (dataPushEnabled) {
            pixelMatrix.drawText("wifi");
            connectToWifi(ssid, password);

            pixelMatrix.drawText("data");
            dataPusher.setup(scriptId);
        }

        Serial.print("\nTaking co2 readings every ");
        Serial.print(this->readingInverval / 1000);
        Serial.println(" seconds:");
    }

    void loop() {
        int value = -1;

        try {
            value = co2.getData();
        } catch (int i) {
            Serial.println("Error getting data.");
            pixelMatrix.drawText("Sensor error.");
            return;
        }

        pixelMatrix.drawText(String(value));

        if (dataPushEnabled) {
            // can only push once every 5 seconds. I update every 10.
            dataPusher.pushData(value);
        }

        delay(readingInverval);
    }
};
