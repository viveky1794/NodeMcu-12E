#include "Server.h"

global gbl;

/*********************************************************/
/*********************************************************/
/* To Check the Status of Client that it is avaialbale or not */
bool CheckClient()
{
  client = server.available();
  
  if(!client)
    return false;
  else
    return true; // Client is avaialabel;
}

/*********************************************************/
/*********************************************************/
/* Return data which received From Client */
String GetDataFromClient()
{
  gbl.SRD = "";
  
  while ( client.available())
  {
    gbl.SRD += (char)client.read();
    if ( !client.available())
      delay(20);
  }
  
  return gbl.SRD;
}//End- GetDataFromClient() 

/*********************************************************/
/*********************************************************/
/* Take user defined Serial data */
String GetSerialData()
{
  gbl.SWR = "";
  while (Serial.available() > 0)
  {
    gbl.SWR += (char)Serial.read();
    if (!(Serial.available() > 0) )
      delay(20);
    yield();
  }
  return gbl.SWR;
}//End- GetSerialData()

/*********************************************************/
/*********************************************************/
String GetSerialData(char *str)
{
  String GPS = String(str);
  if (GPS.equals("GPS"))
  {
    gbl.GpsTime = "";
    while (Serial.available() > 0 )
    {
      gbl.GpsTime += (char)Serial.read();
      if (!(Serial.available() > 0) )
        delay(20);

      yield();
    }
  }
  return gbl.GpsTime;
}//End- GetSerialData()

/*********************************************************/
/*********************************************************/
String GpsTimeData()
{
  if (strstr(gbl.GpsTime.c_str(), "$GPGGA,") != NULL)
  {
    String Sec, Min, Hr;
    int SS, MM, HH;
    int tmt_1, tmt_2, tmt_3, cnt;

    tmt_1 = gbl.GpsTime.indexOf("$GPGGA") + 1;
    tmt_2 = gbl.GpsTime.indexOf(',', tmt_1) + 1;
    tmt_3 = tmt_2 + 6;

    /* Update in Global String */
    gbl.GpsTime = gbl.GpsTime.substring(tmt_2, tmt_3);
    gbl.GpsTime += "\r";

    /* Debug point : What data are you receving */
    return gbl.GpsTime;
  }// End - if()

  return "NULL";
}// End - Stirng GpsTimeData()

/*********************************************************/
/*********************************************************/
void GpsCommand()
{
  /*DEBUG : Connectivity ? */
  CHECKCLIENT // Macro
  CP("GPS MODE : START\n");
  CP("----------------------------\n");
  while (true)
  {
    /* Updating the GpsTime String with GPS Data  */
    
    GetSerialData("GPS");
    delay(1000);

    /* Parsh the global String and get Time data only 
     *  and update global Struture String
     */
    GpsTimeData();
 
    if (gbl.GpsTime.length() == 7)
    {
      /* DEBUG Point : */
      gbl.tout = millis();
      while( !client.print(gbl.GpsTime)  ) // Send data to Client
        {
          delay(100);
          if( !TimeOut(gbl.tout,2000) ) break;
          else CHECKCLIENT
          yield();                   
        }//End- while()
     
      Serial.println("GPS TIME : " + gbl.GpsTime); 
      gbl.GpsTime = "";
          
    }//End -if()
  }// End -while() 
  CP("GPS MODE : END\n");
  CP("============================\n");
}//End -Gpscommand()
