#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define LED 4


char *ssid = "Home-corpnet";
char *password = "";

ESP8266WebServer server(80);

void setup() {
    Serial.begin(9600);

    pinMode(LED, OUTPUT);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);


    while(WiFi.status() != WL_CONNECTED) {
        delay(250);
        digitalWrite(LED, HIGH);
        Serial.print(".");
        delay(250);
        digitalWrite(LED, LOW);
        Serial.print(".");
    }

    digitalWrite(LED, HIGH);
    
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());


    server.on("/", handleRoot);
    server.on("/on", handleOn);
    server.on("/off", handleOff);
    server.on("/reset", handleReset);

    server.onNotFound(handleNotFound);

    server.begin();
}

void loop() {
    server.handleClient();
}

void handleRoot() {
  
}

void handleOn() {
  digitalWrite(LED, LOW);
  server.send(200);
}

void handleOff() {
  digitalWrite(LED, HIGH);
  server.send(200);
}

void handleReset() {
  server.send(200);
  ESP.restart();
}

void handleNotFound() {
  server.send(404, "text/plain", "Page not found");
}
