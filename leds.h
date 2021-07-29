#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED



class Led{
  public:
    Led(int pin);
    void ligar();
    void desligar();
  	//void bip();
  	//void acionar(int controle);
    
  private:
    int pin;
};





#endif // LEDS_H_INCLUDED
