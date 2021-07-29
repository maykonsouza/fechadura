#ifndef DEFINICOES_SISTEMA_H_INCLUDED
#define DEFINICOES_SISTEMA_H_INCLUDED

#define true  1
#define false 0

#define LED_VERDE       13
#define LED_VERMELHO    12
#define BUZZER_PIN      11
#define SERVO_PIN       8
#define PORTA_PIN       A1
#define BOTAO           A0

#define TEMPO 200


#define NUM_ESTADOS 3
#define NUM_EVENTOS 8

// ESTADOS
#define ESPERA                0
#define INSERINDO_SENHA     1
#define PORTA_ABERTA        2


// EVENTOS
#define NENHUM_EVENTO       -1
#define REQUISICAO           0
#define SENHA_VALIDA         1
#define TIMEOUT              2
#define SENHA_INVALIDA       3
#define OUTRA_REQUISICAO     4
#define BOTAO_SENHA          5
#define PORTA_FECHADA        6
#define BOTAO_INTERNO        7

// ACOES
#define NENHUMA_ACAO -1
#define A01  0
#define A02  1
#define A03  2
#define A04  3
#define A05  4
#define A06  5
#define A07  6
#define A08  7
#define A09  8


#endif // DEFINICOES_SISTEMA_H_INCLUDED
