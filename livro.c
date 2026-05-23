#include <stdlib.h>
#include "livro.h"

#include <stdio.h>

Livro * criarLivro ( int codigo , char titulo [] , char autor [] ,int ano , int quantidadeTotal ) {
    Livro * livro = (Livro *) malloc(sizeof(Livro));

    if (livro == NULL) {
        printf("Erro ao criar livro");
        return NULL;
    }
    livro -> codigo = codigo;
    livro ->titulo = titulo;
    livro -> autor = autor;
    livro -> ano = ano;
    livro -> quantidadeTotal = quantidadeTotal;
    return livro;
}

void exibirLivro ( Livro * livro ) {
    printf("Titulo: %s", livro -> titulo);
    printf("Autor: %s", livro -> autor);
    printf("Ano: %d", livro -> ano);
}

int obterCodigoLivro ( Livro * livro ) {
    return livro -> codigo;
}
int obterQuantidadeDisponivel ( Livro * livro ) {
    return livro -> quantidadeDisponivel;
}
void emprestarExemplar ( Livro * livro ) {
    if (livro -> quantidadeDisponivel >0 ) {
        livro -> quantidadeDisponivel--;
    }else {
        printf("Sem livros disponíveis para emprestar");
    }
}
void devolverExemplar ( Livro * livro ) {
    livro -> quantidadeDisponivel++;
}