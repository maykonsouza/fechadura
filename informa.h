#ifndef INFORMA_H_INCLUDED
#define INFORMA_H_INCLUDED

/************************
 informa_inicio
 Aciona o buzzer e o led verde
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
extern void informa_inicio(int k);

/************************
 informa_erro
 Aciona o buzzer e o led vermelho
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
extern void informa_erro(int k);

/************************
 informa_sucesso
 Aciona o buzzer e o led verde e vermelho
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
extern void informa_sucesso(int k);

/************************
 informa_timeout
 Aciona o buzzer e o led vermelho
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
extern void informa_timeout(int k);



#endif // INFORMA_H_INCLUDED
