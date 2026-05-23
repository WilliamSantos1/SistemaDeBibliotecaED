typedef struct NoArvore {
    Livro * livro ;
    struct NoArvore * esquerda ;
    struct NoArvore * direita ;
} NoArvore ;

typedef struct Arvore {
    NoArvore * raiz ;
} Arvore ;