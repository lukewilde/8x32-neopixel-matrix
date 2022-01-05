#include <ESP8266WiFi.h>

void connectToWifi(const char *ssid, const char *password) {
  delay(10);
  Serial.println('\n');

  // Connect to WiFi.
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnection established!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
