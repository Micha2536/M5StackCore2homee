#include <M5EPD.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WebSocketsClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WebServer.h>
//#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#define NAME "M5Stack"                      // Anmerkung: Laenge des Namens ist mit 15 Buchstaben limitiert.
#define NVSBUFSIZE 150
#define LGFX_M5PAPER               
#define LGFX_AUTODETECT 
#include <LovyanGFX.hpp>
#include <ArduinoMqttClient.h>

static LGFX lcd;                 
static LGFX_Sprite sprite(&lcd); 

AsyncWebServer server(80);
Preferences preferences ;
#include "index_html.h"
//#include "M5_WebUI_css.h"


String num; // Abfrage für Attribut ID

// Attribut Storage
int button_get;
int myarray[5000];
String mqttport;
String verbindungsart;
String mqttip;
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

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

//const char broker[] = "192.168.178.61";
//int        port     = 1883;
const char topic[]  = "M5Paper";


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

M5EPD_Canvas canvas(&M5.EPD);
M5EPD_Canvas canvasntp(&M5.EPD);
int point[2][2];

void setup() {
  lcd.init();
  lcd.setRotation(0);
  lcd.setBrightness(255);// 0-255
  lcd.setColorDepth(16); 
  M5.begin();
  //Serial.begin(115200);
  M5.EPD.SetRotation(90);
  M5.TP.SetRotation(90);
  M5.EPD.Clear(true);
  canvas.createCanvas(400, 40);
  canvas.setTextSize(4);
  canvas.drawString("Micha's homee", 0, 0);
  canvas.pushCanvas(140, 10, UPDATE_MODE_GL16);
  //kill canvas overlay main image
  canvas.deleteCanvas();

  drawcicle();
  setup_NVS();
  setup_WIFI();
  http_GET();
  server.onNotFound(notFound);
  server.begin();
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  if (verbindungsart =="WEBSOCKET"){
  // Websocket Beginn
  webSocket.setExtraHeaders("protocolVersion: 13, origin: 192.168.178.80 ,handshakeTimeout: 5000");
  String token_str = String("/connection?access_token=") + token_string;
  webSocket.begin(homeeIP_string.c_str(), 7681, token_str.c_str(), "v2");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
  };
  if (verbindungsart=="MQTT"){
    uint16_t  port = strtol(mqttport.c_str(), NULL, 0);
    if (!mqttClient.connect(mqttip.c_str(), port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();

  };
 page1();
 arrow();


 
}

void loop()
{

  touch();
  if (verbindungsart=="WEBSOCKET"){
  webSocket.loop();
  }
 /* if (verbindungsart=="MQTT"){
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
  }
  */
  timeClient.update();
  ntp();
  //laufzeit();
  if ( M5.BtnL.wasPressed())
  { 
    Serial.printf("BtnL wasPressed!");
  }
  if ( M5.BtnR.wasPressed())
  { 
    Serial.printf("BtnL wasPressed!");
  }
  M5.update();
  mqttClient.poll();
}
void drawcicle() {
  canvas.createCanvas(560, 5);
  canvas.setTextSize(4);
  canvas.drawFastHLine(0, 0, 560, 5, G15);
  canvas.pushCanvas(0, 50, UPDATE_MODE_DU);
  canvas.deleteCanvas();
  
}

void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();

  Serial.println();
}
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
      //M5.Lcd.fillRect(280, 200, 40, 40, BLACK);
      //M5.Lcd.drawPngFile(SD, "/icon/link-variant-off.png", 280, 200);
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      //M5.Lcd.fillRect(280, 200, 40, 40, BLACK);
      //M5.Lcd.drawPngFile(SD, "/icon/link-variant.png", 280, 200);

      // send message to server when Connected
      //webSocket.sendTXT("GET:/nodes/-1");
      break;
    case WStype_TEXT:
        //if (seite == 2){
          // Serial.printf("[WSc] get text: %s\n", payload);
          //}

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
   //homeecounter();
  if (seite == 1 || seite == 2) {
      attribute(payload);
  }
  //if (seite == 3 ) {
  // nodeabf(payload);
  // }
  //nodeabfrage(payload);
}
