/* @Date    : 23-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : 360 Rotatory encoder
   @Version : v.01(NodeMcu 12E)
   @Working : Frist Understand the Working principle of Rotatory Encoder :Visit wiki
              It is telling us rotation( Clockwise or anticlockwise ).
              Pin Diagram :
               1: Output A (Top)
               2: OutPut B
               3: 
               4: Vcc
               5: GND
*/


bool lastD1,newD1;
int counter = 0;

void setup()
{

  Serial.begin(9600);
  // In Place of D1 and D2 we can take any other GPIO
  pinMode(D1,INPUT);
  pinMode(D2,INPUT);

  lastD1 = digitalRead(D1);
  
  Serial.println("\nStart...........!!!! ");
}

void loop()
{
  newD1 = digitalRead(D1);
  
  if( lastD1 != newD1 )
  {
    if(digitalRead(D2) != newD1)
      counter -=1;// Clockwise Rotation
    else
      counter +=1;// Anti-Clockwise Rotation

      Serial.println("Position : " + String(counter));
  }//End - if()
  lastD1 = newD1;
}//End- loop()
