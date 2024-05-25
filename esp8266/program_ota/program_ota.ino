/* Program Uploader ESP8266 OTA
 * 1. silahkan upload library yang ada di folder lib
 * 2. silahkan ganti ssid dan password sesuai dengan router/hotspot
 * 3. buka serial monitor dengan baudrate 9600 dan akses link ip address di web browser (dan pastikan koneksi wifi di perangkat web browsernya sama di esp8266)
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
  Serial.println(F("Connected to"));
  Serial.print(ssid);
  Serial.println(F("IP Address : "));
  Serial.print(ipAddress);
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
