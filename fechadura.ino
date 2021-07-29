#include "definicoes_sistema.h"
//#include "comunicacao.h"

#include "ihm.h"
#include "senhas.h"
#include "timer.h"
#include "buzzer.h"
#include "display.h"
#include "leds.h"
//#include "informa.h"
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
// ComunicacaoSerial com;
// SireneBuzzer sne;
// InterfaceHomemMaquinaKeypad ihm;
// SenhasFixa sha;
// TimerInterno tmr;
// PassiveInfraredSensor pir;


/***********************************************************************
 Estaticos
 ***********************************************************************/
  int codigoEvento = NENHUM_EVENTO;
  int eventoInterno = NENHUM_EVENTO;
  int estado = ESPERA;
  int codigoAcao;

  int codigoAcao_tmp=-2;
  int estado_tmp=-2;
  int codigoEvento_tmp=-2;
  int porta_tmp=0;
  //int porta=1;

  int m=0;
  int u_tmp=0;
  


  int sessaoAberta = false;
 
#define TEMPO 200

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
        tela_imprime(0,"Digite a senha: ");        
        tmr_iniciar(true);
        tela_imprime(1,"     "); 
        break;
    case A02:
        informa_sucesso(2);
        tmr_iniciar(false);
        Serial.println("Abrindo a porta...");
        tela_limpa();
        tela_imprime(0,"   Bem vindo, ");
        tela_imprime(1,usuario[u_tmp][0]);
        Serial.println(usuario[u_tmp][0]);
        simula_porta();
        tela_desliga(1000);
        break;
    case A03:
        informa_timeout(1);
        tela_imprime(0,"Seu tempo acabou!");
        Serial.println("Seu tempo acabou!");
        tmr_iniciar(false);
        tela_desliga(800);
        break;
    case A04:
        informa_erro(1);
        tela_imprime(0,"Senha incorreta");
        Serial.println("Senha incorreta");
        tmr_iniciar(false);
        tela_desliga(800);
        break;
    case A05:
        tela_imprime(0,"Sistema em uso");
        Serial.println("Sistema em uso");
        informa_timeout(1);
        break;
    case A06:
        Serial.println("Atualiza display");
        tela_imprime(2,"*");
        tmr_iniciar(true);
        break;
    case A07:
        Serial.println("Porta está Aberta");
        informa_inicio(1);
        tmr_iniciar(false);
        break;
    case A08:
        Serial.println("Porta foi Fechada");
        informa_inicio(1);
        tmr_iniciar(false);
        break;
    case A09:
        Serial.println("Abrir porta pelo botão interno");
        informa_inicio(1);
        simula_porta();
        tmr_iniciar(false);
        break;
    } // switch

    return retval;
} // executarAcao






int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS] = {
    {INSERINDO_SENHA, ESPERA, ESPERA, ESPERA, ESPERA, ESPERA, ESPERA, PORTA_ABERTA},
    {INSERINDO_SENHA, PORTA_ABERTA, ESPERA, ESPERA, INSERINDO_SENHA, INSERINDO_SENHA, INSERINDO_SENHA,INSERINDO_SENHA},
    {PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, PORTA_ABERTA, ESPERA, PORTA_ABERTA}
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

char pw[6];
char pwi[]={'1','2','3','4','5','6'};
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
    if(tmr_timeout()){
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
    if (sessaoAberta && (teclas[0]>='0' && teclas[0]<='9')) //&& (teclas[0]>='0' && teclas[0]<='9')
    {
        pw[m++]=teclas[0];
        teclas[0]=' ';
        return true;
    }
    return false;
}//decodificarBotao_Senha

int decodificarPorta_Fechada()
{  
    if(analogRead(PORTA_PIN)>800){
        return true;
    }
    return false;
}//decodificarPorta_Fechada

int decodificarBotao_Interno()
{
    if(analogRead(BOTAO)>800){
        sessaoAberta=false;
        return true;
    }
    return false;
}//decodificarBotao_Interno



int obterEvento()
{
  int retval = NENHUM_EVENTO;
  char ps[6];

  
  teclas = ihm_obterTeclas();

  //porta=digitalRead(PORTA);
  //Serial.println(digitalRead(PORTA));
  //Serial.println(analogRead(BOTAO));

    //pw[0]=teclas[0];
    //Serial.println("Password");
    //pw[m++]= '\0';
    //pw={'5','2','\0'} ;
    //ps[0]='1';
    //ps[1]='1';
    //ps[2]='1';
    //ps[3]='\0';

    
    //Serial.println(pw[0]);
    //sprintf(message, "%c%c%c%c%c%c%c%c", BYTE_TO_BINARY(k)); 
    //Serial.println(ps);
    //Serial.println("Teste");
    //Serial.println(teclas[0]);
    //Serial.println("Novo Teste");
    //Serial.println(teclas);
  
    


  if (1){
  
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

  ///Testes
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PORTA_PIN, INPUT);
  pinMode(BOTAO, INPUT);
  //web_setup();
  //lcd.init();
  tela_init();
  //porta_init();
  
  entrada.init();
  
  
  
  ///Testes

  //iniciaSistema();
  Serial.println("Sistema iniciado");
} // setup

void loop() {

//web_loop();
//   char key = kpd.getKey();
//   if(key)  // Checa se um botão foi pressionado.
//   {Serial.println(key);
//   }
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
