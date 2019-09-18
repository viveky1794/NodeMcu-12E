#include "H_Files.h"

#define SDA_PIN 14
#define SCL_PIN 12
#define InterruptPin D7     //GPIO 16
bool RTC_SYNC = false;

const int8_t I2C_SLAVE_READ = 0x65; // RX8025 address
const int8_t I2C_SLAVE_WRITE = 0x64; // RX8025 address

RX8025_RTC epson_rtc;


void RTC_RESET()
{
  Serial.println("RTC RESET :");
  tmElements_t tm = {.Second=00,.Minute=00,.Hour=00};
  epson_rtc.write(tm);
  delay(2000);  
}

void GPS_DATA()
{ 
  Serial.println("Fetching GPS Data :");
  uint8_t i = 5;
  while(i--)
  GPS_read();     
}
/*  interrupt code  */
void ICACHE_RAM_ATTR GetGpsData()
{
Serial.println("Interrupt Came :");
Serial.println("Interrupt Exit :");
RTC_SYNC = true;
}
/*************************************************
          END-RTC
 *************************************************/ 

void setup() 
{
    Serial.begin(9600);
    CommandSetting();  
    Inti_Counter();
    // Counter
    Wire.begin(SDA_PIN, SCL_PIN); // SET I2C Pin with RTC_RX8025

  /* Clock Interrupt */
    pinMode(InterruptPin,INPUT_PULLUP);
    interrupts();
    attachInterrupt(digitalPinToInterrupt(InterruptPin),GetGpsData ,FALLING);

    GPS_DATA(); 
       
    loop();
  
  Serial.println("finished.");
  Stop();
}
/******************************************************/
/******************************************************/
void loop() {
      if(RTC_SYNC)
      {
          RTC_SYNC = false;
          RTC_RESET();
          GPS_DATA();
      }
      else
      {
          tmElements_t vm = epson_rtc.read();
          GPS_Counter(vm.Hour,vm.Minute,vm.Second);
          delay(495);
          display7seg(4,digit((vm.Hour)%10));
          display7seg(2,digit((vm.Minute)%10));
          delay(495);
      }
       yield();
 }  


/******************************************************/
/******************************************************/
/******************************************************/
/******************************************************/
