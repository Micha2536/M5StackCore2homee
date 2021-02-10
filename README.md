# M5StackCore2homee
The Sketch work with Arduino IDE.

You need this Library  
 https://github.com/bblanchon/ArduinoJson
  
 https://www.arduino.cc/reference/en/libraries/websockets/
                      
 https://github.com/arduino-libraries/NTPClient
                      
 https://github.com/m5stack/M5Core2
 
 https://github.com/riotnetwork/ArduinoNvs


https://github.com/me-no-dev/AsyncTCP

https://github.com/me-no-dev/ESPAsyncWebServer

https://github.com/riotnetwork/ArduinoNvs


 

In the sketch edit WIFI password and SSID, the homee token can you find in the browser.
You must open the webapp and then open the developer mode and lokal storage. 
homeeID.accessToken = XXXXXXXXX
In some browsers there is also the following value: local_homee_IP.access_token = XXXXXXXXX
You might test both, if you have connection issues.

The attributID and nodeID find under the https://terminal.pascalmattes.de/







Update 10.02.2021 
Version 0.7

-new webUi , config wlan and button

-new button 1,2,4 or 6

-new debug mode (page 4)



___________________________________________________________________________________________________
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

Update 06.02.2021 M5WebUiButton

new Webui to config the M5StackCore2.
you dont need config in the sketch.
open the Webui 192.168.4.1 
config your WLAN, homeeIP and accessToken
