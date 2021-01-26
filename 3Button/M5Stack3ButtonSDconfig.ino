#include <M5Core2.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";

WebServer server(80);
int checkSDCard(){
    sdcard_type_t Type = SD.cardType();
    if( Type == CARD_UNKNOWN || Type == CARD_NONE )
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

int seite = 0;
String url;
const char* b1name = "Default1";
const char* b2name = "Default2";
const char* b3name = "Default3";
const char* b4name = "Default4";
const char* b5name = "Default5";
const char* b6name = "Default6";
const char* b7name = "Default7";
const char* b8name = "Default8";
const char* b9name = "Default9";
String b1status;
String b2status;
String b3status;
String b4status;
String b5status;
String b6status;
String b7status;
String b8status;
String b9status;
const char* b1webh ;
const char* b2webh ;
const char* b3webh ;
const char* b4webh ;
const char* b5webh ;
const char* b6webh ;
const char* b7webh ;
const char* b8webh ;
const char* b9webh ;
const char* homeeurl;

Button myButton(50, 5, 220, 60, false, b1name,
{BLACK, WHITE, WHITE},
{RED, WHITE, WHITE} );
Button myButton2(50, 70, 220, 60, false, b2name,
{BLACK, WHITE, WHITE},
{RED, WHITE, WHITE} );
Button myButton3(50, 135, 220, 60, false, b3name,
{BLACK, WHITE, WHITE},
{RED, WHITE, WHITE} );
Button Page1 (10, 241, 100, 39);
Button Page2 (110, 241, 100, 39);
Button Page3 (210, 241, 100, 39);

Gesture swipeDown("swipe down", 10, DIR_DOWN, 45);
Gesture swipeLeft("swipe left", 10, DIR_LEFT, 45);

void setup() {

  delay(5000);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.begin();
  M5.begin();
  M5.Buttons.setFont(FS18);
  M5.Buttons.draw();
  myButton.longPressTime = 700;
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setCursor(30 , 230);
  M5.Lcd.print("Seite 1");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(135 , 230);
  M5.Lcd.print("Seite 2");
  M5.Lcd.setCursor(245 , 230);
  M5.Lcd.print("Seite 3");
  M5.Axp.SetLed(0);
  autostart();
  server.on("/config", []() {
    String conf = "";
    for (uint8_t i = 0; i < server.args(); i++) {
      conf += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      DynamicJsonDocument doc(ESP.getMaxAllocHeap());
      deserializeJson(doc, conf);
      b1name = doc["b1"]["name"];
      b1webh = doc["b1"]["webh"];
      b2name = doc["b2"]["name"];
      b2webh = doc["b2"]["webh"];
      b3name = doc["b3"]["name"];
      b3webh = doc["b3"]["webh"];
      b4name = doc["b4"]["name"];
      b4webh = doc["b4"]["webh"];
      b5name = doc["b5"]["name"];
      b5webh = doc["b5"]["webh"];
      b6name = doc["b6"]["name"];
      b6webh = doc["b6"]["webh"];
      b7name = doc["b7"]["name"];
      b7webh = doc["b7"]["webh"];
      b8name = doc["b8"]["name"];
      b8webh = doc["b8"]["webh"];
      b9name = doc["b9"]["name"];
      b9webh = doc["b9"]["webh"];
      homeeurl = doc["homeeurl"];
      if (seite == 0) page1();
      if (seite == 1) page2();
      if (seite == 2) page3();
     File file = SD.open("/M5Stack/config.json", FILE_WRITE);
     serializeJson(doc, file);
     file.close();
    }
  });
  server.on("/b1", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b1status ="";
      b1status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b1status);
      statusbutton();
    }
  });
  server.on("/b2", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b2status ="";
      b2status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b2status);
      statusbutton();
    }
  });
  server.on("/b3", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b3status ="";
      b3status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b3status);
      statusbutton();
    }
  });
  server.on("/b4", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b4status ="";
      b4status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b4status);
      statusbutton();
    }
  });
  server.on("/b5", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b5status ="";
      b5status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b5status);
      statusbutton();
    }
  });
  server.on("/b6", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b6status ="";
      b6status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b6status);
      statusbutton();
    }
  });
  server.on("/b7", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b7status ="";
      b7status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b7status);
      statusbutton();
    }
  });
  server.on("/b8", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b8status ="";
      b8status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b8status);
      statusbutton();
    }
  });
  server.on("/b9", []() {
    for (uint8_t i = 0; i < server.args(); i++) {
      b9status ="";
      b9status += server.arg(i);
      server.send(10, "text/plain", "Vielen Dank fÃ¼r die Nachricht");
      Serial.println("nachricht ist angekommen");
      Serial.println(b9status);
      statusbutton();
    }
  });
  if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void loop() {
  M5.update();
  server.handleClient();
  buttonrequest();
  //Event& e = M5.Buttons.event;
  //E_TAP, E_DBLTAP, E_PRESSED, E_LONGPRESSED und E_DRAGGED
  //E_TOUCH, E_MOVE und E_RELEASE
  pagemenu();
}

void pagemenu() {
  if (Page1.event == E_TOUCH) {
    seite = 0;
    page1();
  };
  if (Page2.event == E_TOUCH) {
    seite = 1;
    page2();
  };
  if (Page3.event == E_TOUCH) {
    seite = 2;
    page3();
  };
}

void page1() {
  M5.Lcd.setCursor(30 , 230);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.print("Seite 1");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(135 , 230);
  M5.Lcd.print("Seite 2");
  M5.Lcd.setCursor(245 , 230);
  M5.Lcd.print("Seite 3");
  myButton.setLabel(b1name);
  myButton2.setLabel(b2name);
  myButton3.setLabel(b3name);
  myButton.draw();
  myButton2.draw();
  myButton3.draw();
  statusbutton();
}

void page2() {
  M5.Lcd.setCursor(135 , 230);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.print("Seite 2");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(245 , 230);
  M5.Lcd.print("Seite 3");
  M5.Lcd.setCursor(30 , 230);
  M5.Lcd.print("Seite 1");
  myButton.setLabel(b4name);
  myButton2.setLabel(b5name);
  myButton3.setLabel(b6name);
  myButton.draw();
  myButton2.draw();
  myButton3.draw();
  statusbutton();
}

void page3() {
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setCursor(245 , 230);
  M5.Lcd.print("Seite 3");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(30 , 230);
  M5.Lcd.print("Seite 1");
  M5.Lcd.setCursor(135 , 230);
  M5.Lcd.print("Seite 2");
  myButton.setLabel(b7name);
  myButton2.setLabel(b8name);
  myButton3.setLabel(b9name);
  myButton.draw();
  myButton2.draw();
  myButton3.draw();
  statusbutton();
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

void request() {
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.GET();
  http.end();
}

void buttonrequest() {
  if (myButton.event == E_TOUCH && seite == 0) {
    url = String(homeeurl) + String(b1webh);
    request();
    //motor();
    statusbutton();
  }
  if (myButton2.event == E_TOUCH && seite == 0) {
    url = String(homeeurl) + String(b2webh);
    request();
    statusbutton();
  }
  if (myButton3.event == E_TOUCH && seite == 0) {
    url = String(homeeurl) + String(b3webh);
    request();
    statusbutton();
  }
  if (myButton.event == E_TOUCH && seite == 1) {
    url = String(homeeurl) + String(b4webh);
    request();
    statusbutton();
  }
  if (myButton2.event == E_TOUCH && seite == 1) {
    url = String(homeeurl) + String(b5webh);
    request();
    statusbutton();
  }
  if (myButton3.event == E_TOUCH && seite == 1) {
    url = String(homeeurl) + String(b6webh);
    request();
    statusbutton();
  }
  if (myButton.event == E_TOUCH && seite == 2) {
    url = String(homeeurl) + String(b7webh);
    request();
    statusbutton();
  }
  if (myButton2.event == E_TOUCH && seite == 2) {
    url = String(homeeurl) + String(b8webh);
    request();
    statusbutton();
  }
  if (myButton3.event == E_TOUCH && seite == 2) {
    url = String(homeeurl) + String(b9webh);
    request();
    statusbutton();
  }
}

void motor() {
  M5.Axp.SetLDOEnable(3, 1);
  delay(1000);
  M5.Axp.SetLDOEnable(3, 0);
}

void statusbutton() {
  if (seite == 0) {
    if (String(b1status) == "on") {
      M5.Buttons.drawFn(myButton, {GREEN, BLACK, RED});
    };
    if (String(b1status) == "off") {
      M5.Buttons.drawFn(myButton, {BLACK, WHITE, WHITE});
    };
    if (String(b2status) == "on") {
      M5.Buttons.drawFn(myButton2, {GREEN, BLACK, RED});
    };
    if (String(b2status) == "off") {
      M5.Buttons.drawFn(myButton2, {BLACK, WHITE, WHITE});
    };
    if (String(b3status) == "on") {
      M5.Buttons.drawFn(myButton3, {GREEN, BLACK, RED});
    };
    if (String(b3status) == "off") {
      M5.Buttons.drawFn(myButton3, {BLACK, WHITE, WHITE});
    };
  };
  if (seite == 1) {
    if (String(b4status) == "on") {
      M5.Buttons.drawFn(myButton, {GREEN, BLACK, RED});
    };
    if (String(b4status) == "off") {
      M5.Buttons.drawFn(myButton, {BLACK, WHITE, WHITE});
    };
    if (String(b5status) == "on") {
      M5.Buttons.drawFn(myButton2, {GREEN, BLACK, RED});
    };
    if (String(b5status) == "off") {
      M5.Buttons.drawFn(myButton2, {BLACK, WHITE, WHITE});
    };
    if (String(b6status) == "on") {
      M5.Buttons.drawFn(myButton3, {GREEN, BLACK, RED});
    };
    if (String(b6status) == "off") {
      M5.Buttons.drawFn(myButton3, {BLACK, WHITE, WHITE});
    };
  };
  if (seite == 2) {
    if (String(b7status) == "on") {
      M5.Buttons.drawFn(myButton, {GREEN, BLACK, RED});
    };
    if (String(b7status) == "off") {
      M5.Buttons.drawFn(myButton, {BLACK, WHITE, WHITE});
    };
    if (String(b8status) == "on") {
      M5.Buttons.drawFn(myButton2, {GREEN, BLACK, RED});
    };
    if (String(b8status) == "off") {
      M5.Buttons.drawFn(myButton2, {BLACK, WHITE, WHITE});
    };
    if (String(b9status) == "on") {
      M5.Buttons.drawFn(myButton3, {GREEN, BLACK, RED});
    };
    if (String(b9status) == "off") {
      M5.Buttons.drawFn(myButton3, {BLACK, WHITE, WHITE});
    };
  }
}

void autostart(){
  File file = SD.open("/M5Stack/config.json");
  DynamicJsonDocument doc(ESP.getMaxAllocHeap());
      deserializeJson(doc, file);
      b1name = doc["b1"]["name"];
      b1webh = doc["b1"]["webh"];
      b2name = doc["b2"]["name"];
      b2webh = doc["b2"]["webh"];
      b3name = doc["b3"]["name"];
      b3webh = doc["b3"]["webh"];
      b4name = doc["b4"]["name"];
      b4webh = doc["b4"]["webh"];
      b5name = doc["b5"]["name"];
      b5webh = doc["b5"]["webh"];
      b6name = doc["b6"]["name"];
      b6webh = doc["b6"]["webh"];
      b7name = doc["b7"]["name"];
      b7webh = doc["b7"]["webh"];
      b8name = doc["b8"]["name"];
      b8webh = doc["b8"]["webh"];
      b9name = doc["b9"]["name"];
      b9webh = doc["b9"]["webh"];
      homeeurl = doc["homeeurl"];
      file.close();
      page1();
}

