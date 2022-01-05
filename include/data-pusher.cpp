// Example Arduino/ESP8266 code to upload data to Google Sheets
// Follow setup instructions found here:
// https://github.com/StorageB/Google-Sheets-Logging
// reddit: u/StorageB107
// email: StorageUnitB@gmail.com

#include <Arduino.h>
#include "HTTPSRedirect.h"

class DataPusher {
public:

  String payload_base = "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"values\": ";
  String payload = "";

  const char *host = "script.google.com";
  const int httpsPort = 443;
  const char *fingerprint = "";
  String url;
  HTTPSRedirect *client = nullptr;

  void setup(const char *scriptId) {
    url = String("/macros/s/") + scriptId + "/exec";
    connectToGoogleSheets();
  }

  void pushData(int logData) {

    static bool flag = false;

    if (!flag) {
      client = new HTTPSRedirect(httpsPort);
      client->setInsecure();
      flag = true;
      client->setPrintResponseBody(true);
      client->setContentTypeHeader("application/json");
    }

    if (client != nullptr) {
      if (!client->connected()) {
        client->connect(host, httpsPort);
      }
    } else {
      Serial.println("Error creating client object!");
    }

    // Create json object string to send to Google Sheets
    payload = payload_base + "\"" + logData + "\"}";

    // Publish data to Google Sheets
    // Serial.println("Publishing data...");
    // Serial.println(payload);
    if (client->POST(url, host, payload)) {
      // do stuff here if publish was successful
    } else {
      // do stuff here if publish was not successful
      Serial.println("Error while connecting");
    }
  }

private:
  void connectToGoogleSheets() {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");

    Serial.print("\nConnecting to ");
    Serial.println(host);

    // Try to connect for a maximum of 5 times
    bool flag = false;
    for (int i = 0; i < 5; i++) {
      int retval = client->connect(host, httpsPort);
      if (retval == 1) {
        flag = true;
        Serial.println("Connection established!");
        Serial.println();
        break;
      }
      else
        Serial.println("Connection failed. Retrying...");
    }
    if (!flag) {
      Serial.print("Could not connect to server: ");
      Serial.println(host);
      return;
    }

    delete client;    // delete HTTPSRedirect object
    client = nullptr; // delete HTTPSRedirect object
  }
};
