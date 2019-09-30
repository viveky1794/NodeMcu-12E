/* @Date    : 24-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Tap module
   @Version : v.01(NodeMcu 12E)
   
   @Working : It dectect any shock/vibration and give Digital(0 or 1)
              Output. Normally it remains HIGH but at any vibration
              it gives LOW.  

   @Notice  : Code is not working. wrong output problem my be in 
              sensor.           
*/


void setup() {
  Serial.begin(9600);
  pinMode(D1,INPUT);
  Serial.println("\nStart.......!!!");
  Serial.println("\nOUTPUT : " + String( digitalRead(D1) ) );
  delay(2000);
}

void loop() {
  Serial.println("\nOUTPUT : " + String( digitalRead(D1) ) );
 
}
