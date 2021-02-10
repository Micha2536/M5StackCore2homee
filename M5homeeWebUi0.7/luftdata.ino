void luft(){
  HTTPClient http;
    http.begin("https://data.sensor.community/airrohr/v1/sensor/000/"); //HTTPS example connection
    int httpCode = http.GET();
    if(httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      //file found at server --> on unsucessful connection code will be -1
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
     }else{
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
  http.end();  
  delay(2000);
}

