/*
 * @Date  : 27/Sep/2019
 * @Author : Vivek Yadav
 * @Puspose : Digital/Analog HALL Magnatic Sensor  
 *            
 * @Working Status : Working 
 * @issue :       
 *         
 */

const float GAUSS_PER_STEP = 2.57;  // Sensor outputs approx 1.9mV / Gauss.  
void setup() {
  Serial.begin(9600);
  pinMode(D2,INPUT_PULLUP);
  pinMode(D1,INPUT);
}

void loop() {
  
  Serial.println( digitalRead(D2) );
  float val = analogRead(D1);
  Serial.println( val );
  delay(1000);
}
