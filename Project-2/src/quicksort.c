#include "quicksort.h"
#include "lista.h"
#include "figure.h"
#include "circle.h"
#include "rectangle.h"
#include "text.h"
#include "line.h"

void* findItem(list lista, int number) {
    Item aux = getFirst(lista);
    bool found = false;
    int count = 0;

    while (!found) {
        if (count == number) {
            found = true;
        }
        aux = getNext(lista, aux);
        count++;
    }
    return aux;
}

void shuffle(int lenght, list lista) {
    int m, n;
    for (int i = 0; i < lenght; i++) {
        m = rand() % lenght;
        n = rand() % lenght;
        while (m == n) {
            n = rand() % lenght;
        }
        
        Item aux1 = findItem(lista, m);
        Item aux2 = findItem(lista, n);
        Item info1 = get(lista, aux1);
        Item info2 = get(lista, aux2);

        insertAfter(lista, aux1, info2);
        insertAfter(lista, aux2, info1);
        remover(lista, aux1);
        remover(lista, aux2);
    }
}

void swap(list lista, Item a, Item b) {
    void* infoA = get(lista, a);
    void* infoB = get(lista, b);

    insertAfter(lista, a, infoB);
    insertAfter(lista, b, infoA);
    remover(lista, a);
    remover(lista, b);
}

int whatIsTheNumber(Item info) {
    char type = get_type(info);
    int id;

    if (type == 'c') {
        id = get_circle_i(info);
    } else if (type == 'r') {
        id = get_rectangle_i(info);
    } else if (type == 'l') {
        id = get_line_i(info);
    } else if (type == 't') {
        id = get_text_i(info);
    }

    return id;
}

void quick_sort(list lista, int left, int right) {
    int x;
    int i = left;
    int j = right;

    Item aux = findItem(lista, (left + right)/2);
    x = whatIsTheNumber(get(lista, aux));
    Item alpha = getFirst(lista);
    void* info = get(lista, alpha);
    while(i <= j) {
        while(whatIsTheNumber(info) < x && i < right) {
            i++;
            alpha = getNext(lista, alpha);
            info = get(lista, alpha);
        }
        Item beta = findItem(lista, j);
        void* infob = get(lista, beta);
        while(whatIsTheNumber(infob) > x && j > left) {
            j--;
            beta = getPrevious(lista, beta);
            infob = get(lista, beta);
        }
        if(i <= j) {
            swap(lista, alpha, beta);
            i++;
            j--;
        }
    }
    if(j > left) {
        quick_sort(lista, left, j);
    }
    if(i < right) {
        quick_sort(lista, i, right);
    }
}