#include "TM1623.h"
#include "Counter.h"
#include "Arduino.h"

int Seg_one,Seg_two,Seg_three,Seg_four,Seg_five;

bool GPS_Counter(int HH,int MM,int SS)
{
      GPS_Hr(HH);
      GPS_Min(MM);
      GPS_Sec(SS);
      
}
void GPS_Hr(int HH)
{
    display7seg(5,digit(HH/10));  
    display7seg(4,digitWdot(HH%10));
    //display7seg(4,digitWdot(HH%10));  
}

void GPS_Min(int MM)
{
    display7seg(3,digit(MM/10));  
    display7seg(2,digitWdot(MM%10));  
}

void GPS_Sec(int SS)
{
    display7seg(1,digit(SS/10));  
    display7seg(0,digit(SS%10));  
}

bool Counter()
{
  /*
  display7seg(0,0x6B); // 2 for LSB
  display7seg(0,0xD6); // 2 for MSB
  delay(2000);
  */
    Inti_Counter();
//while(1)
//{
      Seg_0();
      Seg_1();
      Seg_2();
      Seg_3();
      Seg_4();
      Seg_5();
//}

    return 1;  
}

bool Seg_0()
{
  uint8_t dig;
  
      for(dig=0;dig<10;dig++)
      {
          display7seg(0,digit(dig));
          delay(200);    
      }  

      if(dig == 10)
        ++Seg_one;
      
      if(Seg_one == 10)
      {
        ++Seg_two;
        Seg_one = 0;
      }

       if(Seg_two == 10)
      {
        ++Seg_three;
        Seg_two = 0;
      }

      if(Seg_three == 10)
      {
        ++Seg_four;
        Seg_three = 0;
      }

      if(Seg_four == 10)
      {
        ++Seg_five;
        Seg_four = 0;
      }

      if(Seg_five == 10)
//        Seg_one = Seg_two = Seg_three = Seg_four = Seg_five = 0;
        
return 1;
}

bool Seg_1()
{
   display7seg(1,digit(Seg_one) );
  return 1;
}

bool Seg_2()
{
  display7seg(2,digit(Seg_two) );
  return 1;
}

bool Seg_3()
{
   display7seg(3,digit(Seg_three) );
  return 1;
}

bool Seg_4()
{
   display7seg(4,digit(Seg_four));
   return 1;
}

bool Seg_5()
{
    display7seg(5,digit( Seg_five) );
    return 1;
}

void Inti_Counter()
{
  /* make all 7 segments Zero initially */
  for(uint8_t i=0;i<6;i++)
  display7seg(i,digit(0));
}

uint8_t digit(uint8_t digit)
{
      switch(digit)
      {
        case 0 : return 0xB7; break;
        case 1 : return 0x03; break;
        case 2 : return 0xD6; break;
        case 3 : return 0xC7; break;
        case 4 : return 0x63; break;
        case 5 : return 0xE5; break;
        case 6 : return 0xF5; break;
        case 7 : return 0x83; break;
        case 8 : return 0xF7; break;
        case 9 : return 0xE7; break;
      }    
}


uint8_t digitWdot(uint8_t digit)
{
      switch(digit)
      {
        case 0 : return 0xBF; break;
        case 1 : return 0x0B; break;
        case 2 : return 0xDE; break;
        case 3 : return 0xCF; break;
        case 4 : return 0x6B; break;
        case 5 : return 0xED; break;
        case 6 : return 0xFD; break;
        case 7 : return 0x8B; break;
        case 8 : return 0xFF; break;
        case 9 : return 0xEF; break;
      }    
}
