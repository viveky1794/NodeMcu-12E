
#include "TestServer.h"

WiFiClient client;
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
     CONNECTCLIENT // MACRO * see server.h

    Serial.println("\nClient Connected : ");
    Serial.println("\n-------------------------------------");
    Serial.println("");
  
  
}

void loop() {
  
  GetDataFromClient();
  GetSerialData();

  if(gbl.SRD.length() > 1)
    {
      Serial.println("\nServer : " + gbl.SRD);
    }
    
  else if(gbl.SWR.length() > 1)
    {
      client.print(gbl.SWR);
      Serial.println("\nUser : \n" + gbl.SWR);
      
    }
// delay(1000);
}

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
  client = server.available();

  if(!client)
    return false;
  else
    return true;
}
