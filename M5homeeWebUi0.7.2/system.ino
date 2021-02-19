// homee memory print
void memst() {
  if ( seite == 2 ) {
    M5.Lcd.fillRoundRect(5, 80, 100, 50, 15, BLACK);
    if ((mem[0] > 50.00) && (mem[0] < 75.00)) {
      M5.Lcd.drawRoundRect(5, 80, 100 , 50, 15, YELLOW);
      M5.Lcd.setTextColor(YELLOW);
    } else if (mem[0] > 75.00) {
      M5.Lcd.drawRoundRect(5, 80, 100 , 50, 15, RED);
      M5.Lcd.setTextColor(RED);
    } else
      M5.Lcd.drawRoundRect(5, 80, 100 , 50, 15, WHITE);
    M5.Lcd.setCursor(15, 112 );
    M5.Lcd.printf("%6.1f%%", mem[0]);
  }
}

// homee cpu print
void cpust() {
  if ( seite == 2 ) {
    M5.Lcd.fillRoundRect(110, 80, 100, 50, 15, BLACK);
    if ((cpu[0] > 50.00) && (cpu[0] < 75.00)) {
      M5.Lcd.drawRoundRect(110, 80, 100 , 50, 15, YELLOW);
      M5.Lcd.setTextColor(YELLOW);
    } else if (cpu[0] > 75.00) {
      M5.Lcd.drawRoundRect(110, 80, 100 , 50, 15, RED);
      M5.Lcd.setTextColor(RED);
    } else
      M5.Lcd.drawRoundRect(110, 80, 100 , 50, 15, WHITE);
    M5.Lcd.setCursor(120, 112 );
    M5.Lcd.printf("%6.1f%%", cpu[0]);
  }
}

// homee SSD print
void ssdst() {
  if ( seite == 2 ) {
    M5.Lcd.fillRoundRect(215, 80, 100, 50, 15, BLACK);
    if ((ssd[0] > 50.00) && (ssd[0] < 75.00)) {
      M5.Lcd.drawRoundRect(215, 80, 100 , 50, 15, YELLOW);
      M5.Lcd.setTextColor(YELLOW);
    } else if (ssd[0] > 75.00) {
      M5.Lcd.drawRoundRect(215, 80, 100 , 50, 15, RED);
      M5.Lcd.setTextColor(RED);
    } else
      M5.Lcd.drawRoundRect(215, 80, 100 , 50, 15, WHITE);
    M5.Lcd.setCursor(225, 112 );
    M5.Lcd.printf("%6.1f%%", ssd[0]);
  }
}

void wlanip(){
  M5.Lcd.setFont(FSS9);
  M5.Lcd.setCursor(15,155);
  M5.Lcd.print("M5Stack IP:");
  M5.Lcd.print(WiFi.localIP());
  M5.Lcd.setCursor(15,180);
  M5.Lcd.print("homee IP:");
  M5.Lcd.print(homeeIP_string);
  M5.Lcd.setFont(FSS12);
  
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

