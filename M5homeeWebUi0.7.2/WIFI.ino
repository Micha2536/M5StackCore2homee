void setup_WIFI() {

  preferences.begin (NAME, false);
  String ssid_string = preferences.getString ("ssid");           //Netzwerk SSID
  const char * ssid_char = ssid_string.c_str();
  String passwort_string = preferences.getString ("passwort");   //Netzwerk Passwort
  const char * passwort_char = passwort_string.c_str();
  preferences.end();

  bool localAP = false;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_char, passwort_char);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    localAP = true;
    // return;
  }

  if (localAP)
  {
    Serial.println("WiFi Failed!");
    WiFi.softAP (NAME, NAME);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    M5.Lcd.setFont(FSS12);
    M5.Lcd.setCursor(0, 15);
    M5.Lcd.println("Verbinde dich mit dem Wlan \n M5Stack ( oder ESPressif ) \nund danach oeffne \n im Browser die Seite des\n M5Stack ueber die IP:\n");
    M5.Lcd.print(IP);
    M5.update();
  }
  else
  {
    Serial.println();
    Serial.print("Verbindung zu: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Addresse: ");
    Serial.println(WiFi.localIP());
  }
}
