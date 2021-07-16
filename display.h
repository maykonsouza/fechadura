#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>


// //Inicializa o display no endereco 0x27
// LiquidCrystal_I2C lcd(0x27,16,2);

/************************
 buzzer_beep
 Aciona o buzzer em modo beep
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
///extern void buzzer_beep(int k);

/************************
 buzzer_erro
 Aciona o buzzer em modo beep
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
//void buzzer_erro(int k);

void tela_init(void);
void tela_imprime(int posicao, char mensagem[15]);
void tela_desliga(int tempo);
void tela_limpa(void);

#endif // DISPLAY_H_INCLUDED
