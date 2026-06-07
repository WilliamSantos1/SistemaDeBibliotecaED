#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criarFila() {
    Fila* fila = (Fila*) malloc(sizeof(Fila));

    if (fila == NULL) {
        printf("Erro: Não foi possível criar a fila de reservas!\n");
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

int filaVazia(Fila* fila) {
    if (fila == NULL || fila->inicio == NULL) {
        return 1;
    }

    return 0;
}

//Fila segue FIFO, primeiro que entra é o primeiro que sai.
void enfileirarReserva(Fila* fila, Reserva reserva) {
    if (fila == NULL) {
        printf("Erro: Fila de reservas inválida!\n");
        return;
    }

    NoFila* novoNo = (NoFila*) malloc(sizeof(NoFila));

    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memória para a reserva!\n");
        return;
    }

    novoNo->reserva = reserva;
    novoNo->proximo = NULL;

    if (filaVazia(fila)) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
}

//Remove o primeiro da fila.
Reserva desenfileirarReserva(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Erro: Fila vazia! Nenhuma reserva para remover\n");

        Reserva reservaVazia = {"", -1};
        return reservaVazia;
    }

    NoFila* temp = fila->inicio;
    Reserva reservaRecuperada = temp->reserva;

    // O início da fila passa a ser o próximo nó
    fila->inicio = fila->inicio->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);

    return reservaRecuperada;
}

void exibirReservas(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Nao ha reservas registradas no momento.\n");
        return;
    }

    NoFila* atual = fila->inicio;
    int posicao = 1;

    printf("\n===== FILA DE RESERVAS =====\n");
    printf("Posicao | Usuario | Codigo do Livro\n");
    printf("-----------------------------------\n");

    while (atual != NULL) {
        printf("   %d    | %-18s | %d\n",
               posicao,
               atual->reserva.nomeUsuario,
               atual->reserva.codigoLivro);
        atual = atual->proximo;
        posicao++;
    }
    printf("-----------------------------------\n");
    printf("Total de reservas: %d\n\n", posicao - 1);

}