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
        criarLivro(1,"Historia","Johon",1999,1));

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
        printf("\n");
        switch(opcao) {

            case 1: {

                int codigo;

                printf("Codigo do livro: ");

                if (scanf("%d", &codigo) != 1) {
                    printf("\nErro: Codigo invalido. Digite apenas numeros.\n");
                    while (getchar() != '\n');
                    break;
                }

                Livro *livro =
                    buscarLivroArvore(arvore,codigo);

                if(livro != NULL) {
                    exibirLivro(livro);
                }else {
                    printf("\n[livro nao existente ou arvore vazia.]\n");
                }
                break;
            }

            case 2:

                listarLivrosEmOrdem(arvore);

                break;

            case 3: {

                int codigo;
                char usuario[100];

                printf("Codigo do livro: ");

                if (scanf("%d", &codigo) != 1) {
                    printf("\nErro: Codigo invalido. Digite apenas numeros.\n");
                    while (getchar() != '\n');
                    break;
                }

                printf("Nome do usuario: ");
                scanf(" %[^\n]",usuario);

                Livro *livro =
                    buscarLivroArvore(arvore,codigo);

                if(livro == NULL) {
                    printf("\n[Livro nao encontrado.]\n");
                    break;
                }
                int quantidade = obterQuantidadeDisponivel(livro);

                if(quantidade > 0) {

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
                        "\n[Livro indisponivel.]\n"
                    );

                    printf(
                        "\n[Usuario adicionado na fila].\n"
                    );
                }

                break;
            }

            case 4: {

                int codigo;

                printf("Codigo do livro: ");

                if (scanf("%d", &codigo) != 1) {
                    printf("\nErro: Codigo invalido. Digite apenas numeros.\n");
                    while (getchar() != '\n');
                    break;
                }

                Livro *livro =
                    buscarLivroArvore(arvore,codigo);

                if(livro == NULL) {
                    printf("\n[Livro nao encontrado.]\n");
                    break;
                }

                if (livro->quantidadeDisponivel == livro->quantidadeTotal) {
                    printf("\nErro: este livro nao esta emprestado.\n");
                    break;
                }

                devolverExemplar(livro);

                printf(
                    "\n[Livro devolvido com sucesso!]\n"
                );

                if (!filaVazia(filaReservas)) {

                    NoFila* atual = filaReservas->inicio;
                    NoFila* anterior = NULL;

                    while (atual != NULL && atual->reserva.codigoLivro != codigo) {
                        anterior = atual;
                        atual = atual->proximo;
                    }

                    if (atual != NULL) {

                        Reserva proximo = atual->reserva;

                        if (anterior == NULL) {
                            filaReservas->inicio = atual->proximo;
                        } else {
                            anterior->proximo = atual->proximo;
                        }

                        if (atual == filaReservas->fim) {
                            filaReservas->fim = anterior;
                        }

                        free(atual);

                        emprestarExemplar(livro);

                        printf(
                            "\n[Reserva liberada para: %s]\n",
                            proximo.nomeUsuario
                        );

                    } else {
                        printf("\n[Nenhuma reserva encontrada para este livro.]\n");
                    }
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
                    "\n[Encerrando sistema...]\n"
                );

                break;

            case 7: {

                int codigo, ano, quantidade;
                char titulo[100];
                char autor[100];

                printf("Codigo: ");
                scanf("%d", &codigo);

                Livro * livro = buscarLivroArvore(arvore,codigo);
               if (livro != NULL) {
                   do {
                       if (codigo <=0) {
                           printf("\n[Digite um codigo valido]\n");
                       }else {
                           printf("\n[Codigo de livro ja existente, digite outro valor]\n");
                       }
                       printf("Codigo: ");
                       scanf("%d", &codigo);
                       livro = buscarLivroArvore(arvore,codigo);
                   }while (livro != NULL || codigo <= 0);
               }

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

                break;
            }
            case 8: {

                int codigo;

                printf("Codigo do livro: ");

                if (scanf("%d", &codigo) != 1) {
                    printf("\nErro: Codigo invalido. Digite apenas numeros.\n");
                    while (getchar() != '\n');
                    break;
                }

                Livro *livro = buscarLivroArvore(arvore, codigo);

                if (livro == NULL) {
                    printf("\n[Livro nao encontrado.]\n");
                } else {

                    removerLivroArvore(arvore, livro);
                }

                break;
            }
            case 9:

                listarLivrosPreOrdem(arvore);

                break;
            case 10:

                listarLivrosPosOrdem(arvore);

                break;

            default:

                printf(
                    "\n[Opcao invalida!]\n"
                );
                break;
        }

    } while(opcao != 0);

    liberarHistorico(historico);

    return 0;
}