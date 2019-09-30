/* @Date    : 23-Sep-2019
 * @Author  : Vivek Yadav
   @Brief   : passive buzzer
              working with two differnet sounds.
              Sounds depend on frequency(basically delay() here)
   @Version : v.01
   @Working : Make Pin high with which, your Passive buzzer attached.
              we can change frequency value to get differnet sound in Method : 1
              In Methode : 2, use appropriate delay to get different sounds. 
*/

int buzzer = D1; // set the buzzer control digital IO pin

void setup() {
  pinMode(buzzer, OUTPUT); // set pin 8 as output
}

void loop() {

  //Method : 1
   tone(D1,50000,2500);
   delay(1000);
   noTone(D1);
   delay(1000);

  //Method : 2
  for (int i = 0; i < 80; i++) {
    digitalWrite(buzzer, HIGH); // make a sound
    delay(1); // send high signal to buzzer
    digitalWrite(buzzer, LOW); // delay 1ms
    delay(1); // send low signal to buzzer
  }

  delay(50);

  for (int j = 0; j < 100; j++) {
    digitalWrite(buzzer, HIGH);  //make another sound
    delay(2);
    digitalWrite(buzzer, LOW); // delay 2ms
    delay(2);
  }
  delay(100);

}
