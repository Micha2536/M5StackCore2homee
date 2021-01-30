#include <M5Core2.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WebSocketsClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WebSocketsClient webSocket;


// conficuration Wlan
const char* ssid = "SSID";
const char* password = "PASSWORD";
//configuration Websocket
const char* token =  "/connection?access_token=YOURTOKEN";
const char* homeeip = "HOMEEIP";
// configuration Button   Name, NodeID , AttributID
const char* bn1[] = {"Sideboard", "555", "1769"};
const char* bn2[] = {"Couch", "1022", "2691"};
const char* bn3[] = {"TV Licht", "67", "262"};
const char* bn4[] = {"Erker L", "1020", "2679"};
const char* bn5[] = {"Erker R", "1023", "2698"};
const char* bn6[] = {"Matmos", "266", "1087"};

float bnstate[20];
int seite = 0;
int rssiold = 0;
uint8_t * payload1;
float lasttime = 0;
float lasttime1 = 0;

DynamicJsonDocument doc(ESP.getMaxAllocHeap());

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

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


Button myButton(5, 38, 150, 50, false, bn1[0], {BLACK, WHITE, WHITE});
Button myButton2(5, 93, 150, 50, false, bn2[0], {BLACK, WHITE, WHITE});
Button myButton3(5, 148, 150, 50, false, bn3[0], {BLACK, WHITE, WHITE});
Button myButton4(165, 38, 150, 50, false, bn4[0], {BLACK, WHITE, WHITE});
Button myButton5(165, 93, 150, 50, false, bn5[0], {BLACK, WHITE, WHITE});
Button myButton6(165, 148, 150, 50, false, bn6[0], {BLACK, WHITE, WHITE});




Button Page1 (10, 241, 100, 39);
Button Page2 (110, 241, 100, 39);
Button Page3 (210, 241, 100, 39);

Gesture swipeDown("swipe down", 10, DIR_DOWN, 45);
Gesture swipeLeft("swipe left", 10, DIR_LEFT, 45);

void setup() {
  M5.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  M5.Lcd.setFont(FSS12);
  M5.Buttons.draw();
  myButton.longPressTime = 700;
  M5.Lcd.drawPngFile(SD, "/icon/link-variant-off.png", 280, 200);// WS Link disconnect
  M5.Axp.SetLed(0);
 // Websocket Beginn
  webSocket.setExtraHeaders("protocolVersion: 13, origin: 192.168.178.80 ,handshakeTimeout: 5000");
  webSocket.begin(homeeip, 7681, token, "v2");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
  icon();
}

void loop() {
  M5.update();
  pagemenu();
  webSocket.loop();
  cellular();
  timeClient.update();
  ntp();
  buttonrequest();
  test(); // kamerabild eingebunden 5 minuten Intervall
}

void test() {
  if (timeClient.getMinutes() == 59) {
    lasttime1 = 0;
  }
  if (((timeClient.getMinutes() - lasttime1) > 2) && seite == 2) {
    lasttime1 = timeClient.getMinutes();
    M5.Lcd.fillRect(0, 38, 320, 161, BLACK);
    M5.Lcd.drawPngUrl("http://00.00.00.00:80/test.png", 0, 40, 320, 160, 0, 0, 1);// IP der CAM oder des PI ACHTIUNG PNG File benötigt 320/240
    M5.Lcd.setFont(FSS9);
    M5.Lcd.setCursor(0, 198);
    M5.Lcd.print(timeClient.getHours());
    M5.Lcd.print(":");
    if (timeClient.getMinutes() < 10) {
      M5.Lcd.print("0");
    };
    M5.Lcd.println(timeClient.getMinutes());
    M5.Lcd.setFont(FSS12);
  }
}

void ntp() {
  if (lasttime != timeClient.getMinutes()) {
    M5.Lcd.fillRect(0, 0, 100, 30, BLACK);
    M5.Lcd.setCursor(0, 24);
    M5.Lcd.print(timeClient.getHours());
    M5.Lcd.print(":");
    if (timeClient.getMinutes() < 10) {
      M5.Lcd.print("0");
    };
    M5.Lcd.println(timeClient.getMinutes());
    lasttime = timeClient.getMinutes();
  }
}



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
      webSocket.sendTXT("Connected");
      break;
    case WStype_TEXT:
      //Serial.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);
      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  };
 attribute(payload);
}
void icon() {
  M5.Lcd.drawPngFile(SD, "/icon/lightning-bolt-outline.png", 1, 200);
  M5.Lcd.drawPngFile(SD, "/icon/temperature-celsius.png", 240, 4);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);// Button 1 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);// Button 2 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 160);// Button 3 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 50);// Button 4 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);// Button 5 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 160);// Button 6 off

}
void pagemenu() {
  if (Page1.event == E_TOUCH) {
    seite = 0;
    webSocket.sendTXT("GET:/nodes/-1");
    M5.Lcd.fillRect(0, 38, 320, 162, BLACK);
    M5.Buttons.draw();
    page1();
  };
  if (Page2.event == E_TOUCH) {
    seite = 1;
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
  };
  if (Page3.event == E_TOUCH) {
    seite = 2;
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
    myButton.hide(BLACK);
    M5.Lcd.drawPngUrl("http://00.00.00.00:80/test.png", 0, 40, 320, 160, 0, 0, 1); // IP CAMERA ODER PI 
  };
}
void page1() {
  buttonstate1();
  buttonstate2();
  buttonstate3();
  buttonstate4();
  buttonstate5();
  buttonstate6();
}

void cellular() {

  int rssi = WiFi.RSSI() + 100;
  if (((rssiold - rssi) > 10) || ((rssi - rssiold) > 10) ) {
    Serial.println(rssi);
    rssiold = rssi;
    M5.Lcd.fillRect(296, 1, 24 , 24, BLACK);
    if (rssi > 0 && rssi < 20) {
      M5.Lcd.drawPngFile(SD, "/icon/cellular-outline.png", 296, 4);
    } else if (rssi > 20 && rssi < 40) {
      M5.Lcd.drawPngFile(SD, "/icon/cellular-1.png", 296, 4);
    } else if (rssi > 40 && rssi < 70) {
      M5.Lcd.drawPngFile(SD, "/icon/cellular-2.png", 296, 4);
    } else if (rssi > 70) {
      M5.Lcd.drawPngFile(SD, "/icon/cellular-3.png", 296, 4);
    }
  }
}

void attribute(uint8_t * payload) {
  //JSON Dokument erstellen
  deserializeJson(doc, payload);
  JsonObject object = doc.as<JsonObject>();
  // Variablen erstellen
  float node_id = doc["attribute"]["node_id"].as<float>();
  float attributtype = doc["attribute"]["type"].as<float>();
  float attributid = doc["attribute"]["id"].as<float>();
  float current_value = doc["attribute"]["current_value"].as<float>();

  //Wetter icon
  if ((doc["node"]["attributes"][3]["type"].as<float>() == 243) || (attributtype == 243)) {
    Serial.println(doc["node"]["attributes"][3]["current_value"].as<float>());
    if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 7) || ( current_value == 7)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-cloudy.png", 140, 0);
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 8) || ( current_value == 8)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-partly-cloudy.png", 140, 0);
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 9) || ( current_value == 9)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-night-partly-cloudy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 1) || ( current_value == 1)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-night.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 0) || ( current_value == 0)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-sunny.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 2) || ( current_value == 2)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-rainy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 3) || ( current_value == 3)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-snowy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 4) || ( current_value == 4)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-snowy-rainy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 5) || ( current_value == 5)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-windy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 6) || ( current_value == 6)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-fog.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 10) || ( current_value == 10)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-hail.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 11) || ( current_value == 11)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-lightning.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 12) || ( current_value == 12)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-windy-variant.png", 140, 0 );
    }
  };
  //homee MEMORY UND CPU SOWIE SSD
  if (doc["attribute"]["type"].as<float>() == 311) {
    M5.Lcd.setTextColor(WHITE);
    Serial.print("Memory: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
  };
  if (doc["attribute"]["type"].as<float>() == 312) {
    M5.Lcd.setTextColor(WHITE);
    Serial.print("Prozessor: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
  };
  if (doc["attribute"]["type"].as<float>() == 313) {
    M5.Lcd.setTextColor(WHITE);
    Serial.print("UseStorage: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
  };
  //Gesamtverbrauch LEISTUNG IN WATT
  if (attributid == 3028) {
    M5.Lcd.fillRect(36, 205, 98 , 23, BLACK);
    M5.Lcd.setCursor(36, 225);
    M5.Lcd.printf("%6.1f W", current_value);
  };
  //Schloss Status
  if (attributid == 2905) {
    if (current_value == 1) {
      M5.Lcd.fillRect(100, 0, 35 , 35, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/home-lock.png", 100, 0);
    }
    if (current_value == 0) {
      M5.Lcd.fillRect(100, 0, 35 , 35, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/home-lock-open.png", 100, 0);
    };
  };

  // Temperatur LOKAL TODAY
  if (attributtype == 244) {
    if ((current_value > 9.99) || ( current_value < 0)) {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(181, 24);
      Serial.println(current_value);
      M5.Lcd.printf("%6.1f ", current_value);
    }
    else {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(190, 24);
      M5.Lcd.printf("%6.1f ", current_value);
    }
  };
 //Button state
 if (attributid == atof(bn1[2])) {
    bnstate[1] = current_value;
    buttonstate1();
  }
  if (attributid == atof(bn2[2])) {
    bnstate[2] = current_value;
    buttonstate2();
  }

  if (attributid == atof(bn3[2])) {
    bnstate[3] = current_value ;
    buttonstate3();
  }
  if (attributid == atof(bn4[2])) {
    bnstate[4] = current_value;
    buttonstate4();
  }

  if (attributid == atof(bn5[2])) {
    bnstate[5] = current_value;
    buttonstate5();
  }
  if (attributid == atof(bn6[2])) {
    bnstate[6] = current_value;
    buttonstate6();
  }
}
void buttonrequest() {
  if (myButton.event == E_TOUCH ) {
    if (bnstate[1] == 1.00) {
      String str  = String("PUT:/nodes/")+String(bn1[1])+String("/attributes/")+String(bn1[2])+String("?target_value=0");
      webSocket.sendTXT(str);
    }
    else if ( bnstate[1] == 0.00) {
       String str  = String("PUT:/nodes/")+String(bn1[1])+String("/attributes/")+String(bn1[2])+String("?target_value=1");
      webSocket.sendTXT(str);
    }
  }
   if (myButton2.event == E_TOUCH ) {
    if (bnstate[2] == 1.00) {
      String str  = String("PUT:/nodes/")+String(bn2[1])+String("/attributes/")+String(bn2[2])+String("?target_value=0");
      webSocket.sendTXT(str);
    }
    else if ( bnstate[2] == 0.00) {
       String str  = String("PUT:/nodes/")+String(bn2[1])+String("/attributes/")+String(bn2[2])+String("?target_value=1");
      webSocket.sendTXT(str);
    }
  }
  if (myButton3.event == E_TOUCH ) {
    if (bnstate[3] == 1.00) {
      String str  = String("PUT:/nodes/")+String(bn3[1])+String("/attributes/")+String(bn3[2])+String("?target_value=0");
      webSocket.sendTXT(str);
    }
    else if ( bnstate[3] == 0.00) {
       String str  = String("PUT:/nodes/")+String(bn3[1])+String("/attributes/")+String(bn3[2])+String("?target_value=1");
      webSocket.sendTXT(str);
    }
  }
  if (myButton4.event == E_TOUCH ) {
    if (bnstate[4] == 1.00) {
      String str  = String("PUT:/nodes/")+String(bn4[1])+String("/attributes/")+String(bn4[2])+String("?target_value=0");
      webSocket.sendTXT(str);
    }
    else if ( bnstate[4] == 0.00) {
       String str  = String("PUT:/nodes/")+String(bn4[1])+String("/attributes/")+String(bn4[2])+String("?target_value=1");
      webSocket.sendTXT(str);
    }
  }
  if (myButton5.event == E_TOUCH ) {
    if (bnstate[5] == 1.00) {
      String str  = String("PUT:/nodes/")+String(bn5[1])+String("/attributes/")+String(bn5[2])+String("?target_value=0");
      webSocket.sendTXT(str);
    }
    else if ( bnstate[5] == 0.00) {
       String str  = String("PUT:/nodes/")+String(bn5[1])+String("/attributes/")+String(bn5[2])+String("?target_value=1");
      webSocket.sendTXT(str);
    }
  }
  if (myButton6.event == E_TOUCH ) {
    if (bnstate[6] == 1.00) {
      String str  = String("PUT:/nodes/")+String(bn6[1])+String("/attributes/")+String(bn6[2])+String("?target_value=0");
      webSocket.sendTXT(str);
    }
    else if ( bnstate[6] == 0.00) {
       String str  = String("PUT:/nodes/")+String(bn6[1])+String("/attributes/")+String(bn6[2])+String("?target_value=1");
      webSocket.sendTXT(str);
    }
  }
}
void buttonstate1() {
  if (bnstate[1] == 1) {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 50);
  } else
    M5.Lcd.fillRect(10, 50, 24 , 24, BLACK);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);
}
void buttonstate2() {
  if (bnstate[2] == 1) {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 105);
  } else
    M5.Lcd.fillRect(10, 105, 24 , 24, BLACK);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);
}

void buttonstate3() {
  if (bnstate[3] == 1) {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 160);
  } else
    M5.Lcd.fillRect(10, 160, 24 , 24, BLACK);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 160);
}

void buttonstate4() {
  if (bnstate[4] == 1) {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 50);
  } else
    M5.Lcd.fillRect(170, 50, 24 , 24, BLACK);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 50);
}

void buttonstate5() {
  if (bnstate[5] == 1) {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 105);
  } else
    M5.Lcd.fillRect(170, 105, 24 , 24, BLACK);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);
}

void buttonstate6() {
  if (bnstate[6] == 1) {
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 160);
  } else
    M5.Lcd.fillRect(170, 160, 24 , 24, BLACK);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 160);
}

void disp() {
  delay(2000);
  M5.Lcd.writecommand(ILI9341_DISPOFF);
  M5.Lcd.setBrightness(0);
    delay (2000);
  M5.Lcd.writecommand(ILI9341_DISPON);
  M5.Lcd.setBrightness(100);
  
}
