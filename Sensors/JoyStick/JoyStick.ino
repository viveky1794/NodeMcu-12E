




const int joystick_x_pin = 4;  
const int joystick_y_pin = 14;

void setup() {
  Serial.begin(9600);   /* Define baud rate for serial communication */
  pinMode(joystick_x_pin,INPUT_PULLUP);
    pinMode(joystick_y_pin,INPUT_PULLUP);
}

void loop() {
  int x_adc_val, y_adc_val; 
  float x_volt, y_volt;
  x_adc_val = analogRead(joystick_x_pin);  
  y_adc_val = analogRead(joystick_y_pin);
  x_volt = ( ( x_adc_val * 5.0 ) / 1023 );  /*Convert digital value to voltage */
  y_volt = ( ( y_adc_val * 5.0 ) / 1023 );  /*Convert digital value to voltage */
  Serial.print("X_Voltage = ");
  Serial.print(x_volt);
  Serial.print("\t");
  Serial.print("Y_Voltage = ");
  Serial.println(y_volt);
  delay(100);
}
