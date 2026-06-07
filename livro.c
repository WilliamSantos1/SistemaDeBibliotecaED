#include <stdlib.h>
#include "livro.h"
#include <string.h>
#include <stdio.h>

Livro * criarLivro ( int codigo , char titulo [] , char autor [] ,int ano , int quantidadeTotal ) {
    Livro * livro = (Livro *) malloc(sizeof(Livro));

    if (livro == NULL) {
        printf("Erro ao criar livro");
        return NULL;
    }
    livro -> codigo = codigo;
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    livro -> ano = ano;
    livro -> quantidadeTotal = quantidadeTotal;
    livro->quantidadeDisponivel = quantidadeTotal;
    printf("[livro criado com sucesso!]\n");
    return livro;
}

void exibirLivro ( Livro * livro ) {
    printf("|Titulo: %s\n", livro -> titulo);
    printf("|Autor: %s\n", livro -> autor);
    printf("|Ano: %d\n", livro -> ano);
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
        printf("[Sem livros disponíveis para emprestar.]");
    }
}
void devolverExemplar ( Livro * livro ) {
    livro -> quantidadeDisponivel++;
}