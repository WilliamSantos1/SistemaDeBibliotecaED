#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Historico* criarRegistro(
    int codigoLivro,
    char titulo[],
    char usuario[]
) {

    Historico *novo = (Historico*) malloc(sizeof(Historico));

    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }

    novo->codigoLivro = codigoLivro;

    strcpy(novo->titulo, titulo);
    strcpy(novo->usuario, usuario);

    novo->prox = NULL;

    return novo;
}

int listaVazia(Historico *lista) {
    return (lista == NULL);
}

void inserirHistorico(
    Historico **lista,
    int codigoLivro,
    char titulo[],
    char usuario[]
) {

    Historico *novo = criarRegistro(
        codigoLivro,
        titulo,
        usuario
    );

    if (novo == NULL)
        return;

    if (*lista == NULL) {
        *lista = novo;
        return;
    }

    Historico *aux = *lista;

    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    aux->prox = novo;
}

void listarHistorico(Historico *lista) {

    if (listaVazia(lista)) {
        printf("\n=================================\n");
        printf("Nenhum emprestimo registrado.\n");
        printf("=================================\n");
        return;
    }

    printf("\n=================================\n");
    printf("HISTORICO DE EMPRESTIMOS\n");
    printf("=================================\n");

    while (lista != NULL) {

        printf("Codigo do Livro: %d\n", lista->codigoLivro);
        printf("Titulo: %s\n", lista->titulo);
        printf("Usuario: %s\n", lista->usuario);
        printf("---------------------------------\n");

        lista = lista->prox;
    }
}

void liberarHistorico(Historico *lista) {

    Historico *temp;

    while (lista != NULL) {

        temp = lista;
        lista = lista->prox;

        free(temp);
    }
}