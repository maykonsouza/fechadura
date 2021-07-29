#ifndef PORTA_H_INCLUDED
#define PORTA_H_INCLUDED



class Porta{
  public:
    Porta(int pin);
    void init();
    void abrir();
    void fechar();
    
  private:
    int pin;
    int pp = 0;
};



/************************
 SERVO_beep
 Aciona o SERVO em modo beep
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
extern void porta_init(void);

/************************
 SERVO_erro
 Aciona o SERVO em modo beep
 entradas
   k: Quanridade de beeps
 saidas
   nenhuma
*************************/
extern void porta_abrir(void);



#endif // PORTA_H_INCLUDED
