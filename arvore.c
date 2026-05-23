#include <stdlib.h>
#include "arvore.h"

#include <stdio.h>

Arvore * criarArvore() {
    Arvore * arvore = (Arvore *) malloc(sizeof(Arvore));

    if (arvore != NULL) {
        printf("Erro ao criar arvore\n");
        arvore->raiz = NULL;
    }

    return arvore;
}
