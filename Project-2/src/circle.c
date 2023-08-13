#include "circle.h"

typedef struct circle{
    char corb[100], corp[100];
    int i, hp;
    double x, y, r, protect;
    char type;
}circle;

void set_circle_i(void* aux, int i) {
    circle* c = aux;
    c->i = i;
}

void set_circle_x(void* aux, double x) {
    circle* c = aux;
    c->x = x;
}

void set_circle_y(void* aux, double y) {
    circle* c = aux;
    c->y = y;
}

void set_circle_r(void* aux, double r) {
    circle* c = aux;
    c->r = r;
}

void set_circle_corb(void* aux, char* corb) {
    circle* c = aux;
    //c->corb = calloc(strlen(corb) + 1, sizeof(char));
    strcpy(c->corb, corb);
}

void set_circle_corp(void* aux, char* corp) {
    circle* c = aux;
    //c->corp = calloc(strlen(corp) + 1, sizeof(char));
    strcpy(c->corp, corp);
}

void* build_circle(int i, double x, double y, double r, char* corb, char* corp) {
    circle* c = calloc(1, sizeof(circle));

    set_circle_i(c, i);
    set_circle_x(c, x);
    set_circle_y(c, y);
    set_circle_r(c, r);
    set_circle_corb(c, corb);
    set_circle_corp(c, corp);
    c->type = 'c';
    c->protect = 60.0;
    c->hp = 2;
    return c;
}

void circle_hitted (void* aux) {
    circle* c = aux;
    c->hp--;
}

void circle_damaged (void* aux, double damage) {
    circle* c = aux;
    c->protect = c->protect - damage;
}

int get_circle_hp(void* adress){
    circle* aux = adress;
    return aux -> hp;
}

double get_circle_protect(void* adress){
    circle* aux = adress;
    return aux -> protect;
}

int get_circle_i(void* adress){
    circle* aux = adress;
    return aux -> i;
}

double get_circle_x(void* adress){
    circle* aux = adress;
    return aux -> x;
}

double get_circle_y(void* adress){
    circle* aux = adress;
    return aux -> y;
}

double get_circle_r(void* adress){
    circle* aux = adress;
    return aux -> r;
}

char* get_circle_corp(void* adress){
    circle* aux = adress;
    return aux -> corp;
}

char* get_circle_corb(void* adress){
    circle* aux = adress;
    return aux -> corb;
}

void free_circle(void* aux) {
    circle* c = aux;
    free(c);
}

void print_circle(void* aux) {
    circle* c = aux;
    printf("Circle: %d\n", c->i);
    printf("x: %f\n", c->x);
    printf("y: %f\n", c->y);
    printf("r: %f\n", c->r);
    printf("corb: %s\n", c->corb);
    printf("corp: %s\n", c->corp);
    puts("======================");
}
