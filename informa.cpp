#include <Arduino.h>

#include "definicoes_sistema.h"
#include "informa.h"

#define TEMPO 200

/************************
 informa_inicio
 Aciona o buzzer e o led verde
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
void informa_inicio(int k)
{
    for(int i=0; i<k; i++){
      tone(BUZZER_PIN,440); 
      digitalWrite(LED_VERDE, HIGH);
      delay(TEMPO);
      noTone(BUZZER_PIN);
      digitalWrite(LED_VERDE, LOW);
      delay(TEMPO);
    } 
}

/************************
 informa_erro
 Aciona o buzzer e o led vermelho
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
void informa_erro(int k)
{
    for(int i=0; i<k; i++){
      tone(BUZZER_PIN,329); 
      digitalWrite(LED_VERMELHO, HIGH);
      delay(2*TEMPO);
      noTone(BUZZER_PIN);
      digitalWrite(LED_VERMELHO, LOW);
      delay(2*TEMPO);
    } 
}

/************************
 informa_sucesso
 Aciona o buzzer e o led verde e vermelho
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
void informa_sucesso(int k)
{
    for(int i=0; i<k; i++){
      tone(BUZZER_PIN,440); 
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, HIGH);
      delay(TEMPO);
      noTone(BUZZER_PIN);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      delay(TEMPO);
    } 
}


/************************
 informa_timeout
 Aciona o buzzer e o led vermelho
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
void informa_timeout(int k)
{
    for(int i=0; i<k; i++){
      tone(BUZZER_PIN,329); 
      digitalWrite(LED_VERMELHO, HIGH);
      delay(TEMPO);
      noTone(BUZZER_PIN);
      digitalWrite(LED_VERMELHO, LOW);
      delay(TEMPO);
    } 
}