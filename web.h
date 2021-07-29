#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

/************************
 sha_validar
 Verifica se senha esta cadastrada
 entradas
   texto : texto a ser validado como senha
 saidas
   TRUE:senha valida
   FALSE:senha invalida
*************************/
extern void web_setup();
extern void web_loop();

//extern void sendHttpResponse(WiFiEspClient client)


#endif // WEB_H_INCLUDED
