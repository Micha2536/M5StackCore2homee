/*Nutzung des Websockets ohne Gewähr und auf eigene Verantwortung.
 * by Micha homee Community
 * 
 * 
 *
 * Version 0.7.1  Bug im Get behoben 
 * HG können abgespielt, dazu die Webui aufrufen und anstelle der Node Id die HG Id eintragen und HG auf true stellen
 */

#include <M5Core2.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WebSocketsClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#define NAME "M5Stack"                      // Anmerkung: Laenge des Namens ist mit 15 Buchstaben limitiert.
#define NVSBUFSIZE 150


AsyncWebServer server(80);
Preferences preferences ;
#include "index_html.h"
#include "M5_WebUI_css.h"


String num; // Abfrage für Attribut ID

// Attribut Storage

int myarray[5000];
String varbutton;
String TempOut;
String homeeIP_string;
String token_string;
String name1_string;
String id1_string;
String attr1_string;
String hg1_string;
String name2_string;
String id2_string;
String attr2_string;
String hg2_string;
String name3_string;
String id3_string;
String attr3_string;
String hg3_string;
String name4_string;
String id4_string;
String attr4_string;
String hg4_string;
String name5_string;
String id5_string;
String attr5_string;
String hg5_string;
String name6_string;
String id6_string;
String attr6_string;
String hg6_string;


//Button State Storage

float bnstate[20];

//System Storage

float mem[1];
float cpu[1];
float ssd[1];

int seite = 1;
int rssiold = 0;
uint8_t * payload1;
float lasttime = 0;
float lasttime1 = 0;


DynamicJsonDocument doc(ESP.getMaxAllocHeap());
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
WebSocketsClient webSocket;

int checkSDCard() {
  sdcard_type_t Type = SD.cardType();
  if ( Type == CARD_UNKNOWN || Type == CARD_NONE )
  {
    Serial.println("keine SD card gefunden");
  }
  else
  {
    Serial.println(Type);
    Serial.printf("SDCard Type = %d \r\n", Type);
    Serial.printf("SDCard Size = %d \r\n", (int)(SD.cardSize() / 1024 / 1024));

  }
  return 0;
}



// Red round button bottom
Button Page1 (10, 241, 100, 39);
Button Page2 (110, 241, 100, 39);
Button Page3 (210, 241, 100, 39);

// Gesture
Gesture swipeDown("swipe down", 10, DIR_DOWN, 45);
Gesture swipeLeft("swipe left", 10, DIR_LEFT, 45);

void setup() {
  M5.begin();
  Serial.begin(115200);
  setup_NVS();
  setup_WIFI();
  http_GET();
  server.onNotFound(notFound);
  server.begin();
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  M5.Lcd.setFont(FSS12);
  M5.Buttons.draw();
  M5.Lcd.drawPngFile(SD, "/icon/link-variant-off.png", 280, 200);// WS Link disconnect
  M5.Axp.SetLed(0);

  // Websocket Beginn
  webSocket.setExtraHeaders("protocolVersion: 13, origin: 192.168.178.80 ,handshakeTimeout: 5000");
  String token_str = String("/connection?access_token=") + token_string;
  webSocket.begin(homeeIP_string.c_str(), 7681, token_str.c_str(), "v2");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
  icon();
  page1();
}

void loop() {
  M5.update();
  pagemenu();
  webSocket.loop();
  cellular();
  timeClient.update();
  ntp();
  touch();
  if (seite == 3) {
    keyboardtouch();
  }
}

// Gesture
void geste() {
  if (swipeDown.wasDetected()) {
    Event& e = M5.Buttons.event;
    Serial.println("Swiped down!");
    Serial.println(e.from.y);
    Serial.println(e.to.y);
    Serial.println(e.to.y - e.from.y);
    M5.Lcd.fillRect(0, 0, 320, 240, BLACK);
    M5.Buttons.draw();
    M5.Lcd.setCursor(50, 230);
  }
}



// Websocket
void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t* src = (const uint8_t*) mem;
  Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for (uint32_t i = 0; i < len; i++) {
    if (i % cols == 0) {
      Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    Serial.printf("%02X ", *src);
    src++;
  }
  Serial.printf("\n");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      M5.Lcd.fillRect(280, 200, 40, 40, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/link-variant-off.png", 280, 200);
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      M5.Lcd.fillRect(280, 200, 40, 40, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/link-variant.png", 280, 200);

      // send message to server when Connected
      webSocket.sendTXT("GET:/nodes/-1");
      break;
    case WStype_TEXT:
      if (seite == 4 ) {
        Serial.printf("[WSc] get text: %s\n", payload);
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);
      // send data to server
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  };
  if (seite == 1 || seite == 2) {
    attribute(payload);
  }
  if (seite == 3 ) {
    nodeabf(payload);
  }
  nodeabfrage(payload);
}

// icon on SD card
void icon() {
  M5.Lcd.drawPngFile(SD, "/icon/lightning-bolt-outline.png", 1, 200);
  M5.Lcd.drawPngFile(SD, "/icon/temperature-celsius.png", 240, 4);
  if (varbutton == "6") {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);// Button 1 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);// Button 2 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 160);// Button 3 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 50);// Button 4 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);// Button 5 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 160);// Button 6 off
  }
  else if (varbutton == "1") {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);// Button 1 off

  }
  else if (varbutton == "2") {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);// Button 1 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);// Button 2 off
  }
  else if (varbutton == "4") {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 75);// Button 1 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 155);// Button 2 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 75);// Button 3 off
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 155);// Button 4 off
  }
}


