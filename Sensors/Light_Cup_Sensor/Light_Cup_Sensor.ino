/* @Date    : 25-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : Light Cup Sensor
   @Version : v.01(NodeMcu 12E)
   
   @Working :  KY-027 Magic Light Cup Module is a set of two boards
               , each one has a led and a mercury tilt switch. Using
               PWM to drive the LEDs on each module you can achieve 
               the effect of light being "magically" transferred from
               one module to the other when tilting them.

               In this Arduino sketch we'll use both KY-027 modules to 
               create the magic light cup effect. The mercury switches
               in each module provide a digital signal that is used to
               regulate the brightness of the LEDs using using PWM. 
               Tilting the modules will decrease the brightness on one
               module while increasing it on the other one, creating 
               the illusion of light magically passing from one module
               to the other.

 
   @Notice  : Not working as aspected....:-(
*/

// G connect to GND
// + connect to 5V
// L connect pin D1(1st module) & D3(2nd module)
// S connect pin D2(1st module) & D4(2nd module)

#define LedPinA  D1
#define ButtonPinA D2

#define LedPinB  D3
#define ButtonPinB D4

int buttonStateA = 0;
int buttonStateB = 0;
int brightness = 0;

void setup ()
{
  pinMode (LedPinA, OUTPUT);
  pinMode (LedPinB, OUTPUT);
  pinMode (ButtonPinA, INPUT);
  pinMode (ButtonPinB, INPUT);
}
void loop ()
{
  buttonStateA = digitalRead (ButtonPinA);
  if (buttonStateA == HIGH && brightness != 255)
  {
    brightness += 1;
  }
  buttonStateB = digitalRead (ButtonPinB);
  if (buttonStateB == HIGH && brightness != 0)
  {
    brightness -= 1;
  }
  analogWrite (LedPinA, brightness); // A few Guan Yuan (ii) ? 
  analogWrite (LedPinB, 255 - brightness);// B Yuan (ii) a few Bang ?
  delay (25);
}
