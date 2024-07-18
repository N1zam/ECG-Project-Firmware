#ifndef program_ota_h
#define program_ota_h

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266HTTPUpdateServer.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266mDNS.h>
  #include <ElegantOTA.h>
#else
    #error "Please select an ESP8266 board for this sketch."
#endif

class ProgramMain {
public:
  void setup(const String ssid, const String password, const bool mode_sta) {
    // put your setup code here, to run once:
    Serial.begin(9600);
    if (mode_sta) {
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);

      // wait for connection
      Serial.println("Connecting WiFi.");
      while(WiFi.status() != WL_CONNECTED) {
        Serial.print(F("."));
        delay(500);
      }
      
      ipAddress = WiFi.localIP().toString().c_str();
      Serial.println();
      Serial.print(F("Connected to "));
      Serial.println(ssid);
    }
    else {
      WiFi.mode(WIFI_AP);
      WiFi.softAP(apname, appassword);
      
      ipAddress = WiFi.softAPIP().toString().c_str();
      Serial.println();
      Serial.println(F("Wifi mode : Access Point"));
      Serial.printf("AP Name : %s\nAP Password : %s\n", apname.c_str(), appassword.c_str());
    }
    Serial.print(F("IP Address : "));
    Serial.println(ipAddress);
    Serial.println("http://"+String(ipAddress)+"/");

    if(MDNS.begin("esp8266")) {
      Serial.println(F("MDNS responder started"));
    }
    ElegantOTA.begin(&server);

    server.on("/", HTTP_GET, std::bind(&ProgramMain::mainpage, this));

    httpUpdater.setup(&server);
    server.begin();
    server.onNotFound(std::bind(&ProgramMain::handleNotFound, this));
    Serial.println(F("HTTP Server Started"));
  }

  void loop() {
    // put your main code here, to run repeatedly:
    ElegantOTA.loop();
    server.handleClient();
  }

  ProgramMain(int _port) : server(_port) {
    // TODO(not yet implemented)
  }

private:
  ESP8266WebServer server;
  ESP8266HTTPUpdateServer httpUpdater;
  String ipAddress;
  const String apname = "nodemcuv2-ota";
  const String appassword = "admin1234";

  void handleNotFound() {
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
  }

  void mainpage () {
    String page = "ESP8266 Uploader OTA (Over To Air), please click <a href=\"http://"+String(ipAddress)+"/update\">upload file bin</a>";
    server.send(200, "text/html", page);
  }

};

#endif
