
#include "TM1623.h"
#include "Counter.h"

void setup() {

  /*  Set BaudRate  */
  Serial.begin(9600);
  Serial.println("\n\n\n7 Segments : ");
  Serial.println("--------------------------");

 /*  Make arrengments for 7 Segments */
  CommandSetting(); // Get 7 Segment Ready
  Inti_Counter(); //  make all segments to Zero initially

}

void loop() {

  GPS_Counter(12,34,56);
//  display7seg(0,2);
  delay(500);
}
