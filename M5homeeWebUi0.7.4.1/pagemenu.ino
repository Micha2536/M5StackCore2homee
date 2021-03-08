// red button select page
void pagemenu() {
  if (Page1.event == E_TOUCH) {
    if (seite != 1) {
      seite = 1;
      M5.Lcd.fillRect(0, 38, 320, 162, BLACK);
      M5.Buttons.draw();
      page1();
    }
    else if ( seite == 1) {
      seite = 11;
      M5.Lcd.fillRect(0, 38, 320, 162, BLACK);
    }
  }
  if (Page2.event == E_TOUCH) {
    if (seite != 2) {
      seite = 2;
      M5.Lcd.fillRect(0, 38, 320, 162, BLACK);
      M5.Buttons.draw();
      page2();
    }
    else if ( seite == 2) {
      seite = 22;
      page22();
    }
  }
  if (Page3.event == E_TOUCH) {
    if (seite != 3 ) {
      seite = 3;
      M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
      //M5.Lcd.sleep();
      M5.Lcd.setBrightness(10);
      M5.Lcd.setCursor(50, 80);
      keyboard();
    }
    else if (seite == 3) {
      seite = 4;
      M5.Lcd.fillRect(0, 38, 320, 160, BLACK);

    }
  }
}
void page1() {
  Serial.print("Anzahl an Button = ");
  Serial.println(varbutton);
  const char* name1 = name1_string.c_str();
  const char* name2 = name2_string.c_str();
  const char* name3 = name3_string.c_str();
  const char* name4 = name4_string.c_str();
  const char* name5 = name5_string.c_str();
  const char* name6 = name6_string.c_str();
  if (varbutton == "6") {
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
    testb(5, 38, 150, 50, 15, WHITE, name1, WHITE); // Button1
    testb(5, 93, 150, 50, 15, WHITE, name2, WHITE); // Button2
    testb(5, 148, 150, 50, 15, WHITE, name3, WHITE); // Button3
    testb(165, 38, 150, 50, 15, WHITE, name4, WHITE); // Button4
    testb(165, 93, 150, 50, 15, WHITE, name5, WHITE); // Button5
    testb(165, 148, 150, 50, 15, WHITE, name6, WHITE); // Button6
    buttonstate1();
    buttonstate2();
    buttonstate3();
    buttonstate4();
    buttonstate5();
    buttonstate6();
  }
  else if (varbutton == "1") {
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
    testb(5, 38, 310, 160, 15, WHITE, name1, WHITE); // Button1
    buttonstate1();
  }
  else if (varbutton == "2") {
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
    testb(5, 38, 150, 160, 15, WHITE, name1, WHITE); // Button1
    testb(165, 38, 150, 160, 15, WHITE, name2, WHITE); // Button2
    buttonstate1();
    buttonstate2();
  }
  else if (varbutton == "4") {
    M5.Lcd.fillRect(0, 38, 320, 160, BLACK);
    testb(5, 38, 150, 75, 15, WHITE, name1, WHITE); // Button1
    testb(5, 118, 150, 75, 15, WHITE, name2, WHITE); // Button2
    testb(165, 38, 150, 75, 15, WHITE, name3, WHITE); // Button3
    testb(165, 118, 150, 75, 15, WHITE, name4, WHITE); // Button4
    buttonstate1();
    buttonstate2();
    buttonstate3();
    buttonstate4();
  }
}
void page2() {
  testb(5, 80, 100, 50, 15, WHITE, " ", WHITE);
  M5.Lcd.setCursor(15, 65 );
  M5.Lcd.print("Memory");
  memst();
  testb(110, 80, 100, 50, 15, WHITE, " ", WHITE);
  M5.Lcd.setCursor(135, 65 );
  M5.Lcd.print("CPU");
  cpust();
  testb(215, 80, 100, 50, 15, WHITE, " ", WHITE);
  M5.Lcd.setCursor(218, 65 );
  M5.Lcd.print("Speicher");
  ssdst();
  wlanip();
}
void page22() {
  M5.Lcd.fillRect(0, 38, 320, 162, BLACK);
  M5.Lcd.drawRoundRect(0, 38, 320, 162, 15, WHITE);
  M5.Lcd.drawFastHLine(0, 110, 320, WHITE);
  M5.Lcd.drawFastVLine(160, 110, 90, WHITE);
  M5.Lcd.drawFastHLine(0, 155, 320, WHITE);
  if ((luft_temp > 9.99) || ( luft_temp < 0.00)) {
    //M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
    M5.Lcd.setFont(FSS12);
    M5.Lcd.setCursor(70, 80);
    if (luft_temp < 4 ) {
      M5.Lcd.setTextColor(BLUE);
    }
    if (luft_temp > 4 ) {
      M5.Lcd.setTextColor(WHITE);
    }
    if (luft_temp > 20 ) {
      M5.Lcd.setTextColor(RED);
    }
    Serial.println(luft_temp);
    M5.Lcd.printf("Temp %6.1f ", luft_temp);
    M5.Lcd.setTextColor(WHITE);
  }
  else {
    M5.Lcd.setFont(FSS12);
    M5.Lcd.setCursor(70, 80);
    M5.Lcd.printf("Temp %6.1f ", luft_temp);
    M5.Lcd.setTextColor(WHITE);
  }
  M5.Lcd.drawPngFile(SD, "/icon/temperature-celsius.png", 200, 60);
  M5.Lcd.setFont(FSS12);
  M5.Lcd.setCursor(10, 140 );
  M5.Lcd.printf("%6.1f ", luft_humid);
  M5.Lcd.print(" % r.F.");
  M5.Lcd.setCursor(170, 140 );
  M5.Lcd.printf("%6.1f ", luft_pressure);
  M5.Lcd.print(" Pa");
  M5.Lcd.setCursor(10, 185 );
  M5.Lcd.print("PM2.5: ");
  M5.Lcd.printf("%6.1f ", pm25);
  M5.Lcd.setCursor(170, 185 );
  M5.Lcd.print("PM10: ");
  M5.Lcd.printf("%6.1f ", pm10);



}
