#include <Arduino.h>
#include <Keypad.h>
#include "definicoes_sistema.h"
#include "ihm.h"



const byte ROWS = 4;  // Quatro linhas por...
const byte COLS = 3; //  Quatro colunas.

// Define o Keypad (mapa do circuito do teclado).
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Conecta o teclado matricial em linha 0, linha 1, linha 2, linha 3 e linha 4...
//dos pinos do arduino.
byte rowPins[ROWS] = { 10, 9, 0, 7 };

// Conecta o teclado matricial em coluna 0, coluna 1, coluna 2, coluna 3 e...
//coluna 4 do arduino.
byte colPins[COLS] = { 6, 5, 4};

// Cria um objto Keypad.
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int read_count =0;






/************************
 ihm_exibirMsg
 Exibe mensagem no display
 entradas
   texto : texto a ser validado como senha
 saidas
   nenhuma
*************************/
void ihm_exibirMsg(char* texto)
{
    Serial.print("Mensagem para display: ");
    Serial.println(texto);
}

/************************
 ihm_obterTecla
 Obtem tecla do teclado
 entradas
   nenhuma
 saidas
   teclas lidas do teclado
*************************/
char buf[2];
char buuf[2];
char* ihm_obterTeclas()
 {
//   // Serial.print("obter teclas:");
//   int read_count = 0;
  
  // check for input
  // if (Serial.available() > 0) {
  //   // read the incoming bytes:
  //   read_count = Serial.readBytesUntil('\n',buuf, sizeof(buuf)/sizeof(buuf[0]) - 1);
  // }
  
  // buuf[read_count] = '\0';
  // if(read_count > 0) {
  // 	Serial.println(buuf);
  // }
  
//   return buf;
// }
// {
//   // check for input
//   char keypressed = kpd.getKey();
//   if (keypressed != NO_KEY) {
//   	if(keypressed != 'A' && 
//        keypressed != 'B' && 
//        keypressed != 'C' && 
//        keypressed != 'D') {
//       buf[read_count++] = keypressed;
//       Serial.print(buf[read_count-1]);
//     }
//     else {
//       buf[read_count++] = keypressed + 32;
//       Serial.print(buf[read_count-1]);
//       Serial.print('\n');
//       read_count = 0;
//       return buf;
//     }
//   }
  
//   buf[read_count] = '\0';
//   return buf;
// }

//{
  // check for input
  char key = kpd.getKey();
  if (key != NO_KEY) {
  	
      buf[0] = key;
      Serial.println(key);
      return buf;
  }
  buf[0]=-1;
  return buf;
}


// {
//   // Serial.print("obter teclas:");
//   int read_count = 0;
  
//   // check for input
//   if (Serial.available() > 0) {
//     // read the incoming bytes:
//     read_count = Serial.readBytesUntil('\n',buf, sizeof(buf)/sizeof(buf[0]) - 1);
//   }
  
//   buf[read_count] = '\0';
//   if(read_count > 0) {
//   	Serial.println(buf);
//   }
  
//   return buf;
// }