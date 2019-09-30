/* @Date    : 24-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Reed Switch
   @Version : v.01(NodeMcu 12E)
   
   @Working : A Reed Switch Module is a magnetic sensor that is
               normally open and get closed when exposed to a magnetic 
               field.In our example turn ON/OFF the LED on D1 if the
               megnet is near the Sensor turn On the Light otherwise turn OFF. 
              i.e Fridge Light
              Analog and Digital Output features are also available in the market.
              we are working only Digital Output.Sensitivity can we change with
              the help of potentioal meter available on the reed Switch. 
*/

#define LedStatusPin D1
#define reedStatusPin D4

int LastStatus;
int count = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(LedStatusPin, OUTPUT);
  pinMode(reedStatusPin, INPUT);
  LastStatus = digitalRead(reedStatusPin);
  
  delay(1000);
}

void loop() 
{
  int newStatus = digitalRead(reedStatusPin);

  if(LastStatus != newStatus)
    {
      count += 1;
      Serial.print("count : ");
      Serial.println(count);
      Serial.println("LastStatus : " + String(LastStatus));
      Serial.println("newStatus : " + String(newStatus));
       bool Status = LastStatus;
      switch(Status)
      {
            case 0: digitalWrite(LedStatusPin,LOW); break;
            case 1: digitalWrite(LedStatusPin,HIGH); break;
      }
    }

  LastStatus = newStatus;
}//End- loop()
