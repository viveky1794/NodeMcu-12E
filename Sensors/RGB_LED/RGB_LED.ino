/* @Date    : 23-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : RGB LED
   @Version : v.01(NodeMcu 12E)
   @Working : it is use to blink the LED with Different Color Combinations.
              specified by values.
              
*/

int red_light_pin= D1;
int green_light_pin = D2;
int blue_light_pin = D3; 

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}//End- setup()

void loop() {
  RGB_color(255, 0, 0); // Red
  delay(1000);
  RGB_color(0, 255, 0); // Green
  delay(1000);
  RGB_color(0, 0, 255); // Blue
  delay(1000);
  
  // Mix the color combination
  RGB_color(255, 255, 0); // Yellow
  delay(1000);
  RGB_color(170, 255, 50); //
  delay(1000);
  RGB_color(100, 100, 150); //
  delay(1000);

}//End- loop()

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
