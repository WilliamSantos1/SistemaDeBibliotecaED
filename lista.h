#ifndef LISTA_H
#define LISTA_H

/*
 * Estrutura que representa um registro
 * do histórico de empréstimos.
 */
typedef struct Historico {

    // Código do livro emprestado
    int codigoLivro;

    // Título do livro
    char titulo[100];

    // Nome do usuário que realizou o empréstimo
    char usuario[100];

    // Ponteiro para o próximo nó da lista
    struct Historico *prox;

} Historico;

/*
 * Cria um novo registro de empréstimo.
 */
Historico* criarRegistro(
    int codigoLivro,
    char titulo[],
    char usuario[]
);

/*
 * Insere um novo registro no histórico.
 */
void inserirHistorico(
    Historico **lista,
    int codigoLivro,
    char titulo[],
    char usuario[]
);

/*
 * Exibe todos os registros do histórico.
 */
void listarHistorico(Historico *lista);

/*
 * Verifica se a lista está vazia.
 * Retorna 1 para vazia e 0 caso contrário.
 */
int listaVazia(Historico *lista);

/*
 * Libera toda a memória utilizada pela lista.
 */
void liberarHistorico(Historico *lista);

#endif