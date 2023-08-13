#include "qry.h"
#include "lista.h"
#include "cpt.h"
#include "system.h"
#include "svg.h"
#include "figure.h"
#include "circle.h"
#include "rectangle.h"
#include "text.h"
#include "line.h"

double distanceBetweenTwoPoint (double x1, double y1, double x2, double y2) {
    double distance = 0;
    if (x1 > x2 && y1 < y2) {
        distance = sqrt(pow(x1 - x2, 2) + pow(y2 - y1, 2));
    } else if (x1 < x2 && y1 <y2) {
        distance = sqrt (pow(x2 - x1, 2) + pow(y2 - y1, 2));
    } else if (x1 < x2 && y1 > y2) {
        distance = sqrt (pow(x2 - x1, 2) + pow(y1 - y2, 2));
    } else if (x1 > x2 && y1 > y2) {
        distance = sqrt (pow(x1 - x2, 2) + pow(y1 -y2, 2));
    }
    return distance;
}

void destroyBoat (list lista, list selected, Item figure, char type, Posic p, char whichOne) {
    for (void* node = getFirst(lista); node; node = getNext(lista, node)) {
        void* node_aux = get(lista, node);
        void* element = get_info(node_aux);
        char typeL = get_type(node_aux);

        if (typeL == type && typeL == 'c') {
            if (get_circle_i(element) == get_circle_i(figure)) {
                if (whichOne == 'a')
                    remover(selected, p);
                remover(lista, node);
                
            }
        } else if (typeL == type && typeL == 'r') {
            if (get_rectangle_i(element) == get_rectangle_i(figure)) {
                if (whichOne == 'a')
                    remover(selected, p);
                remover(lista, node);
            }
        } else if (typeL == type && typeL == 'l') {
            if (get_line_i(element) == get_line_i(figure)) {
                if (whichOne == 'a')
                    remover(selected, p); 
                remover(lista, node);
            }
        } else if (typeL == type && typeL == 't') {
            if (get_line_i(element) == get_line_i(figure)) {
                if (whichOne == 'a')
                    remover(selected, p);
                remover(lista, node);
            }
        }
    }
}

void* chooseBoat (list selected, int j, int k, int naucap[]) {
    bool found;
    char type;
    Item item;

    for (void* node = getFirst(selected); node; node = getNext(selected, node)) {
        void* node_aux = get(selected, node);
        void* element = get_info(node_aux);
        type = get_type(node_aux);

        if (type == 'c') {
            if (get_circle_i(element) == naucap[j])
                found = true;
        } else if (type == 'r') {
            if (get_rectangle_i(element) == naucap[j])
                found = true;
        } else if (type == 'l') {
            if (get_line_i(element) == naucap[j])
                found = true;
        } else if (type == 't') {
            if (get_text_i(element) == naucap[j])
                found = true;
        }

        if (found) {
            if (k > 0) {
                for (int i = 0; i > k; i++) {
                    item = getNext(selected, node);
                    if (item == NULL)
                        item = getFirst(selected);
            }
            } else {
                for (int i = 0; i > k; i--) {
                    item = getPrevious(selected, node);
                    if (item == NULL)
                        item = getLast(selected);
                }
            }
            return item;
        }
    }

    return NULL;
}

bool mineInDisplacement (list list, void* figure, char t, char direction, double dx, double dy, FILE* txt_results, FILE* modifiedSVG) {
    char typeFigure = t;
    char type;
    bool found = false;
    bool remove = false;
    bool null = false;
    void* aux_remove;

    if (typeFigure == 'c') {
        for (void* node = getFirst(list); node; node = getNext(list, node)) {
            void* node_aux = get(list, node);
            void* element = get_info(node_aux);
            type = get_type(node_aux);

            if (aux_remove != NULL) {
                remover(list, aux_remove);
                aux_remove = NULL;
            }
            
            if (type == 't' && strcmp(get_text_txto(element), "#") == 0) {
                if (direction == 'r') {
                    if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) + get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) - get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (get_circle_x(figure) <= get_text_x(element) && (get_circle_x(figure) + dx) >= get_text_x(element) && get_text_y(element) <= (get_circle_y(figure) + get_circle_r(figure)) && get_text_y(element) >= (get_circle_y(figure) - get_circle_r(figure))) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) + dx, get_circle_y(figure) + get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) + dx + get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) + dx, get_circle_y(figure) - get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else {
                        found = false;
                    }
                } else if (direction == 'l') {
                    if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) + get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) + get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) - get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (get_text_x(element) <= (get_circle_x(figure) - dx) && get_circle_x(figure) >= get_text_x(element) && get_text_y(element) <= (get_circle_y(figure) + get_circle_r(figure)) && get_text_y(element) >= (get_circle_y(figure) - get_circle_r(figure))) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - dx, get_circle_y(figure) + get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - dx - get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - dx, get_circle_y(figure) - get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else {
                        found = false;
                    }
                } else if (direction == 'd') {
                    if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) + get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) + get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (get_text_x(element) <= (get_circle_x(figure) + get_circle_r(figure)) && (get_circle_x(figure) - get_circle_r(figure)) >= get_text_x(element) && get_text_y(element) >= (get_circle_y(figure) - dy) && get_text_y(element) <= get_circle_y(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - get_circle_r(figure), get_circle_y(figure) + dy) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) - dy - get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - get_circle_r(figure), get_circle_y(figure) - dy) <= get_circle_r(figure)) {
                        found = true;
                    } else {
                        found = false;
                    }
                } else if (direction == 'u') {
                    if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) + get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) - get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - get_circle_r(figure), get_circle_y(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (get_text_x(element) <= (get_circle_x(figure) + get_circle_r(figure)) && (get_circle_x(figure) - get_circle_r(figure)) <= get_text_x(element) && get_text_y(element) <= (get_circle_y(figure) + dy) && get_text_y(element) >= get_circle_y(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) - get_circle_r(figure), get_circle_y(figure) + dy) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure), get_circle_y(figure) + dy + get_circle_r(figure)) <= get_circle_r(figure)) {
                        found = true;
                    } else if (distanceBetweenTwoPoint(get_text_x(element), get_text_y(element), get_circle_x(figure) + get_circle_r(figure), get_circle_y(figure) + dy) <= get_circle_r(figure)) {
                        found = true;
                    } else {
                        found = false;
                    }
                }

                if (found) {
                    fprintf(txt_results, "\nEmbarcação afundada: %d", get_circle_i(figure));
                    fprintf(txt_results, "\nMina destruida: id:%d, x:%lf, y:%lf", get_text_i(element), get_text_x(element), get_text_y(element));
                    fprintf(modifiedSVG, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">\"&\"</text>", get_text_x(element), get_text_y(element), get_text_corp(element), get_text_corb(element));
                    aux_remove = node;
                }

                if (getNext(list, node) == NULL)
                null = true;

                if ((null == true) & (remove == true))
                return true;
            }
        }
    } else if (typeFigure == 'r') {
        for (void* node = getFirst(list); node; node = getNext(list, node)) {
            void* node_aux = get(list, node);
            void* element = get_info(node_aux);
            type = get_type(node_aux);

            if (aux_remove != NULL) {
                remover(list, aux_remove);
                aux_remove = NULL;
            }
            
            if (type == 't' && strcmp(get_text_txto(element), "#") == 0) {
                if (direction == 'r') {
                    if (get_rectangle_x(figure) <= get_text_x(element) && get_text_x(element) <= (get_rectangle_x(figure) + get_rectangle_w(figure) + dx) && get_rectangle_y(figure) <= get_text_y(element) && get_text_y(element) <= (get_rectangle_y(figure) + get_rectangle_h(figure))) {
                        found = true;
                    } else{
                        found = false;
                    }
                } else if (direction == 'l') {
                    if ((get_rectangle_x(figure) - dx) <= get_text_x(element) && get_text_x(element) <= (get_rectangle_x(figure) + get_rectangle_w(figure)) && get_rectangle_y(figure) <= get_text_y(element) && get_text_y(element) <= (get_rectangle_y(figure) + get_rectangle_h(figure))) {
                        found = true;
                    } else{
                        found = false;
                    }
                } else if (direction == 'u') {
                    if (get_rectangle_x(figure) <= get_text_x(element) && get_text_x(element) <= (get_rectangle_x(figure) + get_rectangle_w(figure)) && get_rectangle_y(figure) <= get_text_y(element) && get_text_y(element) <= (get_rectangle_y(figure) + get_rectangle_h(figure) + dy)) {
                        found = true;
                    } else{
                        found = false;
                    }
                } else if (direction == 'd') {
                    if (get_rectangle_x(figure) <= get_text_x(element) && get_text_x(element) <= (get_rectangle_x(figure) + get_rectangle_w(figure)) && (get_rectangle_y(figure) + get_rectangle_h(figure)) >= get_text_y(element) && get_text_y(element) >= (get_rectangle_y(figure) - dy)) {
                        found = true;
                    } else{
                        found = false;
                    }
                } else {
                    found = false;
                }
            }

            if(found) {
                fprintf(txt_results, "\nEmbarcação afundada: %d", get_rectangle_i(figure));
                fprintf(txt_results, "\nMina destruida: id:%d, x:%lf, y:%lf", get_text_i(element), get_text_x(element), get_text_y(element));
                fprintf(modifiedSVG, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">\"&\"</text>", get_text_x(element), get_text_y(element), get_text_corp(element), get_text_corb(element));
                aux_remove = node;
            }

            if (getNext(list, node) == NULL)
                null = true;

            if ((null == true) & (remove == true))
                return true;
        }
    } else if (typeFigure == 'l') {
        for (void* node = getFirst(list); node; node = getNext(list, node)) {
            void* node_aux = get(list, node);
            void* element = get_info(node_aux);
            type = get_type(node_aux);

            if (aux_remove != NULL) {
            remover(list, aux_remove);
            aux_remove = NULL;
            }
            
            if (type == 't' && strcmp(get_text_txto(element), "#") == 0) {
                if (direction == 'r') {
                    if (get_line_x1(figure) == get_line_x2(figure)) {
                        if (get_line_y1(figure) > get_line_y2(figure)) {
                            if (get_line_x1(figure) <= get_text_x(element) && get_text_x(element) <= (get_line_x1(figure) + dx) && get_line_y2(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y1(figure))) {
                            found = true;
                            } else{
                            found = false;
                            }
                        } else if (get_line_y2(figure) > get_line_y1(figure)) {
                            if (get_line_x1(figure) <= get_text_x(element) && get_text_x(element) <= (get_line_x1(figure) + dx) && get_line_y1(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y2(figure))) {
                                found = true;
                            } else{
                                found = false;
                            }
                        }
                    } else if (get_line_y1(figure) == get_line_y2(figure)) {
                        if (get_line_x1(figure) < get_line_x2(figure)) {
                            if (get_line_x1(figure) <= get_text_x(element) && get_text_x(element) <= (get_line_x2(figure) + dx) && get_line_y1(figure) == get_text_y(element)) {
                                found = true;
                            } else {
                                found = false;
                            }
                        } else if (get_line_x2(figure) < get_line_x1(figure)) {
                            if (get_line_x2(figure) <= get_text_x(element) && get_text_x(element) <= (get_line_x1(figure) + dx) && get_line_y1(figure) == get_text_y(element)) {
                                found = true;
                            } else {
                                found = false;
                            }
                        }
                    } else if (get_line_y2(figure) > get_line_y1(figure)) {
                        if (get_line_x2(figure) <= get_text_x(element) && get_text_x(element) <= (get_line_x1(figure) + dx && get_line_y1(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y2(figure)))) {
                            found = true;
                        } else{
                            found = false;
                        }
                    } else if (get_line_y2(figure) < get_line_y1(figure)) {
                        if (get_line_x2(figure) <= get_text_x(element) && get_text_x(element) <= (get_line_x2(figure) + dx) && get_line_y2(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y1(figure))) {
                            found = true;
                        } else{
                            found = false;
                        }
                    }
                } else if (direction == 'l') {
                    if (get_line_x1(figure) == get_line_x2(figure)) {
                        if (get_line_y1(figure) > get_line_y2(figure)) {
                            if ((get_line_x1(figure) - dx) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y2(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y1(figure))) {
                            found = true;
                            } else{
                            found = false;
                            }
                        } else if (get_line_y2(figure) > get_line_y1(figure)) {
                            if ((get_line_x1(figure) - dx) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y1(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y2(figure))) {
                                found = true;
                            } else{
                                found = false;
                            }
                        }
                    } else if (get_line_y1(figure) == get_line_y2(figure)) {
                        if (get_line_x1(figure) < get_line_x2(figure)) {
                            if ((get_line_x1(figure) - dx) <= get_text_x(element) && get_text_x(element) <= get_line_x2(figure) && get_line_y1(figure) == get_text_y(element)) {
                                found = true;
                            } else {
                                found = false;
                            }
                        } else if (get_line_x2(figure) < get_line_x1(figure)) {
                            if ((get_line_x2(figure) - dx) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y1(figure) == get_text_y(element)) {
                                found = true;
                            } else {
                                found = false;
                            }
                        }
                    } else if (get_line_y2(figure) > get_line_y1(figure)) {
                        if ((get_line_x1(figure) + dx) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y1(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y2(figure))) {
                            found = true;
                        } else{
                            found = false;
                        }
                    } else if (get_line_y2(figure) < get_line_y1(figure)) {
                        if ((get_line_x2(figure) - dx) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y2(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y1(figure))) {
                            found = true;
                        } else{
                            found = false;
                        }
                    }
                }
            } else if (direction == 'u') {
                if (get_line_x1(figure) == get_line_x2(figure)) {
                    if (get_line_y1(figure) > get_line_y2(figure)) {
                        if (get_line_x1(figure) == get_text_x(element) && (get_line_y1(figure) + dy) >= get_text_y(element) && get_text_y(element) >= (get_line_y2(figure))) {
                        found = true;
                        } else{
                        found = false;
                        }
                    } else if (get_line_y2(figure) > get_line_y1(figure)) {
                        if (get_line_x1(figure) == get_text_x(element) && (get_line_y2(figure) + dy) >= get_text_y(element) && get_text_y(element) >= get_line_y1(figure)) {
                            found = true;
                        } else{
                            found = false;
                        }
                    }
                } else if (get_line_y1(figure) == get_line_y2(figure)) {
                    if (get_line_x1(figure) < get_line_x2(figure)) {
                        if (get_line_x1(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x2(figure) && get_line_y1(figure) <= get_text_y(element) && (get_line_y1(figure) + dy) >= get_text_y(element)) {
                            found = true;
                        } else {
                            found = false;
                        }
                    } else if (get_line_x2(figure) < get_line_x1(figure)) {
                        if (get_line_x2(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y1(figure) <= get_text_y(element) && (get_line_y1(figure) + dy) >= get_text_y(element)) {
                            found = true;
                        } else {
                            found = false;
                        }
                    }
                } else if (get_line_y2(figure) > get_line_y1(figure)) {
                        if (get_line_x1(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x2(figure) && get_line_y1(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y2(figure) + dy)) {
                            found = true;
                        } else{
                            found = false;
                        }
                    } else if (get_line_y2(figure) < get_line_y1(figure)) {
                        if (get_line_x2(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y2(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y1(figure) + dy)) {
                            found = true;
                        } else{
                            found = false;
                        }
                    }
            } else if (direction == 'd') {
                if (get_line_x1(figure) == get_line_x2(figure)) {
                    if (get_line_y1(figure) > get_line_y2(figure)) {
                        if (get_line_x1(figure) == get_text_x(element) && get_line_y1(figure) >= get_text_y(element) && get_text_y(element) >= (get_line_y2(figure) - dy)) {
                        found = true;
                        } else{
                        found = false;
                        }
                    } else if (get_line_y2(figure) > get_line_y1(figure)) {
                        if (get_line_x1(figure) == get_text_x(element) && get_line_y2(figure) >= get_text_y(element) && get_text_y(element) >= (get_line_y1(figure) - dy)) {
                            found = true;
                        } else{
                            found = false;
                        }
                    }
                } else if (get_line_y1(figure) == get_line_y2(figure)) {
                    if (get_line_x1(figure) < get_line_x2(figure)) {
                        if (get_line_x1(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x2(figure) && get_line_y1(figure) >= get_text_y(element) && (get_line_y1(figure) - dy) <= get_text_y(element)) {
                            found = true;
                        } else {
                            found = false;
                        }
                    } else if (get_line_x2(figure) < get_line_x1(figure)) {
                        if (get_line_x2(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y1(figure) >= get_text_y(element) && (get_line_y1(figure) - dy) <= get_text_y(element)) {
                            found = true;
                        } else {
                            found = false;
                        }
                    }
                } else if (get_line_y2(figure) > get_line_y1(figure)) {
                        if (get_line_x1(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x2(figure) && get_line_y1(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y2(figure) - dy)) {
                            found = true;
                        } else{
                            found = false;
                        }
                    } else if (get_line_y2(figure) < get_line_y1(figure)) {
                        if (get_line_x2(figure) <= get_text_x(element) && get_text_x(element) <= get_line_x1(figure) && get_line_y2(figure) <= get_text_y(element) && get_text_y(element) <= (get_line_y1(figure) - dy)) {
                            found = true;
                        } else{
                            found = false;
                        }
                    }
            }

            if (found) {
                fprintf(txt_results, "\nEmbarcação afundada: %d", get_line_i(figure));
                fprintf(txt_results, "\nMina destruida: id:%d, x:%lf, y:%lf", get_text_i(element), get_text_x(element), get_text_y(element));
                fprintf(modifiedSVG, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">\"&\"</text>", get_text_x(element), get_text_y(element), get_text_corp(element), get_text_corb(element));
                aux_remove = node;
            }

            if (getNext(list, node) == NULL)
                null = true;

            if ((null == true) & (remove == true))
                return true;
        }
    } else if (typeFigure == 't') {
        for (void* node = getFirst(list); node; node = getNext(list, node)) {
            void* node_aux = get(list, node);
            void* element = get_info(node_aux);
            type = get_type(node_aux);

            if (aux_remove != NULL) {
            remover(list, aux_remove);
            aux_remove = NULL;
            }
        
            if (direction == 'r') {
                if (get_text_x(element) <= get_text_x(figure) && get_text_x(figure) <= (strlen(get_text_txto(figure)) + dx) && get_text_y(element) == get_text_y(figure)) {
                    found = true;
                } else {
                    found = false;
                }
            } else if (direction == 'l') {
                if ((strlen(get_text_txto(figure))) <= get_text_x(figure) && get_text_x(figure) <= (get_text_x(element) - dx) && get_text_y(element) == get_text_y(figure)) {
                    found = true;
                } else {
                    found = false;
                }
            } else if (direction == 'u') {
                if ((strlen(get_text_txto(figure))) >= get_text_x(element) && get_text_x(element) <= (strlen(get_text_txto(figure))) && get_text_y(element) >= get_text_y(figure) && (get_text_y(figure) + dy) >= get_text_y(element)) {
                    found = true;
                } else {
                    found = false;
                }
            } else if (direction == 'd') {
                if ((strlen(get_text_txto(figure))) >= get_text_x(element) && get_text_x(element) <= (strlen(get_text_txto(figure))) && get_text_y(element) <= get_text_y(figure) && (get_text_y(figure) - dy) <= get_text_y(element)) {
                    found = true;
                } else {
                    found = false;
                }
            }

            if (found) {
                fprintf(txt_results, "\nEmbarcação afundada: %d", get_text_i(figure));
                fprintf(txt_results, "\nMina destruida: id:%d, x:%lf, y:%lf", get_text_i(element), get_text_x(element), get_text_y(element));
                fprintf(modifiedSVG, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">\"&\"</text>", get_text_x(element), get_text_y(element), get_text_corp(element), get_text_corb(element));
                aux_remove = node;
            }

            if (getNext(list, node) == NULL)
                null = true;

            if ((null == true) & (remove == true))
                return true;
        }
    }
}

char WhatFigureIsIt(void* info) {
    char type;

    type = get_type(info);
    return type;
}

bool rectangleInside(double x, double y, void* rectangle) {   
    if (x >= get_rectangle_x(rectangle) && x <= get_rectangle_x(rectangle) + get_rectangle_w(rectangle)) {
        if (y >= get_rectangle_y(rectangle) && y <= get_rectangle_y(rectangle) + get_rectangle_h(rectangle)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool circleInside(double x, double y, void* circle) {
    if (get_circle_x(circle) - get_circle_r(circle) <= x && get_circle_x(circle) + get_circle_r(circle) >= x) {
        if (get_circle_y(circle) - get_circle_r(circle) <= y && get_circle_y(circle) + get_circle_r(circle) >= y) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool lineInside(double x, double y, void* line) {
    if (get_line_x1(line) == x || get_line_x2(line) == x || get_line_y1(line) == y || get_line_y2(line) == y)
        return true;
    else
        return false;
}

bool textInside(double x, double y, void* text) {
    if (get_text_x(text) == x && get_text_y(text) == y)
        return true;
    else
        return false;
}

bool insideIrradiation(double x, double y, double r, void* figure) {
    Item item;
    double distance1, distance2, distance3, distance4;
    char type;

    item = get_info(figure);
    type = get_type(figure);

    if (type == 't') {
        distance1 = distanceBetweenTwoPoint(x, y, get_text_x(item), get_text_y(item));
        if (distance1 <= r)
            return true;
        else
            return false;
    } else if (type == 'l') {
        distance1 = distanceBetweenTwoPoint(x, y, get_line_x1(item), get_line_y1(item));
        distance2 = distanceBetweenTwoPoint(x, y, get_line_x2(item), get_line_y2(item));
        if (distance1 <= r && distance2 <= r) {
            return true;
        }
        else
            return false;
    } else if (type == 'c') {
        distance1 = distanceBetweenTwoPoint(x, y, get_circle_x(item), get_circle_y(item));
        if (distance1 <= r && get_circle_r(item) <= r)
            return true;
        else
            return false;
    } else {
        distance1 = distanceBetweenTwoPoint(x, y, get_rectangle_x(item), get_rectangle_y(item));
        distance2 = distanceBetweenTwoPoint(x, y, get_rectangle_x(item) + get_rectangle_w(item), get_rectangle_y(item));
        distance3 = distanceBetweenTwoPoint(x, y, get_rectangle_x(item), get_rectangle_y(item) + get_rectangle_h(item));
        distance4 = distanceBetweenTwoPoint(x, y, get_rectangle_x(item) + get_rectangle_w(item), get_rectangle_y(item) + get_rectangle_h(item));
        if (distance1 <= r && distance2 <= r && distance3 <= r && distance4 <= r)
            return true;
        else
            return false;
    }
}

void tp(list list, void* info, FILE* svg, FILE* txt_results, double x, double y, score points) {
    void* item;
    void* aux;
    bool found = false;
    char type;

    if (info == NULL)
        return;
    
    aux = get(list, info);
    item = get_info(aux);
    type = get_type(aux);
            
    if (type == 'c') {
        found = circleInside(x, y, item);
    } else if (type == 'r') {
        found = rectangleInside(x, y, item);
    } else if (type == 'l') {
        found = lineInside(x, y, item);
    } else if (type == 't'){
        found = textInside(x, y, item);
    }

    if (found) {
        fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"red\">*</text>", x, y);

        if (type == 'c'){
            if (get_circle_hp(item) == 0) {
                fprintf(txt_results, "\ncirculo destruido!");
                fprintf(txt_results, "\ncirculo, id = %d, x = %lf, y = %lf, raio = %lf, cor preenchimento = %s, cor borda = %s", get_circle_i(item), get_circle_x(item), get_circle_y(item), get_circle_r(item), get_circle_corp(item), get_circle_corb(item));
                remover(list, info);
                addPoints((75/((3.14*get_circle_r(item)*get_circle_r(item))/5)), points);
                addAgress(points);
            } else {
                fprintf(txt_results, "\ncirculo atingido!");
                fprintf(txt_results, "\nnivel de energia: %d, torpedos acertados: %d", get_circle_hp(item), (2 - get_circle_hp(item)));
                fprintf(txt_results, "\ncirculo, id = %d, x = %lf, y = %lf, raio = %lf, cor preenchimento = %s, cor borda = %s", get_circle_i(item), get_circle_x(item), get_circle_y(item), get_circle_r(item), get_circle_corp(item), get_circle_corb(item));
            }
        } else if (type == 'r') {
            if(get_rectangle_hp(item) == 0) {
                fprintf(txt_results, "\nretângulo destruido!");
                fprintf(txt_results, "\nretangulo, id = %d, x = %lf, y = %lf, altura = %lf, largura = %lf, cor preenchimento = %s, cor borda = %s", get_rectangle_i(item), get_rectangle_x(item), get_rectangle_y(item), get_rectangle_w(item), get_rectangle_h(item), get_rectangle_corp(item), get_rectangle_corb(item));
                remover(list, info);
                addPoints((75/((get_rectangle_w(item)*get_rectangle_h(item))/5)), points);
                addAgress(points);
            } else {
                fprintf(txt_results, "\nretângulo atingido!");
                fprintf(txt_results, "\nnivel de energia: %d, torpedos acertados: %d", get_rectangle_hp(item), (3 - get_rectangle_hp(item)));
                fprintf(txt_results, "\nretangulo, id = %d, x = %lf, y = %lf, altura = %lf, largura = %lf, cor preenchimento = %s, cor borda = %s", get_rectangle_i(item), get_rectangle_x(item), get_rectangle_y(item), get_rectangle_w(item), get_rectangle_h(item), get_rectangle_corp(item), get_rectangle_corb(item));
            }
        } else if (type == 't') {
            if (get_text_hp(item) == 0) {
                fprintf(txt_results, "\ntexto destruido!");
                fprintf(txt_results, "\ntexto, id = %d, x = %lf, y = %lf, ancora = %c, cor preenchimento = %s, cor borda = %s, texto = %s", get_text_i(item), get_text_x(item), get_text_y(item), get_text_a(item), get_text_corp(item), get_text_corb(item), get_text_txto(item));
                remover(list, info);
                addPoints(500, points);
                addAgress(points);
            } else {
                fprintf(txt_results, "\ntexto atingido!");
                fprintf(txt_results, "\nnivel de energia: %d, torpedos acertados: %d", get_text_hp(item), (1 - get_text_hp(item)));
                fprintf(txt_results, "\ntexto, id = %d, x = %lf, y = %lf, ancora = %c, cor preenchimento = %s, cor borda = %s, texto = %s", get_text_i(item), get_text_x(item), get_text_y(item), get_text_a(item), get_text_corp(item), get_text_corb(item), get_text_txto(item));
            }
        } else if (type == 'l') {
            if (get_line_hp(item) == 0) {
                fprintf(txt_results, "\nlinha destruida!");
                fprintf(txt_results, "\nlinha, id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, cor = %s", get_line_i(item), get_line_x1(item), get_line_y1(item), get_line_x2(item), get_line_y2(item), get_line_cor(item));
                remover(list, info);
                addPoints(150, points);
                addAgress(points);
            } else {
                fprintf(txt_results, "\nlinha atingida!");
                fprintf(txt_results, "\nnivel de energia: %d, torpedos acertados: %d", get_line_hp(item), (1 - get_line_hp(item)));
                fprintf(txt_results, "\nlinha, id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, cor = %s", get_line_i(item), get_line_x1(item), get_line_y1(item), get_line_x2(item), get_line_y2(item), get_line_cor(item));
            }
        }
        return;
    } else if (getNext(list, info) == NULL){
        fprintf(svg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"grey\">*</text>", x, y);
        fprintf(txt_results, "\nAGUA");
    }

    tp(list, getNext(list, info), svg, txt_results, x, y, points);
}

void tr(list list, void* info, FILE* svg, FILE* txt_results, double x, double y, double dx, double dy, char id[], score points) {
    void* item;
    void* aux;
    int idInt = atoi(id);
    bool found = false;
    char type;

    if (info == NULL)
        return;

    aux = get(list, info);
    item = get_info(aux);
    type = get_type(aux);

    if (type == 'r') {
        found = rectangleInside(x, y, item);
        if (found) {
            idInt++;
            fprintf(svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\"/>", get_rectangle_x(item) + dx, get_rectangle_y(item) + dy, get_rectangle_w(item), get_rectangle_h(item), get_rectangle_corb(item), get_rectangle_corp(item));
            fprintf(txt_results, "\nATINGIDO: retangulo, id = %d\nx, y = %lf, %lf\naltura = %lf\nlargura = %lf\ncor preenchimento = %s\ncor borda = %s\n", get_rectangle_i(item), get_rectangle_x(item), get_rectangle_y(item), get_rectangle_h(item), get_rectangle_w(item), get_rectangle_corp(item), get_rectangle_corb(item));
            fprintf(txt_results, "\nCLONE: retangulo, id = %d\nx, y = %lf, %lf\naltura = %lf\nlargura = %lf\ncor preenchimento = %s\ncor borda = %s\n\n-----------------------\n", idInt, get_rectangle_x(item) + dx, get_rectangle_y(item) + dy, get_rectangle_h(item), get_rectangle_w(item), get_rectangle_corb(item), get_rectangle_corp(item));
            void* new_rectangle = build_rectangle(idInt, get_rectangle_x(item) + dx, get_rectangle_y(item) + dy, get_rectangle_w(item) + dx, get_rectangle_h(item) + dy, get_rectangle_corp(item), get_rectangle_corb(item));
            void* new_figure = create_figure('r', new_rectangle);
            insert(list, new_figure);
            addMaxPoints((90/((get_rectangle_w(item)*get_rectangle_h(item))/5)), points);
        }
    } else if (type == 'c') {
        found = circleInside(x, y, item);
        if (found) {
            idInt++;
            fprintf(svg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\" stroke=\"%s\"/>", get_circle_x(item) + dx, get_circle_y(item) + dy, get_circle_r(item), get_circle_corb(item), get_circle_corp(item));
            fprintf(txt_results, "\nATINGIDO: circulo, id = %d\nx, y = %lf, %lf\nraio = %lf\ncor preenchimento = %s\ncor borda = %s\n", get_circle_i(item), get_circle_x(item), get_circle_y(item), get_circle_r(item), get_circle_corp(item), get_circle_corb(item));
            fprintf(txt_results, "\nCLONE: circulo, id = %d\nx,y = %lf, %lf\nraio = %lf\ncor preenchimento = %s\ncor borda = %s\n\n-----------------------\n", idInt, get_circle_x(item) + dx, get_circle_y(item) + dy, get_circle_r(item), get_circle_corb(item), get_circle_corp(item));
            void* new_circle = build_circle(idInt, get_circle_x(item) + dx, get_circle_y(item) + dy, get_circle_r(item), get_circle_corp(item), get_circle_corb(item));
            void* new_figure = create_figure('c', new_circle);
            insert(list, new_figure);
            addMaxPoints((75/((3.14*get_circle_r(item)*get_circle_r(item))/5)), points);
        }
    }
    else if (type == 'l') {
        found = lineInside(x, y, item);
        if (found) {
            idInt++;
            fprintf(svg, "\n\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>", get_line_x1(item) + dx, get_line_y1(item) + dy, get_line_x2(item) + dx, get_line_y2(item) + dy, get_line_cor(item));
            fprintf(txt_results, "\nATINGIDO: linha, id = %d\nx1, y1 = %lf, %lf\nx2, y2 = %lf, %lf\ncor = %s\n", get_line_i(item), get_line_x1(item), get_line_y1(item), get_line_x2(item), get_line_y2(item), get_line_cor(item));
            fprintf(txt_results, "\nCLONE: linha, id = %d\nx1, y1 = %lf, %lf\nx2, y2 = %lf, %lf\ncor = %s\n\n-----------------------\n", idInt, get_line_x1(item) + dx, get_line_y1(item) + dy, get_line_x2(item) + dx, get_line_y2(item) + dy, get_line_cor(item));
            void* new_line = build_line(idInt, get_line_x1(item),get_line_y1(item), get_line_x2(item), get_line_y2(item), get_line_cor(item));
            void* new_figure = create_figure('l', new_line);
            insert(list, new_figure);
            addMaxPoints(150, points);
        }
    }
    else if (type == 't') {
        found = textInside(x, y, item);
        if (found) {
            idInt++;
            fprintf(svg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">%s</text>", get_text_x(item) + dx, get_text_y(item) + dy, get_text_corb(item), get_text_corp(item), get_text_txto(item));
            fprintf(txt_results, "\nATINGIDO: texto, id = %d\nx, y = %lf, %lf\nancora = %c\ncor preenchimento = %s\ncor borda = %s\ntexto = %s\n", get_text_i(item), get_text_x(item), get_text_y(item), get_text_a(item), get_text_corp(item), get_text_corb(item), get_text_txto(item));
            fprintf(txt_results, "\nCLONE: texto, id = %d\nx, y = %lf, %lf\nancora = %c\ncor preenchimento = %s\ncor borda = %s\ntexto = %s\n\n-----------------------\n", idInt, get_text_x(item) + dx, get_text_y(item) + dy, get_text_a(item), get_text_corb(item), get_text_corp(item), get_text_txto(item));
            void* new_text = build_text(idInt, get_text_x(item), get_text_y(item), get_text_corp(item), get_text_corb(item), get_text_a(item), get_text_txto(item));
            void* new_figure = create_figure('t', new_text);
            insert(list, new_figure);
            addMaxPoints(500, points);
        }
    } else if (getNext(list, info) == NULL) {
        fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"red\">@</text>", x, y);
        return;
    }

    tr(list, getNext(list, info), svg, txt_results, x, y, dx, dy, id, points);
}

void be(list list, void* info, FILE* svg, FILE* txt_results, double x, double y, double r, double agress, score points) {
    void* item;
    void* aux;
    void* aux_remove = NULL;
    bool found = false;
    double reduction = 0.0;
    double protect = 0.0;
    char type;
    double pi = 3.14;
    
    for (void* node = getFirst(list); node; node = getNext(list, node)) {
        aux = get(list, node);
        item = get_info(aux);
        type = WhatFigureIsIt(aux);

        if (aux_remove != NULL) {
            remover(list, aux_remove);
            aux_remove = NULL;
        }
        
            if (type == 'r') {
            found = insideIrradiation(x, y, r, aux);

            if (found) {
                reduction = (agress * get_rectangle_w(item) * get_rectangle_h(item)) / (pi * r * r);
                rectangle_damaged(item, reduction);

                fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" fill=\"red\" stroke=\"red\" stroke-width=\"1\"/>\n", get_rectangle_x(item), get_rectangle_y(item));

                protect = get_rectangle_protect(item);

                if (protect <= 0) {
                    fprintf(txt_results, "Retangulo REMOVIDO:\n");
                    fprintf(txt_results, "X: %lf\n", get_rectangle_x(item));
                    fprintf(txt_results, "Y: %lf\n", get_rectangle_y(item));
                    fprintf(txt_results, "Widh: %lf\n", get_rectangle_w(item));
                    fprintf(txt_results, "Height: %lf\n", get_rectangle_h(item));
                    fprintf(txt_results, "Corb: %s\n", get_rectangle_corb(item));
                    fprintf(txt_results, "Corp: %s\n\n", get_rectangle_corp(item));
                    aux_remove = info;
                    addAgress(points);
                    addPoints(90, points);
                    
                } else {
                    fprintf(txt_results, "Retangulo ATINGIDO:\n");
                    fprintf(txt_results, "X: %lf\n", get_rectangle_x(item));
                    fprintf(txt_results, "Y: %lf\n", get_rectangle_y(item));
                    fprintf(txt_results, "Widh: %lf\n", get_rectangle_w(item));
                    fprintf(txt_results, "Height: %lf\n", get_rectangle_h(item));
                    fprintf(txt_results, "Corb: %s\n", get_rectangle_corb(item));
                    fprintf(txt_results, "Corp: %s\n\n", get_rectangle_corp(item));
                }
            }
        } else if (type == 'c') {
            found = insideIrradiation(x, y, r, aux);

            if (found) {
                reduction = (agress * (get_circle_r(item) * get_circle_r(item) * pi)) / (pi * r * r);
                circle_damaged(item, reduction);

                fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" fill=\"red\" stroke=\"red\" stroke-width=\"1\"/>\n", get_circle_x(item), get_circle_y(item));

                protect = get_circle_protect(item);

                if (protect <= 0) {
                    fprintf(txt_results, "Circulo REMOVIDO:\n");
                    fprintf(txt_results, "X: %lf\n", get_circle_x(item));
                    fprintf(txt_results, "Y: %lf\n", get_circle_y(item));
                    fprintf(txt_results, "Raio: %lf\n", get_circle_r(item));
                    fprintf(txt_results, "Corb: %s\n", get_circle_corb(item));
                    fprintf(txt_results, "Corp: %s\n\n", get_circle_corp(item));
                    aux_remove = info;
                    addAgress(points);
                    addPoints(75, points);
                } else {
                    fprintf(txt_results, "Circulo ATINGIDO:\n");
                    fprintf(txt_results, "X: %lf\n", get_circle_x(item));
                    fprintf(txt_results, "Y: %lf\n", get_circle_y(item));
                    fprintf(txt_results, "Raio: %lf\n", get_circle_r(item));
                    fprintf(txt_results, "Corb: %s\n", get_circle_corb(item));
                    fprintf(txt_results, "Corp: %s\n\n", get_circle_corp(item));
                }
            }
        } else if (type == 'l') {
            found = insideIrradiation(x, y, r, aux);
            if (found) {
                reduction = (agress * (0.1 * distanceBetweenTwoPoint(get_line_x1(item), get_line_y1(item), get_line_x2(item), get_line_y2(item))) / (pi * r * r));
                line_damaged(item, reduction);

                fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" fill=\"red\" stroke=\"red\" stroke-width=\"1\"/>\n", get_line_x1(item), get_line_y1(item));
                fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" fill=\"red\" stroke=\"red\" stroke-width=\"1\"/>\n", get_line_x2(item), get_line_y2(item));

                protect = get_line_protect(item);

                if (protect <= 0) {
                    fprintf(txt_results, "Linha REMOVIDO:\n");
                    fprintf(txt_results, "X1: %lf\n", get_line_x1(item));
                    fprintf(txt_results, "Y1: %lf\n", get_line_y1(item));
                    fprintf(txt_results, "X2: %lf\n", get_line_x2(item));
                    fprintf(txt_results, "Y2: %lf\n", get_line_y2(item));
                    fprintf(txt_results, "Cor: %s\n\n", get_line_cor(item));
                    aux_remove = info;
                    addAgress(points);
                    addPoints(50, points);
                } else {
                    fprintf(txt_results, "\nLinha ATINGIDA:\n");
                    fprintf(txt_results, "X1: %lf\n", get_line_x1(item));
                    fprintf(txt_results, "Y1: %lf\n", get_line_y1(item));
                    fprintf(txt_results, "X2: %lf\n", get_line_x2(item));
                    fprintf(txt_results, "Y2: %lf\n", get_line_y2(item));
                    fprintf(txt_results, "Cor: %s", get_line_cor(item));
                }
            }
        } else if (type == 't') {
            found = insideIrradiation(x, y, r, aux);

            if (found) {
                reduction = (agress * 0.1) / (pi * r * r);
                text_damaged(item, reduction);

                if (get_text_a(item) == 'i') {
                    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" fill=\"red\" stroke=\"red\" stroke-width=\"1\"/>\n", get_text_x(item), get_text_y(item));
                } else if (get_text_a(item) == 'm' ) {
                    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" fill=\"red\" stroke=\"red\" stroke-width=\"1\"/>\n", (get_text_x(item) + strlen(get_text_txto(item))/2), get_text_y(item));
                } else {
                    fprintf(svg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" fill=\"red\" stroke=\"red\" stroke-width=\"1\"/>\n", (get_text_x(item) + strlen(get_text_txto(item))), get_text_y(item));
                }
                
                protect = get_text_protect(item);

                if (protect <= 0) {
                    fprintf(txt_results, "Texto REMOVIDO:\n");
                    fprintf(txt_results, "X: %lf\n", get_text_x(item));
                    fprintf(txt_results, "Y: %lf\n", get_text_y(item));
                    fprintf(txt_results, "Ancora: %c\n", get_text_a(item));
                    fprintf(txt_results, "Corb: %s\n", get_text_corb(item));
                    fprintf(txt_results, "Corp: %s\n", get_text_corp(item));
                    fprintf(txt_results, "Valor: %s\n\n", get_text_txto(item));
                    aux_remove = info;
                    addAgress(points);
                    addPoints(30, points);
                } else {
                    fprintf(txt_results, "Texto ATINGIDO:\n");
                    fprintf(txt_results, "X: %lf\n", get_text_x(item));
                    fprintf(txt_results, "Y: %lf\n", get_text_y(item));
                    fprintf(txt_results, "Ancora: %c\n", get_text_a(item));
                    fprintf(txt_results, "Corb: %s\n", get_text_corb(item));
                    fprintf(txt_results, "Corp: %s\n", get_text_corp(item));
                    fprintf(txt_results, "Valor: %s\n\n", get_text_txto(item));
                }
            }
        }
    }
}

void se (list lista, list selected, FILE* txt_results, char id[]) {
    void* item;
    bool found = false;
    char type;
    int i;
    int idInt = atoi(id);

    for (void* node = getFirst(lista); node; node = getNext(lista, node)) {
        void* node_aux = get(lista, node);
        void* element = get_info(node_aux);
        type = get_type(node_aux);
        
        if (type == 'c') {
            if (get_circle_i(element) == idInt)
                found = true;
        } else if (type == 'r') {
            if (get_rectangle_i(element) == idInt)
                found = true;
        } else if (type == 't') {
            if (get_text_i(element) == idInt)
                found = true;
        } else if (type == 'l') {
            if (get_line_i(element) == idInt)
                found = true;
        }

        if (found) {
            if (type == 'c') {
                void* new_circle = build_circle(idInt, get_circle_x(element), get_circle_y(element), get_circle_r(element), get_circle_corb(element), get_circle_corp(element));
                void* new_figure = create_figure(type, new_circle);
                insert(selected, new_figure);
                fprintf(txt_results, "\nse: circulo, id = %d, x = %lf, y = %lf, raio = %lf, cor preenchimento = %s, cor borda = %s\n", get_circle_i(item), get_circle_x(item), get_circle_y(item), get_circle_r(item), get_circle_corp(item), get_circle_corb(item));
            } else if (type == 'r') {
                void* new_rectangle = build_rectangle(idInt, get_rectangle_x(element), get_rectangle_y(element), get_rectangle_w(element), get_rectangle_h(element), get_rectangle_corb(element), get_rectangle_corp(element));
                void* new_figure = create_figure(type, new_rectangle);
                insert(selected, new_figure);
                fprintf(txt_results, "\nse: retangulo, id = %d, x = %lf, y = %lf, altura = %lf, largura = %lf, cor preenchimento = %s, cor borda = %s\n", get_rectangle_i(item), get_rectangle_x(item), get_rectangle_y(item), get_rectangle_w(item), get_rectangle_h(item), get_rectangle_corp(item), get_rectangle_corb(item));
            } else if (type == 't') {
                void* new_text = build_text(i, get_text_x(element), get_text_y(element), get_text_corb(element), get_text_corp(element), get_text_a(element), get_text_txto(element));
                void* new_figure = create_figure(type, new_text);
                insert(selected, new_figure);
                fprintf(txt_results, "\nse: texto, id = %d, x = %lf, y = %lf, ancora = %c, cor preenchimento = %s, cor borda = %s, texto = %s\n", get_text_i(item), get_text_x(item), get_text_y(item), get_text_a(item), get_text_corp(item), get_text_corb(item), get_text_txto(item));
            } else if (type == 'l') {
                void* new_line = build_line(i, get_line_x1(element), get_line_y1(element), get_line_x2(element), get_line_y2(element), get_line_cor(element));
                void* new_figure = create_figure(type, new_line);
                insert(selected, new_figure);
                fprintf(txt_results, "\nse: linha, id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, cor = %s\n", get_line_i(item), get_line_x1(item), get_line_y1(item), get_line_x2(item), get_line_y2(item), get_line_cor(item));
            }
        break;
        }
    }
}

void sec (list lista, list selected, FILE* txt_results, char id[], int j, int naucap[]) {
    bool found = false;
    char type;
    int idInt = atoi(id);

    se(lista, selected, txt_results, id);

    for (void* node = getFirst(selected); node; node = getNext(selected, node)) {
        void* node_aux = get(selected, node);
        void* element = get_info(node_aux);
        type = get_type(node_aux);

        if (type == 'c') {
            if (get_circle_i(element) == idInt)
                found = true;
        } else if (type == 'r') {
            if (get_rectangle_i(element) == idInt)
                found = true;
        } else if (type == 't') {
            if (get_text_i(element) == idInt)
                found = true;
        } else if (type == 'l') {
            if (get_line_i(element) == idInt)
                found = true;
        }

        if (found) {
            naucap[j] = idInt;
            if (type == 'c')
                fprintf(txt_results, "\nsec: circulo, id = %d, x = %lf, y = %lf, raio = %lf, cor preenchimento = %s, cor borda = %s\n", get_circle_i(element), get_circle_x(element), get_circle_y(element), get_circle_r(element), get_circle_corp(element), get_circle_corb(element));
            else if (type == 'r')
                fprintf(txt_results, "\nsec: retangulo, id = %d, x = %lf, y = %lf, altura = %lf, largura = %lf, cor preenchimento = %s, cor borda = %s\n", get_rectangle_i(element), get_rectangle_x(element), get_rectangle_y(element), get_rectangle_w(element), get_rectangle_h(element), get_rectangle_corp(element), get_rectangle_corb(element));
            else if (type == 't')
                fprintf(txt_results, "\nsec: texto, id = %d, x = %lf, y = %lf, ancora = %c, cor preenchimento = %s, cor borda = %s, texto = %s\n", get_text_i(element), get_text_x(element), get_text_y(element), get_text_a(element), get_text_corp(element), get_text_corb(element), get_text_txto(element));
            else if (type == 'l')
                fprintf(txt_results, "\nsec: linha, id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, cor = %s\n", get_line_i(element), get_line_x1(element), get_line_y1(element), get_line_x2(element), get_line_y2(element), get_line_cor(element));
        }
    }
}

void mvh (list lista, list selected, FILE* txt_results, FILE* svg, void* info, int j, int k, double dx, int naucap[], score points) {
    void* item;
    void* aux;
    bool mine = false;
    char type;
    char direction;
    
    aux = chooseBoat(selected, j, k, naucap);
    item = get_info(aux);
    type = get_type(item);

    if (dx > 0) {
        direction = 'r';
    } else {
        direction = 'l';
    }

    mine = mineInDisplacement(lista, item, type, direction, dx, 0, txt_results, svg);

    if (mine) {
        addAgress(points);
        if (type == 'c') {
            destroyBoat(lista, selected, item, 'c', aux, 'a');
        } else if (type == 'r') {
            destroyBoat(lista, selected, item, 'r', aux, 'a');
        } else if (type == 't') {
            destroyBoat(lista, selected, item, 't', aux, 'a');
        } else if (type == 'l') {
            destroyBoat(lista, selected, item, 'l', aux, 'a');
        }
    } else {
        if (type == 'c') {
                void* new_circle = build_circle(get_circle_i(item), get_circle_x(item) + dx, get_circle_y(item), get_circle_r(item), get_circle_corb(item), get_circle_corp(item));
                void* new_figure = create_figure(type, new_circle);
                insert(lista, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x = %lf, y = %lf para x = %lf, y = %lf\n", get_circle_i(item), get_circle_x(item), get_circle_y(item), get_circle_x(item) + dx, get_circle_y(item));
                destroyBoat(lista, selected, item, 'c', aux, 'o');
            } else if (type == 'r') {
                void* new_rectangle = build_rectangle(get_rectangle_i(item), get_rectangle_x(item) + dx, get_rectangle_y(item), get_rectangle_w(item), get_rectangle_h(item), get_rectangle_corb(item), get_rectangle_corp(item));
                void* new_figure = create_figure(type, new_rectangle);
                insert(selected, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x = %lf, y = %lf para x = %lf, y = %lf\n", get_rectangle_i(item), get_rectangle_x(item), get_rectangle_y(item), get_rectangle_x(item) + dx, get_rectangle_y(item));
                destroyBoat(lista, selected, item, 'r', aux, 'o');
            } else if (type == 't') {
                void* new_text = build_text(get_text_i(item), get_text_x(item), get_text_y(item), get_text_corb(item), get_text_corp(item), get_text_a(item), get_text_txto(item));
                void* new_figure = create_figure(type, new_text);
                insert(selected, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x = %lf, y = %lf para x = %lf, y = %lf\n", get_text_i(item), get_text_x(item), get_text_y(item), get_text_x(item) + dx, get_text_y(item));
                destroyBoat(lista, selected, item, 't', aux, 'o');
            } else if (type == 'l') {
                void* new_line = build_line(get_line_i(item), get_line_x1(item) + dx, get_line_y1(item), get_line_x2(item) + dx, get_line_y2(item), get_line_cor(item));
                void* new_figure = create_figure(type, new_line);
                insert(selected, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf para x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf\n", get_line_i(item), get_line_x1(item), get_line_y1(item), get_line_x2(item), get_line_y2(item), get_line_x1(item) + dx, get_line_y1(item), get_line_x2(item) + dx, get_line_y2(item));
                destroyBoat(lista, selected, item, 'l', aux, 'o');
            }
    }
}

void mvv (list lista, list selected, FILE* txt_results, FILE* svg, void* info, int j, int k, double dy, int naucap[], score points) {
    void* item;
    void* aux;
    bool mine = false;
    char type;
    char direction;
    
    aux = chooseBoat(selected, j, k, naucap);
    item = get_info(aux);
    type = get_type(item);

    if (dy > 0) {
        direction = 'u';
    } else {
        direction = 'd';
    }

    mine = mineInDisplacement(lista, item, type, direction, 0, dy, txt_results, svg);

    if (mine) {
        addAgress(points);
        if (type == 'c') {
            destroyBoat(lista, selected, item, 'c', aux, 'a');
        } else if (type == 'r') {
            destroyBoat(lista, selected, item, 'r', aux, 'a');
        } else if (type == 't') {
            destroyBoat(lista, selected, item, 't', aux, 'a');
        } else if (type == 'l') {
            destroyBoat(lista, selected, item, 'l', aux, 'a');
        }
    } else {
        if (type == 'c') {
                void* new_circle = build_circle(get_circle_i(item), get_circle_x(item), get_circle_y(item) + dy, get_circle_r(item), get_circle_corb(item), get_circle_corp(item));
                void* new_figure = create_figure(type, new_circle);
                insert(lista, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x = %lf, y = %lf para x = %lf, y = %lf\n", get_circle_i(item), get_circle_x(item), get_circle_y(item), get_circle_x(item), get_circle_y(item) + dy);
                destroyBoat(lista, selected, item, 'c', aux, 'o');
            } else if (type == 'r') {
                void* new_rectangle = build_rectangle(get_rectangle_i(item), get_rectangle_x(item), get_rectangle_y(item) + dy, get_rectangle_w(item), get_rectangle_h(item), get_rectangle_corb(item), get_rectangle_corp(item));
                void* new_figure = create_figure(type, new_rectangle);
                insert(selected, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x = %lf, y = %lf para x = %lf, y = %lf\n", get_rectangle_i(item), get_rectangle_x(item), get_rectangle_y(item), get_rectangle_x(item), get_rectangle_y(item) + dy);
                destroyBoat(lista, selected, item, 'r', aux, 'o');
            } else if (type == 't') {
                void* new_text = build_text(get_text_i(item), get_text_x(item), get_text_y(item) + dy, get_text_corb(item), get_text_corp(item), get_text_a(item), get_text_txto(item));
                void* new_figure = create_figure(type, new_text);
                insert(selected, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x = %lf, y = %lf para x = %lf, y = %lf\n", get_text_i(item), get_text_x(item), get_text_y(item), get_text_x(item), get_text_y(item) + dy);
                destroyBoat(lista, selected, item, 't', aux, 'o');
            } else if (type == 'l') {
                void* new_line = build_line(get_line_i(item), get_line_x1(item), get_line_y1(item) + dy, get_line_x2(item), get_line_y2(item) + dy, get_line_cor(item));
                void* new_figure = create_figure(type, new_line);
                insert(selected, new_figure);
                fprintf(txt_results, "\nEmbarcação movida: id = %d, x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf para x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf\n", get_line_i(item), get_line_x1(item), get_line_y1(item), get_line_x2(item), get_line_y2(item), get_line_x1(item), get_line_y1(item) + dy, get_line_x2(item), get_line_y2(item) + dy);
                destroyBoat(lista, selected, item, 'l', aux, 'o');
            }
    }
}

void get_functions(path paths, FILE* txt_results, CPTree b, score points) {
    char command[100], id[10];
    double x, y, dx, dy, r;
    double agress = 0;
    int j, k, naucap[10];

    void* list = createLista(-1);
    void* selected = createLista(-1);

    FILE* qry = fopen(get_path_QryFile(paths), "r");
    FILE* modifiedSVG = fopen(get_path_modifiedSVG(paths), "w+");

    fprintf(modifiedSVG, "<!-- Matheus Kenzo -->\n <svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">");

    while(fscanf(qry, "%s", command) != EOF) {
        if (!strcmp(command, "na")) {
            fscanf(qry, "%lf ", &agress);
            fprintf(txt_results, "\nagress: %lf", agress);
        } else if (!strcmp(command, "tp")){
            fscanf(qry, "%lf %lf", &x, &y);
            fprintf(txt_results, "\ntp: x = %lf, y = %lf", x, y);
            tp(list, getFirst(list), modifiedSVG, txt_results, x, y, points);
        } else if (!strcmp(command, "tr")) {
            fscanf(qry, "%lf %lf %lf %lf %s", &x, &y, &dx, &dy, id);
            fprintf(txt_results, "\ntr: x = %lf, y = %lf, dx = %lf, dy = %lf, id = %s", x, y, dx, dy, id);
            tr(list, getFirst(list), modifiedSVG, txt_results, x, y, dx, dy, id, points);
        } else if (!strcmp(command, "be")) {
            fscanf(qry, "%lf %lf %lf", &x, &y, &r);
            fprintf(txt_results, "\nbe: x = %lf, y = %lf, r = %lf", x, y, r);
            fprintf(modifiedSVG, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"red\" stroke-width=\"3\" fill=\"none\" stroke-dasharray=\"5,5\" d=\"M5 20 l215 0\" />", x, y, r);
            be(list, getFirst(list), modifiedSVG, txt_results, x, y, r, agress, points);
        } else if (!strcmp(command, "se")) {
            fscanf(qry, "%s", id);
            fprintf(txt_results, "\nse: id = %s", id);
            se(list, selected, txt_results, id);
        } else if (!strcmp(command, "sec")) {
            fscanf(qry, "%s %d", id, &j);
            fprintf(txt_results, "\nbe: id = %s, j = %d", id, j);
            sec(list, selected, txt_results, id, j, naucap);
        } else if (!strcmp(command, "mvh")) {
            fscanf(qry, "%d %d %lf", &j, &k, &dx);
            fprintf(txt_results, "\nmvh: j = %d, k = %d, dx = %lf", j, k, dx);
            mvh(list, selected, txt_results, modifiedSVG, getFirst(selected),j, k, dx, naucap, points);
        } else if (!strcmp(command, "mvv")) {
            fscanf(qry, "%d %d %lf", &j, &k, &dx);
            fprintf(txt_results, "\nmvv: j = %d, k = %d, dy = %lf", j, k, dy);
            mvv(list, selected, txt_results, modifiedSVG, getFirst(selected),j, k, dx, naucap, points);
        }
    }

    printSvg(list, modifiedSVG);

    killLista(selected);
    fprintf(modifiedSVG, "</svg>\n");
    fclose(qry);
    fclose(modifiedSVG);
}

void format_qry_results(path paths, CPTree b, score points) {
    FILE* txt_results = fopen(get_path_TXTQry(paths), "w+");

    fprintf(txt_results, "-Matheus Kenzo-");
    fprintf(txt_results, "\nFunções executadas:");
    get_functions(paths, txt_results, b, points);
    fprintf(txt_results, "\nPontuação total: %lf\nProporção em pontos obtidos e a pontuação máxima: %lf\nProporção entre pontos obtidos e o número de agressões contidas no arquivo .qry: %lf", get_total_points(points), get_obtained_points(points)/get_total_points(points), get_obtained_points(points)/get_agress(points));

    fclose(txt_results);
}