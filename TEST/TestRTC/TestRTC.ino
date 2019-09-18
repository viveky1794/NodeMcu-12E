/** @Developer : Vivek Yadav
    @This a part of a project which i did Modify as you want.
*/



#include "RTC_RX8025.h"

RX8025_RTC RTC;

void setup() {
 
  /*  Set BaudRate  */
  Serial.begin(9600);
  Serial.println("\n\n\nRTC !!!............. : ");
  Serial.println("--------------------------");

  /*  Make arrangemets for RTC  */
  Wire.begin(SDA_PIN, SCL_PIN); // SET I2C Pin with RTC_RX8025
  RTC_RESET(); // get Reset RTC

}

void loop() {

tmElements_t tm = RTC.read();

Serial.println("Time Stamp : " + String(tm.Hour) + ":" + String(tm.Minute) + ":" + String (tm.Second) );
delay(1000);
}


void RTC_RESET()
{
  Serial.println("RTC RESET :");
  tmElements_t tm = {.Second = 00, .Minute = 00, .Hour = 00};
  RTC.write(tm);
  delay(2000);
}
