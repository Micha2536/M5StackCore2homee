/*BY Micha homee Community


*/
// homee attribut analyse

int y = 200;
void attribute( uint8_t * payload) {

  //JSON Dokument erstellen
  deserializeJson(doc, payload);
  JsonObject object = doc.as<JsonObject>();
  // Variablen erstellen
  float node_id = doc["attribute"]["node_id"].as<float>();
  float attributtype = doc["attribute"]["type"].as<float>();
  float attributid = doc["attribute"]["id"].as<float>();
  float current_value = doc["attribute"]["current_value"].as<float>();
  if (doc["homeegram"]) {
    return;
  }
  if (doc["attribute_history"]){
    lcd.fillRect(0,200,540,700,0xFFFFFFu);
      int i;
      for (i = 0 ; i < 100; i++) {
        float test = doc["attribute_history"]["results"][0]["series"][0]["values"][i][1].as<float>();
        Serial.println(test);
        delay(50);
        chart(test);
        }
      }
   
  

if ((doc["node"])){
    int i;
  for (i = 0 ; i <20 ;i++){
    /*Serial.print(doc["node"]["attributes"][i]["type"].as<float>(),0);
    Serial.print(" : ");
    Serial.print(doc["node"]["attributes"][i]["current_value"].as<float>());
    Serial.print(" : Instance ");
     Serial.println(doc["node"]["attributes"][i]["instance"].as<float>(),0);
    */
     if (doc["node"]["attributes"][i]["type"].as<float>() == 1) {
      String inputMessage = String(doc["node"]["attributes"][i]["id"].as<float>(),0);
      Serial.println(inputMessage);
      preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("attr1", inputMessage);
        preferences.end();
        attr1_string = inputMessage;
        Serial.println(inputMessage);
     }
  }
}

if (doc["attribute"]["type"].as<float>() == 311) {
      mem[0] = doc["attribute"]["current_value"].as<float>();
      //memst();
      //chart(mem[0]);
      }




  /*  //Wetter icon
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
  */  //Gesamtverbrauch LEISTUNG IN WATT
  if (attributid == 3028) {
    /*lcd.fillRect(300,920,240,20,0xFFFFFFu);
      lcd.setCursor(300,920);
         lcd.setTextColor(16);
         lcd.setTextSize(3);
         lcd.println(String(current_value)+" W");
    */
    canvas.createCanvas(240, 40);
    canvas.setTextSize(3);
    //String newstr = "x=" + String(x) + ": y= " + String(y);
    String newstr = String(current_value)+" W";
    canvas.drawString(newstr, 0, 0);
    canvas.pushCanvas(300, 920, UPDATE_MODE_DU);
    canvas.deleteCanvas();
    //chart(current_value);
  };

  /*// Temperatur Outdoor
    if(attributid == atof(TempOut.c_str()) || attributtype == 244) {
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
  */
  //Button status
 /* if (seite == 2) {
    lcd.setRotation(0);
    lcd.setCursor(0, y);
    lcd.setTextColor(16);
    lcd.setTextSize(3);
    lcd.println("Node " + String(node_id, 0) + " Value " + String(current_value));
    lcd.println();
    y = y + 27;
    if (y > 850) {
      y = 170;
      delay(500);
      lcd.fillRect(0, 170, 540, 730, 0xFFFFFFu);
    }
  }
  */
  //Serial.println(String(attributid, 0) + ":" + String(node_id, 0) + ":" + String(current_value));

  if (attributid ==  atof(attr1_string.c_str())) {
    if (bnstate[1] != current_value) {
      bnstate[1] = current_value;
      Serial.println("Status Button 1 neugesetzt");
      buttonstate1();
    }
  }
  if (attributid == atof(attr2_string.c_str())) {
    if (bnstate[2] != current_value) {
      bnstate[2] = current_value;
      Serial.println("Status Button 2 neugesetzt");
      buttonstate2();
    }
  }
  if (attributid == atof(attr3_string.c_str())) {
    if (bnstate[3] != current_value) {
      bnstate[3] = current_value ;
      Serial.println("Status Button 3 neugesetzt");
      buttonstate3();
    }
  }
  if (attributid == atof(attr4_string.c_str())) {
    if (bnstate[4] != current_value) {
      bnstate[4] = current_value;
      Serial.println("Status Button 4 neugesetzt");
      buttonstate4();
    }
  }
  if (attributid == atof(attr5_string.c_str())) {
    if (bnstate[5] != current_value) {
      bnstate[5] = current_value;
      Serial.println("Status Button 5 neugesetzt");
      buttonstate5();
    }
  }
  if (attributid == atof(attr6_string.c_str())) {
    if (bnstate[6] != current_value) {
      bnstate[6] = current_value;
      Serial.println("Status Button 6 neugesetzt");
      buttonstate6();
    }
  }
}



