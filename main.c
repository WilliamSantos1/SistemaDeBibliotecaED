#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.c"
#include "arvore.c"
#include "fila.c"
#include "lista.h"

int main() {

    Arvore *arvore = criarArvore();
    Fila *filaReservas = criarFila();
    Historico *historico = NULL;

    inserirLivroArvore(arvore,
        criarLivro(1,"Joaozinho Gamer","Johon",1999,1));

    inserirLivroArvore(arvore,
        criarLivro(2,"Matematica","Carlos",2010,1));

    inserirLivroArvore(arvore,
        criarLivro(3,"Portugues","Ana",2020,1));

    int opcao;

    do {

        printf("\n============================");
        printf("\n SISTEMA BIBLIOTECA");
        printf("\n============================");
        printf("\n1 - Buscar livro");
        printf("\n2 - Listar livros em ordem");
        printf("\n3 - Emprestar livro");
        printf("\n4 - Devolver livro");
        printf("\n5 - Exibir reservas");
        printf("\n6 - Exibir historico");
        printf("\n7 - Cadastrar livro");
        printf("\n8 - Remover livro");
        printf("\n9 - Listar livros em pre-ordem");
        printf("\n10 - Listar livros em pos-ordem");
        printf("\n0 - Sair");
        printf("\nOpcao: ");

        scanf("%d",&opcao);

        switch(opcao) {

            case 1: {

                int codigo;

                printf("Codigo do livro: ");
                scanf("%d",&codigo);

                Livro *livro =
                    buscarLivroArvore(arvore,codigo);

                if(livro != NULL)
                    exibirLivro(livro);

                break;
            }

            case 2:

                listarLivrosEmOrdem(arvore);

                break;

            case 3: {

                int codigo;
                char usuario[100];

                printf("Codigo do livro: ");
                scanf("%d",&codigo);

                printf("Nome do usuario: ");
                scanf(" %[^\n]",usuario);

                Livro *livro =
                    buscarLivroArvore(arvore,codigo);

                if(livro == NULL) {
                    printf("Livro nao encontrado.\n");
                    break;
                }

                if(livro->quantidadeDisponivel > 0) {

                    emprestarExemplar(livro);

                    inserirHistorico(
                        &historico,
                        livro->codigo,
                        livro->titulo,
                        usuario
                    );

                    printf(
                        "\nEmprestimo realizado com sucesso!\n"
                    );

                } else {

                    Reserva reserva;

                    strcpy(
                        reserva.nomeUsuario,
                        usuario
                    );

                    reserva.codigoLivro =
                        livro->codigo;

                    enfileirarReserva(
                        filaReservas,
                        reserva
                    );

                    printf(
                        "\nLivro indisponivel.\n"
                    );

                    printf(
                        "Usuario adicionado na fila.\n"
                    );
                }

                break;
            }

            case 4: {

                int codigo;

                printf("Codigo do livro: ");
                scanf("%d",&codigo);

                Livro *livro =
                    buscarLivroArvore(arvore,codigo);

                if(livro == NULL) {
                    printf("Livro nao encontrado.\n");
                    break;
                }

                devolverExemplar(livro);

                printf(
                    "\nLivro devolvido com sucesso!\n"
                );

                if(!filaVazia(filaReservas)) {

                    Reserva proximo =
                        desenfileirarReserva(
                            filaReservas
                        );

                    printf(
                        "\nReserva liberada para: %s\n",
                        proximo.nomeUsuario
                    );
                }

                break;
            }

            case 5:

                exibirReservas(
                    filaReservas
                );

                break;

            case 6:

                listarHistorico(
                    historico
                );

                break;

            case 0:

                printf(
                    "\nEncerrando sistema...\n"
                );

                break;

            default:

                printf(
                    "\nOpcao invalida!\n"
                );
            case 7: {

                int codigo, ano, quantidade;
                char titulo[100];
                char autor[100];

                printf("Codigo: ");
                scanf("%d", &codigo);

                printf("Titulo: ");
                scanf(" %[^\n]", titulo);

                printf("Autor: ");
                scanf(" %[^\n]", autor);

                printf("Ano: ");
                scanf("%d", &ano);

                printf("Quantidade: ");
                scanf("%d", &quantidade);

                Livro *novoLivro = criarLivro(
                    codigo,
                    titulo,
                    autor,
                    ano,
                    quantidade
                );

                inserirLivroArvore(arvore, novoLivro);

                printf("Livro cadastrado com sucesso!\n");

                break;
            }
            case 8: {

                int codigo;

                printf("Codigo do livro: ");
                scanf("%d", &codigo);

                Livro *livro = buscarLivroArvore(arvore, codigo);

                if (livro == NULL) {

                    printf("Livro nao encontrado.\n");

                } else {

                    removerLivroArvore(arvore, livro);

                    printf("Livro removido com sucesso.\n");
                }

                break;
            }
            case 9:

                listarLivrosPreOrdem(arvore);

                break;
            case 10:

                listarLivrosPosOrdem(arvore);

                break;
        }

    } while(opcao != 0);

    liberarHistorico(historico);

    return 0;
}