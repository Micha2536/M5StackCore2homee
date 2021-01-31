#include <M5Core2.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WebSocketsClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WebServer.h>


// conficuration Wlan
const char* ssid = "SSID";
const char* password = "PASS";

//configuration Websocket

const char* token =  "/connection?access_token=YOURTOKEN";
const char* homeeip = "HOMEEIP";

// Attribut Storage

int myarray[5000];

// configuration Button   Name, NodeID , AttributID

const char* bn1[] = {"Sideboard", "555", "1769"};
const char* bn2[] = {"Couch", "1022", "2691"};
const char* bn3[] = {"TV Licht", "67", "262"};
const char* bn4[] = {"Erker L", "1020", "2679"};
const char* bn5[] = {"Erker R", "1023", "2698"};
const char* bn6[] = {"Matmos", "266", "1087"};

//sensor local outdoor 

const char* outsen[] = {"0"};

//Button State Storage

float bnstate[20];

//System Storage

float mem[1];
float cpu[1];
float ssd[1];

int seite = 0;
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

// New Button Config
void testb(int16_t x, int16_t y, int16_t w, int16_t h, int16_t radius, uint16_t color, const char* name, uint16_t textcolor ) {
  M5.Lcd.drawRoundRect(x, y, w, h, radius, color);
  size_t Size = strlen(name);
  int posy = ((h - 12) / 2) + y + 12;
  int posx = ((w - (Size * 9)) / 2) + x;
  M5.Lcd.setTextColor(textcolor);
  M5.Lcd.setFont(FSS9);
  M5.Lcd.setCursor(posx, posy);
  M5.Lcd.print(name);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setFont(FSS12);
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
  Serial.println(WiFi.RSSI());
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  M5.Lcd.setFont(FSS12);
  M5.Buttons.draw();
  M5.Lcd.drawPngFile(SD, "/icon/link-variant-off.png", 280, 200);// WS Link disconnect
  M5.Axp.SetLed(0);

  // Websocket Beginn
  webSocket.setExtraHeaders("protocolVersion: 13, origin: 192.168.1.1 ,handshakeTimeout: 5000");
  webSocket.begin(homeeip, 7681, token, "v2");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
  icon();
  page1();
}

void loop() {
  M5.update();
  //E_TAP, E_DBLTAP, E_PRESSED, E_LONGPRESSED und E_DRAGGED
  //E_TOUCH, E_MOVE und E_RELEASE
  pagemenu();
  webSocket.loop();
  cellular();
  timeClient.update();
  ntp();
  //test(); // kamerabild eingebunden 5 minuten Intervall
  touch();
}

void touch() {

  if (M5.Touch.changed && M5.Touch.points == 1) {
    Event& e = M5.Buttons.event;
    int b1 = ((float)e.to.y > 38 && (float)e.to.y < 88) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 1
    int b2 = ((float)e.to.y > 93 && (float)e.to.y < 143) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 2
    int b3 = ((float)e.to.y > 148 && (float)e.to.y < 198) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 3
    int b4 = ((float)e.to.y > 38 && (float)e.to.y < 88) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 4
    int b5 = ((float)e.to.y > 93 && (float)e.to.y < 143) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 5
    int b6 = ((float)e.to.y > 148 && (float)e.to.y < 198) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 6
    if (seite == 0 ) {
      if (b1)  {
        if (bnstate[1] == 1.00) {
          String str  = String("PUT:/nodes/") + String(bn1[1]) + String("/attributes/") + String(bn1[2]) + String("?target_value=0");
          webSocket.sendTXT(str);
        }
        else if ( bnstate[1] == 0.00) {
          String str  = String("PUT:/nodes/") + String(bn1[1]) + String("/attributes/") + String(bn1[2]) + String("?target_value=1");
          webSocket.sendTXT(str);
        }
      };
      if (b2)  {
        if (bnstate[2] == 1.00) {
          String str  = String("PUT:/nodes/") + String(bn2[1]) + String("/attributes/") + String(bn2[2]) + String("?target_value=0");
          webSocket.sendTXT(str);
        }
        else if ( bnstate[2] == 0.00) {
          String str  = String("PUT:/nodes/") + String(bn2[1]) + String("/attributes/") + String(bn2[2]) + String("?target_value=1");
          webSocket.sendTXT(str);
        }
      };
      if (b3)  {
        if (bnstate[3] == 1.00) {
          String str  = String("PUT:/nodes/") + String(bn3[1]) + String("/attributes/") + String(bn3[2]) + String("?target_value=0");
          webSocket.sendTXT(str);
        }
        else if ( bnstate[3] == 0.00) {
          String str  = String("PUT:/nodes/") + String(bn3[1]) + String("/attributes/") + String(bn3[2]) + String("?target_value=1");
          webSocket.sendTXT(str);
        }
      };
      if (b4)  {
        if (bnstate[4] == 1.00) {
          String str  = String("PUT:/nodes/") + String(bn4[1]) + String("/attributes/") + String(bn4[2]) + String("?target_value=0");
          webSocket.sendTXT(str);
        }
        else if ( bnstate[4] == 0.00) {
          String str  = String("PUT:/nodes/") + String(bn4[1]) + String("/attributes/") + String(bn4[2]) + String("?target_value=1");
          webSocket.sendTXT(str);
        }
      };
      if (b5)  {
        if (bnstate[5] == 1.00) {
          String str  = String("PUT:/nodes/") + String(bn5[1]) + String("/attributes/") + String(bn5[2]) + String("?target_value=0");
          webSocket.sendTXT(str);
        }
        else if ( bnstate[5] == 0.00) {
          String str  = String("PUT:/nodes/") + String(bn5[1]) + String("/attributes/") + String(bn5[2]) + String("?target_value=1");
          webSocket.sendTXT(str);
        }
      };
      if (b6)  {
        if (bnstate[6] == 1.00) {
          String str  = String("PUT:/nodes/") + String(bn6[1]) + String("/attributes/") + String(bn6[2]) + String("?target_value=0");
          webSocket.sendTXT(str);
        }
        else if ( bnstate[6] == 0.00) {
          String str  = String("PUT:/nodes/") + String(bn6[1]) + String("/attributes/") + String(bn6[2]) + String("?target_value=1");
          webSocket.sendTXT(str);
        }
      };
    }
  }
}

// Camera test
void test() {
  if (timeClient.getMinutes() == 59) {
    lasttime1 = 0;
  }
  if (((timeClient.getMinutes() - lasttime1) > 2) && seite == 2) {
    lasttime1 = timeClient.getMinutes();
    M5.Lcd.fillRect(0, 38, 320, 161, BLACK);
    M5.Lcd.drawPngUrl("http://192.168.1.1:80/test.png", 0, 40, 320, 160, 0, 0, 1);
    M5.Lcd.setFont(FS9);
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

//Clock left top
void ntp() {

  if (lasttime != timeClient.getMinutes()) {
    M5.Lcd.fillRect(0, 0, 100, 30, BLACK);
    M5.Lcd.setCursor(0, 24);
    //M5.Lcd.print(timeClient.getFormattedTime());
    M5.Lcd.print(timeClient.getHours());
    M5.Lcd.print(":");
    if (timeClient.getMinutes() < 10) {
      M5.Lcd.print("0");
    };
    M5.Lcd.println(timeClient.getMinutes());
    lasttime = timeClient.getMinutes();
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
// icon on SD card
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

// red button select page
void pagemenu() {
  if (Page1.event == E_TOUCH) {
    seite = 0;
    M5.Lcd.fillRect(0, 38, 320, 162, BLACK);
    M5.Buttons.draw();
    page1();
  };
  if (Page2.event == E_TOUCH) {
    seite = 1;
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
    page2();
  };
  if (Page3.event == E_TOUCH) {
    seite = 2;
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
    M5.Lcd.setCursor(50, 120);
    M5.Lcd.print("test camera snapshot");
    //M5.Lcd.drawPngUrl("http://192.168.1.1:80/test.png", 0, 40, 320, 160, 0, 0, 1);
  };
}
void page1() {
  M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
  testb(5, 38, 150, 50, 15, WHITE, bn1[0], WHITE); // Button1
  testb(5, 93, 150, 50, 15, WHITE, bn2[0], WHITE); // Button2
  testb(5, 148, 150, 50, 15, WHITE, bn3[0], WHITE); // Button3
  testb(165, 38, 150, 50, 15, WHITE, bn4[0], WHITE); // Button4
  testb(165, 93, 150, 50, 15, WHITE, bn5[0], WHITE); // Button5
  testb(165, 148, 150, 50, 15, WHITE, bn6[0], WHITE); // Button6
  buttonstate1();
  buttonstate2();
  buttonstate3();
  buttonstate4();
  buttonstate5();
  buttonstate6();
}
void page2() {
  testb(5, 80, 100, 100, 15, WHITE, " ", WHITE);
  M5.Lcd.setCursor(15, 65 );
  M5.Lcd.print("Memory");
  memst();
  testb(110, 80, 100, 100, 15, WHITE, " ", WHITE);
  M5.Lcd.setCursor(135, 65 );
  M5.Lcd.print("CPU");
  cpust();
  testb(215, 80, 100, 100, 15, WHITE, " ", WHITE);
  M5.Lcd.setCursor(218, 65 );
  M5.Lcd.print("Speicher");
  ssdst();
}

// homee memory print
void memst() {
  if ( seite == 1 ) {
    M5.Lcd.fillRoundRect(5, 80, 100, 100, 15, BLACK);
    if ((mem[0] > 50.00) && (mem[0] < 75.00)) {
      M5.Lcd.drawRoundRect(5, 80, 100 , 100, 15, YELLOW);
      M5.Lcd.setTextColor(YELLOW);
    } else if (mem[0] > 75.00) {
      M5.Lcd.drawRoundRect(5, 80, 100 , 100, 15, RED);
      M5.Lcd.setTextColor(RED);
    } else
      M5.Lcd.drawRoundRect(5, 80, 100 , 100, 15, WHITE);
    M5.Lcd.setCursor(15, 130 );
    M5.Lcd.printf("%6.1f%%", mem[0]);
  }
}

// homee cpu print
void cpust() {
  if ( seite == 1 ) {
    M5.Lcd.fillRoundRect(110, 80, 100, 100, 15, BLACK);
    if ((cpu[0] > 50.00) && (cpu[0] < 75.00)) {
      M5.Lcd.drawRoundRect(110, 80, 100 , 100, 15, YELLOW);
      M5.Lcd.setTextColor(YELLOW);
    } else if (cpu[0] > 75.00) {
      M5.Lcd.drawRoundRect(110, 80, 100 , 100, 15, RED);
      M5.Lcd.setTextColor(RED);
    } else
      M5.Lcd.drawRoundRect(110, 80, 100 , 100, 15, WHITE);
    M5.Lcd.setCursor(120, 130 );
    M5.Lcd.printf("%6.1f%%", cpu[0]);
  }
}

// homee SSD print
void ssdst() {
  if ( seite == 1 ) {
    M5.Lcd.fillRoundRect(215, 80, 100, 100, 15, BLACK);
    if ((ssd[0] > 50.00) && (ssd[0] < 75.00)) {
      M5.Lcd.drawRoundRect(215, 80, 100 , 100, 15, YELLOW);
      M5.Lcd.setTextColor(YELLOW);
    } else if (ssd[0] > 75.00) {
      M5.Lcd.drawRoundRect(215, 80, 100 , 100, 15, RED);
      M5.Lcd.setTextColor(RED);
    } else
      M5.Lcd.drawRoundRect(215, 80, 100 , 100, 15, WHITE);
    M5.Lcd.setCursor(225, 130 );
    M5.Lcd.printf("%6.1f%%", ssd[0]);
  }
}

// Wlan RSSI
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

// homee attribut analyse
void attribute( uint8_t * payload) {

  //JSON Dokument erstellen
  deserializeJson(doc, payload);
  JsonObject object = doc.as<JsonObject>();
  // Variablen erstellen
  float node_id = doc["attribute"]["node_id"].as<float>();
  float attributtype = doc["attribute"]["type"].as<float>();
  float attributid = doc["attribute"]["id"].as<float>();
  float current_value = doc["attribute"]["current_value"].as<float>();

  //Wetter icon
  if ((doc["node"]["attributes"][3]["type"].as<float>() == 243) || (attributid == 1322)) {
    Serial.println(doc["node"]["attributes"][3]["current_value"].as<float>());
    M5.Lcd.fillRect(140, 0, 35, 35, BLACK);
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
  //homee MEMORY and CPU and SSD
  if (doc["attribute"]["type"].as<float>() == 311) {
    M5.Lcd.setTextColor(WHITE);
    mem[0] = doc["attribute"]["current_value"].as<float>();
    Serial.print("Memory: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
    memst();
  };
  if (doc["attribute"]["type"].as<float>() == 312) {
    M5.Lcd.setTextColor(WHITE);
    cpu[0] = doc["attribute"]["current_value"].as<float>();
    Serial.print("Prozessor: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
    cpust();
  };
  if (doc["attribute"]["type"].as<float>() == 313) {
    M5.Lcd.setTextColor(WHITE);
    ssd[0] = doc["attribute"]["current_value"].as<float>();
    Serial.print("UseStorage: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
    ssdst();
  };
  //Gesamtverbrauch LEISTUNG IN WATT
  if (attributid == 3028) {
    M5.Lcd.fillRect(36, 205, 98 , 23, BLACK);
    M5.Lcd.setCursor(36, 225);
    M5.Lcd.printf("%6.1f W", current_value);
  };

  // Temperatur Outdoor
  if (attributid == atof(outsen[0])) {
    if ((current_value > 9.99) || ( current_value < 0.00)) {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(181, 24);
      if (current_value < 4 ) {
        M5.Lcd.setTextColor(BLUE);
      }
      if (current_value > 4 ) {
        M5.Lcd.setTextColor(WHITE);
      }
      if (current_value > 20 ) {
        M5.Lcd.setTextColor(RED);
      }
      Serial.println(current_value);
      M5.Lcd.printf("%6.1f ", current_value);
      M5.Lcd.setTextColor(WHITE);
    }
    else {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(190, 24);
      M5.Lcd.printf("%6.1f ", current_value);
    }//webSocket.sendTXT("GET:/nodes/-1");
  };
  //Button status
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


void buttonstate1() {
  if (seite == 0) {
    if (bnstate[1] == 1) {
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 50);
    } else
      M5.Lcd.fillRect(10, 50, 24 , 24, BLACK);
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);
  }
}
void buttonstate2() {
  if (seite == 0) {
    if (bnstate[2] == 1) {
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 105);
    } else
      M5.Lcd.fillRect(10, 105, 24 , 24, BLACK);
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);
  }
}
void buttonstate3() {
  if (seite == 0) {
    if (bnstate[3] == 1) {
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 160);
    } else
      M5.Lcd.fillRect(10, 160, 24 , 24, BLACK);
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 160);
  }
}

void buttonstate4() {
  if (seite == 0) {
    if (bnstate[4] == 1) {
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 50);
    } else
      M5.Lcd.fillRect(170, 50, 24 , 24, BLACK);
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 50);
  }
}
void buttonstate5() {
  if (seite == 0) {
    if (bnstate[5] == 1) {
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 105);
    } else
      M5.Lcd.fillRect(170, 105, 24 , 24, BLACK);
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);
  }
}
void buttonstate6() {
  if (seite == 0) {
    if (bnstate[6] == 1) {
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 170, 160);
    } else
      M5.Lcd.fillRect(170, 160, 24 , 24, BLACK);
    M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 160);
  }
}
