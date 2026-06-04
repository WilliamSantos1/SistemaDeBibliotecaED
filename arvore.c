#include <stdlib.h>
#include "arvore.h"
#include <stdio.h>

Arvore * criarArvore() {
    Arvore * arvore = (Arvore *) malloc(sizeof(Arvore));

    if (arvore == NULL) {
        printf("[Erro ao criar arvore.]\n");
        return NULL;
    }
    arvore->raiz = NULL;
    return arvore;
}

Livro * buscarLivroArvore ( Arvore * arvore , int codigo ) {
    if (arvore->raiz == NULL) {
        printf("[livro nao existente ou arvore vazia.]\n");
        return NULL;
    }
    if (arvore->raiz->livro->codigo == codigo) {
        return arvore->raiz->livro;
    }
    Arvore noEsq;
    noEsq.raiz = arvore->raiz->esquerda;
    Arvore noDir;
    noDir.raiz = arvore->raiz->direita;

    if (codigo < arvore->raiz->livro->codigo) {
        return buscarLivroArvore(&noEsq,codigo);
    }else {
        return buscarLivroArvore(&noDir,codigo);
    }

}

void listarLivrosEmOrdem ( Arvore * arvore ) {

    if (arvore->raiz != NULL) {
        //primeiro nó esquerdo
        Arvore  noEsq;
        noEsq.raiz = arvore->raiz->esquerda;
        listarLivrosEmOrdem(&noEsq);

        //nó do meio
        printf("[%d][%s]\n",arvore->raiz->livro->codigo,arvore->raiz->livro->titulo);

        //nó da direita
        Arvore noDir;
        noDir.raiz = arvore->raiz->direita;
        listarLivrosEmOrdem(&noDir);
    }
}

void listarLivrosPreOrdem ( Arvore * arvore ) {
    if (arvore->raiz != NULL) {
        //nó do meio
        printf("[%d][%s]\n",arvore->raiz->livro->codigo,arvore->raiz->livro->titulo);

        // nó esquerdo
        Arvore  noEsq;
        noEsq.raiz = arvore->raiz->esquerda;
        listarLivrosPreOrdem(&noEsq);

        //nó da direita
        Arvore noDir;
        noDir.raiz = arvore->raiz->direita;
        listarLivrosPreOrdem(&noDir);
    }
}
void listarLivrosPosOrdem ( Arvore * arvore ) {
    if (arvore->raiz != NULL) {
        // nó esquerdo
        Arvore  noEsq;
        noEsq.raiz = arvore->raiz->esquerda;
        listarLivrosPosOrdem(&noEsq);

        //nó da direita
        Arvore noDir;
        noDir.raiz = arvore->raiz->direita;
        listarLivrosPosOrdem(&noDir);

        //nó do meio
        printf("[%d][%s]\n",arvore->raiz->livro->codigo,arvore->raiz->livro->titulo);
    }
}
int contarLivros ( Arvore * arvore ) {
    if (arvore->raiz == NULL) {
        return 0;
    }
    Arvore noEsq;
    noEsq.raiz = arvore->raiz->esquerda;
    Arvore noDir;
    noDir.raiz = arvore->raiz->direita;

    return 1
    + contarLivros(&noEsq)
    + contarLivros(&noDir);
}
int calcularAlturaArvore ( Arvore * arvore ) {
    if (arvore->raiz == NULL) {
        return -1;
    }
    Arvore noEsq;
    noEsq.raiz = arvore->raiz->esquerda;
    Arvore noDir;
    noDir.raiz = arvore->raiz->direita;

    int alturaEsquerda = calcularAlturaArvore(&noEsq);
    int alturaDireita = calcularAlturaArvore(&noDir);

    if (alturaEsquerda > alturaDireita) {
        return alturaEsquerda + 1;
    }else {
        return alturaDireita + 1;
    }
}

int fatorBalanceamento(Arvore *arvore) {
    if (arvore->raiz == NULL) {
        return 0;
    }

    Arvore noEsq;
    noEsq.raiz = arvore->raiz->esquerda;

    Arvore noDir;
    noDir.raiz = arvore->raiz->direita;

    int alturaEsquerda = calcularAlturaArvore(&noEsq);
    int alturaDireita = calcularAlturaArvore(&noDir);

    return alturaEsquerda - alturaDireita;
}
void rotacaoDireita(Arvore *arvore) {
    NoArvore *novaRaiz = arvore->raiz->esquerda;
    NoArvore *subArvore = novaRaiz->direita;

    novaRaiz->direita = arvore->raiz;
    arvore->raiz->esquerda = subArvore;

    arvore->raiz = novaRaiz;
}
void rotacaoEsquerda(Arvore *arvore) {
    NoArvore *novaRaiz = arvore->raiz->direita;
    NoArvore *subArvore = novaRaiz->esquerda;

    novaRaiz->esquerda = arvore->raiz;
    arvore->raiz->direita = subArvore;

    arvore->raiz = novaRaiz;
}

void inserirLivroArvore ( Arvore * arvore , Livro * livro ) {
    if (arvore == NULL || livro == NULL) {
        printf("[Dados de livro ou arvore inválidos.]\n");
        return;
    }

    NoArvore * novo = malloc(sizeof(NoArvore));

    if (novo == NULL) {
        printf("[Erro ao alocar memória para o livro.]\n");
        return;
    }

    novo->livro = livro;
    novo->esquerda = NULL;
    novo->direita = NULL;

    // nó vazio ou arvore vazia
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
        printf("[Livro adicionado ao acervo da biblioteca com sucesso!]\n");

        //verificar balanceamento
        int altura = fatorBalanceamento(arvore);
        if (altura < -1) {
            //no da direita maior
            rotacaoEsquerda(arvore);
        }else if ( altura > 1) {
            //no da esquerda maior
            rotacaoDireita(arvore);
        }
        return;
    }
    free(novo);

    //arvore com livros, repetir a função dependendo do valor do código

    if (livro->codigo < arvore->raiz->livro->codigo) {

        Arvore noEsq;
        noEsq.raiz = arvore->raiz->esquerda;
        inserirLivroArvore(&noEsq,livro);

        arvore->raiz->esquerda = noEsq.raiz;
    }else {

        Arvore noDir;
        noDir.raiz = arvore->raiz->direita;
        inserirLivroArvore(&noDir,livro);

        arvore->raiz->direita = noDir.raiz;
    }
}