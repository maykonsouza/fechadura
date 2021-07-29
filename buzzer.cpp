#include <Arduino.h>

#include "definicoes_sistema.h"
#include "buzzer.h"




Buzzer::Buzzer(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}


void Buzzer::sucesso(){
  tone(pin,440);
}


void Buzzer::erro(){
  tone(pin,329);
}


void Buzzer::desligar(){
  noTone(pin);
}
