#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/*
 * Cria um novo nó da lista de histórico.
 * Recebe os dados do empréstimo e aloca memória dinamicamente.
 */
Historico* criarRegistro(
    int codigoLivro,
    char titulo[],
    char usuario[]
) {

    // Aloca memória para um novo registro
    Historico *novo = (Historico*) malloc(sizeof(Historico));

    // Verifica se a alocação foi bem sucedida
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }

    // Armazena os dados recebidos
    novo->codigoLivro = codigoLivro;

    strcpy(novo->titulo, titulo);
    strcpy(novo->usuario, usuario);

    // Como é o último nó criado, aponta para NULL
    novo->prox = NULL;

    return novo;
}

/*
 * Verifica se a lista está vazia.
 * Retorna 1 (verdadeiro) se a lista for NULL.
 */
int listaVazia(Historico *lista) {
    return (lista == NULL);
}

/*
 * Insere um novo empréstimo no final da lista.
 */
void inserirHistorico(
    Historico **lista,
    int codigoLivro,
    char titulo[],
    char usuario[]
) {

    // Cria o novo registro
    Historico *novo = criarRegistro(
        codigoLivro,
        titulo,
        usuario
    );

    // Se não conseguiu criar, encerra a função
    if (novo == NULL)
        return;

    // Caso a lista esteja vazia,
    // o novo registro vira o primeiro nó
    if (*lista == NULL) {
        *lista = novo;
        return;
    }

    // Ponteiro auxiliar para percorrer a lista
    Historico *aux = *lista;

    // Percorre até o último nó
    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    // Liga o último nó ao novo registro
    aux->prox = novo;
}

/*
 * Exibe todos os empréstimos registrados.
 */
void listarHistorico(Historico *lista) {

    // Verifica se existe algum registro
    if (listaVazia(lista)) {
        printf("\n=================================\n");
        printf("Nenhum emprestimo registrado.\n");
        printf("=================================\n");
        return;
    }

    printf("\n=================================\n");
    printf("HISTORICO DE EMPRESTIMOS\n");
    printf("=================================\n");

    // Percorre toda a lista
    while (lista != NULL) {

        // Exibe os dados do nó atual
        printf("Codigo do Livro: %d\n", lista->codigoLivro);
        printf("Titulo: %s\n", lista->titulo);
        printf("Usuario: %s\n", lista->usuario);
        printf("---------------------------------\n");

        // Avança para o próximo nó
        lista = lista->prox;
    }
}

/*
 * Libera toda a memória utilizada pela lista.
 */
void liberarHistorico(Historico *lista) {

    Historico *temp;

    // Percorre todos os nós
    while (lista != NULL) {

        // Guarda o nó atual
        temp = lista;

        // Avança para o próximo
        lista = lista->prox;

        // Libera o nó anterior
        free(temp);
    }
}