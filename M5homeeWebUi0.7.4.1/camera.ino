// Camera test
void test() {
  if (timeClient.getMinutes() == 59) {
    lasttime1 = 0;
  }
  if (((timeClient.getMinutes() - lasttime1) > 2) && seite == 3) {
    lasttime1 = timeClient.getMinutes();
    M5.Lcd.fillRect(0, 38, 320, 161, BLACK);
    M5.Lcd.drawPngUrl("http://192.168.178.28:1400/getaa?s=1&u=x-sonosapi-stream%3as25224%3fsid%3d254%26flags%3d8224%26sn%3d0", 0, 40, 320, 160, 0, 0, 1);
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

