#include <Arduino.h>
#include <Servo.h>

#include "definicoes_sistema.h"
#include "porta.h"

Servo myservo;  // create servo object to control a servo

// twelve servo objects can be created on most boards
Servo motor;  // create servo object to control a servo

int pp = 0;    // variable to store the servo ppition

void porta_init( void) {
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  myservo.write(57);
}

void porta_abrir(void) {
  
  for (pp = 58; pp <= 160; pp += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pp);
                // tell servo to go to ppition in variable 'pp'
    delay(15);                       // waits 15ms for the servo to reach the ppition
  }
  delay(1000); 
  for (pp = 160; pp >= 58; pp -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pp);              // tell servo to go to ppition in variable 'pp'
    delay(15);                       // waits 15ms for the servo to reach the ppition
  }
}