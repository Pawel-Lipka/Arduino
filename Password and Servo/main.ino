/*
Password is 4 digits long and contains digits from 0 to 6. 
Set potentiometers in correct position(like in a safe). 
If all potentiometers are in correct position green led lights.
If not - red led lights and bell rings. 
Additionally, the servomotor tilts acordingly with the 
position of all potentiometers from 0 to 90 degrees 
*/

// library to support servo motors
#include <Servo.h>

// definition of four potentiometers and two LEDs
#define potentiometer1 A0
#define potentiometer2 A1
#define potentiometer3 A2
#define potentiometer4 A3
#define red_led 1
#define green_led 2

// Servo object
Servo servomotor;

void setup()
{
  // pins setup
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  servomotor.attach(0);
 }

  // variables initialization
  int s_motor_rotation;
  int read1, read2, read3, read4;
  int map1, map2, map3, map4;
  int status, controll_sum;

  // password setup
  int pas1 = 1;
  int pas2 = 2;
  int pas3 = 3;
  int pas4 = 4;
 

void loop()
{
  //controll sum is read from all summed potentiometers
  controll_sum = analogRead(potentiometer1) + analogRead(potentiometer2) 
               + analogRead(potentiometer3) + analogRead(potentiometer4);
    
  /* readings from the potentiometers mapped from 0 - 1023
   to 0 - 22.5 degres. Servo max rotation should be 90 degrees*/
  map1 = map(analogRead(potentiometer1), 0, 1023, 0, 22.5);
  map2 = map(analogRead(potentiometer2), 0, 1023, 0, 22.5);
  map3 = map(analogRead(potentiometer3), 0, 1023, 0, 22.5);
  map4 = map(analogRead(potentiometer4), 0, 1023, 0, 22.5);

  // rotation of servo is summ of all potentimeters
  s_motor_rotation = map1 + map2 + map3 + map4;
  
  // servo rotation
  servomotor.write(s_motor_rotation); 
  
   /* readings from the potentiometers mapped from 0 - 1023
   to 0 - 6. Password contains four digits from 0 - 6 */
  map1 = map(analogRead(potentiometer1), 0, 1023, 0, 6);
  map2 = map(analogRead(potentiometer2), 0, 1023, 0, 6);
  map3 = map(analogRead(potentiometer3), 0, 1023, 0, 6);
  map4 = map(analogRead(potentiometer4), 0, 1023, 0, 6);
  
  // check if the potentiometers have been moved
  if (status == controll_sum)
  {
    // if password correct green led light for 3s.
    if (map1 == pas1 && map2 == pas2 &&
        map3 == pas3 && map4 == pas4)
    {
      digitalWrite(green_led, HIGH);
      delay(3000);
      digitalWrite(green_led, LOW);
    }
    //if password incorrect red led light and bell ring for 3s.
    else {digitalWrite(red_led, HIGH);}
    delay(3000);
    digitalWrite(red_led, LOW);
  }
  
  //check if potentiometers wasn't moved
  status = controll_sum;
  delay(2000);
}
