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
