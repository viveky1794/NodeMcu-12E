/* @Date    : 24-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Tracking Sensor
   @Version : v.01(NodeMcu 12E)
   
   @Working : 
              digital Output : 0 or 1
              Analog Output  : 0(dark) or 1023(white)
   
*/

#define sensorOutput D1 

void setup() {
  Serial.begin(9600);
  pinMode(sensorOutput,INPUT);
  Serial.println();
  Serial.println("Reading : ");
}

void loop() {
 
  bool Sval = digitalRead(sensorOutput);
  if(Sval == 0)
  {
  Serial.println( analogRead(sensorOutput) );
  Serial.print("-------------------------- \n\n");
  }
}
