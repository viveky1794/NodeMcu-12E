/* @Date    : 25-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Laser Emitter
   @Version : v.01(NodeMcu 12E)
   
   @Working : This 100mW laser module emits a small intense focused
              beam of visible red light. The module can be used with
              an Arduino and photo resistor module to perform basic 
              remote signaling.
   @Warning : This is a low power laser device, however as with all 
              laser devices care should be taken when in use. You 
              should never look directly in to its beam or point the
              laser at another person. Doing so may cause permanent
              eye damage. This item is not suitable for children.
              
   @Notice  : Working
*/

#define Signal D1
void setup() {
  Serial.begin(9600);
  pinMode(Signal,OUTPUT);
  
}

void loop() {
  digitalWrite(Signal,LOW);
  delay(1000);
  digitalWrite(Signal,HIGH);
  delay(1000);
}
