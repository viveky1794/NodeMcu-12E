/* @Date    : 24-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Light Blocking Sensor
   @Version : v.01(NodeMcu 12E)
   
   @Working : This Infrared Obstacle Avoidance Sensor returns 
              a signal when it detects an object in range. The 
              range of the sensor is around 2-40 cm is distance.
              It operates at 3.5 to 5 volts at around 20 milliamps.
              The Obstacle Avoidance Sensors usually come in two types
              - with 3 and 4 pins. The 3 pin version does not have the
              ability to be enabled/disabled. The 4 pin version has 
              optional Enable pin. Infrared obstacle avoidance sensor is
              designed to detect obstacles or the difference in
              reflective services. One application is to help a wheeled
              robot avoid obstacles with a sensor to react to adjustable
              distance settings. This device has an infrared transmitter
              and receiver, that forms the sensor pair. The transmitter 
              LED emits a certain frequency of infrared, which the receiver
              LED will detect. The receiving LED will detect some of the 
              signal back and will trigger the digital on/off “signal” pin
              when a specific threshold “distance” has been detected. Most
              boards will have 2 potentiometers, one of which is to adjust
              how sensitive the sensor is. You can use it to adjust the 
              distance from the object at which the sensor detects it. 
              Typically, the other potentiometer, which changes the 
              transmitter IR frequency is not adjusted..  

   @Notice  : NOT Working...!!! :-)            
*/

#define OP D1
#define EN D2

void setup() {
 Serial.begin(9600);
 pinMode(OP,INPUT_PULLUP);
 pinMode(EN,OUTPUT);
 Serial.println("\nStart...!!!");
 digitalWrite(EN,HIGH);
}

void loop() {
int val = digitalRead(OP);
//Serial.println(analogRead(OP));
if(val == LOW)
  Serial.println(val);

}
