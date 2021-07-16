#include <Arduino.h>

#include "definicoes_sistema.h"
#include "leds.h"

#define TEMPO 200

/************************
 led_vermelho
 Aciona o led vermelho
 entradas
   k: Quantidade de piscados
 saidas
   nenhuma
*************************/
void led_vermelho(int k)
{
    for(int i=0; i<k; i++){
      digitalWrite(LED_VERMELHO, HIGH);
      delay(300);
      digitalWrite(LED_VERMELHO, LOW);
    } 
}

/************************
 led_verde
 Aciona o led verde
 entradas
   k: Quantidade de piscados
 saidas
   nenhuma
*************************/
void led_verde(int k)
{
    for(int i=0; i<k; i++){
      digitalWrite(LED_VERDE, HIGH);
      delay(TEMPO);
      digitalWrite(LED_VERDE, LOW);
      delay(TEMPO);
    } 
}


/************************
 led_verde
 Aciona todos os leds
 entradas
   k: Quantidade de piscados
 saidas
   nenhuma
*************************/
void led_todos(int k)
{
    for(int i=0; i<k; i++){
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, HIGH);
      delay(TEMPO);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      delay(TEMPO);
    } 
}