// Debuganzeige im Display auf Seite 4 Button rechts 2x tippen

float count ;
void nodeabfrage( uint8_t * payload) {

  //JSON Dokument erstellen
  deserializeJson(doc, payload);
  JsonObject object = doc.as<JsonObject>();
  // Variablen erstellen
  float node_id = doc["attribute"]["node_id"].as<float>();
  float attributtype = doc["attribute"]["type"].as<float>();
  float attributid = doc["attribute"]["id"].as<float>();
  float current_value = doc["attribute"]["current_value"].as<float>();
  float attri;


  
  if (seite == 4) {if (count >=7){count = 0;}
    if (count == 0 ){M5.Lcd.setCursor(0, 60);M5.Lcd.fillRect(0, 35, 320, 165, BLACK);
    }
      M5.Lcd.setFont(FSS9);
      M5.Lcd.setTextSize(0.5);
    count++;
    //M5.Lcd.setCursor(5, 60);
    //M5.Lcd.fillRect(200, 65, 120, 120, BLACK);
    String testaus = (String)doc["node"]["name"].as<char*>();
    testaus.replace("%20", " ");

    M5.Lcd.printf("N %6.0f ,", node_id);
     M5.Lcd.printf("A %6.0f ,", attributid);
      M5.Lcd.printf("Value %6.2f", current_value);
    M5.Lcd.println("");
    M5.Lcd.setFont(FSS12);
    //Serial.print(testaus);
  }
}

  


