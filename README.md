# M5StackCore2homee
The Sketch work with Arduino IDE.

You need this Library  
 https://github.com/bblanchon/ArduinoJson
  
 https://www.arduino.cc/reference/en/libraries/websockets/
                      
 https://github.com/arduino-libraries/NTPClient
                      
 https://github.com/m5stack/M5Core2

In the sketch edit WIFI password and SSID, the homee token can you find in the browser.
You must open the webapp and then open the developer mode and lokal storage. 
homeeID.accessToken = XXXXXXXXX

The attributID and nodeID find under the https://terminal.pascalmattes.de/

New config for the button and state

// conficuration Wlan

const char* ssid = "SSID";

const char* password = "PASSWORD";

//configuration Websocket

const char* token =  "/connection?access_token=YOURTOKEN";

const char* homeeip = "HOMEEIP";

// configuration Button   Name, NodeID , AttributID

const char* bn1[] = {"Sideboard", "555", "1769"};



The folder icon must upload on the SD Card

Update
-new buttonstate 
-snapshot from url as png
-you can switch the page and the buttonstate is like befor
