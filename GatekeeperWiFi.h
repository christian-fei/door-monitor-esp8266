#ifndef GatekeeperWiFi_h
#define GatekeeperWiFi_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

class GatekeeperWiFi
{
public:
  GatekeeperWiFi();
  void createAP(String ssid);
  void connectWifi(String ssid, String password);
};

#endif
