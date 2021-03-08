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

void touch() {
  if (varbutton == "6") {
    if (M5.Touch.changed && M5.Touch.points == 1) {
      Event& e = M5.Buttons.event;
      int b1 = ((float)e.to.y > 38 && (float)e.to.y < 88) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 1
      int b2 = ((float)e.to.y > 93 && (float)e.to.y < 143) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 2
      int b3 = ((float)e.to.y > 148 && (float)e.to.y < 198) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 3
      int b4 = ((float)e.to.y > 38 && (float)e.to.y < 88) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 4
      int b5 = ((float)e.to.y > 93 && (float)e.to.y < 143) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 5
      int b6 = ((float)e.to.y > 148 && (float)e.to.y < 198) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 6
      if (seite == 1 ) {
        if (b1)  {
          Serial.println(hg1_string);
          if (bnstate[1] == 1.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=0");
            Serial.println(str);
            webSocket.sendTXT(str);
            delay(500);
            webSocket.sendTXT("Get:/settings");
          }
          else if ( bnstate[1] == 0.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=1");
            Serial.println(str);
            webSocket.sendTXT(str);
          }
        };
        if ((b1) && (hg1_string == "true"))  {
          
            String str  = String("PUT:/homeegrams/") + id1_string + String("?play=1");
            Serial.println(str);
            webSocket.sendTXT(str);
        };
        if (b2)  {
          if (bnstate[2] == 1.00) {
            String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=0");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
          else if ( bnstate[2] == 0.00) {
            String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=1");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
        };
        if (b3)  {
          if (bnstate[3] == 1.00) {
            String str  = String("PUT:/nodes/") + id3_string + String("/attributes/") + attr3_string + String("?target_value=0");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
          else if ( bnstate[3] == 0.00) {
            String str  = String("PUT:/nodes/") + id3_string + String("/attributes/") + attr3_string + String("?target_value=1");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
        };
        if (b4)  {
          if (bnstate[4] == 1.00) {
            String str  = String("PUT:/nodes/") + id4_string + String("/attributes/") + attr4_string + String("?target_value=0");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
          else if ( bnstate[4] == 0.00) {
            String str  = String("PUT:/nodes/") + id4_string + String("/attributes/") + attr4_string + String("?target_value=1");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
        };
        if (b5)  {
          if (bnstate[5] == 1.00) {
            String str  = String("PUT:/nodes/") + id5_string + String("/attributes/") + attr5_string + String("?target_value=0");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
          else if ( bnstate[5] == 0.00) {
            String str  = String("PUT:/nodes/") + id5_string + String("/attributes/") + attr5_string + String("?target_value=1");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
        };
        if (b6)  {
          if (bnstate[6] == 1.00) {
            String str  = String("PUT:/nodes/") + id6_string + String("/attributes/") + attr6_string + String("?target_value=0");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
          else if ( bnstate[6] == 0.00) {
            String str  = String("PUT:/nodes/") + id6_string + String("/attributes/") + attr6_string + String("?target_value=1");
            webSocket.sendTXT(str);
            Serial.println(str);
          }
        };
      }
    }
  }
  if (varbutton == "1") {
    if (M5.Touch.changed && M5.Touch.points == 1) {
      Event& e = M5.Buttons.event;
      int b1 = ((float)e.to.y > 38 && (float)e.to.y < 195) && ((float)e.to.x > 5 && (float)e.to.x < 315); // Button 1
      if (seite == 1 ) {
        if (b1)  {
          if (bnstate[1] == 1.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=0");
            Serial.println("varbutton 1-1");
            Serial.println(str);
            webSocket.sendTXT(str);
          }
          else if ( bnstate[1] == 0.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=1");
            Serial.println(str);
            webSocket.sendTXT(str);
          }
        };
      }
    }
  }
  if (varbutton == "4") {
    if (M5.Touch.changed && M5.Touch.points == 1) {
      Event& e = M5.Buttons.event;
      int b1 = ((float)e.to.y > 40 && (float)e.to.y < 115) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 1
      int b2 = ((float)e.to.y > 120 && (float)e.to.y < 195) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 2
      int b3 = ((float)e.to.y > 40 && (float)e.to.y < 115) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 3
      int b4 = ((float)e.to.y > 120 && (float)e.to.y < 195) && ((float)e.to.x > 165 && (float)e.to.x < 305); // Button 4
      if (seite == 1 ) {
        if (b1)  {
          if (bnstate[1] == 1.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=0");
            Serial.println(str);
            Serial.println("varbutton 2 -1");
            webSocket.sendTXT(str);
          }
          else if ( bnstate[1] == 0.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=1");
            Serial.println(str);
            Serial.println("varbutton 2 -1");
            webSocket.sendTXT(str);
          }
        };
        if (b2)  {
          if (bnstate[2] == 1.00) {
            String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=0");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
          else if ( bnstate[2] == 0.00) {
            String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=1");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
        };
        if (b3)  {
          if (bnstate[3] == 1.00) {
            String str  = String("PUT:/nodes/") + id3_string + String("/attributes/") + attr3_string + String("?target_value=0");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
          else if ( bnstate[3] == 0.00) {
            String str  = String("PUT:/nodes/") + id3_string + String("/attributes/") + attr3_string + String("?target_value=1");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
        };
        if (b4)  {
          if (bnstate[4] == 1.00) {
            String str  = String("PUT:/nodes/") + id4_string + String("/attributes/") + attr4_string + String("?target_value=0");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
          else if ( bnstate[4] == 0.00) {
            String str  = String("PUT:/nodes/") + id4_string + String("/attributes/") + attr4_string + String("?target_value=1");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
        };
      }
    }
  }
   if (varbutton == "2") {
    if (M5.Touch.changed && M5.Touch.points == 1) {
      Event& e = M5.Buttons.event;
      int b1 = ((float)e.to.y > 38 && (float)e.to.y < 195) && ((float)e.to.x > 5 && (float)e.to.x < 155); // Button 1
      int b2 = ((float)e.to.y > 38 && (float)e.to.y < 195) && ((float)e.to.x > 165 && (float)e.to.x < 315); // Button 2
      if (seite == 1 ) {
        if (b1)  {
          if (bnstate[1] == 1.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=0");
            Serial.println(str);
            Serial.println("varbutton 2 -1");
            webSocket.sendTXT(str);
          }
          else if ( bnstate[1] == 0.00) {
            String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=1");
            Serial.println(str);
            Serial.println("varbutton 2 -1");
            webSocket.sendTXT(str);
          }
        };
        if (b2)  {
          if (bnstate[2] == 1.00) {
            String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=0");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
          else if ( bnstate[2] == 0.00) {
            String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=1");
            Serial.println(str);
            Serial.println("varbutton 2 -2");
            webSocket.sendTXT(str);
          }
        };
      }
    }
  }
}
