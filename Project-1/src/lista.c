#include "lista.h"
#include "libs.h"
#include "figure.h"
#include "circle.h"
#include "rectangle.h"
#include "text.h"
#include "line.h"

typedef struct node {
    Item info;
    struct node* next;
} node;

typedef struct lista{
    node* head;
    node* end;
    int max_size;
    int size;
} lista;

Lista createLista(int capacidade) {
    lista* newList = malloc(sizeof(lista));
    newList -> head = NULL;
    newList -> end = NULL;
    if (capacidade < 0)
        newList -> max_size = CAPAC_ILIMITADA;
    else
        newList -> max_size = capacidade;
    newList -> size = 0;
    return newList;
}

int length(Lista L) {
    lista* list_aux = L;
    return list_aux->size;
}

int maxLength(Lista L) {
    lista* list_aux = L;
    return list_aux->size;
}

bool isEmpty(Lista L) {
    lista* list_aux = L;
    
    if (list_aux->size != 0) {
        return false;
    } else {
        return true;
    }
}

bool isFull(Lista L) {
    lista* list_aux = L;

    if (list_aux->max_size == CAPAC_ILIMITADA)
        return false;
    
    if (list_aux->size == list_aux->max_size) {
        return true;
    } else {
        return false;
    }
}

Posic insert(Lista L, Item info) {
    lista* list_aux = L;
    node* node_aux = calloc(1, sizeof(node));
    node_aux->info = info;

    if (list_aux->size == 0) {
        node_aux->next = NULL;
        list_aux->head = node_aux;
        list_aux->end = node_aux;
    } else {
        if (isFull(L)) {
            return NIL;
        } else {
            node_aux->next = NULL;
            list_aux->end->next = node_aux;
            list_aux->end = node_aux;
        }
    }

    list_aux->size++;
    return node_aux;
}

Item pop(Lista L) {
    lista* list_aux = L;
    node* aux_remove = list_aux->head;
    node* node_aux = list_aux->head->info;

    if (!isEmpty(L)) {
        if (list_aux->head->next != list_aux->end) {
            list_aux->head = list_aux->head->next;
            free(aux_remove);
            list_aux->size--;
            return node_aux;
        } else {
            free(node_aux);
            list_aux->head = NULL;
            list_aux->end = NULL;
            list_aux->size--;
            return list_aux->head;
        }
    } else {
        return NIL;
    }
}

void remover(Lista L, Posic p) {
    lista* list_aux = L;
    node* node_aux = p;
    
    int size = length(L);
    
    if (size == 1) {
        list_aux->head = NULL;
        list_aux->end = NULL;
        list_aux->size--;
        free(node_aux);
        return;
    } else {
        node* aux_remove = getPrevious(L, node_aux);
        if (aux_remove == list_aux->head) {
            aux_remove = getNext(L, p);
            list_aux->head = aux_remove;
            free(node_aux);
        } else {
            aux_remove->next = node_aux->next;
            if (aux_remove->next == NIL) {
                list_aux->end = aux_remove;
            }
            free(node_aux);
        }
        list_aux->size--;
        return;
    }
}

Item get(Lista L, Posic p) {
    lista* list_aux = (lista*) L;
    
    if(!isEmpty(list_aux)) {
        node* node_aux = p;
        return node_aux->info;
    }
    else return NIL;
}

Posic insertBefore(Lista L,Posic p, Item info) {
    lista* list_aux = L;
    node* node_aux = p;
    node* previous = getPrevious(L, p);
    node* newNode = calloc(1,sizeof(node));
    
    newNode->next = node_aux;
    newNode->info = info;
    previous->next = newNode;
    list_aux->size++;
    return newNode;
}

Posic insertAfter(Lista L,Posic p, Item info) {
    lista* list_aux = L;
    node* node_aux = p;
    node* next = getNext(L, p);
    node* newNode = calloc(1,sizeof(node));
    
    newNode->next = next;
    newNode->info = info;
    node_aux->next = newNode;
    list_aux->size++;
    return newNode;
}

Posic getFirst(Lista L) {
    lista* list_aux = L;

    if (list_aux->size == 0){
        return NIL;
    } else {
        return list_aux->head;
    }
}

Posic getNext(Lista L,Posic p) {
    node* node_aux = (node*) p;
    
    if(node_aux->next == NIL)
        return NIL;
    
    return node_aux->next;
        
}

Posic getLast(Lista L) {
    lista* list_aux = L;

    if (list_aux->size == 0){
        return NIL;
    } else {
        return list_aux->end;
    }
}

Posic getPrevious(Lista L,Posic p) {
    lista* list_aux = L;
    
    if(list_aux->head->next == NIL)
        return NIL;
    
    node* node_aux = p;
    node* previous = list_aux->head;
    while(node_aux!=previous->next) {
        previous = getNext(L, previous);
    }
    
    return previous;
}

void killLista(Lista L) {
    lista* list_aux = L;

    if (list_aux->size == 0) {
        free(list_aux);
        return;
    }

    char type;
    node* node_aux;
    node* element_aux;
    node* aux;

    while (list_aux->size != 0) {
        node_aux = list_aux->head;
        aux = node_aux->info;
        element_aux = get_info(aux);
        list_aux->head = getNext(list_aux, node_aux);

        type = get_type(element_aux);
        switch (type) {
        case 'c':
            free_circle(element_aux);
            break;
        case 'r':
            free_rectangle(element_aux);
            break;
        case 'l':
            free_line(element_aux);
            break;
        case 't':
            free_text(element_aux);
            break;
        default:
            break;
        }
        free(element_aux);
        free(node_aux);
        free(aux);
        list_aux->size--;
    }

    free(list_aux);
}