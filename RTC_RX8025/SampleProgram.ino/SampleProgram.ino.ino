// Wire Master Reader
// by devyte
// based on the example of the same name by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// This example code is in the public domain.


#include <Wire.h>
#include <PolledTimeout.h>


#include "RX8025.h"

#define SDA_PIN 4
#define SCL_PIN 5

const int8_t I2C_SLAVE_READ = 0x65; // RX8025 address
const int8_t I2C_SLAVE_WRITE = 0x64; // RX8025 address

RX8025_RTC epson_rtc;

void setup() {
  
  Serial.begin(115200);  // start serial for output
  Wire.begin(SDA_PIN, SCL_PIN);        // join i2c bus (address optional for master)
  Serial.println("Started RTC read");

  // value assignment to structure
  
  tmElements_t tm = {.Second=00,.Minute=54,.Hour=05};
  epson_rtc.write(tm);
}

void loop() {
  //  Serial.println("\nloop");

    tmElements_t vm = epson_rtc.read(); // tmElements_t is a structure. for more information visit Timelib.h file. 

    int ss = vm.Second;
    int mm = vm.Minute;
    int hh = vm.Hour;

    Serial.print("Curr_Time : ");
    if( hh < 10) Serial.print("0" + String(hh) +":");
    else Serial.print(String(hh) + ":");
    
    if( mm < 10) Serial.print("0" + String(mm) + ":");
    else Serial.print(String(mm) + ":");

    if( ss < 10) Serial.println("0" + String(ss) );
    else Serial.println(String(ss));
    
//    Serial.println("Cur_Time : " + String(vm.Hour) + ":" + String(vm.Minute) + ":" + String(vm.Second) );
    delay(1000);
}
