#ifndef __COUNTER_H__
#define __COUNTER_H__

/* Global decalrations */
extern int Seg_one,Seg_two,Seg_three,Seg_four,Seg_five; // By default Zero

/* PROJECT[COUNTER] FUNCATION DECLARATION */
bool Counter();
void Inti_Counter();

uint8_t digit(uint8_t ); //used in GPS_Counter internally
uint8_t digitWdot(uint8_t ); //used in GPS_Counter internally

bool GPS_Counter(int,int,int); // For User

void GPS_Hr(int); //used in GPS_Counter internally
void GPS_Min(int);//used in GPS_Counter internally
void GPS_Sec(int);//used in GPS_Counter internally

bool Seg_0();
bool Seg_1();
bool Seg_2();
bool Seg_3();
bool Seg_4();
bool Seg_5();

/*  Project[ GPS COUNTER ] FUNCATIONS DECLARATIONS */
void GPS_read();
void GPS_Start();
void Parsh_time(char *);
void Out_Format(char *);


#endif
