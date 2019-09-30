/* @Date    : 24-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : SMD RGB LED
   @Version : v.01(NodeMcu 12E)
   @Working : it is use to blink the LED with Different Color Combinations.
              specified by values.
              
*/

#define red D1
#define green D2
#define blue D3


void setup() {

pinMode(red,OUTPUT);
pinMode(green,OUTPUT);
pinMode(blue,OUTPUT);

digitalWrite(red,LOW);
digitalWrite(green,LOW);
digitalWrite(blue,LOW);

delay(5000);
}

void loop()
{

digitalWrite(red,HIGH);
delay(1000);
digitalWrite(green,HIGH);
delay(1000);
digitalWrite(blue,HIGH);
delay(1000);

// mix the colors
int tout = millis();
while( millis() - tout < 1000 ) 
{
  digitalWrite(red,HIGH);
  delay(1);
  digitalWrite(green,HIGH);
  delay(2);
  digitalWrite(blue,HIGH);
  delay(3);
}

// mix the colors
 tout = millis();
while( millis() - tout < 1000 ) 
{
  digitalWrite(red,HIGH);
  delay(1);
  digitalWrite(red,LOW);
  
  digitalWrite(green,HIGH);
  delay(3);
  digitalWrite(green,LOW);
  
  digitalWrite(blue,HIGH);
  delay(5);
  digitalWrite(blue,LOW);
}

}//End-loop()
