#include <Adafruit_NeoPixel.h>

class NeopixelDebugging {
private:

    int pin = D5;
    int numPixels = 8 * 32;
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);

public:

    void setup() {
        pixels.begin();
    }

    void loop() {

        int waitTime = 3000;

        pixels.clear();
        pixels.show();
        delay(waitTime);
        setColourAndBrightness(pixels.Color(255, 255, 255), 50);
        delay(waitTime);
        setColourAndBrightness(pixels.Color(255, 255, 255), 100);
        delay(waitTime);
        setColourAndBrightness(pixels.Color(255, 255, 255), 150);
        delay(waitTime);
        setColourAndBrightness(pixels.Color(255, 255, 255), 200);
        delay(waitTime);
        setColourAndBrightness(pixels.Color(255, 255, 255), 255);
        delay(waitTime);
    }

    void setColourAndBrightness(uint32_t colour, int brightness) {
        pixels.clear();
        pixels.setBrightness(brightness);

        for (int i = 0; i < 32; i++) {
            pixels.setPixelColor(i, colour);
        }

        pixels.show();
    }
};
