/*
 * @Date  : 27/Sep/2019
 * @Author : Vivek Yadav
 * @Puspose : Get the temperature Data with the help of Digital 
 *            Temp Sensor.
 * @Working Status : Working Set Sensitivity a/c
 * @issue :       
 *         
 */


void setup() {
  Serial.begin(9600);
  pinMode(D2,INPUT_PULLUP);
  
}

void loop() {
  
  Serial.println( digitalRead(D2) );
  Serial.println( analogRead(D2) );
  delay(1000);
}
