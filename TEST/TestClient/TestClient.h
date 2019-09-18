#ifndef __ClientNode_H__
#define __ClientNode_H__

#include <ESP8266WiFi.h>
#include <Wire.h>

#define CP Serial.print
typedef struct WiFiNode
{
  const char *host; // Server IP which you want to Connect
  const char *ssid; // name of WiFi
  const char *password; // Password of WiFi
  const int httpPort;
}WiFiNode;

typedef struct global
{
  String CRD;// Client Read Data
  String CWR;// Client Write Data
  int tout;
  bool flag;
  bool upd; /* Update Flag  */
}global;

#endif
