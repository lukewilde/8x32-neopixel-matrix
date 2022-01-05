#include <SoftwareSerial.h>

class Co2Sensor {

public:

  SoftwareSerial co2Serial;

  void setup() {
    delay(1000);
    co2Serial.begin(9600, SWSERIAL_8N1, D7, D8, false);

    if (!co2Serial) {
      Serial.println("Invalid SoftwareSerial pin configuration, check config");

      // Don't continue with invalid configuration.
      while (1) {
        delay (1000);
      }
    }
  }

  int getData() {
    requestData();
    waitForResponse();
    return retriveValue();
  }

private:

  // Command packet to read Co2.
  byte readCO2[7] = { 0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25 };

  void requestData() {

    // Keep sending requests until we start to get a response.
    while (!co2Serial.available()) {
      co2Serial.write(readCO2, 7);
      delay(50);
      Serial.print(".");
    }

  }

  void waitForResponse() {
    int timeout = 0;
    while (co2Serial.available() < 7) {

      // If it takes to long there was probably an error.
      timeout ++;
      if (timeout > 10) {

        Serial.print("There was some kind of error waiting for the co2 serial response. I cba to parse what it is tho.");

        // Flush response.
        while (co2Serial.available()) {
          co2Serial.read();
          delay(50);
        }

        throw 1;
      }

      delay(50);
    }
  }

  unsigned long formatResponseData(byte packet[]) {

    int high = packet[3];
    int low = packet[4];

    unsigned long formattedValue = high * 256 + low;
    return formattedValue;
  }

  unsigned long retriveValue() {

    byte response[] = { 0, 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < 7; i++) {
      response[i] = co2Serial.read();
    }

    return formatResponseData(response);
  }
};
