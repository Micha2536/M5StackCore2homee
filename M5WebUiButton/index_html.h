// index.html file in raw data format for PROGMEM
//

String PARAM_SSID = "inputSsid";
String PARAM_PASSWORT = "inputPasswort";
String PARAM_TOKEN = "inputToken";
String PARAM_homeeIP = "inputhomeeIP";

String UI_name1 = "inputName1";
String UI_id1 = "inputId1";
String UI_attr1 = "inputAttr1";
String UI_name2 = "inputName2";
String UI_id2 = "inputId2";
String UI_attr2 = "inputAttr2";
String UI_name3 = "inputName3";
String UI_id3 = "inputId3";
String UI_attr3 = "inputAttr3";
String UI_name4 = "inputName4";
String UI_id4 = "inputId4";
String UI_attr4 = "inputAttr4";
String UI_name5 = "inputName5";
String UI_id5 = "inputId5";
String UI_attr5 = "inputAttr5";
String UI_name6 = "inputName6";
String UI_id6 = "inputId6";
String UI_attr6 = "inputAttr6";
String UI_TempOut = "inputTempOut";
String UI_debug = "inputdebug";

#define index_html_version 180102

// HTML web page to handle input fields
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>M5Stack Konfiguration</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    function submitMessage() {
      //alert("Wert gespeichert");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
  </script>
 </head>
 <body>
  <center>
   <h1>** M5Stack Konfiguration **</h1>
  <form action="/get" target="hidden-form">
    Eingabe SSID (Aktuelle SSID %inputSsid%): <input type="text" name="inputSsid">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe WLAN Passwort (Aktuelles Passwort ************): <input type="text" name="inputPasswort">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe homee IP (Aktuelle homee IP %inputhomeeIP%): <input type="text" name="inputhomeeIP"">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Token (Aktueller Token ************): <input type="text" name="inputToken">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Name Geraet 1 (Aktueller Name Geraet 1 %inputName1%): <input type="text" name="inputName1">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe ID Geraet 1 (Aktuelle ID Geraet 1 %inputId1%): <input type="text" name="inputId1">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Attribut Geraet 1 (Aktuelles Attribut Geraet 1 %inputAttr1%): <input type="text" name="inputAttr1">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Name Geraet 2 (Aktueller Name Geraet 2 %inputName2%): <input type="text" name="inputName2">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe ID Geraet 2 (Aktuelle ID Geraet 2 %inputId2%): <input type="text" name="inputId2">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Attribut Geraet 2 (Aktuelles Attribut Geraet 2 %inputAttr2%): <input type="text" name="inputAttr2">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Name Geraet 3 (Aktueller Name Geraet 3 %inputName3%): <input type="text" name="inputName3">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe ID Geraet 3 (Aktuelle ID Geraet 3 %inputId3%): <input type="text" name="inputId3">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Attribut Geraet 3 (Aktuelles Attribut Geraet 3 %inputAttr3%): <input type="text" name="inputAttr3">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Name Geraet 4 (Aktueller Name Geraet 4 %inputName4%): <input type="text" name="inputName4">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe ID Geraet 4 (Aktuelle ID Geraet 4 %inputId4%): <input type="text" name="inputId4">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Attribut Geraet 4 (Aktuelles Attribut Geraet 4 %inputAttr4%): <input type="text" name="inputAttr4">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Name Geraet 5 (Aktueller Name Geraet 5 %inputName5%): <input type="text" name="inputName5">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe ID Geraet 5 (Aktuelle ID Geraet 5 %inputId5%): <input type="text" name="inputId5">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Attribut Geraet 5 (Aktuelles Attribut Geraet 5 %inputAttr5%): <input type="text" name="inputAttr5">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Name Geraet 6 (Aktueller Name Geraet 6 %inputName6%): <input type="text" name="inputName6">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe ID Geraet 6 (Aktuelle ID Geraet 6 %inputId6%): <input type="text" name="inputId6">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Attribut Geraet 6 (Aktuelles Attribut Geraet 6 %inputAttr6%): <input type="text" name="inputAttr6">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Eingabe Temperaturanzeige im Display (Aktuelles Attribut Geraet Temperatur Outdoor %inputTempOut%): <input type="text" name="inputTempOut">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Debug aktiviern fuer seriele Ausgabe true/false( %inputdebug%): <input type="text" name="inputdebug">
    <input type="submit" value="Speichern" onclick="submitMessage()">
  </form>
  <iframe style="display:none" name="hidden-form"></iframe>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

// Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "inputSsid"){
    preferences.begin (NAME, false);
    return preferences.getString ("ssid");
    preferences.end();
  }
  else if(var == "inputPasswort"){
    preferences.begin (NAME, false);
    return preferences.getString ("passwort");
    preferences.end();
  }
  else if(var == "inputToken"){
    preferences.begin (NAME, false);
    return preferences.getString ("token");
    preferences.end();
  }
  else if(var == "inputName1"){
    preferences.begin (NAME, false);
    return preferences.getString ("name1");
    preferences.end();
  }
  else if(var == "inputId1"){
    preferences.begin (NAME, false);
    return preferences.getString ("id1");
    preferences.end();
  }
  else if(var == "inputAttr1"){
    preferences.begin (NAME, false);
    return preferences.getString ("attr1");
    preferences.end();
  }
  else if(var == "inputName2"){
    preferences.begin (NAME, false);
    return preferences.getString ("name2");
    preferences.end();
  }
  else if(var == "inputId2"){
    preferences.begin (NAME, false);
    return preferences.getString ("id2");
    preferences.end();
  }
  else if(var == "inputAttr2"){
    preferences.begin (NAME, false);
    return preferences.getString ("attr2");
    preferences.end();
  }
  else if(var == "inputName3"){
    preferences.begin (NAME, false);
    return preferences.getString ("name3");
    preferences.end();
  }
  else if(var == "inputId3"){
    preferences.begin (NAME, false);
    return preferences.getString ("id3");
    preferences.end();
  }
  else if(var == "inputAttr3"){
    preferences.begin (NAME, false);
    return preferences.getString ("attr3");
    preferences.end();
  }
  else if(var == "inputName4"){
    preferences.begin (NAME, false);
    return preferences.getString ("name4");
    preferences.end();
  }
  else if(var == "inputId4"){
    preferences.begin (NAME, false);
    return preferences.getString ("id4");
    preferences.end();
  }
  else if(var == "inputAttr4"){
    preferences.begin (NAME, false);
    return preferences.getString ("attr4");
    preferences.end();
  }
  else if(var == "inputName5"){
    preferences.begin (NAME, false);
    return preferences.getString ("name5");
    preferences.end();
  }
  else if(var == "inputId5"){
    preferences.begin (NAME, false);
    return preferences.getString ("id5");
    preferences.end();
  }
  else if(var == "inputAttr5"){
    preferences.begin (NAME, false);
    return preferences.getString ("attr5");
    preferences.end();
  }
  else if(var == "inputName6"){
    preferences.begin (NAME, false);
    return preferences.getString ("name6");
    preferences.end();
  }
  else if(var == "inputId6"){
    preferences.begin (NAME, false);
    return preferences.getString ("id6");
    preferences.end();
  }
  else if(var == "inputAttr6"){
    preferences.begin (NAME, false);
    return preferences.getString ("attr6");
    preferences.end();
  }
  else if(var == "inputTempOut"){
    preferences.begin (NAME, false);
    return preferences.getString ("TempOut");
    preferences.end();
  }
  else if(var == "inputdebug"){
    preferences.begin (NAME, false);
    return preferences.getString ("debug");
    preferences.end();
  }
  return String();
}
