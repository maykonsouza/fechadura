#include <Arduino.h>

#include "definicoes_sistema.h"
#include "buzzer.h"

/************************
 buzzer_beep
 Aciona o buzzer em modo beep
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
void buzzer_beep(int k)
{
    for(int i=0; i<k; i++){
      tone(BUZZER_PIN,440); 
      delay(200);
      noTone(BUZZER_PIN);
      delay(200); 
    } 
}

/************************
 buzzer_erro
 Aciona o buzzer em modo beep
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
void buzzer_erro(int k)
{
    for(int i=0; i<k; i++){
      tone(BUZZER_PIN,329); 
      delay(300);
      noTone(BUZZER_PIN);
      delay(300); 
    } 
}
