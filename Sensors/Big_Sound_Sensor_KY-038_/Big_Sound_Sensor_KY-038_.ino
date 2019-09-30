/* @Date    : 25-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Big Sound Sensor(KY-038)/Small Sound 
   @Version : v.01(NodeMcu 12E)
   
   @Working : The microphone sound sensor, as the name says, 
              detects sound. It gives a measurement of how loud
              a sound is...
              sensor modules have a built-in potentiometer to adjust
              the sensitivity of the digital output pin
              In this example, a microphone sensor will detect the 
              sound intensity of your surroundings and will light up an
              LED if the sound intensity is above a certain threshold.
              
   @Notice  : Working...!!! :-)            
*/
#define Dout D1
#define Aout D2
void setup() {
  Serial.begin(9600);
  pinMode(Dout,INPUT);
  pinMode(Aout,INPUT);
  
}

void loop() {
  int Dval = digitalRead(Dout);
  
  if(Dval == HIGH)
  {
      Serial.println("Dout : " + String(Dval) );
      delay(100);
  }
  else
  {
      int Aval = analogRead(Aout);
      if(Aval >= 800)
        Serial.println("Aout : " + String(Aval));    
  }
//delay(100);
}
