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
Arvore *arvoreMenorLivroCodigo(Arvore *arvore) {

    while (arvore->raiz->esquerda != NULL) {
        arvore->raiz = arvore->raiz->esquerda;
    }

    return arvore;
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
        printf("\n[Dados de livro ou arvore invalidos.]\n");
        return;
    }

    if (arvore->raiz == NULL) {
        NoArvore *novo = malloc(sizeof(NoArvore));

        if (novo == NULL) {
            printf("\n[Erro ao alocar memoria.]\n");
            return;
        }

        novo->livro = livro;
        novo->esquerda = NULL;
        novo->direita = NULL;

        arvore->raiz = novo;
        return;
    }

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
    //verificar balanceamento
    int fb = fatorBalanceamento(arvore);

    if (fb > 1) {
        //ramo da esquerda maior que direita

        Arvore esq;
        esq.raiz = arvore->raiz->esquerda;

        int fbEsq = fatorBalanceamento(&esq);

        if (fbEsq >= 0) {
            // LL
            rotacaoDireita(arvore);
        } else {
            // LR
            rotacaoEsquerda(&esq);
            arvore->raiz->esquerda = esq.raiz;
            rotacaoDireita(arvore);
        }
    }else if (fb < -1) {
        //ramo da direita maior que o da esquerda
        Arvore dir;
        dir.raiz = arvore->raiz->direita;

        int fbDir = fatorBalanceamento(&dir);

        if (fbDir <= 0) {
            // RR
            rotacaoEsquerda(arvore);
        } else {
            // RL
            rotacaoDireita(&dir);
            arvore->raiz->direita = dir.raiz;
            rotacaoEsquerda(arvore);
        }
    }

}
void removerLivroArvore(Arvore * arvore , Livro * livro) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("[livro nao encontrado!]\n");
        return;
    }

    if (livro->codigo < arvore->raiz->livro->codigo) {
        Arvore arvoreEsq;
        arvoreEsq.raiz = arvore->raiz->esquerda;
        removerLivroArvore(&arvoreEsq,livro);
        arvore->raiz->esquerda = arvoreEsq.raiz;

    }else if (livro->codigo > arvore->raiz->livro->codigo) {
        Arvore arvoreDir;
        arvoreDir.raiz = arvore->raiz->direita;
        removerLivroArvore(&arvoreDir,livro);
        arvore->raiz->direita = arvoreDir.raiz;

    }else {
        //encontrou o Nó
        //caso 1 Nó sem filhos
        if (arvore->raiz->esquerda == NULL && arvore->raiz->direita == NULL) {
            free(arvore->raiz);
            arvore->raiz = NULL;
            printf("[Livro removido com sucesso.]\n");
            return;
        } else if (arvore->raiz->esquerda == NULL) {
            //caso 2 Nó com um filho a direita
            NoArvore *temp = arvore->raiz;
            arvore->raiz = arvore->raiz->direita;
            free(temp);
            printf("[Livro removido com sucesso.]\n");
            return;
        } else if (arvore->raiz->direita == NULL) {
            //caso 2 Nó com um filho a esquerda
            NoArvore *temp = arvore->raiz;
            arvore->raiz = arvore->raiz->esquerda;
            free(temp);
            printf("[Livro removido com sucesso.]\n");
            return;
        }else {
            //caso 3 Nó com dois filhos
            Arvore temp;
            temp.raiz = arvore->raiz->direita;
            Arvore *sucessor = arvoreMenorLivroCodigo(&temp);
            arvore->raiz->livro = sucessor->raiz->livro;

            Arvore dir;
            dir.raiz = arvore->raiz->direita;

            removerLivroArvore(&dir, sucessor->raiz->livro);
            arvore->raiz->direita = dir.raiz;
        }
    }
    //verificar balanceamento
    int fb = fatorBalanceamento(arvore);

    if (fb > 1) {
        //ramo da esquerda maior que direita

        Arvore esq;
        esq.raiz = arvore->raiz->esquerda;

        int fbEsq = fatorBalanceamento(&esq);

        if (fbEsq >= 0) {
            // LL
            rotacaoDireita(arvore);
        } else {
            // LR
            rotacaoEsquerda(&esq);
            arvore->raiz->esquerda = esq.raiz;
            rotacaoDireita(arvore);
        }
    }else if (fb < -1) {
        //ramo da direita maior que o da esquerda
        Arvore dir;
        dir.raiz = arvore->raiz->direita;

        int fbDir = fatorBalanceamento(&dir);

        if (fbDir <= 0) {
            // RR
            rotacaoEsquerda(arvore);
        } else {
            // RL
            rotacaoDireita(&dir);
            arvore->raiz->direita = dir.raiz;
            rotacaoEsquerda(arvore);
        }
    }
}

void imprimirNivel(NoArvore *raiz, int nivel, int base, int altura) {

    if (raiz == NULL) {
        //se altura par ou inpar é igual a base
         if (altura -1 == base && altura % 2 != 0 ||
             altura/2 == base && altura % 2 == 0) {
            //esta na base
            printf("[ ] ");
            }else {
                for (int i = 0; i<base; i++) {
                    printf(" ");
                }
            }
        return;
        }

    if (nivel == 0) {
        if (altura -1 != base) {
            for (int i = 0; i<base; i++) {
                printf(" ");
            }
            printf("[%d]", raiz->livro->codigo);
        }else {
            printf("[%d] ", raiz->livro->codigo);
        }
        return;
    }

    imprimirNivel(raiz->esquerda, nivel - 1, base/2, altura);
    imprimirNivel(raiz->direita, nivel - 1, base/2, altura);
}

void imprimirArvore(Arvore * arvore) {
    if (arvore->raiz == NULL) {
        printf("\n[Arvore vazia!]\n");
        return;
    }
    int altura = calcularAlturaArvore(arvore);

    //calculando a largura da base para definir o espaçamento entre níveis
    int larguraBase = 2;
    for (int w = altura; w > 0;w--) {
        larguraBase = larguraBase*2;
    }

    printf("\n===============================\n");
    printf("Arvore de Livros\n");
    printf("\n-------------------------------\n");
    //imprimindo arvore nível por nível
    for (int i = 0; i < altura + 1; i++) {
        imprimirNivel(arvore->raiz,i,larguraBase, altura);
        printf("\n");
    }
    printf("\n-------------------------------");


}

void liberarArvore(NoArvore *no) {
    if (no == NULL)
        return;

    liberarArvore(no->esquerda);
    liberarArvore(no->direita);

    free(no->livro);
    free(no);
}