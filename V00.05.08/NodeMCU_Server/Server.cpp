#include "Server.h"

global gbl;

/*********************************************************/
/*********************************************************/
/* To Check the Status of Client that it is avaialbale or not */
//bool CheckClient()
//{
//  client = server.available();
//
//  if (!client)
//    return false;
//  else
//    return true; // Client is avaialabel;
//}

/*********************************************************/
/*********************************************************/
/* Return data which received From Client */
String GetDataFromClient()
{
  gbl.SRD = "";
  while ( client[0]->available())
  {
    gbl.SRD += (char)client[0]->read();
    if ( !client[0]->available())
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
//  CHECKCLIENT // Macro
  CP("GPS MODE : START\n");
  CP("----------------------------\n");
  while (true)
  {
    //---------------STAGE  >> 1--------------//
    // Get data From GPS and Find only Time String from chunck of that data  */
    GetSerialData("GPS");
    delay(1000);
    GpsTimeData();
    //---------------END----------------------//
    
    if (gbl.GpsTime.length() == 7)
    {
      //------------STAGE  >> 2---------------//
      //Check for Cleint availability periodically after  1 min
      
      checkMultiClient();
      #define strremoteIP remoteIP().toString().c_str()   
        
         for(uint8_t i=0; i< 5; i++)
          {
            if(client[i] == NULL) continue;           
              
            CP("\nClient : " + String(i) + ": ");
            CP(client[i]->remoteIP());                  
          }//End- for()
          
       for(uint8_t i=0;i< 5;i++)
       {  
          if(client[i] == NULL) continue;
          
          if( strcmp( client[i]->strremoteIP, "(IP unset)") == 0  )
            { 
              CP("Index : ");CP(i);CP(": IP unset : \n");
              client[i] = NULL;
            }
       }//End- for( i )
      //-------------END----------------------//
      
      //-------------STAGE  >> 3-------------//    
      for (uint8_t i = 0; i < 5; i++)
      {
         gbl.tout = millis();
        if (client[i] != NULL)
        {
          while ( !client[i]->print( gbl.GpsTime ) )
          {
            delay(100);
            if ( millis() - gbl.tout > 500 ) break;
            yield();
          }//End-while()
        }//End-if()
      }//End-for()
      //--------------END--------------------//
      Serial.println("GPS TIME : " + gbl.GpsTime);
      gbl.GpsTime = "";

    }//End -if()
  }// End -while()
  CP("GPS MODE : END\n");
  CP("============================\n");
}//End -Gpscommand()

bool checkMultiClient()
{
  newClient = server.available();   
  if (newClient)
  {
    Serial.println("New Client :...........!!!");
    for (uint8_t i = 0; i < 5; i++)
    {
      if (client[i] == NULL)
      {
        client[i] = new WiFiClient(newClient);
        return 1;
      }
    }//End- for()
  }//End-if()
  else
    return 0;
}//End - checkMultiClient
