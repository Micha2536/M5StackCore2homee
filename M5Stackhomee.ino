#include <M5Core2.h>
#include <WiFi.h>
//#include <WebServer.h>
//#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <WebSocketsClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WebSocketsClient webSocket;


const char* ssid = "";
const char* password = "";

int seite = 0;
int rssiold = 0;
uint8_t * payload1;
float lasttime = 0;
DynamicJsonDocument doc(ESP.getMaxAllocHeap());

//WebServer server(80);

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


Button myButton(5, 38, 150, 50, false, "Sideboard", {BLACK, WHITE, WHITE});
Button myButton2(5, 93, 150, 50, false, "Couch", {BLACK, WHITE, WHITE});
Button myButton3(5, 148, 150, 50, false, "TV Licht", {BLACK, WHITE, WHITE});
Button myButton4(165, 38, 150, 50, false, "Erker L", {BLACK, WHITE, WHITE});
Button myButton5(165, 93, 150, 50, false, "Erker R", {BLACK, WHITE, WHITE});
Button myButton6(165, 148, 150, 50, false, "Matmos", {BLACK, WHITE, WHITE});




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
  Serial.println(WiFi.RSSI());
  //  if (MDNS.begin("esp32")) {
  //  Serial.println("MDNS responder started");
  //}
  //server.begin();
  timeClient.begin();
  timeClient.setTimeOffset(3600);
  M5.Lcd.setFont(FSS12);
  M5.Buttons.draw();
  myButton.longPressTime = 700;
  // M5.Lcd.setTextColor(YELLOW);
  //M5.Lcd.setCursor(30 , 230);
  //M5.Lcd.print("Seite 1");
  //M5.Lcd.setTextColor(WHITE);
  //M5.Lcd.setCursor(135 , 230);
  // M5.Lcd.print("Seite 2");
  // M5.Lcd.setCursor(245 , 230);
  // M5.Lcd.print("Seite 3");
  M5.Axp.SetLed(0);
  // Websocket Beginn
  webSocket.setExtraHeaders("protocolVersion: 13, origin: M5IP ,handshakeTimeout: 5000");
  webSocket.begin("homeeip", 7681, "/connection?access_token=deintoken", "v2");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
  icon();
}

void loop() {
  M5.update();
  //server.handleClient();

  //E_TAP, E_DBLTAP, E_PRESSED, E_LONGPRESSED und E_DRAGGED
  //E_TOUCH, E_MOVE und E_RELEASE
  pagemenu();
  webSocket.loop();
  cellular();
  timeClient.update();
  ntp();

}

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
  payload1 = payload;
  attribute();
}
void icon() {
  M5.Lcd.drawPngFile(SD, "/icon/link-variant-off.png", 280, 200);
  M5.Lcd.drawPngFile(SD, "/icon/lightning-bolt-outline.png", 1, 200);
  //M5.Lcd.drawPngFile(SD, "/icon/thermometer-lines24.png", 180, 6);
  M5.Lcd.drawPngFile(SD, "/icon/temperature-celsius.png", 240, 4);
  //M5.Lcd.drawPngFile(SD, "/icon/home-lock.png", 100, 0);
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);// Button 1 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 105);// Button 2 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 160);// Button 3 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 50);// Button 4 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 105);// Button 5 off
  M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 170, 160);// Button 6 off

  //M5.Lcd.drawPngFile(SD, "/icon/memw.png", 180, 6);
}
void pagemenu() {
  if (Page1.event == E_TOUCH) {
    seite = 0;
    M5.Lcd.drawPngFile(SD, "/icon/lightning-bolt-outline.png", 1, 200);
    webSocket.sendTXT("GET:/nodes/-1");
    //icon();
    //   page1();
  };
  if (Page2.event == E_TOUCH) {
    seite = 1;
    M5.Lcd.writecommand(ILI9341_DISPOFF);
    M5.Lcd.setBrightness(0);
    // page2();
    //M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);
  };
  if (Page3.event == E_TOUCH) {
    seite = 2;
    M5.Lcd.writecommand(ILI9341_DISPON);
    M5.Lcd.setBrightness(100);
    // page3();
    //webSocket.sendTXT("GET:/attributes/1786");
    //M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 50);
  };
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

void attribute() {
  //JSON Dokument erstellen
  //DynamicJsonDocument doc(ESP.getMaxAllocHeap());
  deserializeJson(doc, payload1);
  JsonObject object = doc.as<JsonObject>();
  // Variablen erstellen
  float attributtype = doc["attribute"]["type"].as<float>();
  float attributid = doc["attribute"]["id"].as<float>();
  float current_value = doc["attribute"]["current_value"].as<float>();

  //Wetter icon
  if ((doc["node"]["attributes"][3]["type"].as<float>() == 243.00) || (attributid == 243.00)) {
    Serial.println(doc["node"]["attributes"][3]["current_value"].as<float>());
    if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 7.00) || ( current_value == 7.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-cloudy.png", 140, 0);
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 8.00) || ( current_value == 8.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-partly-cloudy.png", 140, 0);
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 9.00) || ( current_value == 9.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-night-partly-cloudy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 1.00) || ( current_value == 1.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-night.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 0.00) || ( current_value == 0.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-sunny.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 2.00) || ( current_value == 2.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-rainy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 3.00) || ( current_value == 3.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-snowy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 4.00) || ( current_value == 4.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-snowy-rainy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 5.00) || ( current_value == 5.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-windy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 6.00) || ( current_value == 6.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-fog.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 10.00) || ( current_value == 10.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-hail.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 11.00) || ( current_value == 11.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-lightning.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 12.00) || ( current_value == 12.00)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-windy-variant.png", 140, 0 );
    }
  };
  //homee MEMORY UND CPU SOWIE SSD
  if (doc["attribute"]["type"].as<float>() == 311.00) {
    M5.Lcd.setTextColor(WHITE);
    //if ((doc["attribute"]["current_value"].as<float>() > 50.00) && (doc["attribute"]["current_value"].as<float>() < 75.00)) {
    //M5.Lcd.fillRoundRect(1, 1, 98 , 23, 10, YELLOW);
    //M5.Lcd.setTextColor(BLACK);
    //} else if (doc["attribute"]["current_value"].as<float>() > 75.00) {
    //M5.Lcd.fillRoundRect(1, 1, 98 , 23, 10, RED);
    //M5.Lcd.setTextColor(WHITE);
    //} else
    //M5.Lcd.fillRoundRect(26, 1, 78 , 23, 10, BLACK);
    //M5.Lcd.setCursor(26, 18);
    //M5.Lcd.printf("%6.1f%%", doc["attribute"]["current_value"].as<float>());
    Serial.print("Memory: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
  };
  if (doc["attribute"]["type"].as<float>() == 312.00) {
    M5.Lcd.setTextColor(WHITE);
    //if ((doc["attribute"]["current_value"].as<float>() > 50.00) && (doc["attribute"]["current_value"].as<float>() < 75.00)) {
    //M5.Lcd.fillRoundRect(106, 1, 98 , 23, 10, YELLOW);
    //M5.Lcd.setTextColor(BLACK);
    //} else if (doc["attribute"]["current_value"].as<float>() > 75.00) {
    //M5.Lcd.fillRoundRect(106, 1, 98 , 23, 10, RED);
    //M5.Lcd.setTextColor(WHITE);
    //} else
    //M5.Lcd.fillRoundRect(106, 1, 98 , 23, 10, BLACK);
    //M5.Lcd.setCursor(114, 18);
    //M5.Lcd.printf("C %6.1f%%", doc["attribute"]["current_value"].as<float>());
    Serial.print("Prozessor: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
  };
  if (doc["attribute"]["type"].as<float>() == 313.00) {
    M5.Lcd.setTextColor(WHITE);
    //if ((doc["attribute"]["current_value"].as<float>() > 50.00) && (doc["attribute"]["current_value"].as<float>() < 75.00)) {
    //M5.Lcd.fillRoundRect(211, 1, 98 , 23, 10, YELLOW);
    //M5.Lcd.setTextColor(BLACK);
    //} else if (doc["attribute"]["current_value"].as<float>() > 75.00) {
    //M5.Lcd.fillRoundRect(211, 1, 98 , 23, 10, RED);
    // M5.Lcd.setTextColor(WHITE);
    //} else
    //M5.Lcd.fillRoundRect(211, 1, 98 , 23, 10, BLACK);
    //M5.Lcd.setCursor(218, 18);
    // M5.Lcd.printf("S %6.1f%%", doc["attribute"]["current_value"].as<float>());
    Serial.print("UseStorage: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
  };
  //Gesamtverbrauch LEISTUNG IN WATT
  if (attributid == 3028.00) {
    M5.Lcd.fillRect(36, 205, 98 , 23, BLACK);
    M5.Lcd.setCursor(36, 225);
    M5.Lcd.printf("%6.1f W", current_value);
  };
  //Schloss Status
  if (attributid == 2905.00) {
    if (current_value == 1.00) {
      M5.Lcd.fillRect(100, 0, 35 , 35, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/home-lock.png", 100, 0);
    }
    if (current_value == 0.00) {
      M5.Lcd.fillRect(100, 0, 35 , 35, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/home-lock-open.png", 100, 0);
    };
  };

  // Temperatur Outdoor
  if (attributid == 1786.00) {
    if ((current_value > 9.99) || ( current_value < 0.00)) {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(181, 24);
      Serial.println(current_value);
      M5.Lcd.printf("%6.1f ", current_value);
    }
    else {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(190, 24);
      M5.Lcd.printf("%6.1f ", current_value);
    }//webSocket.sendTXT("GET:/nodes/-1");
  };
  //Sideboard
  if (attributid == 1769.00) {
    if (current_value == 1.00) {
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on24.png", 10, 50);
    }
    if (current_value == 0.00) {
      M5.Lcd.fillRect(10, 50, 24 , 24, BLACK);
      M5.Lcd.drawPngFile(SD, "/icon/lightbulb-on-outline24.png", 10, 50);
    }
  }
}
void wetter() {

}
void startpage() {

}
void disp() {
  delay(2000);
  M5.Lcd.writecommand(ILI9341_DISPOFF);
  M5.Lcd.setBrightness(0);
  //M5.Axp.ScreenBreath(7);
  //  M5.Axp.SetLDO2(false);
  //M5.Axp.SetLDO3(false);
  // M5.Speaker.beep();
  delay (2000);
  M5.Lcd.writecommand(ILI9341_DISPON);
  M5.Lcd.setBrightness(100);
  //M5.Axp.ScreenBreath(15);
  // M5.Axp.SetLDO2(true);
  //M5.Axp.SetLDO3(true);
}
