#include "TM1623.h"
#include "Arduino.h"

void inti()
{
  pinMode(Dout,OUTPUT);
  pinMode(Clk,OUTPUT);
  pinMode(STB,OUTPUT);

  digitalWrite(Dout,HIGH);
  digitalWrite(Clk,HIGH);
  digitalWrite(STB,HIGH);
}

void CommandSetting()
{
  inti();
  /* see headerfile TM1623.h */
  command_1;  // Display control command
  command_2;  // Data command setting, Fixed write
  command_3;  // brightness set 
  command_4;  // Display control command 

}

/* SendCommand funcation */
void SendCommand(uint8_t cmd)
{
  Write(cmd);  
}

/* Write any data into device */
void Write(uint8_t data)
{
      digitalWrite(STB,LOW);
      shiftOut(Dout,Clk, LSBFIRST, data);
      digitalWrite(STB,HIGH);
}

/* Funcation for Displaying digits on 7-Segments

   Arguments :  
    1 - position : Segment Positions where data will display
    2-  value    : which data you want to Display on segment

   Return Type :
    NOthing will return

    
*/

void display7seg(uint8_t position,uint8_t value)
{
  digitalWrite(STB,LOW);
  
  shiftOut(Dout,Clk,LSBFIRST,SEG_ADR + (position << 1));
//shiftOut(Dout,Clk,LSBFIRST,value);
  shiftOut(Dout,Clk,MSBFIRST,value);
  
  digitalWrite(STB,HIGH);
}

/* STOP the Process via making STB pin HIGH*/
void Stop()
{
  digitalWrite(Clk,HIGH);
  digitalWrite(STB,HIGH);  
}
