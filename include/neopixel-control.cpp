#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <gameboy.h>

class NeoPixelControl {

public:

    int width = 32;
    int height = 8;
    double brightness = 80;

    double maxCurrent = 1;
    double currentMargin = 0.1;
    double maxBrightness = 255;

    int layoutConfig = NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG;

    Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(width, height, D5, layoutConfig);

    uint16_t lightestGreen = matrix.Color(155, 188, 15);
    uint16_t lightGreen = matrix.Color(139, 172, 15);
    uint16_t darkGreen = matrix.Color(48, 98, 48);
    uint16_t darkestGreen = matrix.Color(15, 56, 15);
    uint16_t itBurns = matrix.Color(255, 255, 255);

    void setup(double brightness) {

        this->brightness = brightness;

        matrix.begin();
        matrix.clear();
        matrix.setTextWrap(false);
        matrix.setBrightness(brightness);
        // matrix.fillScreen(darkGreen);
        matrix.setFont(&GameBoy4pt7b);
        matrix.setTextColor(lightGreen);

        matrix.show();
    }

    void drawText(String text) {
        matrix.clear();
        // matrix.fillScreen(darkGreen);
        matrix.setCursor(1, 6);
        matrix.print(text);

        matrix.show();
    }
};
