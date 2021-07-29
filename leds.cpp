#include <Arduino.h>
#include "leds.h"


Led::Led(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}


void Led::ligar(){
  digitalWrite(pin, HIGH);
}


void Led::desligar(){
  digitalWrite(pin, LOW);
}