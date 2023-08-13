#include "libs.h"

#ifndef flags_h
#define flags_h

/*
    Este modulo prove funcoes para checagem dos parâmetros opcionais informados.
    Basicamente, exitem 2 tipos de funcoes:
        - Definem se o parâmetro foi informado.
        - Informam se o parâmetro foi informado.
*/

/** Retorna flags. As flags definem os parâmetros passados para trabalharmos */
void* create_flags();

/** Retorna verdadeiro se o parâmetro -q (qry) foi informado */
bool get_qry_inserted(void* current_flags);

/** Retorna verdadeiro se o parâmetro -e (BED (diretório-base de entrada)) foi informado */
bool get_bed_inserted(void* current_flags);

/** Atualiza a variável booleana, verdadeiro caso o parâmetro -q foi informado, caso contrário, falso */
void set_qry_inserted(void* current_flags, bool new_value);

/** Atualiza a variável booleana, verdadeiro caso o parâmetro -e foi informado, caso contrário, falso */
void set_bed_inserted(void* current_flags, bool new_value);

#endif