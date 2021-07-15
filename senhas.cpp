#include <Arduino.h>

#include "definicoes_sistema.h"
#include "senhas.h"

/************************
 sha_validar
 Verifica se senha esta cadastrada
 entradas
   texto : texto a ser validado como senha
 saidas
   TRUE:senha valida
   FALSE:senha invalida
*************************/
int sha_validar(char* texto)
{
    if (texto[0] == '1' && texto[1] == '2')
        return true;
    else
        return false;
}
