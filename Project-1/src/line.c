#include "line.h"

typedef struct line{
    char cor[100];
    int i, hp;
    double x1, y1, x2, y2, protect;
    char type;
}line;

void set_line_i(void* aux, int i) {
    line* l = aux;
    l->i = i;
}

void set_line_x1(void* aux, double x1) {
    line* l = aux;
    l->x1 = x1;
}

void set_line_y1(void* aux, double y1) {
    line* l = aux;
    l->y1 = y1;
}

void set_line_x2(void* aux, double x2) {
    line* l = aux;
    l->x2 = x2;
}

void set_line_y2(void* aux, double y2) {
    line* l = aux;
    l->y2 = y2;
}

void set_line_cor(void* aux, char* cor) {
    line* l = aux;
    strcpy(l->cor, cor);
}

void* build_line(int i, double x1, double y1, double x2, double y2, char* cor) {
    line* l = calloc(1, sizeof(line));

    set_line_i(l, i);
    set_line_x1(l, x1);
    set_line_y1(l, y1);
    set_line_x2(l, x2);
    set_line_y2(l, y2);
    set_line_cor(l, cor);
    l->hp = 1;
    l->protect = 50.0;
    l->type = 'l';
    return l;
}

void line_hitted (void* aux) {
    line* l = aux;
    l->hp--;
}

void line_damaged (void* aux, double damage) {
    line* l = aux;
    l->protect = l->protect - damage;
}

int get_line_hp(void* adress){
    line* aux = adress;
    return aux -> hp;
}

double get_line_protect(void* adress){
    line* aux = adress;
    return aux -> protect;
}

int get_line_i(void* adress){
    line* aux = adress;
    return aux -> i;
}

double get_line_x1(void* adress){
    line* aux = adress;
    return aux -> x1;
}

double get_line_y1(void* adress){
    line* aux = adress;
    return aux -> y1;
}

double get_line_x2(void* adress){
    line* aux = adress;
    return aux -> x2;
}

double get_line_y2(void* adress){
    line* aux = adress;
    return aux -> y2;
}

char* get_line_cor(void* adress){
    line* aux = adress;
    return aux -> cor;
}

void free_line(void* aux) {
    line* l = aux;
    free(l->cor);
    free(l);
}

void print_line(void* aux) {
    line* l = aux;
    printf("line: %d\n", l->i);
    printf("x1: %f\n", l->x1);
    printf("y1: %f\n", l->y1);
    printf("x2: %f\n", l->x2);
    printf("y2: %f\n", l->y2);
    printf("cor: %s\n", l->cor);
    puts("======================");
}
