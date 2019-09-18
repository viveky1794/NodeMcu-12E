#include "ClientNode.h"

/*  Global  Resources & Declarations  */
WiFiServer GPSServer(80);
WiFiClient GPSClient;

extern RX8025_RTC RTC;// class object
extern global gbl; // Global Structure

#define updatePin 10 //ESP8266-12E GPIO

/* Interrupt Service Rooutine */
void ICACHE_RAM_ATTR updateRtcwithTime()
{
  detachInterrupt(updatePin);
  Serial.println("Interrupt Occur : \n");
  delayMicroseconds(1000000);
  gbl.upd = true;
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

  /* Update RTC with Data */
  while (1)
  {
    loop(); // jump to loop
    yield();
  }

  Serial.println("finished--OUT of LOOP");
  Stop();
} // END - setup();

void loop()
{
  /* Debug Point : Check for Client-Server Connection. */
  Testing();// Check what are we receiving from Server
  
  if (gbl.upd)
  {
    CONNECTSERVER ();//First Check for server Connection.   
    updateRtc();
    interrupts();
    attachInterrupt(digitalPinToInterrupt(updatePin), updateRtcwithTime, FALLING);
    gbl.upd = false;
  }//End - if()
  else
  {  
    toReadRtc(); /* Reading RTC  */
  }//End - else
  
} // END - LOOP()
