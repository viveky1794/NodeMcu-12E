
#include "TestClient.h"

/*  Global  Resources & Declarations  */
WiFiServer GPSServer(80);
WiFiClient GPSClient; //Problem,Use client

IPAddress ip(192, 168, 43, 12); // Client Static IP
IPAddress subnet(255, 255, 255, 0);

WiFiNode ClientInfo = {.host = "192.168.43.5", .ssid ="AB",
                       .password ="Vivek@1234", .httpPort = 80};
global gbl;


void setup() {

  /*  Set BaudRate  */
  Serial.begin(9600);
  Serial.println("\n\n\nClient : ");
  Serial.println("--------------------------");
  
  /*  Set mode and Static IP */
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, ip, subnet);
  WiFi.begin(ClientInfo.ssid, ClientInfo.password);
  delay(500);


  /* Wait for Connection with WiFi  */
  Serial.print("Connecting WiFi : ");
  while (WiFi.status() !=  WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi Status : Connected");
  Serial.println("Local IP Address : ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  /*  Connected With Server */
   CHECKSERVER();       
  delay(1000); // Give Some Time to Connect with Server
 gbl.tout = millis();
}

void loop() {

  if(millis() - gbl.tout > 10000)
 {
  CHECKSERVER();
  gbl.tout = millis();
 }
  GetDataFromServer();
  GetSerialData();

  if(gbl.CRD.length() > 1)
    {
      Serial.println("\nServer : " + gbl.CRD);
    }
 
  else if(gbl.CWR.length() > 1)
  {
    GPSClient.print(gbl.CWR);
    Serial.println("\nUser : " + gbl.CWR);
  } 

  
//  delay(1000);
}

void CONNECTSERVER ()
{ 
  Serial.print(" Connecting Server : ");
  while (!ConnectServer())
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Server Status : Connected");
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
    GPSClient.connect(ClientInfo.host, ClientInfo.httpPort);

    if(!GPSClient.connected())
      return false;
    else
      return true;
} // END - ConnectServer()


/* Return data which received From Server */
String GetDataFromServer()
{
    gbl.CRD = ""; // Get String and Update Globally
    while(GPSClient.available() > 0)
    {
      gbl.CRD += (char)GPSClient.read();
      if (!GPSClient.available() > 0)
        delay(20);
        
      yield();
    }
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
  Serial.flush();
  return gbl.CWR;
}// END-GetSerialData()
