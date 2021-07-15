#ifndef SIRENE_H_INCLUDED
#define SIRENE_H_INCLUDED


/************************
 sne_bip
 Aciona momentaneamente a sirene
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
extern void sne_bip();


/************************
 sne_acionar
 Aciona ou desaciona a sirene
 entradas
   controle: TRUE:ligar FALSE:desligar
 saidas
   nenhuma
*************************/
extern void sne_acionar(int controle);

#endif // SIRENE_H_INCLUDED
