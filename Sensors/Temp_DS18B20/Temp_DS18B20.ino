/*
 * @Date  : 27/Sep/2019
 * @Author : Vivek Yadav
 * @Puspose : Get the temperature Data with the help of DS18B20 
 *            Sensor.
 * @Working Status : NOT Working
 * @issue : 
 *          1: Not able to get the device Id.
 *          2: I am 95% sure that my Funcations for Writing and
 *             Reading are correct.If you find any mistake let me 
 *             know.
 *          3: Sensor can we Faulty. May be
 * 
 */





#define CP Serial.print
#define READ_ROM 0x33
#define MATCH_ROM 0x55
#define SKIP_ROM 0xCC
#define SEARCH_ROM 0xF0
#define ALARM_ROM 0xEC

#define READ_SCR 0XBE
#define WRITE_SCR 0X4E
#define COPY_SCR 0X48
#define CONVT_SCR 0X44
#define RECALL_E2 0XB8
#define READ_POWER 0XB4
#define  resolution_12bit 0x7F
const int Spin = 4; // GPIO
unsigned long deviceName;
void setup()
{

  Serial.begin(115200);
  unsigned long TempH,TempL;
  if( !tempInit(Spin) )
   {
    CP("\nTemp Start.....!!!\n\n");  
    while(tempRead(Spin,1) == 0)
      {
        tempWrite(0xF0,Spin);
        tempWrite(READ_ROM,Spin);CP("\n");

        deviceName = tempRead(Spin,1);
      CP(deviceName);
        CP(" ");
        delay(1000);
        yield();
      }
   
   
    for(int i=0;i<8;i++)
    {
//      while();
      
    }
    
    TempH = tempRead(Spin,1);
    TempL = tempRead(Spin,1);
    CP("\nTempL : "); CP(tempRead(Spin,1));
    CP("\nTempH : "); CP(tempRead(Spin,1));
   }
  else
    CP("\nError : Temp NOT responding...\n\n");

    deviceName=((unsigned int)TempH << 8 ) + (unsigned int)TempL; //put both value in one variable
      deviceName = deviceName * 6.25;   //calculations used from the table provided in the data sheet of ds18b20
      
  CP("\n");CP(deviceName);
}

void loop()
{
  
}

bool tempInit(const int pin)
{
  pinMode(pin,OUTPUT);// Set OutPut Mode 
  digitalWrite(pin,HIGH);
  delay(1);

  // See datasheet
  digitalWrite(pin,LOW);// Set Low
  delayMicroseconds(480);
  pinMode(pin,INPUT_PULLUP);
  delayMicroseconds(60);// Wait for 60uSec
 
  bool device = digitalRead(pin)?1:0; // 0-Present; 1-Not present
  delayMicroseconds(480);
  return device;
}
/***************************************************/

/***************************************************/
void tempWrite(const char data,const int pin)
{
  
  for(int i =0; i<8; i++)
  {
    if( data & (1<<i) )//LSB first
    {
      //Write 1
      pinMode(pin,OUTPUT); 
      digitalWrite(pin,LOW);
      delayMicroseconds(1);
      pinMode(pin,INPUT_PULLUP);
      delayMicroseconds(60);
    }
    else
    {
      //Write 0
      pinMode(pin,OUTPUT);
      digitalWrite(pin,LOW);// make line Low 
      delayMicroseconds(60);
      pinMode(pin,INPUT_PULLUP);// realise the line
    }
    
  }//End- for()

//  CP("cmd : ");CP(data,HEX);CP(" : ");
//  for(int i=7;i>=0;i--)
//    CP( (data >> i ) &1 );
}


unsigned long tempRead(const int pin,bool cmd)
{
  unsigned long data = 0;
   
    for(int i=0;i<8;i++)
    {
      pinMode(pin,OUTPUT);
      digitalWrite(pin,HIGH);
      delay(1);
    
    // Reading Algorithams
      digitalWrite(pin,LOW);// Pull down by master
      delayMicroseconds(2);// 
      pinMode(pin,INPUT_PULLUP);// Realise the Pin
//      delayMicroseconds(15);
      if(digitalRead(pin))
        data |= 1<<i;
      delayMicroseconds(60);
    } 
  return data;
  }
