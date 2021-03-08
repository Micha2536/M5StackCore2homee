//const dataType windows[] PROGMEM = {};
// homee attribut analyse
void attribute( uint8_t * payload) {

  //JSON Dokument erstellen
  deserializeJson(doc, payload);
  //JsonObject object = doc.as<JsonObject>();
  // Variablen erstellen
  float node_id = doc["attribute"]["node_id"].as<float>();
  float attributtype = doc["attribute"]["type"].as<float>();
  float attributid = doc["attribute"]["id"].as<float>();
  float current_value = doc["attribute"]["current_value"].as<float>();

  if (device_conf == 99) {
    Serial.println("devconf io");
    Serial.print(device_conf);
    if (doc["node"]) {
      int i;
      for (i = 0 ; i < 10; i++) {
        Serial.print(doc["node"]["attributes"][i]["type"].as<float>(), 0);
        Serial.print(" : ");
        Serial.print(doc["node"]["attributes"][i]["current_value"].as<float>());
        Serial.print(" : Instance ");
        Serial.println(doc["node"]["attributes"][i]["instance"].as<float>(), 0);

        if (doc["node"]["attributes"][i]["type"].as<float>() == 5 ) {
          String inputMessage = String(doc["node"]["attributes"][i]["id"].as<float>(), 0);
          Serial.println(inputMessage);
          preferences.begin ( NAME, false ) ;// Open for read/write
          preferences.putString ("TempOut", inputMessage);
          preferences.end();
          TempOut = inputMessage;
          device_conf = 0;
        }
      }
    }
  }


  if (device_conf > 0) {
    Serial.println("devconf io");
    Serial.print(device_conf);
    if (doc["node"]) {
      int i;
      for (i = 0 ; i < 10; i++) {
        Serial.print(doc["node"]["attributes"][i]["type"].as<float>(), 0);
        Serial.print(" : ");
        Serial.print(doc["node"]["attributes"][i]["current_value"].as<float>());
        Serial.print(" : Instance ");
        Serial.println(doc["node"]["attributes"][i]["instance"].as<float>(), 0);

        if (doc["node"]["attributes"][i]["type"].as<float>() == 1) {
          String inputMessage = String(doc["node"]["attributes"][i]["id"].as<float>(), 0);
          Serial.println(inputMessage);
          preferences.begin ( NAME, false ) ;// Open for read/write
          String var_attr = String("attr") + String(device_conf);
          Serial.println(var_attr);
          preferences.putString (var_attr.c_str(), inputMessage);
          preferences.end();
          device_conf = 0;
        }
      }
    }
  }

  //Wetter icon
  if ((doc["node"]["attributes"][3]["type"].as<float>() == 243) || (attributid == 1322)) {
    Serial.println(doc["node"]["attributes"][3]["current_value"].as<float>());
    M5.Lcd.fillRect(140, 0, 35, 35, BLACK);
    if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 7) || ( current_value == 7)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-cloudy.png", 140, 0);
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 8) || ( current_value == 8)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-partly-cloudy.png", 140, 0);
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 9) || ( current_value == 9)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-night-partly-cloudy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 1) || ( current_value == 1)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-night.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 0) || ( current_value == 0)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-sunny.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 2) || ( current_value == 2)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-rainy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 3) || ( current_value == 3)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-snowy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 4) || ( current_value == 4)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-snowy-rainy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 5) || ( current_value == 5)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-windy.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 6) || ( current_value == 6)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-fog.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 10) || ( current_value == 10)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-hail.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 11) || ( current_value == 11)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-lightning.png", 140, 0 );
    }
    else if ((doc["node"]["attributes"][3]["current_value"].as<float>() == 12) || ( current_value == 12)) {
      M5.Lcd.drawPngFile(SD,  "/icon/weather-windy-variant.png", 140, 0 );
    }
  };

  //homee MEMORY and CPU and SSD
  if (doc["attribute"]["type"].as<float>() == 311) {
    M5.Lcd.setTextColor(WHITE);
    mem[0] = doc["attribute"]["current_value"].as<float>();
    Serial.print("Memory: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
    memst();
  };
  if (doc["attribute"]["type"].as<float>() == 312) {
    M5.Lcd.setTextColor(WHITE);
    cpu[0] = doc["attribute"]["current_value"].as<float>();
    Serial.print("Prozessor: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
    cpust();
  };
  if (doc["attribute"]["type"].as<float>() == 313) {
    M5.Lcd.setTextColor(WHITE);
    ssd[0] = doc["attribute"]["current_value"].as<float>();
    Serial.print("UseStorage: ");
    Serial.print(doc["attribute"]["current_value"].as<float>(), 2);
    Serial.println(doc["attribute"]["unit"].as<char*>());
    ssdst();
  };
  //Gesamtverbrauch LEISTUNG IN WATT
  if (attributid == 3028) {
    M5.Lcd.fillRect(36, 205, 120 , 23, BLACK);
    M5.Lcd.setCursor(36, 225);
    M5.Lcd.printf("%6.1f W", current_value);
  };

  // Temperatur Outdoor
  if (attributid == atof(TempOut.c_str()) || attributtype == 244) {
    if ((current_value > 9.99) || ( current_value < 0.00)) {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(181, 24);
      if (current_value < 4 ) {
        M5.Lcd.setTextColor(BLUE);
      }
      if (current_value > 4 ) {
        M5.Lcd.setTextColor(WHITE);
      }
      if (current_value > 20 ) {
        M5.Lcd.setTextColor(RED);
      }
      Serial.println(current_value);
      M5.Lcd.printf("%6.1f ", current_value);
      M5.Lcd.setTextColor(WHITE);
    }
    else {
      M5.Lcd.fillRect(180, 0, 60 , 36, BLACK);
      M5.Lcd.setCursor(190, 24);
      M5.Lcd.printf("%6.1f ", current_value);
    }//webSocket.sendTXT("GET:/nodes/-1");
  };
  //Button status
  if (attributid ==  atof(attr1_string.c_str())) {
    bnstate[1] = current_value;
    buttonstate1();
  }
  if (attributid == atof(attr2_string.c_str())) {
    bnstate[2] = current_value;
    buttonstate2();
  }

  if (attributid == atof(attr3_string.c_str())) {
    bnstate[3] = current_value ;
    buttonstate3();
  }
  if (attributid == atof(attr4_string.c_str())) {
    bnstate[4] = current_value;
    buttonstate4();
  }

  if (attributid == atof(attr5_string.c_str())) {
    bnstate[5] = current_value;
    buttonstate5();
  }
  if (attributid == atof(attr6_string.c_str())) {
    bnstate[6] = current_value;
    buttonstate6();
  }


// Window 
 if(doc["attribute"]["type"].as<float>() == 10 ){
     Serial.println("test");
      if (current_value == 0){
        Serial.println("Fenster Geschlossen"); 
      }
      if (current_value == 1 ){
        Serial.println("fenster geöffnet");
     
      }
     }
}




