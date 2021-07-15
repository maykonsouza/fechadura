#include "definicoes_sistema.h"
//#include "comunicacao.h"
#include "ihm.h"
#include "senhas.h"
#include "timer.h"
#include "buzzer.h"
#include "display.h"




/***********************************************************************
 Estaticos
 ***********************************************************************/
  int codigoEvento = NENHUM_EVENTO;
  int eventoInterno = NENHUM_EVENTO;
  int estado = IDLE;
  int codigoAcao;

  int codigoAcao_tmp=-2;
  int estado_tmp=-2;
  int codigoEvento_tmp=-2;
  int porta_tmp=0;
  int porta=1;


  int sessaoAberta = false;
 


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
        //tmr_iniciar(true);
        buzzer_beep(1);
        //lcd.setBacklight(HIGH);
        //lcd.setCursor(0,0);
        //lcd.print("Digite a senha");
        tela_imprime(0,"Digite a senha:");
        digitalWrite(LED_VERDE, HIGH);
        delay(300);
        digitalWrite(LED_VERDE, LOW);
        tmr_iniciar(true);
        break;
    case A02:
        buzzer_beep(2);
        //com_notificar("Alarme em alerta");
        tmr_iniciar(false);
        Serial.println("Abrindo a porta...");
        //lcd.setCursor(0,0);
        tela_imprime(0,"Abrindo a porta.");
        for(int i=0;i<4;i++){
            digitalWrite(LED_VERMELHO, HIGH);
            digitalWrite(LED_VERDE, HIGH);
            delay(100);
            digitalWrite(LED_VERMELHO, LOW);
            digitalWrite(LED_VERDE, LOW);
            delay(100);
        }
        tela_desliga(200);
        //delay(300);
        //lcd.setBacklight(LOW);
        break;
    case A03:
        buzzer_beep(1);
        //lcd.setCursor(0,0);
        tela_imprime(0,"Seu tempo acabou!");
        Serial.println("Seu tempo acabou!");
        digitalWrite(LED_VERMELHO, HIGH);
        delay(300);
        digitalWrite(LED_VERMELHO, LOW);
        //com_notificar("Alarme desacionado");
        tmr_iniciar(false);
        //delay(300);
        //lcd.setBacklight(LOW);
        tela_desliga(400);
        break;
    case A04:
        buzzer_erro(1);
        //lcd.setCursor(0,0);
        tela_imprime(0,"Senha incorreta");
        Serial.println("Senha incorreta");
        digitalWrite(LED_VERMELHO, HIGH);
        delay(300);
        digitalWrite(LED_VERMELHO, LOW);
        //com_notificar("Alarme desacionado");
        tmr_iniciar(false);
        //delay(300);
        //lcd.setBacklight(LOW);
        tela_desliga(200);
        break;
    case A05:
        Serial.println("Sistema em uso");
        digitalWrite(LED_VERMELHO, HIGH);
        delay(300);
        digitalWrite(LED_VERMELHO, LOW);
        //tmr_iniciar(true);
        //tmr_iniciar(false);
        break;
    case A06:
        Serial.println("Atualiza display");
        ///sne_acionar(true);
        //com_notificar("Invasao");
        tmr_iniciar(false);
        break;
    case A07:
        Serial.println("Porta Aberta");
        digitalWrite(LED_VERDE, HIGH);
        delay(300);
        digitalWrite(LED_VERDE, LOW);
        //com_notificar("Alarme desacionado");
        tmr_iniciar(false);
        //sne_acionar(false);
        break;
    case A08:
        Serial.println("Porta Fechada");
        digitalWrite(LED_VERDE, HIGH);
        delay(300);
        digitalWrite(LED_VERDE, LOW);
        ///sne_acionar(true);
        //com_notificar("Invasao");
        tmr_iniciar(false);
        break;
    case A09:
        Serial.println("Porta Aberta");
        digitalWrite(LED_VERDE, HIGH);
        delay(300);
        digitalWrite(LED_VERDE, LOW);
        tmr_iniciar(false);
        //com_notificar("Alarme desacionado");
        //tmr_iniciar(false);
        //sne_acionar(false);
        break;
    } // switch

    return retval;
} // executarAcao






int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS] = {
    {INSERINDO_SENHA, IDLE, IDLE, IDLE, IDLE, IDLE, IDLE, PORTA_ABERTA},
    {INSERINDO_SENHA, PORTA_ABERTA, IDLE, IDLE, INSERINDO_SENHA, INSERINDO_SENHA, INSERINDO_SENHA,INSERINDO_SENHA},
    {PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, IDLE, PORTA_ABERTA}
};

int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS] = {
    {A01, NENHUMA_ACAO, NENHUMA_ACAO, NENHUMA_ACAO, NENHUMA_ACAO, NENHUMA_ACAO, NENHUMA_ACAO, A09},
    {NENHUMA_ACAO, A02, A03, A04, A05, A06, NENHUMA_ACAO, NENHUMA_ACAO},
    {A07, NENHUMA_ACAO, NENHUMA_ACAO, NENHUMA_ACAO, NENHUMA_ACAO, NENHUMA_ACAO, A08, NENHUMA_ACAO}
};




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

/************************************************************************
 obterEvento
 Obtem um evento, que pode ser da IHM ou do alarme
 Parametros de entrada: nenhum
 Retorno: codigo do evento
*************************************************************************/
char* teclas;



int decodificarRequisicao()
{
    if (teclas[0] == '*' && !sessaoAberta)
    {
        teclas[0]='0';
        teclas[1]='0';
        teclas[2]='0';
        //Serial.println("Requisicao");
        sessaoAberta=true;
        return true;
    }
    return false;
}//decodificarRequisicao

int decodificarSenha_Valida()
{
    if (teclas[2] == '#' && teclas[1] == '1')
    {
        sessaoAberta=false;
        teclas[0]='0';
        teclas[1]='0';
        teclas[2]='0';
        return true;
    }
    return false;
}//decodificarSenha_Valida

int decodificarTimeout()
{    
    if(tmr_timeout()){
        sessaoAberta=false;
        return true;
    }
    return false;
}

int decodificarSenha_Invalida()
{
    if (teclas[2] == '#' && teclas[1] != '1')
    {
        teclas[0]='0';
        teclas[1]='0';
        teclas[2]='0';
        sessaoAberta=false;
        return true;
    }
    return false;
}//decodificarSenha_Invalida

int decodificarOutra_Requisicao()
{
    if (teclas[0] == '*')
    {
        teclas[0]='0';
        teclas[1]='0';
        teclas[2]='0';
        //Serial.println("Outra_Requisicao");
        return true;
    }
    return false;
}//decodificarOutra_Requisicao

int decodificarBotao_Senha()
{
    if (teclas[3] == '*')
    {
        teclas[0]='0';
        teclas[1]='0';
        teclas[2]='0';
        return true;
    }
    return false;
}//decodificarBotao_Senha

int decodificarPorta_Fechada()
{  
    return digitalRead(PORTA);
}//decodificarPorta_Fechada

int decodificarBotao_Interno()
{
    if(analogRead(BOTAO)>800){
        sessaoAberta=false;
        return true;
    }
    return false;
    
    //return analogRead(BOTAO)>800 ? true : false;
}//decodificarBotao_Interno



int obterEvento()
{
  int retval = NENHUM_EVENTO;

  //porta=digitalRead(PORTA);
  //Serial.println(digitalRead(PORTA));
  //Serial.println(analogRead(BOTAO));
  
    


  if (1){
  teclas = ihm_obterTeclas();
  //porta = ihm_verificarPorta();
  if (decodificarBotao_Interno())
    return BOTAO_INTERNO;
  if (decodificarRequisicao())
    //porta=digitalRead(PORTA);
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
  }
    return retval;
 

} // obterEvento






/************************************************************************
 Main
 Loop principal de controle que executa a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/

void setup() {
  Serial.begin(9600);

  ///Testes
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PORTA, INPUT);
  pinMode(BOTAO, INPUT);
  //lcd.init();
  tela_init();
  
  
  ///Testes

  //iniciaSistema();
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
