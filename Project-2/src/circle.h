#include "libs.h"

#ifndef circle_h
#define circle_h

//build circle ira criar e inicializar uma struct pros circulos
void* build_circle(int i, double x, double y, double r, char* corb, char* corp);
//
void circle_hitted (void* aux);
void circle_damaged (void* aux, double damage);
int get_circle_hp(void* adress);
double get_circle_protect(void* adress);
// as funções get, retornam o valor das informação pedida
int get_circle_i(void* adress);
double get_circle_x(void* adress);
double get_circle_y(void* adress);
double get_circle_r(void* adress);
char* get_circle_corp(void* adress);
char* get_circle_corb(void* adress);

// a função free, libera o circulo
void free_circle(void* aux);
// a função print, printa as informações do circulo
void print_circle(void* aux);

#endif