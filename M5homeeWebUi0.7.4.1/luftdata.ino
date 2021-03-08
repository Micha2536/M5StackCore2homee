
void luft() {
  if ((millis() == 30000) || lastluftmillis + (900 * 1000) == millis()) {
    lastluftmillis = millis();
    HTTPClient http;
    Serial.println("Getabfrage startet");
    http.begin("http://data.sensor.community/airrohr/v1/sensor/39197/"); //HTTPS example connection
    http.addHeader("Content-Type", "text/plain");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      luft_state = true;
      String payload = http.getString();
      Serial.println(payload);
      deserializeJson(doc, payload);
      for ( int i = 0; i < 4; i++) {
        if  (String (doc[0]["sensordatavalues"][i]["value_type"].as<char*>()) == "temperature") {
          luft_temp = doc[0]["sensordatavalues"][i]["value"].as<float>();
        }
        if  (String (doc[0]["sensordatavalues"][i]["value_type"].as<char*>()) == "pressure") {
          luft_pressure = doc[0]["sensordatavalues"][i]["value"].as<float>();
        }
        if  (String (doc[0]["sensordatavalues"][i]["value_type"].as<char*>()) == "humidity") {
          luft_humid = doc[0]["sensordatavalues"][i]["value"].as<float>();
        }
      }
    }
    deserializeJson(doc, "");
    http.end();
    luft_state = false;
    if (seite == 22){
  page22();}
  } 
}

void luft2() {
  if ((millis() == 60000) || lastluftmillis2 + (900 * 1000) == millis()) {
    lastluftmillis2 = millis();
    HTTPClient http;
    Serial.println("Getabfrage startet");
    http.begin("http://data.sensor.community/airrohr/v1/sensor/39266/"); //HTTPS example connection
    http.addHeader("Content-Type", "text/plain");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      luft_state = true;
      String payload = http.getString();
      Serial.println(payload);
      deserializeJson(doc, payload);
       for ( int i = 0; i < 4; i++) {
        if  (String (doc[0]["sensordatavalues"][i]["value_type"].as<char*>()) == "P1") {
          pm10 = doc[0]["sensordatavalues"][i]["value"].as<float>();
        }
        if (String (doc[0]["sensordatavalues"][i]["value_type"].as<char*>()) == "P2") {
          pm25 = doc[0]["sensordatavalues"][i]["value"].as<float>();
        }
      }
    }
    deserializeJson(doc, "");
    http.end();
    luft_state = false;
    if (seite == 22){
  page22();}
  }
}

