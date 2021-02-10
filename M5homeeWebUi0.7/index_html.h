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
String UI_button = "inputbutton";

#define index_html_version 180102

// HTML web page to handle input fields
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html style="background-color:dimgrey"><head>
  <title>M5Stack Konfiguration</title>
  <html lang="de">
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    function submitMessage() {
     // alert("Wert gespeichert");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
  </script>
 </head>
 <body style="font-size:15px;">

<h1 style="color:darkblue;font-size:50px;"><strong>M5 Stack</strong></h1>
<p>Konfiguration des WLAN und der Button.</p>
<form action="/get" target="hidden-form" >
  <label for="inputSsid"><strong>WLAN %inputSsid%</strong></label><br>
  <input type="SSID" name="inputSsid" placeholder="SSID" style="background-color:lightgrey; font-size:15px;">
  <input type="password" name="inputPasswort" placeholder="Password" style="background-color:lightgrey; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputhomeeIP"><strong>homee %inputhomeeIP%</strong></label><br>
  <input type="text" name="inputhomeeIP" placeholder="homeeIP" style="background-color:lightgrey; font-size:15px;">
  <input type="text" name="inputToken" placeholder="Token" style="background-color:lightgrey; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputName1"><strong>Button 1    %inputName1% %inputAttr1% %inputId1%</strong></label><br>
  <input type="text" name="inputName1" placeholder="Name" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputAttr1" placeholder="Attribut ID" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputId1" placeholder="Node-ID" style="background-color:lightgrey; color:darkblue; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputName2"><strong>Button 2    %inputName2% %inputAttr2% %inputId2%</strong></label><br>
  <input type="text" name="inputName2" placeholder="Name" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputAttr2" placeholder="Attribut ID" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputId2" placeholder="Node-ID" style="background-color:lightgrey; color:darkblue; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputName3"><strong>Button 3    %inputName3% %inputAttr3% %inputId3%</strong></label><br>
  <input type="text" name="inputName3" placeholder="Name" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputAttr3" placeholder="Attribut ID" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputId3" placeholder="Node-ID" style="background-color:lightgrey; color:darkblue; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputName4"><strong>Button 4    %inputName4% %inputAttr4% %inputId4%</strong></label><br>
  <input type="text" name="inputName4" placeholder="Name" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputAttr4" placeholder="Attribut ID" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputId4" placeholder="Node-ID" style="background-color:lightgrey; color:darkblue; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputName5"><strong>Button 5    %inputName5% %inputAttr5% %inputId5%</strong></label><br>
  <input type="text" name="inputName5" placeholder="Name" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputAttr5" placeholder="Attribut ID" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputId5" placeholder="Node-ID" style="background-color:lightgrey; color:darkblue; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputName6"><strong>Button 6    %inputName6% %inputAttr6% %inputId6%</strong></label><br>
  <input type="text" name="inputName6" placeholder="Name" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputAttr6" placeholder="Attribut ID" style="background-color:lightgrey; font-size:15px;">
  <input type="number" name="inputId6" placeholder="Node-ID" style="background-color:lightgrey; color:darkblue; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputTempOut"><strong>Temperatursensor Outdoor    %inputTempOut%</strong></label><br>
  <input type="number" name="inputTempOut" placeholder="Attribut ID" style="background-color:lightgrey; font-size:15px;">
  <input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<form action="/get" target="hidden-form" >
  <label for="inputnutton"><strong>Button Anzahl 2, 4 oder 6  (%inputbutton%)</strong></label><br>
  <input list="range" id="a" name="inputbutton" placeholder="1" style="background-color:lightgrey; font-size:15px;">
  <datalist id="range">
  <option value="1">
  <option value="2">
  <option value="4">
  <option value="6">
</datalist>
<input type="submit" value="Speichern" onclick="submitMessage()"><br>
</form><br>
<br>
<br>
<p>Nach der Eingabe der Wlan Daten ist der M5 lokal über die vergebene IP erreichbar und der SoftAP des M5 ist deaktiviert</p>
<p>Die Werte werden nach dem speichern im Eeprom des M5 festgeschrieben und sind nach einem Neustart wieder vorhanden. </p>
<p></p>
<br>
<a href="https://community.hom.ee/t/m5stack-core2-mit-homee-nutzen/33968"><strong>Community Website M5Stack</strong></a>
<br><br>
<a href="https://hom.ee"><strong>homee Website</strong></a>
<br><br>
<a href="https://m5stack.com"><strong>M5Stack Website</strong></a>
<br><br>
<iframe width="320" height="240" src="https://www.youtube.com/embed/gHyEFjMJBnY" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe><br> <br>
<iframe style="display:none" name="hidden-form"></iframe>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
// style="position:absolute;top:20px;bottom:0px;right: 20px"
// Replaces placeholder with stored values
String processor(const String& var) {
  if (var == "inputSsid") {
    preferences.begin (NAME, false);
    return preferences.getString ("ssid");
    preferences.end();
  }
  else if (var == "inputPasswort") {
    preferences.begin (NAME, false);
    return preferences.getString ("passwort");
    preferences.end();
  }
  else if (var == "inputToken") {
    preferences.begin (NAME, false);
    return preferences.getString ("token");
    preferences.end();
  }
  else if (var == "inputhomeeIP") {
    preferences.begin (NAME, false);
    return preferences.getString ("homeeIP");
    preferences.end();
  }
  else if (var == "inputName1") {
    preferences.begin (NAME, false);
    return preferences.getString ("name1");
    preferences.end();
  }
  else if (var == "inputId1") {
    preferences.begin (NAME, false);
    return preferences.getString ("id1");
    preferences.end();
  }
  else if (var == "inputAttr1") {
    preferences.begin (NAME, false);
    return preferences.getString ("attr1");
    preferences.end();
  }
  else if (var == "inputName2") {
    preferences.begin (NAME, false);
    return preferences.getString ("name2");
    preferences.end();
  }
  else if (var == "inputId2") {
    preferences.begin (NAME, false);
    return preferences.getString ("id2");
    preferences.end();
  }
  else if (var == "inputAttr2") {
    preferences.begin (NAME, false);
    return preferences.getString ("attr2");
    preferences.end();
  }
  else if (var == "inputName3") {
    preferences.begin (NAME, false);
    return preferences.getString ("name3");
    preferences.end();
  }
  else if (var == "inputId3") {
    preferences.begin (NAME, false);
    return preferences.getString ("id3");
    preferences.end();
  }
  else if (var == "inputAttr3") {
    preferences.begin (NAME, false);
    return preferences.getString ("attr3");
    preferences.end();
  }
  else if (var == "inputName4") {
    preferences.begin (NAME, false);
    return preferences.getString ("name4");
    preferences.end();
  }
  else if (var == "inputId4") {
    preferences.begin (NAME, false);
    return preferences.getString ("id4");
    preferences.end();
  }
  else if (var == "inputAttr4") {
    preferences.begin (NAME, false);
    return preferences.getString ("attr4");
    preferences.end();
  }
  else if (var == "inputName5") {
    preferences.begin (NAME, false);
    return preferences.getString ("name5");
    preferences.end();
  }
  else if (var == "inputId5") {
    preferences.begin (NAME, false);
    return preferences.getString ("id5");
    preferences.end();
  }
  else if (var == "inputAttr5") {
    preferences.begin (NAME, false);
    return preferences.getString ("attr5");
    preferences.end();
  }
  else if (var == "inputName6") {
    preferences.begin (NAME, false);
    return preferences.getString ("name6");
    preferences.end();
  }
  else if (var == "inputId6") {
    preferences.begin (NAME, false);
    return preferences.getString ("id6");
    preferences.end();
  }
  else if (var == "inputAttr6") {
    preferences.begin (NAME, false);
    return preferences.getString ("attr6");
    preferences.end();
  }
  else if (var == "inputTempOut") {
    preferences.begin (NAME, false);
    return preferences.getString ("TempOut");
    preferences.end();
  }
  else if (var == "inputbutton") {
    preferences.begin (NAME, false);
    return preferences.getString ("varbutton");
    preferences.end();
    Serial.print(preferences.getString ("varbutton"));
  }
  return String();
}
