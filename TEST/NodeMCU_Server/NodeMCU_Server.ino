#include "Server.h"

flag flg;
extern global gbl;
WiFiNode ServerInfo = {.host = "192.168.43.10", .ssid = "AB",
                       .password = "Vivek@1234", .httpPort = 80
                       };

WiFiServer server(80);
WiFiClient client;

/* Static IP Addresses */
IPAddress ip(192,168,43,5);
IPAddress subnet(255,255,255,0);

void setup() {
  
  Serial.begin(9600); // initialize serial:
  delay(10);

  Serial.println("");
  Serial.println("\n\nServer :\n-------------------------------");
  
  //WiFi.mode(WIFI_AP_STA);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip,ip,subnet);
  WiFi.begin(ServerInfo.ssid,ServerInfo.password);
  
  /* Satatic IP */
  

  // Waiting to connect to wifi
    CONNECTWITHWIFI // MACRO
    
  // Start the server
  server.begin();
  server.setNoDelay(true);
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
    gbl.tout = millis();
}// end setup()

void loop() 
{  
    CHECKCLIENT // Macro
    TestCommand();
    if((millis() - gbl.tout) > 5000 )
    {
      GpsCommand();   
      gbl.tout = millis();  
    }
} // END - Loop()
