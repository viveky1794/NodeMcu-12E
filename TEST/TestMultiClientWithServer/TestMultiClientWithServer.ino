
#include "TestServer.h"

WiFiClient *client[2] = {NULL};
WiFiServer server(80);

global gbl;

WiFiNode ServerInfo = {.host = "192.168.43.10", .ssid = "AB",
                       .password = "Vivek@1234", .httpPort = 80
                       };


/* Static IP Addresses */
IPAddress ip(192,168,43,5);
IPAddress subnet(255,255,255,0);

void setup() {
 
  Serial.begin(9600); // initialize serial:
  delay(10);

  Serial.println("");
  Serial.println("\n\nServer :\n-------------------------------");

   /* Satatic IP */
  WiFi.config(ip,ip,subnet);
  
  WiFi.mode(WIFI_AP);
  WiFi.begin(ServerInfo.ssid,ServerInfo.password);

  
  // Waiting to connect to wifi
    CONNECTWITHWIFI // MACRO
    
  // Start the server
  server.begin();
  Serial.println("Server started : ");

  // Print the IP address
  Serial.print("Local IP Address : ");
  Serial.println(WiFi.localIP());

   /* Debug Point */
  // Check if a client has connected
     gbl.cnt = 0;
     while(!server.hasClient())
      {
        Serial.println("IN loop_1 hasCleint Funcation : " + String(server.hasClient()));
        delay(1000);
        yield();
      }
        Serial.println("hasCleint Funcation : " + String(server.hasClient()) );
    while(!server.hasClient())
      {
        Serial.println("IN loop_2 hasCleint Funcation : " + String(server.hasClient()) );
        delay(1000);
        yield();
      }
     CONNECTCLIENT // MACRO * see server.h

    Serial.println("\nClient Connected : ");
    Serial.println(client[0]->remoteIP());// to get client IP address
    Serial.println(client[1]->remoteIP());
    Serial.println("\n-------------------------------------");
    Serial.println("");
  
  
}

void loop() {
  while(server.hasClient())
    CONNECTCLIENT // MACRO * see server.h
  
  GetDataFromClientOne();
  GetDataFromClientTwo();
  GetSerialData();

  if(gbl.SRD.length() > 1)
    {
      Serial.println("\nServer_1 : " + gbl.SRD);
    }

  else if(gbl.SRD_2.length() > 1)
    {
      Serial.println("\nServer_2 : " + gbl.SRD_2);
    }
  
  else if(gbl.SWR.length() > 1)
    {
      gbl.SWR += "ONE";
      client[0]->print(gbl.SWR);
      Serial.println("\nUser_1 : \n" + gbl.SWR);
      gbl.SWR += "TWO";
      client[1]->print(gbl.SWR);
      Serial.println("\nUser_2 : \n" + gbl.SWR);
    }
 delay(1000);
}

/* Return data which received From Client */
String GetDataFromClientOne()
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

String GetDataFromClientTwo()
{
  gbl.SRD_2 = "";
  
  while ( client[1]->available())
  {
    gbl.SRD_2 += (char)client[1]->read();
    if ( !client[1]->available())
      delay(20);
  }
  
  return gbl.SRD_2;
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
  Serial.flush();
  return gbl.SWR;// return '\r' if nothing is there.
}//End- GetSerialData()


/* To Check the Status of Client that it is avaialbale or not */
bool CheckClient()
{
  
  WiFiClient newClient = server.available();
  if(newClient)
  {
    Serial.println("New Cleint.......!!!");
    client[gbl.cnt++] = new WiFiClient(newClient); 
   }//End -if()

   newClient = server.available();
  if(newClient)
  {
    Serial.println("New Cleint.......!!!");
    client[gbl.cnt++] = new WiFiClient(newClient); 
   }//End -if()
  
    if(gbl.cnt==2)
      return true;
    else
      return false;
}
