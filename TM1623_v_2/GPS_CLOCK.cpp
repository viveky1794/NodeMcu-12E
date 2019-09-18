#include "H_Files.h"
extern  RX8025_RTC epson_rtc;

void GPS_read()
{ 
  String str = "";
  unsigned long tout = millis();    //millis(): 1ms system ticker

/******************************************/
  while ( millis() - tout < 100)
  {
   
    if (Serial.available() > 0)
    {
      str += (char)Serial.read();
      tout = millis();
      /* DEBUG : 1 */
      
    }
    yield();
  }
    /* DEBUG : 2 */
//  Serial.println(String(str));
  
  if (str.length() > 7)
  {
        String fmt;

        if ( strstr(str.c_str(), "$GPGGA") != NULL)
        {
          int offset = strstr(str.c_str(), "$GPGGA") - str.c_str();
          Serial.println("\n\n\n");
          int cnt = 0;
          while (str[offset] != '\r' )
          {
            fmt += (char)str[offset++];
          }
        }
    Serial.println("Read Data Successfully");
    Out_Format((char *)fmt.c_str());
  }
  
 }

void Out_Format(char *fmt)
{
  /* TIME STAMP */
  Parsh_time(fmt);
  
}

void Parsh_time(char *fmt)
{
  String Sec, Min, Hr;
  int SS, MM, HH;
  int tmt_1, tmt_2, cnt;

  tmt_1 = tmt_2 = 0;
  tmt_1 = String(fmt).indexOf(',');
  tmt_2 = String(fmt + tmt_1 + 1).indexOf('.');

  /* 
   *  DEBUG POINT :
   *               1 : Check the postion of the first comma and dot.
   *               2 : BWT these two points we have our desired output Time Stiring.
   *               //Serial.println("\n\n\nTime Stamp :\n tmt_1 :  " + String (tmt_1) + "\n\ntmt_2 : " + String(tmt_2) );
   *               
   */               

  cnt = 0;
  while (cnt < 2)
  {
    Hr  += fmt[++tmt_1];
    cnt++;
  }
  cnt = 0;

  while (cnt < 2)
  {
    Min += fmt[++tmt_1];
    cnt++;
  }
  cnt = 0;

  while (cnt < 2)
  {
    Sec += fmt[++tmt_1];
    cnt++;
  }

  /**********************************/
  /* Convert Stirng into Integers */
  HH = Hr.toInt() + 5;
  MM = Min.toInt() + 30;
  SS = Sec.toInt();

  if ( MM  >= 60 ) {
    MM -= 60;
    HH++;
  }
  /*Print the time in the Format */
  Serial.println("Time Stamp : " + String(HH) + ":" + String(MM) + ":" + String(SS) );
  //  tmElements_t tm = {.Hour=HH,.Minute=MM,.Second=SS}; // NOT WORKing

  /*  DEBUG Point */
  
  uint8_t H,M,S;
  H = HH;
  M = MM;
  S = SS;
  tmElements_t tm = {.Second=S,.Minute=M,.Hour=H};
  epson_rtc.write(tm);
}
