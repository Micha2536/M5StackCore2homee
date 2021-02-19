void test(uint16_t x , uint16_t  y) {
  canvas.createCanvas(270, 40);
  canvas.setTextSize(3);
  String newstr = "x=" + String(x) + ": y= " + String(y);
  canvas.drawString(newstr, 0, 0);
  canvas.pushCanvas(5, 920, UPDATE_MODE_DU);
  canvas.deleteCanvas();
}

void touch() {
  if (M5.TP.avaliable()) {
    M5.TP.update();
    if (!M5.TP.isFingerUp()) {
      M5.TP.update();
      //Serial.print(M5.TP.isFingerUp());
      bool is_update = false;
      for (int i = 0; i < 2; i++) {
        tp_finger_t FingerItem = M5.TP.readFinger(i);
        if ((point[i][0] != FingerItem.x) || (point[i][1] != FingerItem.y)) {
          is_update = true;
          point[i][0] = FingerItem.x;
          point[i][1] = FingerItem.y;
          //canvas.fillRect(FingerItem.x - 50, FingerItem.y - 50, 100, 100, 15);
          Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y , FingerItem.size);
          device(FingerItem.x,FingerItem.y);
          if ( FingerItem.x > 0 && FingerItem.x < 900 ) {
            test(FingerItem.x, FingerItem.y);
          }
          if ( (FingerItem.x > 0 && FingerItem.x < 110) && (FingerItem.y > 70 && FingerItem.y < 170)) {
            page1();
            Serial.println("pfeil links");
          }
          if ( (FingerItem.x > 440 && FingerItem.x < 540) && (FingerItem.y > 70 && FingerItem.y < 170)) {
            page2();
            Serial.println("pfeil rechts");
          }

          if (seite == 1) {
            // Button 1
            if ( (FingerItem.x > 137 && FingerItem.x < 230) && (FingerItem.y > 370 && FingerItem.y < 400)) {
              if (bnstate[1] == 1) {
                String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=0");
                Serial.println(str);
                webSocket.sendTXT(str);
              }
            }
            else if ( (FingerItem.x > 37 && FingerItem.x < 137) && (FingerItem.y > 370 && FingerItem.y < 400)) {
              if ( bnstate[1] == 0) {
                String str  = String("PUT:/nodes/") + id1_string + String("/attributes/") + attr1_string + String("?target_value=1");
                Serial.println(str);
                webSocket.sendTXT(str);
              }
            }
            // button 2
            if ( (FingerItem.x > 137 && FingerItem.x < 230) && (FingerItem.y > 600 && FingerItem.y < 630)) {
              if (bnstate[2] == 1) {
                String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=0");
                Serial.println(str);
                webSocket.sendTXT(str);
                mqttClient.subscribe(name3_string.c_str());
                mqttClient.beginMessage(name3_string.c_str());
                mqttClient.print("taste 2 off ");
                mqttClient.endMessage();
              }
            }
            else if ( (FingerItem.x > 37 && FingerItem.x < 137) && (FingerItem.y > 600 && FingerItem.y < 630)) {
              if ( bnstate[2] == 0) {
                String str  = String("PUT:/nodes/") + id2_string + String("/attributes/") + attr2_string + String("?target_value=1");
                Serial.println(str);
                webSocket.sendTXT(str);
              }
            }
          }
        }
      }
    }
  }
  if (M5.TP.avaliable()) {
    if (M5.TP.isFingerUp()) {
      M5.TP.update();
      //Serial.print(M5.TP.isFingerUp());
      bool is_update = false;
      for (int i = 0; i < 2; i++) {
        tp_finger_t FingerItem = M5.TP.readFinger(i);
        if ((point[i][0] != FingerItem.x) || (point[i][1] != FingerItem.y)) {
          is_update = true;
          point[i][0] = FingerItem.x;
          point[i][1] = FingerItem.y;
          //canvas.fillRect(FingerItem.x - 50, FingerItem.y - 50, 100, 100, 15);
          Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y , FingerItem.size);
          
}}}}}
