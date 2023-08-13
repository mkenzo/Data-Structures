#include "libs.h"

#ifndef text_h
#define text_h

//build line ira criar e inicializar uma struct pros textos
void* build_text(int i, double x, double y, char* corb, char* corp, char a, char* txto);
//
void text_hitted (void* aux);
void text_damaged (void* aux, double damage);
int get_text_hp(void* adress);
double get_text_protect(void* adress);
// as funções get, retornam o valor das informação pedida
int get_text_i(void* adress);
double get_text_x(void* adress);
double get_text_y(void* adress);
char* get_text_corb(void* adress);
char* get_text_corp(void* adress);
char get_text_a(void* adress);
char* get_text_txto(void* adress);
// a função free, libera o texto
void free_text(void* aux);
// a função print, printa as informações do texto
void print_text(void* aux);

#endif
