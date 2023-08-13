#include "rectangle.h"

typedef struct rectangle{
    char corb[100], corp[100];
    int i, hp;
    double x, y, w, h, protect;
    char type;
}rectangle;

void set_rectangle_i(void* aux, int i) {
    rectangle* r = aux;
    r->i = i;
}

void set_rectangle_x(void* aux, double x) {
    rectangle* r = aux;
    r->x = x;
}

void set_rectangle_y(void* aux, double y) {
    rectangle* r = aux;
    r->y = y;
}

void set_rectangle_w(void* aux, double w) {
    rectangle* r = aux;
    r->w = w;
}

void set_rectangle_h(void* aux, double h) {
    rectangle* r = aux;
    r->h = h;
}

void set_rectangle_corb(void* aux, char* corb) {
    rectangle* r = aux;
    //c->corb = calloc(strlen(corb) + 1, sizeof(char));
    strcpy(r->corb, corb);
}

void set_rectangle_corp(void* aux, char* corp) {
    rectangle* r = aux;
    //c->corp = calloc(strlen(corp) + 1, sizeof(char));
    strcpy(r->corp, corp);
}

void* build_rectangle(int i, double x, double y, double w, double h, char* corb, char* corp) {
    rectangle* r = calloc(1, sizeof(rectangle));

    set_rectangle_i(r, i);
    set_rectangle_x(r, x);
    set_rectangle_y(r, y);
    set_rectangle_w(r, w);
    set_rectangle_h(r, h);
    set_rectangle_corb(r, corb);
    set_rectangle_corp(r, corp);
    r->type = 'r';
    r->hp = 3;
    r->protect = 60.0;
    return r;
}

void rectangle_hitted (void* aux) {
    rectangle* r = aux;
    r->hp--;
}

void rectangle_damaged (void* aux, double damage) {
    rectangle* r = aux;
    r->protect = r->protect - damage;
}

int get_rectangle_hp(void* adress){
    rectangle* aux = adress;
    return aux -> hp;
}

double get_rectangle_protect(void* adress){
    rectangle* aux = adress;
    return aux -> protect;
}

int get_rectangle_i(void* adress){
    rectangle* aux = adress;
    return aux -> i;
}

double get_rectangle_x(void* adress){
    rectangle* aux = adress;
    return aux -> x;
}

double get_rectangle_y(void* adress){
    rectangle* aux = adress;
    return aux -> y;
}

double get_rectangle_w(void* adress){
    rectangle* aux = adress;
    return aux -> w;
}

double get_rectangle_h(void* adress){
    rectangle* aux = adress;
    return aux -> h;
}

char* get_rectangle_corp(void* adress){
    rectangle* aux = adress;
    return aux -> corp;
}

char* get_rectangle_corb(void* adress){
    rectangle* aux = adress;
    return aux -> corb;
}

void free_rectangle(void* aux) {
    rectangle* r = aux;
    free(r);
}

void print_rectangle(void* aux) {
    rectangle* r = aux;
    printf("rectangle: %d\n", r->i);
    printf("x: %f\n", r->x);
    printf("y: %f\n", r->y);
    printf("r: %f\n", r->w);
    printf("r: %f\n", r->h);
    printf("corb: %s\n", r->corb);
    printf("corp: %s\n", r->corp);
    puts("======================");
}
