#ifndef LISTA_H
#define LISTA_H

typedef struct Historico {
    int codigoLivro;
    char titulo[100];
    char usuario[100];

    struct Historico *prox;
} Historico;


Historico* criarRegistro(
    int codigoLivro,
    char titulo[],
    char usuario[]
);

void inserirHistorico(
    Historico **lista,
    int codigoLivro,
    char titulo[],
    char usuario[]
);

void listarHistorico(Historico *lista);

int listaVazia(Historico *lista);

void liberarHistorico(Historico *lista);

#endif