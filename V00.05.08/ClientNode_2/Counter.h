#ifndef __COUNTER_H__
#define __COUNTER_H__

/* Global decalrations */
extern int Seg_one,Seg_two,Seg_three,Seg_four,Seg_five; // By default Zero

/* PROJECT[COUNTER] FUNCATION DECLARATION */
bool Counter();
void Inti_Counter();
uint8_t digit(uint8_t );
uint8_t digitWdot(uint8_t );
bool GPS_Counter(int,int,int);
void GPS_Hr(int);
void GPS_Min(int);
void GPS_Sec(int);

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
