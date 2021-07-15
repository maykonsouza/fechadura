#include <Arduino.h>

#include "definicoes_sistema.h"
#include "sirene.h"

/************************
 sne_bip
 Aciona momentaneamente a sirene
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
void sne_bip()
{
    Serial.println("Bip da sirene");
}


/************************
 sne_acionar
 Aciona ou desaciona a sirene
 entradas
   controle: TRUE:ligar FALSE:desligar
 saidas
   nenhuma
*************************/
void sne_acionar(int controle)
{
    Serial.print("Acionamento da sirene: ");
    Serial.println(controle);
}
