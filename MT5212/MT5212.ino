 /*
    Name : Vivek Yadav
    Date : 9/8/2019(Start) - 13/8/2019(End)

    Purpose :
              Program for showing GPS cordinates/Time. Through MT/5212 module
              and NODEMCU v3 with ESP8266
  
    Version :
    1->
    Take dummy data at fixed interval and parsh the required String from
    Multiple Strings given by GPS.
    
    2->
    Repalce dummy data with Real time data.
    
    3->
    Now Real time data must come at my desire,For that i have connected a
    push button to GPIO 14( ESP8266(pin 5) ).High to Low
  
    4->
    Now include interrupt serivce routine with it to perfrom same task.
    Whenever it get the high to low pulse. we will get the data(Time).


*/

/* Funcation decalration */

void read_serial();
void Out_Format(char *);
void Parsh_time(char *);

const int PushButton = 14;
bool ButtonState = 0;
bool READ_GPS = false;

void ICACHE_RAM_ATTR f1() // Interrupt service Routine
{
  READ_GPS = true;
}
/* START */
void setup() {
  Serial.begin(9600);
  Serial.println( "Start : ");
  pinMode(PushButton, INPUT);

  interrupts();
  attachInterrupt(digitalPinToInterrupt(14), f1, FALLING);
}

void loop() {
  //   ButtonState = digitalRead( PushButton);
  //   Serial.println("\n\n\nButtonState : " + String(ButtonState) );
  Serial.println("...." );

  //  if(! ButtonState)
  if (READ_GPS)
  {
    read_serial();
    READ_GPS = false;
  }

  delay(2000);
}

void read_serial()
{
  String str = "";
  unsigned long tout = millis();    //millis(): 1ms system ticker

   /******************************************/
  while ( millis() - tout < 500)
  {
    if (Serial.available() > 0)
    {
      str += (char)Serial.read();
      tout = millis();

      /* DEBUG : 1 */
      // Serial.println("A"); // valid
    }
    yield();
  }
  /*******************************************/
  /* DEBUG : 2  */
  //    Serial.println("DATA IS COMING : \n" +String(str) );
  //    Serial.println("\n\n\nlength : " + String(str.length()));
 /*******************************************/
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
 /*******************************************/
      /* DEBUG POINT */
      //         Serial.print(fmt); // GPGGA string printing
      //        Serial.println("\n\n\n");
 /*******************************************/      
    }

    Out_Format((char *)fmt.c_str());
  }
  /*******************************************/

  //  Serial.println("END DATA");
  //  Serial.println("");
 /*******************************************/
}
void Out_Format(char *fmt)
{
  /* TIME STAMP */
  Parsh_time(fmt);
  /* Latitute & Longitude */
  //    Parsh_Long_Lati(fmt);
}

void Parsh_time(char *fmt)
{
  String Sec, Min, Hr;
  int SS, MM, HH;
  int tmt_1, tmt_2, cnt;

  tmt_1 = tmt_2 = 0;
  tmt_1 = String(fmt).indexOf(',');
  tmt_2 = String(fmt + tmt_1 + 1).indexOf('.');

  /* DEBUG POINT :
        1 : Check the postion of the first comma and dot.
        2 : BWT these two points we have our desired output Time Stiring.

       //Serial.println("\n\n\nTime Stamp :\n tmt_1 :  " + String (tmt_1) + "\n\ntmt_2 : " + String(tmt_2) );

  */


  /****************************/
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
} 
