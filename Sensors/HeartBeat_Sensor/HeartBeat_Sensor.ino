/* @Date    : 25-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : HeartBeat Sensor
   @Version : v.01(NodeMcu 12E)
   
   @Working : 
   @Notice  : Not Working As named Suggested...... :-(
*/

#define SenSig D1

void setup() {
Serial.begin(9600);
  pinMode(SenSig,INPUT);
}

void loop() {
int Aval = analogRead(SenSig);
  Serial.println(Aval);
  delay(100);

/*
if(digitalRead(SenSig))
{
  int cnt =0;
  int tout = millis();
 while(millis() - tout < 60000)
  if(digitalRead(SenSig))
    cnt++;
  Serial.println(cnt);
}
*/

}
