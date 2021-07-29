#include <Arduino.h>

#include "definicoes_sistema.h"
#include "ihm.h"


//keymap defines the key pressed according to the row and columns just as appears on the keypad
char InterfaceHomemMaquinaKeypad::keymap[KEYROWS][KEYCOLS]= 
{
{'1', '2', '3'}, 
{'4', '5', '6'}, 
{'7', '8', '9'},
{'*', '0', '#'}
};

//Code that shows the the keypad connections to the arduino terminals
byte InterfaceHomemMaquinaKeypad::rowPins[KEYROWS] = { 10, 9, 0, 7 }; //Rows 0 to 3
byte InterfaceHomemMaquinaKeypad::colPins[KEYCOLS]= { 6, 5, 4}; //Columns 0 to 3

InterfaceHomemMaquinaKeypad::InterfaceHomemMaquinaKeypad() : 
  keypad(Keypad(makeKeymap(keymap), rowPins, colPins, KEYROWS, KEYCOLS)),
  read_count(0)
{
}

/************************
 InterfaceHomemMaquinaKeypad::exibirMsg
 Exibe mensagem no display
 entradas
   texto : texto a ser validado como senha
 saidas
   nenhuma
*************************/
void InterfaceHomemMaquinaKeypad::exibirMsg(char* texto)
{
    Serial.print("Mensagem para display: ");
    Serial.println(texto);
}

/************************
 InterfaceHomemMaquinaKeypad::obterTecla
 Obtem tecla do teclado
 entradas
   nenhuma
 saidas
   teclas lidas do teclado
*************************/
char* InterfaceHomemMaquinaKeypad::obterTeclas()
{
  // check for input
  char key = keypad.getKey();
  if (key != NO_KEY) {
  	
      buf[0] = key;
      Serial.println(key);
      return buf;
  }
  buf[0]=-1;
  return buf;
}


Chave::Chave(int pin){
  this->pin = pin;
  
}


void Chave::init(){
  pinMode(pin, INPUT);
}

int Chave::estado(){
  if(analogRead(pin)>800){
        return true;
    }
  return false;
}