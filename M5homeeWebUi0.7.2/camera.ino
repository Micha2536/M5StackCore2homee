// Camera test
void test() {
  if (timeClient.getMinutes() == 59) {
    lasttime1 = 0;
  }
  if (((timeClient.getMinutes() - lasttime1) > 2) && seite == 3) {
    lasttime1 = timeClient.getMinutes();
    M5.Lcd.fillRect(0, 38, 320, 161, BLACK);
    M5.Lcd.drawPngUrl("http://xxxxxxxxxxx/test.png", 0, 40, 320, 160, 0, 0, 1);
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

