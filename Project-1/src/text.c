#include "text.h"

typedef struct text{
    char corb[100], corp[100], txto[100], a;
    int i, hp;
    double x, y, protect;
    char type;
}text;

void set_text_i(void* aux, int i) {
    text* t = aux;
    t->i = i;
}

void set_text_x(void* aux, double x) {
    text* t = aux;
    t->x = x;
}

void set_text_y(void* aux, double y) {
    text* t = aux;
    t->y = y;
}

void set_text_corb(void* aux, char* corb) {
    text* t = aux;
    strcpy(t->corb, corb);
}

void set_text_corp(void* aux, char* corp) {
    text* t = aux;
    strcpy(t->corp, corp);
}

void set_text_a(void* aux, char a) {
    text* t = aux;
    t->a = a;
}

void set_text_txto(void* aux, char* txto) {
    text* t = aux;
    strcpy(t->txto, txto);
}

void* build_text(int i, double x, double y, char* corb, char* corp, char a, char* txto) {
    text* t = calloc(1, sizeof(text));

    set_text_i(t, i);
    set_text_x(t, x);
    set_text_y(t, y);
    set_text_corb(t, corb);
    set_text_corp(t, corp);
    set_text_a(t, a);
    set_text_txto(t, txto);
    t->type = 't';
    t->protect = 5.0;
    t->hp = 1;
    return t;
}

void text_hitted (void* aux) {
    text* t = aux;
    t->hp--;
}

void text_damaged (void* aux, double damage) {
    text* t = aux;
    t->protect = t->protect - damage;
}

int get_text_hp(void* adress){
    text* aux = adress;
    return aux -> hp;
}

double get_text_protect(void* adress){
    text* aux = adress;
    return aux -> protect;
}

int get_text_i(void* adress){
    text* aux = adress;
    return aux -> i;
}

double get_text_x(void* adress){
    text* aux = adress;
    return aux -> x;
}

double get_text_y(void* adress){
    text* aux = adress;
    return aux -> y;
}

char* get_text_corp(void* adress){
    text* aux = adress;
    return aux -> corp;
}

char* get_text_corb(void* adress){
    text* aux = adress;
    return aux -> corb;
}

char get_text_a(void* adress){
    text* aux = adress;
    return aux -> a;
}

char* get_text_txto(void* adress){
    text* aux = adress;
    return aux -> txto;
}

void free_text(void* aux) {
    text* t = aux;
    free(t->corb);
    free(t->corp);
    free(t->txto);

    free(t);
}

void print_text(void* aux) {
    text* t = aux;
    printf("text: %d\n", t->i);
    printf("x: %f\n", t->x);
    printf("y: %f\n", t->y);
    printf("corb: %s\n", t->corb);
    printf("corp: %s\n", t->corp);
    printf("a: %c\n", t->a);
    printf("txto: %s\n", t->txto);
    puts("======================");
}
