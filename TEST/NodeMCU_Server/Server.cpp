#include "Server.h"

global gbl;

/* To Check the Status of Client that it is avaialbale or not */
bool CheckClient()
{
  client = server.available();
  unsigned long tout = millis();
  if (!client)
  {
    while (millis() - tout < 5000)
    {
      client = server.available();

      if (!client)
      {
        delay(200);
        yield();
      }
      else
        return true;
    }
    return false; // Cleint is NOT available :
  }
  return true; // Client is avaialabel;
}

/* Return data which received From Client */
String GetDataFromClient()
{
  gbl.SRD = "";
  while ( client.available())
  {
    gbl.SRD = client.readStringUntil('\r');
    if ( !client.available())
      delay(20);
  }
  gbl.SRD += "\r";
  return gbl.SRD;// return '\r' if nothing is there.
}//End- GetDataFromClient() 

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
  gbl.SWR += "\r";
  return gbl.SWR;// return '\r' if nothing is there.
}//End- GetSerialData()

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
  gbl.GpsTime += "\r";
  return gbl.GpsTime;// return '\r' if nothing is there.
}//End- GetSerialData()


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
    /* UPdate Time in Global Structure  */
    //  gbl.GpsTime = String(HH) + ":" + String(MM) + ":" + String(SS) + "\r";
    return gbl.GpsTime;
  }// End - if()

  return "NULL";
}// End - Stirng GpsTimeData()



void TestCommand()
{
  GetDataFromClient();
  GetSerialData();

  if ( (gbl.SRD.equals("@TEST\n\r") ) || (gbl.SWR.equals("@TEST\n\r")) )
  {
    Serial.println("TEST MODE : START ");
    CP("--------------------------\n");
    while (true)
    {
      GetDataFromClient();
      GetSerialData();
      gbl.tout = millis();

      if (gbl.SRD.length() > 1 )
      {
        /* Print received data from Client */
        Serial.print("Client : " + gbl.SRD);
      }
      else if (gbl.SWR.length() > 1 )
      {
        Serial.print("User : " + gbl.SWR);
        client.print(gbl.SWR); // Send data to Client
      }//End- else if()
      
      if ( (gbl.SRD.equals("@GPS\n\r") ) || ( (gbl.SWR.equals("@GPS\n\r")) ) )
      {
        Serial.println("TEST MODE : Finished ");
        CP("--------------------------\n");
        break;// break the loop
      }//End-if()
      yield();
    }//end while()
  }// End- if()
}// End - TestCommand()

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
    delay(500);

    if ( gbl.GpsTime.equals("@EXIT\n\r") )
      break;// exit the loop

    /* DEBUG : Print the String received From GPS
     * Serial.println("\n\n\n-------\n\n" + gbl.GpsTime + "\n\n\n---------\n\n"); 
     */
     
    /* Parsh the global String and get Time data only 
     *  and update global Struture String
     */
    GpsTimeData();
    
    if (gbl.GpsTime.length() == 7)
    {
      client.print(gbl.GpsTime); // Send data to Client
      Serial.println("GPS TIME : " + gbl.GpsTime);
      gbl.GpsTime = "";
      delay(500);
    
      /* Get Acknowledgement from Client */
      if ( GetAckFromClient() )
          { 
            while( !client.print("OK\n\r") )// Send "OK" to Client.
              {
                delay(50);
                yield();
              }
          }//End- if()
          
    }//End -if()
  }// End -while()
  gbl.tout = millis();
  
  CP("GPS MODE : END\n");
  CP("----------------------------\n");
}//End -Gpscommand()


bool GetAckFromClient()
{
  gbl.tout = millis();
  while (true)
  {
    GetDataFromClient();
    delay(10);
    
    /* DEBUG : Check what you are receving */
    
    if ( gbl.SRD.equals("ACK\n\r") )
    {
      CP(" : Receive ACK from Client\n");
      return true;
    }
    else if (millis() - gbl.tout > 10000)
    {
      CP(" : Didn't Receive ACK from Client\n");
      return false;
    }
  }//End -while()
  return false;// no need of this 
}//End - GetAckFromClient
