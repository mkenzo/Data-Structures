#include "svg.h"
#include "geo.h"
#include "system.h"
#include "lista.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "text.h"
#include "figure.h"

void insertCircle(FILE* svg, Info aux){
    fprintf(svg, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\" stroke=\"%s\"/>", get_circle_x(aux), get_circle_y(aux), get_circle_r(aux), get_circle_corp(aux), get_circle_corb(aux));
}

void insertRectangle(FILE* svg, Info aux){
    fprintf(svg, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\"/>", get_rectangle_x(aux), get_rectangle_y(aux), get_rectangle_w(aux), get_rectangle_h(aux), get_rectangle_corp(aux), get_rectangle_corb(aux));
}

void insertLine(FILE* svg, Info aux){
    fprintf(svg, "\n<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>", get_line_x1(aux), get_line_y1(aux), get_line_x2(aux), get_line_y2(aux), get_line_cor(aux));
}

void insertText(FILE* svg, Info aux){
    fprintf(svg, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">%s</text>", get_text_x(aux), get_text_y(aux), get_text_corp(aux), get_text_corb(aux), get_text_txto(aux));
}

void write_on_SVG(list list, path paths){
    char type;
    
    FILE* original_svg = fopen(get_path_SVG(paths), "w+");
    fprintf(original_svg, "<!-- Matheus Kenzo -->\n <svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">");

    for (void* node = getFirst(list); node; node = getNext(list, node)){
        void* node_aux = get(list, node);
        type = get_type(node_aux);
        
        if (type == 'c') {
            insertCircle(original_svg, get_info(node_aux));
        } else if (type == 'r') {
            insertRectangle(original_svg, get_info(node_aux));
        } else if (type == 'l') {
            insertLine(original_svg, get_info(node_aux));
        } else if (type == 't'){
            insertText(original_svg, get_info(node_aux));
        }
    }
    fprintf(original_svg, "\n</svg>");

    fclose(original_svg);
}

void printSvg(list list, void *aux){
    FILE *original_svg = aux;
    char type;

    for (void* node = getFirst(list); node; node = getNext(list, node)){
        void* node_aux = get(list, node);
        type = get_type(node_aux);
        
        if (type == 'c') {
            insertCircle(original_svg, get_info(node_aux));
        } else if (type == 'r') {
            insertRectangle(original_svg, get_info(node_aux));
        } else if (type == 'l') {
            insertLine(original_svg, get_info(node_aux));
        } else if (type == 't'){
            insertText(original_svg, get_info(node_aux));
        }
    }
}