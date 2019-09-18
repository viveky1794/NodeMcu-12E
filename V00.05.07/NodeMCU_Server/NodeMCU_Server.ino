#include "Server.h"


extern global gbl;
WiFiNode ServerInfo = {.host = "192.168.43.10", .ssid = "AB",
                       .password = "Vivek@1234", .httpPort = 80
                       };

WiFiServer server(80);
WiFiClient client;

/* Static IP Addresses */
IPAddress ip(192,168,43,5);
IPAddress subnet(255,255,255,0);

void setup() 
{ 
  Serial.begin(9600); // initialize serial:
  Serial.println("");
  Serial.println("\n\nServer :");
  Serial.println("=====================================");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ServerInfo.ssid,ServerInfo.password);
  /* Satatic IP Configration */
  WiFi.config(ip,ip,subnet);
  /* Waiting to connect with WiFi */
    CONNECTWITHWIFI // MACRO    
  /* Start the server */
  server.begin();
  Serial.println("Server started : ");
  /* Print the IP address */
  Serial.print("Local IP Address : ");
  Serial.println(WiFi.localIP());
  /* Debug Point : Check if a client has connected */
  CONNECTCLIENT // MACRO * see server.h
  Serial.println("\nClient Connected : ");
  Serial.println("=====================================");
  Serial.println("");
  gbl.tout = millis();
}// end setup()

void loop() 
{  
    CHECKCLIENT // Macro
    GpsCommand();     
} // END - Loop()


void Testing()
{/* Testing Purpose Only */
   GetDataFromClient();
    GetSerialData();
    
    if(gbl.SRD.length() > 1)
      Serial.println("\nFrom Client : " + gbl.SRD);
    else if(gbl.SWR.length() > 1)
      {
        client.print(gbl.SWR);
        Serial.println("\nME : " + gbl.SWR);
      }
}
