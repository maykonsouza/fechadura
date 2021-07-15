#ifndef SENHAS_H_INCLUDED
#define SENHAS_H_INCLUDED

/************************
 sha_validar
 Verifica se senha esta cadastrada
 entradas
   texto : texto a ser validado como senha
 saidas
   TRUE:senha valida
   FALSE:senha invalida
*************************/
extern int sha_validar(char* texto);


#endif // SENHAS_H_INCLUDED
