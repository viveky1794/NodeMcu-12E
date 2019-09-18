#include "Server.h"


extern global gbl;
WiFiNode ServerInfo = {.host = "192.168.43.10", .ssid = "AB",
                       .password = "Vivek@1234", .httpPort = 80
                      };

WiFiServer server(80);
WiFiClient *client[5] = {NULL};
WiFiClient newClient;

/* Static IP Addresses */
IPAddress ip(192, 168, 43, 5);
IPAddress subnet(255, 255, 255, 0);

void setup()
{
  Serial.begin(9600); // initialize serial:
  Serial.println("");
  Serial.println("\n\nServer :");
  Serial.println("=====================================");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ServerInfo.ssid, ServerInfo.password);
  /* Satatic IP Configration */
  WiFi.config(ip, ip, subnet);
  /* Waiting to connect with WiFi */
  CONNECTWITHWIFI // MACRO
  /* Start the server */
  server.begin();
  Serial.println("Server started : ");
  /* Print the IP address */
  Serial.print("Local IP Address : ");
  Serial.println(WiFi.localIP());
  /* Debug Point : Check if a client has connected */
  // Wait for at least one client to connected
  while ( !checkMultiClient() )
  {
    CONNECTWITHWIFI // MACRO
    Serial.print(".");
    delay(500);
    yield();
  }
    for(uint8_t i=0; i< 5; i++)
            {
              if(client[i] == NULL) break;
              Serial.print("Connected Client : " + String(i) + ": " );
              Serial.println( client[i]->remoteIP());
            }
  Serial.println("\nClient Connected : ");
  Serial.println("=====================================");
  Serial.println("");
  
  gbl.tout = millis();
}// end setup()

void loop()
{
  GpsCommand();
  yield();
} // END - Loop()


//void Testing()
//{ /* Testing Purpose Only */
//  GetDataFromClient();
//  GetSerialData();
//
//  if (gbl.SRD.length() > 1)
//    Serial.println("\nFrom Client : " + gbl.SRD);
//  else if (gbl.SWR.length() > 1)
//  {
//    client.print(gbl.SWR);
//    Serial.println("\nME : " + gbl.SWR);
//  }
//}
