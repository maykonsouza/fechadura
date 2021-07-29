#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED



class Display{
  public:
    Display();
    void init();
    void imprimir(int posicao, char mensagem[15]);
    void desligar(int tempo);
    void limpa();
  private:

};


#endif // DISPLAY_H_INCLUDED
