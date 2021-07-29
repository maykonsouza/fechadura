#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "definicoes_sistema.h"
#include "display.h"

LiquidCrystal_I2C lcd(0x27,16,2);


Display::Display(){

}


void Display::init(){
  lcd.init();
}


void Display::limpa(){
  lcd.clear();
}


void Display::imprimir(int posicao, char mensagem[15]){
    if (posicao==2){
        lcd.setBacklight(HIGH);
        lcd.print(mensagem);
    }
    else{
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,posicao);
        lcd.print(mensagem);
    }
}


void Display::desligar(int tempo){
    delay(tempo);
    lcd.clear();
    lcd.setBacklight(LOW); 
}