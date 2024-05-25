/* Program Uploader ESP8266 OTA
 * 1. please upload the library first in the program_ota/lib folder
 * 2. please change the ssid and password according to the router/hotspot
 * 3. open the serial monitor with baudrate 9600 and access the ip address link in the web browser 
    (and make sure the wifi connection in the web browser device is the same in esp8266)
 *
 * ********************************** Thank you for using Project ECG V2.0 program. **********************************
 * creator : Nizam Albar
 */

#include <ESP8266WiFi.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "........";
const char* password = "........";

AsyncWebServer server(80);
String ipAddress;

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
  Serial.print(F("Connected to"));
  Serial.println(ssid);
  Serial.print(F("IP Address : "));
  Serial.println(ipAddress);
  Serial.println("http://"+String(ipAddress)+"/");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", "ESP8266 Uploader OTA (Over To Air), please click <a href=\"http://"+String(ipAddress)+"/update\">upload file bin</a>");
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  AsyncElegantOTA.loop();
}
