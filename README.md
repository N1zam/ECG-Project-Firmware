# ECG PROJECT FIRMWARE
## Last Version
- V2.2.2 (HW Version)
- V2.2.4 (SW Version)

## Changelog
- fix includes files (esp8266)
- add LittleFS in program (esp8266)
- update WebServer (add html & css styles on littleFS) (esp8266)

## Uploader Aplication
<p>Use the Uploader App if you want to upload firmware files on atmega328p (uno) and esp8266</p>

- Arduino Uno : <a href="https://drive.google.com/drive/folders/1Jd0Euq1-ti-_1vtQXpMNdb4uExqVydhc?usp=sharing" target="-blank">Download</a>
- Esp8266     : Flashing with OTA Library (Elegant OTA). "Please upload the Elegant OTA library program first in the Arduino IDE -> <a href="https://youtu.be/LDk_tKrHIdI?si=OgcLtV9RhKXbJCEk" target="-blank">Tutorial</a> or <a href="https://github.com/N1zam/ECG-Project-Firmware/blob/V2.2.2.4/esp8266/program_ota/program_ota.ino" target="-blank">Program</a>"

## Steps upload firmware for Software WebServer
- set enable recovery mode and set AP mode on settings
- open /update on browser

<div align="center">
    <img align="center" src="img/img1.jpg" width="50%">
</div>
<br />
- set OTA Mode : LittleFS/SPIFFS
- select file ecg-v2-2.2.4-esp8266-filesystem.bin
- auto reboot and click back (or reopen /update)
- set OTA Mode : Firmware
- select file ecg-v2-2.2.4-esp8266-firmware.bin
- auto reboot and finish

<h2 align=center><a href="https://github.com/N1zam/ECG-Project-Firmware/archive/refs/tags/2.2.2.4.zip">Download Firmware Here</a></h2>