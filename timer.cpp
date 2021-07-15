#include <Arduino.h>

#include "definicoes_sistema.h"
#include "timer.h"

#define TEMPO 10

int tmr_situacao = false;
unsigned long horaInicio;

/*******************************
 tmr_iniciar
 Aciona ou desaciona o timer
 entradas
   controle: TRUE:liga FALSE:desliga
 saidas
   nenhuma
********************************/
void tmr_iniciar(int controle)
{
   tmr_situacao = controle;
   if (controle)
   {
      horaInicio = millis();
   }
}

/*******************************
 tmr_timeout
 Retorna se o timer esta em timeout.
 entradas
    nenhuma
 saidas
    FALSE: não houve estouro do temporizador
    TRUE: houve estouro do temporizador
********************************/
int tmr_timeout()
{
    if (tmr_situacao == false)
    {
        return false;
    }
    if(millis() - horaInicio > TEMPO*1000)
    {
        return true;
    }
    return false;
}
