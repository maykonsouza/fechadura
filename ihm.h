#ifndef IHM_H_INCLUDED
#define IHM_H_INCLUDED
#include <Keypad.h>


#define NENHUMA_TECLA -1
#define KEYROWS 4
#define KEYCOLS 3

class InterfaceHomemMaquinaKeypad {
  public:
  InterfaceHomemMaquinaKeypad();
  void exibirMsg(char* texto);
  char* obterTeclas();

  private:
  char buf[1];
  static char keymap[KEYROWS][KEYCOLS];
  static byte rowPins[KEYROWS];
  static byte colPins[KEYCOLS];
  Keypad keypad;
  int read_count;
};


class Chave{
  public:
    Chave(int pin);
    void init();
    int estado();
    
  private:
    int pin;
};



#endif // IHM_H_INCLUDED
