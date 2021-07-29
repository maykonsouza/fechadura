#include "definicoes_sistema.h"
#include "ihm.h"
#include "timer.h"
#include "buzzer.h"
#include "display.h"
#include "leds.h"
#include "usuarios.h"
#include "porta.h"
#include "web.h"


/***********************************************************************
 Componentes
 ***********************************************************************/
Led ledVerde(LED_VERDE);
Led ledVermelho(LED_VERMELHO);
Buzzer beep(BUZZER_PIN);
Porta entrada(SERVO_PIN);
Chave botao(BOTAO);
Chave sensor(PORTA_PIN);
InterfaceHomemMaquinaKeypad ihm;
TimerInterno tmr;
Display tela;


/***********************************************************************
 Estaticos
***********************************************************************/
int codigoAcao_tmp=-2;
int estado_tmp=-2;
int codigoEvento_tmp=-2;
int porta_tmp=0;
int m=0;
int u_tmp=0;
int sessaoAberta = false;
int codigoEvento = NENHUM_EVENTO;
int eventoInterno = NENHUM_EVENTO;
int estado = ESPERA;
int codigoAcao;
int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];



/************************************************************************
 executarAcao
 Executa uma acao
 Parametros de entrada:
    (int) codigo da acao a ser executada
 Retorno: (int) codigo do evento interno ou NENHUM_EVENTO
*************************************************************************/
int executarAcao(int codigoAcao)
{
    int retval;

    retval = NENHUM_EVENTO;
    if (codigoAcao == NENHUMA_ACAO)
        return retval;

    switch(codigoAcao)
    {
    case A01:
        informa_inicio(1);        
        tela.imprimir(0,"Digite a senha: ");        
        tmr.iniciar(true);
        tela.imprimir(1,"     "); 
        break;
    case A02:
        informa_sucesso(2);
        tmr.iniciar(false);
        Serial.println("Abrindo a porta...");
        tela.limpa();
        tela.imprimir(0,"   Bem vindo, ");
        tela.imprimir(1,usuario[u_tmp][0]);
        Serial.println(usuario[u_tmp][0]);
        simula_porta();
        tela.desligar(1000);
        break;
    case A03:
        informa_timeout(1);
        tela.imprimir(0,"Seu tempo acabou!");
        tmr.iniciar(false);
        tela.desligar(800);
        break;
    case A04:
        informa_erro(1);
        tela.imprimir(0,"Senha incorreta");
        tmr.iniciar(false);
        tela.desligar(800);
        break;
    case A05:
        tela.imprimir(0,"Sistema em uso");
        informa_timeout(1);
        break;
    case A06:
        Serial.println("Atualiza display");
        tela.imprimir(2,"*");
        tmr.iniciar(true);
        break;
    case A07:
        Serial.println("Porta está Aberta");
        informa_inicio(1);
        tmr.iniciar(false);
        break;
    case A08:
        Serial.println("Porta foi Fechada");
        informa_inicio(1);
        tmr.iniciar(false);
        break;
    case A09:
        Serial.println("Abrir porta pelo botão interno");
        informa_inicio(1);
        simula_porta();
        tmr.iniciar(false);
        break;
    } // switch

    return retval;
} // executarAcao

/************************************************************************
 iniciaMaquina de Estados
 Carrega a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaMaquinaEstados()
{
  int i;
  int j;

  for (i=0; i < NUM_ESTADOS; i++) {
    for (j=0; j < NUM_EVENTOS; j++) {
       acao_matrizTransicaoEstados[i][j] = NENHUMA_ACAO;
       proximo_estado_matrizTransicaoEstados[i][j] = i;
    }
  }
  proximo_estado_matrizTransicaoEstados[ESPERA][REQUISICAO] = INSERINDO_SENHA;
  acao_matrizTransicaoEstados[ESPERA][REQUISICAO] = A01;

  proximo_estado_matrizTransicaoEstados[PORTA_ABERTA][REQUISICAO] = PORTA_ABERTA;
  acao_matrizTransicaoEstados[PORTA_ABERTA][REQUISICAO] = A07;

  proximo_estado_matrizTransicaoEstados[INSERINDO_SENHA][SENHA_VALIDA] = PORTA_ABERTA;
  acao_matrizTransicaoEstados[INSERINDO_SENHA][SENHA_VALIDA] = A02;

  proximo_estado_matrizTransicaoEstados[INSERINDO_SENHA][TIMEOUT] = ESPERA;
  acao_matrizTransicaoEstados[INSERINDO_SENHA][TIMEOUT] = A03;

  proximo_estado_matrizTransicaoEstados[INSERINDO_SENHA][SENHA_INVALIDA] = ESPERA;
  acao_matrizTransicaoEstados[INSERINDO_SENHA][SENHA_INVALIDA] = A04;

  proximo_estado_matrizTransicaoEstados[INSERINDO_SENHA][OUTRA_REQUISICAO] = INSERINDO_SENHA;
  acao_matrizTransicaoEstados[INSERINDO_SENHA][OUTRA_REQUISICAO] = A05;

  proximo_estado_matrizTransicaoEstados[INSERINDO_SENHA][BOTAO_SENHA] = INSERINDO_SENHA;
  acao_matrizTransicaoEstados[INSERINDO_SENHA][BOTAO_SENHA] = A06;

  proximo_estado_matrizTransicaoEstados[PORTA_ABERTA][PORTA_FECHADA] = ESPERA;
  acao_matrizTransicaoEstados[PORTA_ABERTA][PORTA_FECHADA] = A08;

  proximo_estado_matrizTransicaoEstados[ESPERA][BOTAO_INTERNO] = PORTA_ABERTA;
  acao_matrizTransicaoEstados[ESPERA][BOTAO_INTERNO] = A09;


} // initStateMachine

/************************************************************************
 iniciaSistema
 Inicia o sistema ...
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaSistema()
{
   iniciaMaquinaEstados();
} // initSystem

/************************************************************************
 obterAcao
 Obtem uma acao da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo da acao
*************************************************************************/
int obterAcao(int estado, int codigoEvento) {
  return acao_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao


/************************************************************************
 obterProximoEstado
 Obtem o proximo estado da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo do estado
*************************************************************************/
int obterProximoEstado(int estado, int codigoEvento) {
  return proximo_estado_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao

char* teclas;
char pw[6];
int senha_errada=false;

int decodificarRequisicao()
{
    if (teclas[0] == '*' && !sessaoAberta)
    {
        teclas[0]=' ';
        sessaoAberta=true;
        return true;
    }
    return false;
}//decodificarRequisicao

int decodificarSenha_Valida()
{
    int u=0;
    
    if ( m==6)
    {
        for (int i=0; usuario[i][0][0]; i++)
        { 
            if(!(strncmp(pw, usuario[i][1], 6)) )
            {
                sessaoAberta=false;
                m=0;
                teclas[0]=' ';
                u_tmp=u;
                return true;
            }
            u++;       
        }
        senha_errada=true;        
        return false;        
    }  
    return false;
}//decodificarSenha_Valida

int decodificarTimeout()
{    
    if(tmr.timeout()){
        sessaoAberta=false;
        return true;
    }
    return false;
}

int decodificarSenha_Invalida()
{
    if (senha_errada)
    {
        sessaoAberta=false;
        m=0;
        teclas[0]=' ';
        senha_errada=false;
        return true;
    }
    return false;
}//decodificarSenha_Invalida

int decodificarOutra_Requisicao()
{
    if (teclas[0] == '*')
    {
        teclas[0]=' ';
        return true;
    }
    return false;
}//decodificarOutra_Requisicao

int decodificarBotao_Senha()
{
    if (sessaoAberta && (teclas[0]>='0' && teclas[0]<='9'))
    {
        pw[m++]=teclas[0];
        teclas[0]=' ';
        return true;
    }
    return false;
}//decodificarBotao_Senha

int decodificarPorta_Fechada()
{  
    if(sensor.estado()){
        return true;
    }
    return false;
}//decodificarPorta_Fechada

int decodificarBotao_Interno()
{
    if(botao.estado()){
        sessaoAberta=false;
        return true;
    }
    return false;
}//decodificarBotao_Interno



int obterEvento()
{
  int retval = NENHUM_EVENTO;

  teclas = ihm.obterTeclas();

  if (decodificarBotao_Interno())
    return BOTAO_INTERNO;
  if (decodificarRequisicao())
    return REQUISICAO;
  if (decodificarSenha_Valida())
    return SENHA_VALIDA;
  if (decodificarTimeout())
    return TIMEOUT;
  if (decodificarSenha_Invalida())
    return SENHA_INVALIDA;
  if (decodificarOutra_Requisicao())
    return OUTRA_REQUISICAO;
  if (decodificarBotao_Senha())
    return BOTAO_SENHA;
  if (decodificarPorta_Fechada())
    return PORTA_FECHADA;
  
  return retval;
 

} // obterEvento


/***********************************************************************
 * Tarefas
 ***********************************************************************/
void informa_inicio(int k)
{
    for(int i=0; i<k; i++){
        beep.sucesso();
        ledVerde.ligar();
      delay(TEMPO);
        beep.desligar();
        ledVerde.desligar();
      delay(TEMPO);
    } 
}

void informa_erro(int k)
{
    for(int i=0; i<k; i++){
        beep.erro();
        ledVermelho.ligar();
      delay(2*TEMPO);
        beep.desligar();
        ledVermelho.desligar();
      delay(2*TEMPO);
    } 
}

void informa_sucesso(int k)
{
    for(int i=0; i<k; i++){
        beep.sucesso();
        ledVerde.ligar();
        ledVermelho.ligar();
      delay(TEMPO);
        beep.desligar();
        ledVermelho.desligar();
        ledVerde.desligar();
      delay(TEMPO);
    } 
}


void informa_timeout(int k)
{
    for(int i=0; i<k; i++){
        beep.erro();
        ledVermelho.ligar();
      delay(TEMPO);
        beep.desligar();
        ledVermelho.desligar();
      delay(TEMPO);
    } 
}

void simula_porta()
{
    entrada.abrir();
    delay(2000);
    entrada.fechar();
}


/************************************************************************
 Main
 Loop principal de controle que executa a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/

void setup() {
  Serial.begin(9600);
  sensor.init();
  tela.init();
  entrada.init();
  ledVermelho.init();
  ledVerde.init();
  beep.init();
  botao.init();
  iniciaSistema();

  Serial.println("Sistema iniciado");
} // setup

void loop() {

  if (eventoInterno == NENHUM_EVENTO) {
      codigoEvento = obterEvento();
  } else {
      codigoEvento = eventoInterno;
  }
  if (codigoEvento != NENHUM_EVENTO)
  {
      codigoAcao = obterAcao(estado, codigoEvento);
      estado = obterProximoEstado(estado, codigoEvento);
      eventoInterno = executarAcao(codigoAcao);
      if(codigoAcao!=codigoAcao_tmp || estado != estado_tmp || codigoEvento != codigoEvento_tmp ){
        Serial.print("Estado: ");
        Serial.print(estado+1);
        Serial.print(" Evento: ");
        Serial.print(codigoEvento+1);
        Serial.print(" Acao: ");
        Serial.println(codigoAcao+1);
        codigoAcao_tmp=codigoAcao;
        estado_tmp=estado;
        codigoEvento_tmp=codigoEvento;
      }
  }
 
  
  delay(50);
} // loop
