#include <Arduino.h>
#include "led-co2-service.cpp"

int readingInverval = 10000;
int brightness = 80;

LedCo2Service ledCo2Service(readingInverval, brightness);

// If you want to push data to google sheets use this constructor instead.
// const char *ssid = "your network ssid";
// const char *password = "your network passwrod";
// const char *scriptId = "your google sheets api key.";
// LedCo2Service ledCo2Service(readingInverval, brightness, ssid, password, scriptId);

void setup() {
  Serial.begin(9600);

  ledCo2Service.setup();
}

void loop() {
  ledCo2Service.loop();
}
