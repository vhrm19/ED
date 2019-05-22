#ifndef lista_Dupla_Encadeada_h
#define lista_Dupla_Encadeada_h

#include <stdio.h>
#include <stdlib.h>

typedef struct NodeLista NodeListaPtr;

typedef struct NodeLista{
    int item;
    NodeListaPtr *proximo;
    NodeListaPtr *anterior;
}NodeLista;

typedef struct{
    int tam;
    NodeListaPtr *primeiro;
}Lista;

void iniciaLista(Lista *lista){
    lista->primeiro = NULL;
    lista->tam = 0;
}

int tamanhoLista(Lista *lista){
    return lista->tam;
}

int estaVazia(Lista *lista){
    return(lista->tam == 0);
}

int pesquisa(int item, Lista *lista){
    NodeListaPtr *percorre;
    for(percorre = lista->primeiro; percorre != NULL; percorre = percorre->proximo){
        if(percorre->item == item){
            return 1;
        }
    }
    return 0;
}

void inserirLista(int item, Lista *lista){
    NodeListaPtr *aux;
    aux = (NodeListaPtr *) malloc(sizeof(NodeLista));
    aux->item = item;
    if(lista->tam == 0 || item < lista->primeiro->item){
        aux->proximo = lista->primeiro;
        if(lista->tam > 0)
            lista->primeiro->anterior = aux;
        lista->primeiro = aux;
        aux->anterior = NULL;
    } else {
        NodeListaPtr *percorre;
        for(percorre = lista->primeiro; percorre->proximo != NULL && item > percorre->proximo->item; percorre = percorre->proximo);
        if(pesquisa(item, lista) == 1)
            return;
        aux->proximo = percorre->proximo;
        percorre->proximo = aux;
        aux->anterior = percorre;
        if(aux->proximo != NULL)
            aux->proximo->anterior = aux;
    }
    lista->tam ++;
}

void imprimeLista(Lista *lista){
    NodeListaPtr *percorre;

    printf("{");
    for(percorre = lista->primeiro; percorre != NULL; percorre = percorre->proximo){
        printf(" %i ", percorre->item);
    }
    printf("}\n");
}

int remover(int chave, Lista *lista, int *item){
    if(lista->tam == 0 || chave < lista->primeiro->item){
        printf("Item nao removido.\n");
        return 0;
    }
    else{
        NodeListaPtr *percorre;
        for(percorre = lista->primeiro; percorre != NULL && percorre->item != chave; percorre = percorre->proximo);
        if(percorre == NULL){
            printf("Item nao removido.\n");
            return 0;}
        else {
            *item = percorre->item;
            lista->tam --;
            if(percorre->anterior == NULL && percorre->proximo == NULL){
                lista->primeiro = NULL;
                free(percorre);
                printf("Item removido: %i.\n", *item);
                return 1;
            }
            if(percorre->anterior == NULL){
                percorre->proximo->anterior = NULL;
                lista->primeiro = percorre->proximo;
                free(percorre);
                printf("Item removido: %i.\n", *item);
                return 1;
            }
            if(percorre->proximo == NULL){            
                percorre->anterior->proximo = NULL;
                free(percorre);
                printf("Item removido: %i.\n", *item);
                return 1;
            }
            percorre->anterior->proximo = percorre->proximo;
            percorre->proximo->anterior = percorre->anterior;
            free(percorre);
            printf("Item removido: %i.\n", *item);
            return 1;
        }
    }
}

void removerUltimo(Lista *lista, int *item){
    if(lista->tam == 1){
        *item = lista->primeiro->item;
        lista->primeiro = NULL;
        printf("Ultimo item removido: %i.\n", *item);
        lista->tam --;
    }
    if(lista->tam != 0){
        NodeListaPtr *percorre;
        for(percorre = lista->primeiro; percorre->proximo != NULL; percorre = percorre->proximo);
        *item = percorre->item;
        percorre->anterior->proximo = NULL;
        printf("Ultimo item removido: %i.\n", *item);
        lista->tam --;
    }
}

void removerPrimeiro(Lista *lista, int *item){
    if(lista->tam == 1){
        *item = lista->primeiro->item;
        lista->primeiro = NULL;
        printf("Primeiro item removido: %i.\n", *item);
        lista->tam --;
    }
    if(lista->tam != 0){
        *item = lista->primeiro->item;
        lista->primeiro->proximo->anterior = NULL;
        lista->primeiro = lista->primeiro->proximo;
        printf("Primeiro item removido: %i.\n", *item);
        lista->tam --;
    }
}

int retornaPrimeiro(Lista *lista){
    if(lista->tam != 0){
        printf("Primeiro item retorndado: %i.\n", lista->primeiro->item);

        return lista->primeiro->item;
    }
    else{
        printf("Primeiro item nao retorndado.\n");
        return -1234567890;
    }
}

int retornaUltimo(Lista *lista){
    if(lista->tam != 0){
        NodeListaPtr *percorre;
        for(percorre = lista->primeiro; percorre->proximo != NULL; percorre = percorre->proximo);
        printf("Ultimo item retorndado: %i.\n", percorre->item);
        return percorre->item;
    }
    else{
        printf("Ultimo item nao retorndado.\n");
        return -1234567890;
    }
}

void destruir(Lista *lista){
    NodeListaPtr *aux, *percorre;
    for(percorre = lista->primeiro; percorre->proximo != NULL; percorre = percorre->proximo);
    while(percorre != NULL){
        aux = percorre;
        percorre = percorre->anterior;
        free(aux);
    }
    lista->primeiro = NULL;
    lista->tam = 0;
    printf("Lista destruida.\n");
}

void imprimeListainversa(Lista *lista){
    NodeListaPtr *percorre;
    percorre = NULL;
    if(lista->tam != 0)
        for(percorre = lista->primeiro; percorre->proximo != NULL; percorre = percorre->proximo);

    printf("{");
    for(; percorre != NULL; percorre = percorre->anterior){
        printf(" %i ", percorre->item);
    }
    printf("}\n");
}

#endif