/* @Date    : 25-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Photoresistor Sensor
   @Version : v.01(NodeMcu 12E)
   
   @Working :  

 
   @Notice  : Not Working
*/
#define Dout D2

void setup() {
  Serial.begin(9600);
  pinMode(Dout,INPUT);
}

void loop() {
  int Dval = digitalRead(Dout);
  if( Dval == HIGH)
    Serial.println(Dval);
  else
    Serial.println("Analog : " + String(analogRead(Dout)));

    delay(2000);
}
