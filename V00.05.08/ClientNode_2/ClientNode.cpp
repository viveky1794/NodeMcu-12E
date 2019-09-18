
#include "ClientNode.h"

extern WiFiServer GPSServer;
extern WiFiClient GPSClient;

RX8025_RTC RTC;
IPAddress ip(192, 168, 43, 11); // Client Static IP
IPAddress subnet(255, 255, 255, 0);

WiFiNode ClientInfo = {.host = "192.168.43.5", .ssid = "AB",
                       .password = "Vivek@1234", .httpPort = 80
                      };
global gbl;

/*********************************************************/
/*********************************************************/

void CHECKSERVER()
{
  if (!GPSClient.connected())
    CONNECTSERVER();
}

/*********************************************************/
/*********************************************************/

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

/*********************************************************/
/*********************************************************/

bool ConnectServer()
{ /* To check wheather Client-Server is connected OR not */
  /* Use WiFiClient class to create TCP connections
      connect with Server(host) */
  GPSClient.connect(ClientInfo.host, ClientInfo.httpPort);

  if (GPSClient.connected())
    return true; // Server Connect with Client
  else
    return false; //
} // END - ConnectServer()

/*********************************************************/
/*********************************************************/

void SETUP_CLIENT()
{
  /*  Set mode and Static IP */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ClientInfo.ssid, ClientInfo.password);
  delay(1000);
  WiFi.config(ip, ip, subnet);

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
  delay(5000); // Give Some Time to Connect with Server
}// END - Setup()

/*********************************************************/
/*********************************************************/

String GetDataFromServer()
{ /* Return data which received From Server */
  gbl.CRD = ""; // Get String and Update Globally
  while (GPSClient.available() > 0)
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

String GetSerialData()
{ /* Take user defined Serial data */
  gbl.CWR = "";
  while (Serial.available() > 0)
  {
    gbl.CWR += (char)Serial.read();
    if (!Serial.available() > 0)
      delay(20);

    yield();
  }
  Serial.flush();
  return gbl.CWR;
}// END-GetSerialData()

/*********************************************************/
/*********************************************************/

void RTC_RESET()
{
  Serial.println("RTC RESET :");
  tmElements_t tm = {.Second = 00, .Minute = 00, .Hour = 00};
  RTC.write(tm);
  delay(2000);
}

/*********************************************************/
/*********************************************************/

void Testing()
{
//  CONNECTSERVER ();
  GetDataFromServer();
  GetSerialData();

  if (gbl.CRD.length() > 1)
    Serial.println("\nFrom Server : " + gbl.CRD);
  else if (gbl.CWR.length() > 1)
  {
    GPSClient.print(gbl.CWR);
    Serial.println("\nME : " + gbl.CWR);
  }
}//End- Testing()

/*********************************************************/
/*********************************************************/

void updateRtc()
{/*     */
  gbl.tout = millis();
  while ( !(gbl.CRD.length() > 2) )
  {
    GetDataFromServer();
    delay(20);
    yield();
  }
  /*==================================================*/
  if (gbl.CRD.length() > 1)
  {
    gbl.CRD = gbl.CRD.substring(0, 6);
    Serial.print("\nServer :" + gbl.CRD);

    /* convert Time String into Integers */
    /* UPdate only when ask to update via interrupt */
    Serial.println("\nRTC UPdating !!!........ ");
    toTime();
  } //End-if()
  /*==================================================*/
  else if (gbl.CWR.length() > 1 )
  {
    GPSClient.print(gbl.CWR);
    Serial.print("User : " + gbl.CWR);
  }// End-else if()

}//End - TEST()

/*********************************************************/
/*********************************************************/

void toTime()
{/* Convert Time String into Integers and update RTC.....!!! */
  char arr[6];
  strcpy(arr, gbl.CRD.c_str());/* OR Use .CharAt() */

  /*==================================================*/
  uint8_t Hr = (arr[0] - 48) * 10 + (arr[1] - 48);
  Hr += 5;

  uint8_t Min = (arr[2] - 48) * 10 + (arr[3] - 48);
  Min += 30;
  if (Min > 59)
  {
    Hr += 1;
    Min -= 60;
  }//End- if()

  uint8_t Sec = (arr[4] - 48) * 10 + (arr[5] - 48);
  if (Sec > 59)
  {
    Min += 1;
    Sec -= 60;
  }//End- if()
  /*==================================================*/
  CP("\n\n\n-------------\n\n");

  // update the RTC with new Value:
  tmElements_t vm;
  vm.Hour = Hr;
  vm.Minute = Min;
  vm.Second = Sec;
  RTC.write(vm);
  /*==================================================*/
  Serial.println("RTC UPdated ............!!!! \n\n");
  Serial.println("Time Stampe : " + String(Hr) + ":" + String(Min) + ":" + String(Sec));
  CP("\n\n\n-------------\n\n\n");

}//End- toTime()

/*********************************************************/
/*********************************************************/

void toReadRtc()
{/* Reading RTC and Displying Data on 7 segment */
  Serial.println("Reading RTC : \n");
  tmElements_t vm = RTC.read();
  GPS_Counter(vm.Hour, vm.Minute, vm.Second);
  delay(495);
  display7seg(4, digit((vm.Hour) % 10));
  display7seg(2, digit((vm.Minute) % 10));
  delay(495);

}//End - toReadRtc()
