#include "Empire.h"
#include "Vader.h"
#include "Settings.h"

ESP8266WebServer server(WEBSERVER_PORT);

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

const int externalLight = externalLight_BUILTIN;

void setup(void) {
  Serial.begin(115200);
  SPIFFS.begin();
  delay(10);

  timeClient.begin();
}

void loop() {
  timeClient.update();
}

void handleRoot() {
  digitalWrite(externalLight, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(externalLight, 0);
}

void handleNotFound() {
  digitalWrite(externalLight, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(externalLight, 0);
}
