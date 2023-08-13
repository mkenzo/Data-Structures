#include "figure.h"

typedef struct figure{
    void* info;
    char type;
}figure;

void set_type(void* aux, char type) {
    figure* f = aux;
    f->type = type;
}

void set_figure(void* aux, void* info) {
    figure* f = aux;
    f->info = info;
}

void* create_figure(char type, Info info) {
    figure* f = calloc(1, sizeof(figure));

    set_type(f, type);
    set_figure(f, info);
    
    return f;
}

char get_type(void* adress){
    figure* aux = adress;
    return aux -> type;
}

void* get_info(void* adress){
    figure* aux = adress;
    return aux->info;
}