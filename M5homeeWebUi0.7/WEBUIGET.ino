void http_GET() {

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

 
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    if (request->hasParam(PARAM_SSID)) {
      inputMessage = request->getParam(PARAM_SSID)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("ssid", inputMessage);
      preferences.end();
    }
    
    else if (request->hasParam(PARAM_PASSWORT)) {
      inputMessage = request->getParam(PARAM_PASSWORT)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("passwort", inputMessage);
      preferences.end();
    }
   
    else if (request->hasParam(PARAM_homeeIP)) {
      inputMessage = request->getParam(PARAM_homeeIP)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("homeeIP", inputMessage);
      preferences.end();
    }
    
    else if (request->hasParam(PARAM_TOKEN)) {
      inputMessage = request->getParam(PARAM_TOKEN)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("token", inputMessage);
      preferences.end();

    }
    
    else if (request->hasParam(UI_name1)) {
      inputMessage = request->getParam(UI_name1)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("name1", inputMessage);
      preferences.end();
      name1_string = inputMessage;
    }
    
    else if (request->hasParam(UI_id1)) {
      inputMessage = request->getParam(UI_id1)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("id1", inputMessage);
      preferences.end();
      id1_string = inputMessage;
    }
    
    else if (request->hasParam(UI_attr1)) {
      inputMessage = request->getParam(UI_attr1)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("attr1", inputMessage);
      preferences.end();
      attr1_string = inputMessage;
    }
    
    else if (request->hasParam(UI_name2)) {
      inputMessage = request->getParam(UI_name2)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("name2", inputMessage);
      preferences.end();
      name2_string = inputMessage;
    }
    
    else if (request->hasParam(UI_id2)) {
      inputMessage = request->getParam(UI_id2)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("id2", inputMessage);
      preferences.end();
      id2_string = inputMessage;
    }
    
    else if (request->hasParam(UI_attr2)) {
      inputMessage = request->getParam(UI_attr2)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("attr2", inputMessage);
      preferences.end();
      attr2_string = inputMessage;
    }
    
    else if (request->hasParam(UI_name3)) {
      inputMessage = request->getParam(UI_name3)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("name3", inputMessage);
      preferences.end();
      name3_string = inputMessage;
    }
   
    else if (request->hasParam(UI_id3)) {
      inputMessage = request->getParam(UI_id3)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("id3", inputMessage);
      preferences.end();
      id3_string = inputMessage;
    }
    // GET inputAttr3 value on <ESP_IP>/get?inputAttr3=<inputMessage>
    else if (request->hasParam(UI_attr3)) {
      inputMessage = request->getParam(UI_attr3)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("attr3", inputMessage);
      preferences.end();
      attr3_string = inputMessage;
    }
    // GET inputName4 value on <ESP_IP>/get?inputName4=<inputMessage>
    else if (request->hasParam(UI_name4)) {
      inputMessage = request->getParam(UI_name4)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("name4", inputMessage);
      preferences.end();
      name4_string = inputMessage;
    }
    // GET inputId4 value on <ESP_IP>/get?inputId4=<inputMessage>
    else if (request->hasParam(UI_id4)) {
      inputMessage = request->getParam(UI_id4)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("id4", inputMessage);
      preferences.end();
      id4_string = inputMessage;
    }
    // GET inputAttr4 value on <ESP_IP>/get?inputAttr4=<inputMessage>
    else if (request->hasParam(UI_attr4)) {
      inputMessage = request->getParam(UI_attr4)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("attr4", inputMessage);
      preferences.end();
      attr4_string = inputMessage;
    }
    // GET inputName5 value on <ESP_IP>/get?inputName5=<inputMessage>
    else if (request->hasParam(UI_name5)) {
      inputMessage = request->getParam(UI_name5)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("name5", inputMessage);
      preferences.end();
      name5_string = inputMessage;
    }
    // GET inputId5 value on <ESP_IP>/get?inputId5=<inputMessage>
    else if (request->hasParam(UI_id5)) {
      inputMessage = request->getParam(UI_id5)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("id5", inputMessage);
      preferences.end();
      id5_string = inputMessage;
    }
    // GET inputAttr5 value on <ESP_IP>/get?inputAttr5=<inputMessage>
    else if (request->hasParam(UI_attr5)) {
      inputMessage = request->getParam(UI_attr5)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("attr5", inputMessage);
      preferences.end();
      attr5_string = inputMessage;
    }
    // GET inputName6 value on <ESP_IP>/get?inputName6=<inputMessage>
    else if (request->hasParam(UI_name6)) {
      inputMessage = request->getParam(UI_name6)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("name6", inputMessage);
      preferences.end();
      name6_string = inputMessage;
    }
    // GET inputId6 value on <ESP_IP>/get?inputId6=<inputMessage>
    else if (request->hasParam(UI_id6)) {
      inputMessage = request->getParam(UI_id6)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("id6", inputMessage);
      preferences.end();
      id6_string = inputMessage;
    }
    // GET inputAttr6 value on <ESP_IP>/get?inputAttr6=<inputMessage>
    else if (request->hasParam(UI_attr6)) {
      inputMessage = request->getParam(UI_attr6)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("attr6", inputMessage);
      preferences.end();
      attr6_string = inputMessage;
    }
    // GET inputTempOut value on <ESP_IP>/get?inputTempOut=<inputMessage>
    else if (request->hasParam(UI_TempOut)) {
      inputMessage = request->getParam(UI_TempOut)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("TempOut", inputMessage);
      preferences.end();
      TempOut = inputMessage;
    }
    // GET inputdebug value on <ESP_IP>/get?inputdebug=<inputMessage>
    else if (request->hasParam(UI_button)) {
      inputMessage = request->getParam(UI_button)->value();
      preferences.begin ( NAME, false ) ;                 // Open for read/write
      preferences.putString ("varbutton", inputMessage);
      preferences.end();
      varbutton = inputMessage;
      Serial.print("neue Anzahl an Button = ");
      Serial.println(inputMessage);
    }
    else {
      inputMessage = "No message sent";
    }
    request->send(200);
  });
}
