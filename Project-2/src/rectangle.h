#include "libs.h"

#ifndef rectangle_h
#define rectangle_h

//build rectangle ira criar e inicializar uma struct pras retangulo
void* build_rectangle(int i, double x, double y, double w, double h, char* corb, char* corp);
//
void rectangle_hitted (void* aux);
void rectangle_damaged (void* aux, double damage);
int get_rectangle_hp(void* adress);
double get_rectangle_protect(void* adress);
// as funções get, retornam o valor das informação pedida
int get_rectangle_i(void* adress);
double get_rectangle_x(void* adress);
double get_rectangle_y(void* adress);
double get_rectangle_w(void* adress);
double get_rectangle_h(void* adress);
char* get_rectangle_corb(void* adress);
char* get_rectangle_corp(void* adress);
// a função free, libera a retangulo
void free_rectangle(void* aux);
// a função print, printa as informações da retangulo
void print_rectangle(void* aux);

#endif
