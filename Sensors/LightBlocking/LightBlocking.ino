/* @Date    : 24-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Light Blocking Sensor
   @Version : v.01(NodeMcu 12E)
   
   @Working : This is a light block sensor module, where there
              is an object in the middle of the U shape. The sensor
              will output a high level signal.  

   @Notice  :            
*/

void setup() {
  Serial.begin(9600);
  pinMode(D1,INPUT);
  Serial.println("\nStart.......!!!");
}

void loop() {
  Serial.println("OUTPUT : " + String( digitalRead(D1) ) );
  
  delay(500);
}
