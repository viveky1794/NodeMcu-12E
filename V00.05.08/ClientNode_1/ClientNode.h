#ifndef __ClientNode_H__
#define __ClientNode_H__

#include <ESP8266WiFi.h>
#include <Wire.h>
#include "Counter.h"
#include "RTC_RX8025.h"
#include "TM1623.h"


#define SCL_PIN D1 // GPIO 5
#define SDA_PIN D2 // GPIO 4
#define CP Serial.print // Testing purpose

typedef struct WiFiNode
{
  const char *host; // Server IP which you want to Connect
  const char *ssid; // name of WiFi
  const char *password; // Password of WiFi
  const int httpPort;
} WiFiNode;

typedef struct global
{
  String CRD;// Client Read Data
  String CWR;// Client Write Data
  int tout;
  bool serverNotAvailable;
  bool upd; /* Update Flag  */
} global;


/* Make arrangmets for Client */
void SETUP_CLIENT(); // Get NodeMCu ready
void RTC_RESET();
String GetDataFromServer();
String GetSerialData();
bool ConnectServer(); // Responsible for making Connections between Client and Server
void CONNECTSERVER ();
void CHECKSERVER();
void toTime();
void toReadRtc();
void Testing();
void updateRtc();

#endif
