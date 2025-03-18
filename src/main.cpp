#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "env.h"
#include "site.h"
#include "sensor.h"
#include "enumState.h"

// Globals ----------------------------
const uint8_t INPUT_PIN     = D1;                     // Input-Pin - LOW aktiv
const enumState WIFI_STATE  = STATION;                // STATION | ACCESS
const uint32_t BOUNCE       = 10;                     // Entprellen
// ------------------------------------

Site site;                                           // HTML-Seite
AsyncWebServer server(80);                           // Port 80
Sensor sensor(INPUT_PIN, BOUNCE);

void notFound(AsyncWebServerRequest *request);
void setStationMode();
void setAccessMode();
void setWlan(enumState state);

void setup() {
  sensor.setup();
  Serial.begin(115200);
  delay(500);
  setWlan(WIFI_STATE);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", site.get());
  });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("poll")) {
      String message = "{\"value\":";
      message += sensor.getCounter();
      message += "}";
      request->send(200, "application/json", message);
    }
    if (request->hasParam("cont")) {
      String message = request->getParam("cont")->value();
      sensor.setCounter(message.toInt());
      request->send(200, "text/plain", message);
    }
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  sensor.update(millis());
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setStationMode() {
  WiFi.mode(WIFI_STA);
  uint8_t macAddr[] = {0xC4, 0x5B, 0xBE, 0x63, 0x2E, 0x78};
  wifi_set_macaddr(STATION_IF, &macAddr[0]);
  WiFi.begin(sta_ssid,sta_password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("ESP im Station-Modus.");
  Serial.print("IP Addresse: ");
  Serial.println(WiFi.localIP());
}

void setAccessMode() {
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println("");
  Serial.println("ESP als Access-Point.");
  Serial.print("IP Addresse: ");
  Serial.println(IP);
  Serial.println(WiFi.localIP());
}

void setWlan(enumState state) {
  switch (state) {
    case NONE: {} break;
    case STATION: setStationMode(); break;
    case ACCESS: setAccessMode(); break;
  }
}

