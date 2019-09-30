/* @Date    : 24-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : 3V ~ 5Vdc Relay
   @Version : v.01(NodeMcu 12E)
   
   @Working : Work two mode Normally Open(NO) and Normally Close(NC)
              controll devices according to your Input at Signal Pin. 
*/



void setup() {
pinMode(D1,OUTPUT);

}

void loop() {
delay(5000);
digitalWrite(D1,HIGH); 
delay(5000);
digitalWrite(D1,LOW);
}
