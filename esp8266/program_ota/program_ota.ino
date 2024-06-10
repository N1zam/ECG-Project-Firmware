/* **************************************** Program Uploader ESP8266 OTA ***********************************************
 * 1. please upload the library first in the program_ota/lib folder
 * 2. please insert the ssid and password variables according to the router/hotspot
 * 3. open the serial monitor with baudrate 9600 and access the ip address link in the web browser 
 *    (and make sure the wifi connection in the web browser device is the same in esp8266)
 *
 * ********************************** Thank you for using Project ECG V2.0 program. ************************************
 * creator : Nizam Albar
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ElegantOTA.h>

const char* ssid = "........";
const char* password = "........";

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
String ipAddress;

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

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
  Serial.print(F("IP Address : "));
  Serial.println(ipAddress);
  Serial.println("http://"+String(ipAddress)+"/");

  if(MDNS.begin("esp8266")) {
    Serial.println(F("MDNS responder started"));
  }
  ElegantOTA.begin(&server);

  ESP8266WebServer* request = &server;
  server.on("/", HTTP_GET, [request]() {
    request->send(200, "text/html", "ESP8266 Uploader OTA (Over To Air), please click <a href=\"http://"+String(ipAddress)+"/update\">upload file bin</a>");
  });

  httpUpdater.setup(&server);
  server.begin();
  server.onNotFound(handleNotFound);
  Serial.println(F("HTTP Server Started"));
}

void loop() {
  // put your main code here, to run repeatedly:
  ElegantOTA.loop();
  server.handleClient();
}
