#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define LED 4
#define BTN 2
int btnCounter = 0;


char *ssid = "Home-corpnet";
char *password = "4lambertfamilyonly!";

String state;

ESP8266WebServer server(80);

void setup() {
    Serial.begin(9600);

    pinMode(LED, OUTPUT);
    pinMode(BTN, INPUT);

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

    digitalWrite(LED, LOW);
    delay(500);
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

    delay(1000);

    printIP();
}

void loop() {
    server.handleClient();

    // Short press released
    if(btnCounter < 100 && btnCounter > 0 && digitalRead(BTN) == HIGH) {
      printIP();
      btnCounter = 0;
    }
    if(btnCounter > 100) {
      ESP.restart();
    }

    if(digitalRead(BTN) == LOW) {
      btnCounter++;
    }
    else if(digitalRead(BTN) == HIGH) {
      btnCounter = 0;
    }

    delay(10);
}

void handleRoot() {
  String htmlHead = "<head><title>Meeting-Display</title><link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\"></head>";
  String htmlBody = "<body><h1>Meeting-Display</h1><a class=\"w3-btn w3-green w3-block w3-margin \" href=\"/on\" target=\"myFrame\">ON</a> <a class=\"w3-btn w3-green w3-block w3-margin\" href=\"/off\" target=\"myFrame\">Off</a> <a class=\"w3-btn w3-red w3-block w3-margin\" href=\"/reset\" >Reset</a><iframe name=\"myFrame\"></iframe width=\"10\" height=\"10\" frameBorder=\"0\" style=\"display: none\"></body>";
  String htmlPage = "<!DOCTPE HTML> <html lang=\"de\">" + htmlHead + htmlBody + "</html>";

  server.send(200, "text/html", htmlPage);
}

void handleOn() {
  digitalWrite(LED, LOW);
  state = "off";
  server.send(200);
}

void handleOff() {
  digitalWrite(LED, HIGH);
  state = "on";
  server.send(200);
}

void handleReset() {
  server.send(200);
  ESP.restart();
}

void handleNotFound() {
  server.send(404, "text/plain", "<h1>Page not found</h1>");
}

void printIP() {
  String ip = WiFi.localIP().toString();
  ip = ip.substring(12);

  for(int i = 0; i < 3; i++) {
    int currentSegment = int(ip.charAt(i)) - 48;
    Serial.println(currentSegment);
    for(int j = 0; j < currentSegment; j++) {
      digitalWrite(LED, LOW);
      delay(500);
      digitalWrite(LED, HIGH);
      delay(500);
    }
      delay(500);
      digitalWrite(LED, LOW);
      delay(2000);
      digitalWrite(LED, HIGH);
  }
}
