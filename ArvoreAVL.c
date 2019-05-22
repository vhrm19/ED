#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(){
    NodeArvorePtr *raiz;
    iniciaArvore(&raiz);
    insereItem(&raiz, 13);
    insereItem(&raiz, 14);
    insereItem(&raiz, 15);
    insereItem(&raiz, 12);
    insereItem(&raiz, 11);
    insereItem(&raiz, 17);
    insereItem(&raiz, 16);
    insereItem(&raiz, 8);
    insereItem(&raiz, 9);
    insereItem(&raiz, 1);
    printArvoreAVL(&raiz, 0);
    return 0;
}