/**
 * @Developer : Vivek Yadav
 * @Purpose   : To Understand How SPIFFS File system Works. 
 *              We are Getting data from User through Serial
 *              port. After receiving data store into Flash
 *              memory and then read from there continuously.
 */


#include <ESP8266WiFi.h>
#include <FS.h>

struct global
{
  String serialData;
    
}gbl;

String filename = "/samplefile.txt";
void setup() 
{
delay(1000);
Serial.begin(115200);

SPIFFS.begin();//start SPIFFS
//It may take some time
//SPIFFS.format();//format previous data
File fp = SPIFFS.open(filename,"w");
if( !fp )
  {
    Serial.println("New File Creatation UnSuccessful...!!!");
    return;
  }
else
  {
    Serial.println("Give data form Serial Port.....!!!");
    Serial.println("Data Format : <IP>, <gateway>, <subnet>,<SSID>, <Password> ");    
    Serial.println("Waiting for data.....!!!");
    gbl.serialData = "";
    while(gbl.serialData.length() == 0)
      {
        GetSerialData();
      }
    Serial.println("Data has been recevied from user.....!!!");
    Serial.println("Writing data into Flash memory.....!!!");
    fp.print(gbl.serialData);
    fp.close();
  } 
  
}//End- setup()

void loop()
{
  File fp = SPIFFS.open(filename,"r");

  if( !fp )
  {
    Serial.println("File opening Unsucessfull.....!!!");
    return;  
  }
  else
  {
    Serial.println("Reading Data From File.....!!!");
    for(int i=0; i<fp.size(); i++)
    {
      Serial.print((char)fp.read());
    }
    fp.close();
  }
  Serial.println();
  delay(1000);
}

String GetSerialData()
{/* @brief : Get data from Serial and store into global Sturcture String.
    @return : String which we received from user.
  */
  gbl.serialData = "";
  while( Serial.available() > 1 )
    {
      gbl.serialData = Serial.readStringUntil('\r');
      if( !Serial.available()>0 ) 
        delay(20);  
    }
 Serial.flush();
 return gbl.serialData;   
}
