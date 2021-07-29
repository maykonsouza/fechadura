#ifndef BUZZER_H_INCLUDED
#define BUZZER_H_INCLUDED


class Buzzer{
  public:
    Buzzer(int pin);
    void init();
    void sucesso();
    void erro();
    void desligar();
    
  private:
    int pin;
};




#endif // BUZZER_H_INCLUDED
