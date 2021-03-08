void http_GET() {

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  //AsyncWebServerRequest * request
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *  request) {
    int params = request->params();
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);

      Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());

      String inputMessage;
      if (p->name() == PARAM_SSID) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("ssid", inputMessage);
        preferences.end();
      }

      else if (p->name() == PARAM_PASSWORT) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("passwort", inputMessage);
        preferences.end();
      }

      else if (p->name() == PARAM_homeeIP) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("homeeIP", inputMessage);
        preferences.end();
        homeeIP_string = inputMessage;
      }
       else if (p->name() == PARAM_USERNAME) {
        inputMessage = p->value();
        username_string = inputMessage;
       }
      else if (p->name() == PARAM_PASSWORD) {
        inputMessage = p->value();
        password_string = inputMessage;
        homee(username_string,password_string,homeeIP_string);

      }

      else if (p->name() == UI_name1 ) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("name1", inputMessage);
        preferences.end();
        name1_string = inputMessage;
      }

      else if (p->name() == UI_id1) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("id1", inputMessage);
        preferences.end();
        id1_string = inputMessage;
        device_conf = 1;
        homee_getnode(inputMessage);
      }

      /*else if (p->name() == UI_attr1) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("attr1", inputMessage);
        preferences.end();
        attr1_string = inputMessage;
      }*/
      else if (p->name() == UI_hg1) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("hg1", inputMessage);
        preferences.end();
        hg1_string = inputMessage;
      }

      else if (p->name() == UI_name2) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("name2", inputMessage);
        preferences.end();
        name2_string = inputMessage;
      }

      else if (p->name() == UI_id2) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("id2", inputMessage);
        preferences.end();
        id2_string = inputMessage;
         device_conf = 2;
        homee_getnode(inputMessage);
      }

      else if (p->name() == UI_attr2) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("attr2", inputMessage);
        preferences.end();
        attr2_string = inputMessage;
      }

      else if (p->name() == UI_hg2) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("hg2", inputMessage);
        preferences.end();
        hg2_string = inputMessage;
      }

      else if (p->name() == UI_name3) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("name3", inputMessage);
        preferences.end();
        name3_string = inputMessage;
      }

      else if (p->name() == UI_id3) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("id3", inputMessage);
        preferences.end();
        id3_string = inputMessage;
         device_conf = 3;
        homee_getnode(inputMessage);
      }
      // GET inputAttr3 value on <ESP_IP>/get?inputAttr3=<inputMessage>
      else if (p->name() == UI_attr3) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("attr3", inputMessage);
        preferences.end();
        attr3_string = inputMessage;
      }

      else if (p->name() == UI_hg3) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("hg3", inputMessage);
        preferences.end();
        hg3_string = inputMessage;
      }

      // GET inputName4 value on <ESP_IP>/get?inputName4=<inputMessage>
      else if (p->name() == UI_name4) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("name4", inputMessage);
        preferences.end();
        name4_string = inputMessage;
      }
      // GET inputId4 value on <ESP_IP>/get?inputId4=<inputMessage>
      else if (p->name() == UI_id4) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("id4", inputMessage);
        preferences.end();
        id4_string = inputMessage;
         device_conf = 4;
        homee_getnode(inputMessage);
      }
      // GET inputAttr4 value on <ESP_IP>/get?inputAttr4=<inputMessage>
      else if (p->name() == UI_attr4) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("attr4", inputMessage);
        preferences.end();
        attr4_string = inputMessage;
      }

      else if (p->name() == UI_hg4) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("hg4", inputMessage);
        preferences.end();
        hg4_string = inputMessage;
      }

      // GET inputName5 value on <ESP_IP>/get?inputName5=<inputMessage>
      else if (p->name() == UI_name5) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("name5", inputMessage);
        preferences.end();
        name5_string = inputMessage;
      }
      // GET inputId5 value on <ESP_IP>/get?inputId5=<inputMessage>
      else if (p->name() == UI_id5) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("id5", inputMessage);
        preferences.end();
        id5_string = inputMessage;
         device_conf = 5;
        homee_getnode(inputMessage);
      }
      // GET inputAttr5 value on <ESP_IP>/get?inputAttr5=<inputMessage>
      else if (p->name() == UI_attr5) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("attr5", inputMessage);
        preferences.end();
        attr5_string = inputMessage;
      }

      else if (p->name() == UI_hg5) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("hg5", inputMessage);
        preferences.end();
        hg5_string = inputMessage;
      }

      // GET inputName6 value on <ESP_IP>/get?inputName6=<inputMessage>
      else if (p->name() == UI_name6) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("name6", inputMessage);
        preferences.end();
        name6_string = inputMessage;
      }
      // GET inputId6 value on <ESP_IP>/get?inputId6=<inputMessage>
      else if (p->name() == UI_id6) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("id6", inputMessage);
        preferences.end();
        id6_string = inputMessage;
         device_conf = 6;
        homee_getnode(inputMessage);
      }
      // GET inputAttr6 value on <ESP_IP>/get?inputAttr6=<inputMessage>
      else if (p->name() == UI_attr6) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("attr6", inputMessage);
        preferences.end();
        attr6_string = inputMessage;
      }

      else if (p->name() == UI_hg6) {
        inputMessage = p->value();
        preferences.begin ( NAME, false ) ;                 // Open for read/write
        preferences.putString ("hg6", inputMessage);
        preferences.end();
        hg6_string = inputMessage;
      }

      // GET inputTempOut value on <ESP_IP>/get?inputTempOut=<inputMessage>
      else if (p->name() == UI_TempOut) {
        inputMessage = p->value();
       
        device_conf = 99;
        homee_getnode(inputMessage);
      }
      // GET inputdebug value on <ESP_IP>/get?inputdebug=<inputMessage>
      else if (p->name() == UI_button) {
        inputMessage = p->value();
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
    }
  }
           );
}
void homee_getnode( String inputMessage){
        String mess_string = "Get:/nodes/"+ String(inputMessage);
        webSocket.sendTXT(mess_string);
        Serial.println(mess_string);
}

void handleBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  if (!index) {
    Serial.printf("BodyStart: %u B\n", total);
  }
  for (size_t i = 0; i < len; i++) {
    Serial.write(data[i]);
  }
  if (index + len == total) {
    Serial.printf("BodyEnd: %u B\n", total);
  }
}
