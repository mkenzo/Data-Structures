#include "libs.h"

#ifndef line_h
#define line_h

//build line ira criar e inicializar uma struct pras linhas
void* build_line(int i, double x1, double y1, double x2, double y2, char* cor);
//
void line_hitted (void* aux);
void line_damaged (void* aux, double damage);
int get_line_hp(void* adress);
double get_line_protect(void* adress);
// as funções get, retornam o valor das informação pedida
int get_line_i(void* adress);
double get_line_x1(void* adress);
double get_line_y1(void* adress);
double get_line_x2(void* adress);
double get_line_y2(void* adress);
char* get_line_cor(void* adress);
// a função free, libera a linha
void free_line(void* aux);
// a função print, printa as informações da linha
void print_line(void* aux);

#endif
