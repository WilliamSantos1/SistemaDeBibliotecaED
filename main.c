#include <stdlib.h>
#include "arvore.c"
#include "livro.c"
#include <stdio.h>


int main(void) {

    Livro *livro = criarLivro(1,"joaozinho gamer","johon",1999,1);
    Livro *livro2 = criarLivro(2,"joaozinho que brincou com robo","jonas",1998,1);
    Livro *livro3 = criarLivro(3,"matematica","joao",1300,1);
    Livro *livro4 = criarLivro(4,"portugues","joao",1300,1);
    Livro *livro5 = criarLivro(5,"Thaeon do bts","vivi",2026,1);
    Arvore * arvore;
    arvore = criarArvore();
    //antes de inserir precisa buscar o livro para ver se ele já não está na biblioteca
    inserirLivroArvore(arvore, livro);
    inserirLivroArvore(arvore, livro2);
    inserirLivroArvore(arvore, livro3);
    inserirLivroArvore(arvore, livro4);
    inserirLivroArvore(arvore, livro5);

    Livro *busca = buscarLivroArvore(arvore,5);
    if (busca != NULL) {
        exibirLivro(busca);
    }
    int quant = contarLivros(arvore);
    int altura = calcularAlturaArvore(arvore);
    printf("\nquantidade de livros: %d \n", quant);
    printf("altura da arvore: %d \n", altura);
    printf("\nlivros em ordem\n");
    listarLivrosEmOrdem(arvore);
    printf("\nlivros em pre-ordem\n");
    listarLivrosPreOrdem(arvore);
    printf("\nlivros em pos-ordem\n");
    listarLivrosPosOrdem(arvore);
    printf("\nlivros 2 removido\n");
    removerLivroArvore(arvore,livro2);
    printf("\nlivros 2 removido\n");
    printf("\nlivros em pre-ordem\n");
    listarLivrosPreOrdem(arvore);
    removerLivroArvore(arvore,livro2);
    return 0;
}
