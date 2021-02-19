void keyboardtouch() {
  if (M5.Touch.changed && M5.Touch.points == 1) {
    Event& e = M5.Buttons.event;
    int n1 = ((float)e.to.y > 40 && (float)e.to.y < 76) && ((float)e.to.x > 20 && (float)e.to.x < 56); // Number1
    int n2 = ((float)e.to.y > 40 && (float)e.to.y < 76) && ((float)e.to.x > 80 && (float)e.to.x < 116); // Number 2
    int n3 = ((float)e.to.y > 40 && (float)e.to.y < 76) && ((float)e.to.x > 140 && (float)e.to.x < 176); // Number 3
    int n4 = ((float)e.to.y > 80 && (float)e.to.y < 116) && ((float)e.to.x > 20 && (float)e.to.x < 56); // Number 4
    int n5 = ((float)e.to.y > 80 && (float)e.to.y < 116) && ((float)e.to.x > 80 && (float)e.to.x < 116); // Number 5
    int n6 = ((float)e.to.y > 80 && (float)e.to.y < 116) && ((float)e.to.x > 140 && (float)e.to.x < 176); // Number 6
    int n7 = ((float)e.to.y > 120 && (float)e.to.y < 156) && ((float)e.to.x > 20 && (float)e.to.x < 56); // Number 7
    int n8 = ((float)e.to.y > 120 && (float)e.to.y < 156) && ((float)e.to.x > 80 && (float)e.to.x < 116); // Number 8
    int n9 = ((float)e.to.y > 120 && (float)e.to.y < 156) && ((float)e.to.x > 140 && (float)e.to.x < 176); // Number 9
    int nb = ((float)e.to.y > 160 && (float)e.to.y < 196) && ((float)e.to.x > 20 && (float)e.to.x < 56); // back
    int n0 = ((float)e.to.y > 160 && (float)e.to.y < 196) && ((float)e.to.x > 80 && (float)e.to.x < 116); // Number 0
    int nr = ((float)e.to.y > 160 && (float)e.to.y < 196) && ((float)e.to.x > 140 && (float)e.to.x < 176); // return
    if (seite == 3) {
      if (n1) {
        num += "1";
      }
      if (n2) {
        num += "2";
      }
      if (n3) {
        num += "3";
      }
      if (n4) {
        num += "4";
      }
      if (n5) {
        num += "5";
      }
      if (n6) {
        num += "6";
      }
      if (n7) {
        num += "7";
      }
      if (n8) {
        num += "8";
      }
      if (n9) {
        num += "9";
      }
      if (n0) {
        num += "0";
      }
      if (nb) {
        num = "";
      }
      if (nr) {
        String webs = "GET:/nodes/" + num;
        webSocket.sendTXT(webs);
      }
      M5.Lcd.fillRect(200, 40, 120, 30, BLACK);
      M5.Lcd.fillRect(200, 80, 120, 40, BLACK);
      M5.Lcd.setCursor(200, 60);
      M5.Lcd.print(num);
    }
  }
}

void keyboard() {
  M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-1-box-outline.png", 20 , 40);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-2-box-outline.png", 80 , 40);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-3-box-outline.png", 140 , 40);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-4-box-outline.png", 20 , 80);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-5-box-outline.png", 80 , 80);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-6-box-outline.png", 140 , 80);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-7-box-outline.png", 20 , 120);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-8-box-outline.png", 80 , 120);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-9-box-outline.png", 140 , 120);
  M5.Lcd.drawPngFile(SD, "/icon/keyboard-backspace.png", 20 , 160);
  M5.Lcd.drawPngFile(SD, "/icon/numeric-0-box-outline.png", 80 , 160);
  M5.Lcd.drawPngFile(SD, "/icon/keyboard-return.png", 140 , 160);
}
void nodeabf( uint8_t * payload) {

  //JSON Dokument erstellen
  deserializeJson(doc, payload);
  JsonObject object = doc.as<JsonObject>();
  // Variablen erstellen
  float node_id = doc["attribute"]["node_id"].as<float>();
  float attributtype = doc["attribute"]["type"].as<float>();
  float attributid = doc["attribute"]["id"].as<float>();
  float current_value = doc["attribute"]["current_value"].as<float>();
  float attri;
  if ((seite == 3) && (doc["node"]) && (doc["node"]["id"].as<float>() != -1)) {
    M5.Lcd.setCursor(200, 85);
    M5.Lcd.fillRect(200, 65, 120, 120, BLACK);
    String testaus = (String)doc["node"]["name"].as<char*>();
    testaus.replace("%20", " ");
    if (doc["node"]["attributes"][0]["type"].as<float>() == 1) {
      attri = doc["node"]["attributes"][0]["id"].as<float>();
      M5.Lcd.printf("%6.0f   ", attri);
    }
    if (doc["node"]["attributes"][1]["type"].as<float>() == 1) {
      attri = doc["node"]["attributes"][1]["id"].as<float>();
      M5.Lcd.setCursor(200, 110);
      M5.Lcd.printf("%6.0f   ", attri);
    }
    if (doc["node"]["attributes"][2]["type"].as<float>() == 1) {
      attri = doc["node"]["attributes"][2]["id"].as<float>();
      M5.Lcd.setCursor(200, 135);
      M5.Lcd.printf("%6.0f   ", attri);
    }
    if (doc["node"]["attributes"][3]["type"].as<float>() == 1) {
      attri = doc["node"]["attributes"][3]["id"].as<float>();
      M5.Lcd.setCursor(200, 160);
      M5.Lcd.printf("%6.0f   ", attri);
    }
    Serial.print(testaus);
  }
}

