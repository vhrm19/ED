#ifndef ArvoreAVL_h
#define ArvoreAVL_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodeArvore NodeArvorePtr;

typedef struct NodeArvore{
    int elemento;
    NodeArvorePtr *esquerda;
    NodeArvorePtr *direita;
    int altura;
}NodeArvore;

void iniciaArvore(NodeArvorePtr **arvore){
    (*arvore) = NULL;
}

void destroiArvore(NodeArvorePtr **arvore){
    if((*arvore) != NULL){
        if((*arvore)->direita != NULL)
            destroiArvore(&(*arvore)->direita);
        if((*arvore)->esquerda != NULL)
            destroiArvore(&(*arvore)->esquerda);
    }
    free((*arvore));
    (*arvore) = NULL;
}

void preOrdem(NodeArvorePtr **arvore){
    if((*arvore) != NULL){
        printf(" %i ", (*arvore)->elemento);
        preOrdem(&(*arvore)->esquerda);
        preOrdem(&(*arvore)->direita);
    }
}

void posOrdem(NodeArvorePtr **arvore){
    if((*arvore) != NULL){
        posOrdem(&(*arvore)->esquerda);
        posOrdem(&(*arvore)->direita);
        printf(" %i ", (*arvore)->elemento);
    }
}

void EmOrdem(NodeArvorePtr **arvore){
    if((*arvore) != NULL){
        EmOrdem(&(*arvore)->esquerda);
        printf(" %i ", (*arvore)->elemento);
        EmOrdem(&(*arvore)->direita);
    }
}

bool insereItem(NodeArvorePtr **arvore, int item){
    bool aux;
    if((*arvore) == NULL){
        (*arvore) = (NodeArvorePtr *) malloc(sizeof(NodeArvore));
        (*arvore)->direita = (*arvore)->esquerda = NULL;
        (*arvore)->elemento = item;
        (*arvore)->altura = 0;
        return true;
    } else if((*arvore)->elemento == item)
        return false;
    else if((*arvore)->elemento > item)
        aux = insereItem(&(*arvore)->esquerda, item);
    else
        aux = insereItem(&(*arvore)->direita, item);

    if(aux){
        AplicarRotacao(arvore);
        atualizaAltura(arvore);
        return true;
    }
    else
        return false;
}

bool procuraItem(NodeArvorePtr **arvore, int chave, NodeArvorePtr **recebe){
    if((*arvore) == NULL)
        return false;
    else if((*arvore)->elemento == chave){
        *recebe = (*arvore);
        return true;
    }
    else if(chave > (*arvore)->elemento)
        return procuraItem(&(*arvore)->direita, chave, recebe);
    else
        return procuraItem(&(*arvore)->esquerda, chave, recebe);
}

bool estaVaziaArvore(NodeArvorePtr **arvore){
    return((*arvore) == NULL);
}

NodeArvorePtr* getMinAux(NodeArvorePtr **arvore){
    if((*arvore)->esquerda != NULL)
        return getMinAux(&(*arvore)->esquerda);
    return (*arvore);
}

NodeArvorePtr* getMaxAux(NodeArvorePtr **arvore){
    if((*arvore)->direita != NULL)
        return getMaxAux(&(*arvore)->direita);
    return (*arvore);
}

bool removeItem(NodeArvorePtr **arvore, int chave){
    if((*arvore) == NULL)
        return false;

    else if((*arvore)->elemento == chave){
        NodeArvore *aux = (*arvore);

        if((*arvore)->esquerda == NULL)
            (*arvore) = (*arvore)->direita;

        if((*arvore)->direita == NULL)
            (*arvore) = (*arvore)->esquerda; 

        if((*arvore)->direita == NULL && (*arvore)->esquerda == NULL)
            (*arvore) = NULL;

        else{
            (*arvore) = getMaxAux(&(*arvore)->esquerda);
            (*arvore)->direita = aux->direita;
        }
        atualizaAltura(arvore);
        free(aux);
        return true;
    }
    else if((*arvore)->elemento > chave)
        return removeItem(&(*arvore)->esquerda, chave);
    else
        return removeItem(&(*arvore)->direita, chave);
}

int altura(NodeArvorePtr **arvore){  
    if (estaVaziaArvore(arvore))  
        return 0;  
    else{
        int alturaEsq = altura(&(*arvore)->esquerda);  
        int alturaDir = altura(&(*arvore)->direita);  
      
        if(alturaEsq > alturaDir)  
            return(alturaEsq + 1);  
        else return(alturaDir + 1);  
    }
}

void atualizaAltura(NodeArvorePtr **arvore){
    if(estaVaziaArvore(arvore))
        return;
    else{
        (*arvore)->altura = altura(arvore);
        atualizaAltura(&(*arvore)->direita);
        atualizaAltura(&(*arvore)->direita);
    }
}

void AplicarRotacao(NodeArvorePtr **arvore){
    int bar = altura(&(*arvore)->direita) - altura(&(*arvore)->esquerda);
    if(bar >= 2 || bar <= -2)
        if(bar < 0)
            if(altura(&(*arvore)->esquerda->esquerda) >= altura(&(*arvore)->esquerda->direita))
                rotacaoDireitaSimples(arvore);
            else
                rotacaoDireitaDupla(arvore);
        else
            if(altura(&(*arvore)->direita->esquerda) > altura(&(*arvore)->direita->direita))
                rotacaoEsquerdaDupla(arvore);
            else
                rotacaoEsquerdaSimples(arvore);
}

void rotacaoDireitaSimples(NodeArvorePtr **arvore){
    NodeArvorePtr *u = (*arvore)->esquerda;
    (*arvore)->esquerda = u->direita;
    u->direita = (*arvore);
    atualizaAltura(&u);
    atualizaAltura(arvore);
    (*arvore) = u;
}

void rotacaoEsquerdaSimples(NodeArvore **arvore){
    NodeArvorePtr *u = (*arvore)->direita;
    (*arvore)->direita = u->esquerda;
    u->esquerda = (*arvore);
    atualizaAltura(&u);
    atualizaAltura(arvore);
    (*arvore) = u;
}

void rotacaoDireitaDupla(NodeArvore **arvore){
    NodeArvorePtr *u = (*arvore)->esquerda;
    NodeArvorePtr *v = u->direita;
    u->direita = v->esquerda;
    v->esquerda = u;
    (*arvore)->esquerda = v->direita;
    v->direita = (*arvore);
    atualizaAltura(&u);
    atualizaAltura(&v);
    atualizaAltura(arvore);
    (*arvore) = v;
}

void rotacaoEsquerdaDupla(NodeArvore **arvore){
    NodeArvorePtr *u = (*arvore)->direita;
    NodeArvorePtr *v = u->esquerda;
    (*arvore)->direita = v->esquerda;
    u->esquerda = v->direita;
    v->direita = u;
    v->esquerda = (*arvore);
    atualizaAltura(&u);
    atualizaAltura(&v);
    atualizaAltura(arvore);
    (*arvore) = v;
}

void printArvoreAVL(NodeArvorePtr **arvore, int count){
    if (!estaVaziaArvore(arvore)){
        count += 10;
        
        printArvoreAVL(&(*arvore)->direita, count); 
        printf("\n"); 
        for (int i = 10; i < count; i++) 
            printf(" "); 
        printf("%i\n", (*arvore)->elemento); 
    
        printArvoreAVL(&(*arvore)->esquerda, count); 
    }
} 
#endif
