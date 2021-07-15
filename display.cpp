#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "definicoes_sistema.h"
#include "display.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void tela_init(void)
{
 lcd.init();
}

void tela_imprime(int posicao, char mensagem[15])
{
 lcd.setBacklight(HIGH);
 lcd.setCursor(0,posicao);
 lcd.print(mensagem);
}

void tela_desliga(int tempo)
{
 delay(tempo);
 lcd.setBacklight(LOW);
 lcd.print("");
}
// /************************
//  buzzer_beep
//  Aciona o buzzer em modo beep
//  entradas
//    k: Quanridade de beeps
//  saidas
//    nenhuma
// *************************/
// void buzzer_beep(int k)
// {
//     for(int i=0; i<k; i++){
//       tone(BUZZER_PIN,440); 
//       delay(200);
//       noTone(BUZZER_PIN);
//       delay(200); 
//     } 
// }

// /************************
//  buzzer_erro
//  Aciona o buzzer em modo beep
//  entradas
//    k: Quanridade de beeps
//  saidas
//    nenhuma
// *************************/
// void buzzer_erro(int k)
// {
//     for(int i=0; i<k; i++){
//       tone(BUZZER_PIN,329); 
//       delay(300);
//       noTone(BUZZER_PIN);
//       delay(300); 
//     } 
// }
