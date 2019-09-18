#include "ClientNode.h"

/*  Global  Resources & Declarations  */
WiFiServer GPSServer(80);
WiFiClient GPSClient; //Problem,Use client

extern RX8025_RTC RTC;// class object
extern global gbl;

#define updatePin D7

/* Interrupt Service Rooutine */
void ICACHE_RAM_ATTR updateRtcwithTime()
{ 
  Serial.println("Interrupt Occur : \n"); 
  gbl.upd = true;
  delayMicroseconds(1000000);
  Serial.println("Interrupt EXIT : \n");
}//End -


void setup()
{
  gbl.upd = false;

  /*  Set BaudRate  */
  Serial.begin(9600);
  Serial.println("\n\n\nClient : ");
  Serial.println("--------------------------");

  /*  Make arrangemets for RTC  */
  Wire.begin(SDA_PIN, SCL_PIN); // SET I2C Pin with RTC_RX8025
  RTC_RESET(); // get Reset RTC

  /*  Make arrengments for 7 Segments */
  CommandSetting(); // Get 7 Segment Ready
  Inti_Counter(); //  make all segments to Zero initially

  /* Make arrangmets for Client */
  SETUP_CLIENT(); // Get NodeMCu ready

  /* Initiate Interrupts */
  pinMode(updatePin, INPUT_PULLUP);
  interrupts();
  attachInterrupt(digitalPinToInterrupt(updatePin), updateRtcwithTime, FALLING);

  Serial.println("\n--------------------------");
  
} // END - setup();

void loop()
{
  /* Debug Point : Check for Client-Server Connection. */
  CHECKSERVER();

 if(gbl.upd)
 {
  Serial.println("Trying to update RTC!!!!..........");
  
  TEST();
  gbl.upd = false;
 }
 
 /* Reading RTC  */
 else toReadRtc(); 
  
} // END - LOOP()

void TEST()
{
  gbl.tout = millis();
  while( true )
  {
    
    GetDataFromServer();
    GetSerialData();
    
    if(gbl.CRD.length() > 1) break;
    else if(gbl.CWR.length() > 1) break;

    delay(50);
  }
    
    

  gbl.tout = millis();

  if (gbl.CRD.length() > 0)
  {
    Serial.println("\ndata read successfully....... : " + gbl.CRD);
      Serial.print("\nServer :" + gbl.CRD);
      
      while ( !GPSClient.print("ACK\n\r") )
      {
        delay(50);
        yield();
      } //End- while()

      /* convert Time String into Integers */
      /* UPdate only when ask to update via interrupt */
        Serial.println("\n\nUPdate : " + gbl.CRD);
        toTime(); 
        
      while ( !gbl.CRD.equals("OK\n"))
      { 
        GetDataFromServer();
        delay(50);
        yield(); 
      } //End - while()            
  } //End-if()
  
  else if (gbl.CWR.length() > 1 )
  {
    GPSClient.print(gbl.CWR);
    Serial.print("User : " + gbl.CWR);
  }// End-else if()

  Serial.println("EXIT : \n");
}//End - TEST()


bool toTime()
{
  char arr[6];
  strcpy(arr, gbl.CRD.c_str());/* OR Use .CharAt() */

  /* Add 5hr 30Min time to make it for India  */
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
  
  CP("\n\n\n-------------\n\n");

  // update the RTC with new Value:
  tmElements_t vm;
  vm.Hour = Hr;
  vm.Minute = Min;
  vm.Second = Sec;
  Serial.println("RTC UPdated : \n\n");
  Serial.println("Time Stampe : " + String(Hr) + ":" + String(Min) + ":" + String(Sec));
  CP("\n\n\n-------------\n\n\n");

}//End- toTime()



void toReadRtc()
{

  Serial.println("Reading RTC : \n");
  tmElements_t vm = RTC.read();
  GPS_Counter(vm.Hour, vm.Minute, vm.Second);
  delay(495);
  display7seg(4, digit((vm.Hour) % 10));
  display7seg(2, digit((vm.Minute) % 10));
  delay(495);

}
