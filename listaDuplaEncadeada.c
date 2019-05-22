#include "listaDuplaEncadeada.h"

int main(){
    Lista lista;
    int recebe;
    iniciaLista(&lista);
    printf("Tamanho inicial da lista: %i\n", lista.tam);
    printf("Esta vazia inicialmente: %i\n", estaVazia(&lista));
    inserir(3, &lista);
    inserir(1, &lista);
    inserir(6, &lista);
    inserir(8, &lista);
    inserir(4, &lista);
    printf("Tamanho da lista: %i\n", lista.tam);
    printf("Esta vazia: %i\n", estaVazia(&lista));
    imprimeLista(&lista);
    imprimeListainversa(&lista);
    pesquisa(8, &lista);
    pesquisa(10, &lista);
    remover(4, &lista, &recebe);
    remover(3, &lista, &recebe);
    remover(6, &lista, &recebe);
    imprimeLista(&lista);
    imprimeListainversa(&lista);
    removerPrimeiro(&lista, &recebe);
    imprimeLista(&lista);
    removerUltimo(&lista, &recebe);
    imprimeLista(&lista);
    return 0;
}
