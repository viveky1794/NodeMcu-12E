
#include "ClientNode.h"

//extern WiFiServer GPSServer;
extern WiFiClient GPSClient;

RX8025_RTC RTC;
IPAddress ip(192, 168, 43, 10); // Client Static IP
IPAddress subnet(255, 255, 255, 0);

WiFiNode ClientInfo = {.host = "192.168.43.5", .ssid ="AB",
                       .password ="Vivek@1234", .httpPort = 80};
global gbl;

void CONNECTSERVER ()
{ 
  Serial.print(" Connecting Server : ");
  if(ConnectServer())
  {
    Serial.println("Server Status : Connected");
  }
  else if(!ConnectServer())
  {
    for(uint8_t i = 0; i < 5; i++)
    {
      if(ConnectServer())
      {
        Serial.println("Server Status : Connected");
        break;
      }
      else
      {
        Serial.print(".");
        yield();
      }
    }
  }
  Serial.println("");
}

/* make it marco  */
void CHECKSERVER()
{
   if (!GPSClient.connected())
    CONNECTSERVER();
}

/* To check wheather Client-Server is connected OR not */
bool ConnectServer()
{
  /* Use WiFiClient class to create TCP connections
      connect with Server(host) */
      bool client_connected = false;
  GPSClient.connect(ClientInfo.host, ClientInfo.httpPort);
   
  if (!GPSClient.connected())
  {
    gbl.tout = millis();
    while (millis() - gbl.tout < 2000)
    {
      GPSClient.connect(ClientInfo.host, ClientInfo.httpPort);
      if (GPSClient.connected())
      {
        client_connected = true; // Server Connect with Client
        break;
      }
      delay(250);
      yield();
    }
    
  }
  if(client_connected)
  {
    return true;
  }
    return false; //
} // END - ConnectServer()

/*********************************************************/
/*********************************************************/
void SETUP_CLIENT()
{

  /*  Set mode and Static IP */
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, ip, subnet);
  WiFi.begin(ClientInfo.ssid, ClientInfo.password);
  //delay(1000);

  /* Wait for Connection with WiFi  */
  Serial.print("Connecting WiFi : ");
  for(uint8_t i = 0; i < 5; i++)
  {
    while (WiFi.status() !=  WL_CONNECTED)
    {
      Serial.print(".");
      delay(500);
    }
  }
  Serial.println("");
  Serial.println("WiFi Status : Connected");
  Serial.println("Local IP Address : ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  /*  Connected With Server */
   CHECKSERVER();     
  //delay(5000); // Give Some Time to Connect with Server
}// END - Setup()

/*********************************************************/
/*********************************************************/

/* Return data which received From Server */
String GetDataFromServer()
{
    gbl.CRD = ""; // Get String and Update Globally
    gbl.tout = millis();

    while(GPSClient.available() > 0)
      {
          char ch = (char)GPSClient.read();
          if(ch == '\r')
          {
            break;
          }
          else
          {
            gbl.CRD += (String)ch;
          }
          
          if( !GPSClient.available() )
            delay(20);  
      }
    /*
    while(millis() - gbl.tout < 2000)
    {
      if(GPSClient.available() > 0)
      {
        char ch = (char)GPSClient.read();
        if(ch == '\r')
        {
          break;
        }
        else
        {
          gbl.CRD += (String)ch;
        }
        gbl.tout = millis();
      }
      else
      {
        yield();
      }
    }
    */
  return gbl.CRD;
} // END - GetDataFromServer()

/*************************************************/
/************************************************/

/* Take user defined Serial data */ 
String GetSerialData()
{
   gbl.CWR = "";
  while (Serial.available() > 0)
  {
    gbl.CWR += (char)Serial.read();
      if(!Serial.available()>0)
        delay(20);
        
    yield();
  }
  gbl.CWR += "\r";
  return gbl.CWR;
}// END-GetSerialData()

/*********************************************************/

/*********************************************************/
void RTC_RESET()
{
  Serial.println("RTC RESET :");
  tmElements_t tm = {.Second = 00, .Minute = 00, .Hour = 00};
  RTC.write(tm);
  delay(2000);
}

/*********************************************************/

/*********************************************************/
bool UPDATE_RTC(int Time)
{
  uint8_t hr = ( (Time / 100000) * 10 ) + (Time / 10000);
  /* UPdate RTC now after converting String into intizers  */
  tmElements_t tm = {.Second = 00, .Minute = 00, .Hour = hr };
  if ( RTC.write(tm) )
  {
    delay(2000);
    return 1; // RTC is UPdated
  }
  return 0; // RTC is not UPdated
}
