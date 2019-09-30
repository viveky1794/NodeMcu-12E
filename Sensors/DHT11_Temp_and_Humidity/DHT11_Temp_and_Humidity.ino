/* 
 *  @Date : 28/Sep/2019
 *  @Author : Vivek Yadav
 *  @Purpose : Check temperature and humidity with DHT11 
 *             Totally depend on Datasheet.
 *  @issue : 
 *  
 *  
 */

#define DL D2
#define delay_us delayMicroseconds 
uint8_t data[5];

void setup() {

Serial.begin(9600);
Serial.println("\nStart..........!!!!");

//initilization
  
}//End- steup();

void loop()
{
getData();
delay(2000);
}//End- loop()



bool CRCCheck()
{
  if(data[4] == (data[0]+data[2]))
    return 1;
 return 0;
}


void getData()
{
    data[0] =data[1] = data[2] = data[3] = data[4] = 0 ;
     int index = 0;
      int d = 128;
    
       initDHT11();

        for(int i=0;i<40;i++)
        {
            while(! digitalRead(DL) )
            {
                yield();
              }
              int tout = micros();  
               while( digitalRead(DL) )
                {
                    yield();   
                  }           
                  if(micros() - tout > 40)
                   {  
                     data[index] |= d;
                     }
                      d >>= 1;
                      if(d==0)
                        {
                          d=128;
                          index++;
                          }
                     
          }    
           Serial.print("Humidity : ");
            Serial.print(data[0],DEC);
             Serial.print("\tTemperature : ");
              Serial.println(data[2],DEC);
                 
}//End- getData() 


void initDHT11()
{
  pinMode(DL,OUTPUT);
   digitalWrite(DL,HIGH);
    delay(1);  
     digitalWrite(DL,LOW);
      delay(18);
       pinMode(DL,INPUT_PULLUP);
        delay_us(40);

// Waiting for Sensor Data now
  int tout = millis();
   while(digitalRead(DL))
    {
     if(millis() - tout > 1000)
      break;
       yield(); 
     } 
      delayMicroseconds(80);
       if(digitalRead(DL))
        delayMicroseconds(80);
       else
          Serial.println("No Respone 2");
  
}
