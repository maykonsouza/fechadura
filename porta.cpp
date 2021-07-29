#include <Arduino.h>
#include <Servo.h>

#include "definicoes_sistema.h"
#include "porta.h"


Servo myservo; 


Porta::Porta(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}


void Porta::init(){
  myservo.attach(pin); 
  myservo.write(57);
}


void Porta::abrir(){
  for (pp = 58; pp <= 160; pp += 1) {
    myservo.write(pp);
    delay(15);                    
  }
}


void Porta::fechar(){
  for (pp = 160; pp >= 58; pp -= 1) { 
    myservo.write(pp);             
    delay(15);   
  }
}

