/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Logic.h"
#include "GatekeeperWiFi.h"

long interval = 1000;

int inputPin = 14;
int outputPin = 12;
bool soundOn = true;
bool doorIsOpen;
Logic logic(inputPin, outputPin);
GatekeeperWiFi wifi;
bool apModeOn = true;

AsyncWebServer server(80);
unsigned long previousMillis = 0;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .pad {
      padding: 1em;
    }
  </style>
</head>
<body>
  <h2>ESP8266 Gatekeeper</h2>
  <div class="pad">
    <span class="dht-labels">door</span> 
    <span id="door"></span>
  </div>
  <div class="pad">
    <button id="toggle-sound"></button>
  </div>
  %SETUP_HTML%
  <div id="message"></div>
</body>
<script>
%SETUP_JS%

function request ({ url, method = "GET", body }, callback) {
  var req = new XMLHttpRequest();
  req.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      callback({text: this.responseText})
    }
  };
  req.open(method, url, true);
  req.send();
}

request({url: '/sound'}, ({text}) => {
  document.getElementById("toggle-sound").innerText = "Sound: " + text;  
})

document.getElementById("toggle-sound").addEventListener('click', function () { 
  request({url: '/toggle-sound', method: 'POST'}, ({text}) => {
    document.getElementById("toggle-sound").innerText = "Sound is " + text;  
  })
})


setInterval(function ( ) {
  request({url: '/door'}, ({text}) => {
    document.getElementById("door").innerHTML = text;
    document.getElementById("door").style.backgroundColor = (text == "open") ? "red" : "green";
    document.getElementById("door").style.color = "white";
  })
}, 1000 ) ;

</script>
</html>)rawliteral";

String processor(const String& var){
  if(var == "SETUP_HTML"){
    if (apModeOn) {
      return R"rawliteral(<form>
      <small>only needed in AP mode                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      </small>
        <div>
          <label for="ssid">SSID</label>
          <input id="ssid" name="ssid" placeholder="Enter name of WiFi Network"/>
        </div>
        <div>
          <label for="password">Password</label>
          <input id="password" name="password" placeholder="The password to connect to WiFi" autofocus/>
        </div>
        <button type="submit">Submit</button>
      </form>)rawliteral";
    }
  }
  if(var == "SETUP_JS"){
    if (apModeOn) {
      return R"rawliteral(const form = document.querySelector('form');
      form.addEventListener('submit', submit);
      
      function  submit() {
        var ssid = document.getElementById("ssid").value;
        var password = document.getElementById("password").value;
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          debugger
          document.getElementById("message").innerText = "Connect to " + ssid;
          if (this.readyState == 4 && this.status == 200) {
          }
        };
        xhttp.open("POST", "/setup");
        xhttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
        xhttp.send(JSON.stringify({ "ssid": ssid, "password": password }));
        event.preventDefault();
      })rawliteral";
    }
  }

  return String();
}


void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT);

  wifi.createAP("Gatekeeper");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/door", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", logic.doorIsOpen() ? "open" : "closed");
  });
  server.on("/sound", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", soundOn ? "on" : "off");
  });
  server.on("/toggle-sound", HTTP_POST, [](AsyncWebServerRequest * request) {
    soundOn = !soundOn;
    request->send_P(200, "text/plain", soundOn ? "on" : "off");
  });
  server.on("/setup", 
    HTTP_POST, 
    [](AsyncWebServerRequest * request) {},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, data);
      request->send(200);

      String hostSSID = doc["ssid"];
      String hostPassword = doc["password"];

      Serial.println("setup to connect to");
      Serial.println(hostSSID);
      Serial.println(hostPassword);

      wifi.connectWifi(hostSSID, hostPassword);
      apModeOn = false;

      /*
      EEPROM.write(0, hostSSID);    
      EEPROM.write(1, hostPassword);    
      EEPROM.commit();
      */
  });

  server.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    logic.run(soundOn);
  }
}
