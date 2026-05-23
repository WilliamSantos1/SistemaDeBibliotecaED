#ifndef ARVORE_H
#define ARVORE_H
#include "livro.h"

typedef struct NoArvore {
    Livro * livro ;
    struct NoArvore * esquerda ;
    struct NoArvore * direita ;
} NoArvore ;

typedef struct Arvore {
    NoArvore * raiz ;
} Arvore ;

#endif