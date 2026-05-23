#include <stdlib.h>
#include "arvore.h"

#include <stdio.h>

Arvore * criarArvore() {
    Arvore * arvore = (Arvore *) malloc(sizeof(Arvore));

    if (arvore == NULL) {
        printf("Erro ao criar arvore\n");
        return NULL;
    }
    arvore->raiz = NULL;
    return arvore;
}

void inserirLivroArvore ( Arvore * arvore , Livro * livro ) {
    if (arvore == NULL || livro == NULL) {
        printf("dados de livro ou arvore inválidos\n");
        return;
    }
    NoArvore * novo = malloc(sizeof(NoArvore));

    if (novo == NULL) {
        printf("Erro ao alocar no\n");
        return;
    }

    novo->livro = livro;
    novo->esquerda = NULL;
    novo->direita = NULL;

    // árvore vazia
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
        return;
    }
    //arvore com livros

    NoArvore * atual = arvore->raiz;
    NoArvore * pai = NULL;

    //organizando de acordo com o valor do código
    while (atual != NULL) {
        pai = atual;
        if (livro->codigo < atual->livro->codigo) {
            atual = atual->esquerda;
        }
        else if (livro->codigo > atual->livro->codigo) {
            atual = atual->direita;
        }
        else {
            // código repetido
            printf("Livro com codigo ja existe\n");
            free(novo);
            return;
        }
    }
    //definindo a posição do livro

    if (livro->codigo < pai->livro->codigo)
        pai->esquerda = novo;
    else
        pai->direita = novo;
}

Livro * buscarNo(NoArvore * no, int codigo) {

    if (no == NULL)
        return NULL;

    if (no->livro->codigo == codigo)
        return no->livro;

    if (codigo < no->livro->codigo)
        return buscarNo(no->esquerda, codigo);

    return buscarNo(no->direita, codigo);
}

Livro * buscarLivroArvore ( Arvore * arvore , int codigo ) {
    //arvore vazia ou com apenas um elemento
    if (arvore->raiz == NULL || arvore->raiz->codigo == codigo) {
        return arvore->raiz->livro;
    }
    return buscarNo(arvore->raiz, codigo);

    }

}
void listarLivrosEmOrdem ( Arvore * arvore ) ;
void listarLivrosPreOrdem ( Arvore * arvore ) ;
void listarLivrosPosOrdem ( Arvore * arvore ) ;
int contarLivros ( Arvore * arvore ) ;
int calcularAlturaArvore ( Arvore * arvore ) ;
