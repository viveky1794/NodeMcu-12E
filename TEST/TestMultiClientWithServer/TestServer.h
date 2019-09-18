#ifndef __SERVER_H__
#define __SERVER_H__


#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PolledTimeout.h>

#define   CP Serial.print /* TESTing Only */

typedef struct WiFiNode
{
  const char *host; // Server IP which you want to Connect
  const char *ssid; // name of WiFi
  const char *password; // Password of WiFi
  const int httpPort;
} WiFiNode;

typedef struct global
{
  String SRD;// Server Read Data from Client 
  String SRD_2;
  String SWR;// Server Write Data from Client
  String GpsTime; // GPS time data
  unsigned long tout;
  uint8_t cnt;
} global;


#define CONNECTWITHWIFI   while (WiFi.status() != WL_CONNECTED)\
                                {\
                                  delay(500);\
                                  Serial.print(".");\
                                }\
                                Serial.println("");\
                                Serial.println("WiFi connected");

                              
#define CONNECTCLIENT Serial.print("Connecting with Client : ");\
                          while(!CheckClient()){\
                            Serial.print(".");\
                            delay(500);\
                          }
/*  Check client is connected or not. If not connedted then Connect */
#define CHECKCLIENT   if (!client.connected())\
                           { CONNECTCLIENT }


#endif
