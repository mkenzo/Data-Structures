#include "libs.h"

#ifndef figure_h
#define figure_h

void* create_figure(char type, Info info);

char get_type(void* adress);

void* get_info(void* adress);

#endif