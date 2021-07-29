#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED



class Led{
  public:
    Led(int pin);
    void init();
    void ligar();
    void desligar();

  private:
    int pin;
};





#endif // LEDS_H_INCLUDED
