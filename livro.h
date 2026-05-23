#ifndef LIVRO_H
#define LIVRO_H

typedef struct Livro {
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    int quantidadeTotal;
    int quantidadeDisponivel;
} Livro;

#endif