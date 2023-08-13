#include "libs.h"

#ifndef svg_h
#define svg_h

/**
    Este modulo prove a funcao responsavel para criacao do arquivo .svg
    e escrever as figuras nesse mesmo arquivo.
*/

/*cria o arquivo svg e chama as funções insert dependendo das infos da lista recebida*/
void write_on_SVG(list list, path paths);
void printSvg(list list, void *aux);

#endif