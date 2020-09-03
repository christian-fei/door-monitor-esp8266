#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "GatekeeperWiFi.h"

GatekeeperWiFi::GatekeeperWiFi()
{
}

void GatekeeperWiFi::createAP(String ssid)
{
  Serial.println("Setting AP (Access Point)");
  Serial.println(ssid);
  WiFi.softAP(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);
  Serial.println(WiFi.localIP());

}
void GatekeeperWiFi::connectWifi(String ssid, String password)
{
  Serial.println("setup to connect to");
  Serial.println(ssid);
  Serial.println(password);

  WiFi.softAPdisconnect(true);

  Serial.println("connecting..");
  WiFi.begin(ssid, password);
  
  Serial.println("successfully connected");
  WiFi.printDiag(Serial);
}
