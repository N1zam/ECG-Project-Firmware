/* **************************************** Program Uploader ESP8266 OTA ***********************************************
 * 1. please upload the library first in the program_ota/lib folder
 * 2. please insert the ssid and password variables according to the router/hotspot (if mode_sta true)
 * 3. open the serial monitor with baudrate 9600 and access the ip address link in the web browser 
 *    (and make sure the wifi connection in the web browser device is the same in esp8266)
 *
 * ********************************** Thank you for using Project ECG V2.0 program. ************************************
 * creator : Nizam Albar
 */

#include "program_ota.h"


// mode_sta = true or false
bool mode_sta = false;

// if mode_sta = true : insert the ssid and password
const char* ssid = "........";
const char* password = "........";

ProgramMain Main(80);

void setup(void) {
  Main.setup(ssid, password, mode_sta);
}

void loop() {
  Main.loop();
}
