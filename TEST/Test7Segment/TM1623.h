#ifndef __TM1623_H__
#define __TM1623_H__

#include "Arduino.h"


#define Dout D5 // GPIO 14
#define Clk  D6 // GPIO 12
#define STB  D7 // GPIO 13

#define ACTIVATE_TM 0x8F // Start up
#define BUTTONS_MODE 0x42 // Buttons mode
#define WRITE_LOC 0x44 // Write to a location
#define WRITE_INC 0x40 // Incremental write
#define SEG_ADR 0XC0  // leftmost segment Address C0 C2 C4 C6 C8 CA CC CE
#define LEDS_ADR 0xC1  // Leftmost LED address C1 C3 C5 C7 C9 CB CD CF
#define BRIGHT_ADR 0x88 // Brightness address
#define BRIGHT_MASK 0x07 // Brightness mask 
#define DEFAULT_BRIGHTNESS 0x02 //can be 0x00 to 0x07 
#define ASCII_OFFSET 32 // Ascii table offset to jump over first missing 32 chars
#define HEX_OFFSET   16 // Ascii table offset to reach number position
#define DOT_MASK_DEC    128 // 0x80 Mask to  switch on decimal point in seven seg.   

/* COMMANDS AS PER DATASHEET MOSTLY SIMILIAR IN TM16XX FAMILY */
#define command_1 digitalWrite(STB,HIGH);digitalWrite(STB,LOW);SendCommand(0x03);   // Display control command  
#define command_2 digitalWrite(STB,HIGH);digitalWrite(STB,LOW);SendCommand(0x44);   // Data command setting, Fixed write
#define command_3 digitalWrite(STB,HIGH);digitalWrite(STB,LOW);SendCommand(0x87);   // brightness set 
#define command_4 digitalWrite(STB,HIGH);digitalWrite(STB,LOW);SendCommand(0x88);   // Display control command  


/*  CORE FUNCATIONS DECLARATIONS */
void inti();
void CommandSetting();
void Stop();
void Write(uint8_t );
void SendCommand(uint8_t );
void display7seg(uint8_t ,uint8_t );


/*      
 *       _A__                   DEC |A|B|C|D|E|F|G|H| HEX |
 *     C|   |G                   0  |1|0|1|1|0|1|1|1|0xB7 | 
 *      --B--                    1  | | | | | | | | |0x03 |
 *     D|   |H                   2  | | | | | | | | |0xD6 |
 *      --F--   dot(E)           3  | | | | | | | | |0xC7 |
 *                               4  | | | | | | | | |0x63 |
 *                               5  | | | | | | | | |0xE5 |
 *                               6  | | | | | | | | |0xF5 |
                                 7  | | | | | | | | |0x83 |
                                 8  | | | | | | | | |0xF7 |
                                 9  | | | | | | | | |0xE7 |
                                    | | | | | | | | |     |
 *
 *
 */


#endif
