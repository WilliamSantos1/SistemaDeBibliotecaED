# Sistema de Biblioteca em C

## Descrição

Projeto desenvolvido para a disciplina de Estrutura de Dados utilizando a linguagem C.

O sistema simula o gerenciamento de uma biblioteca por meio de estruturas de dados clássicas:

* Árvore Binária de Busca (ABB/AVL) para armazenamento dos livros.
* Fila para gerenciamento das reservas.
* Lista Encadeada para histórico de empréstimos.

O objetivo é permitir o cadastro, consulta, empréstimo, devolução e reserva de livros de forma organizada e eficiente.

---

## Integrantes

* William
* Beatriz
* Vitória

---

## Estruturas de Dados Utilizadas

### Árvore Binária de Busca (ABB)

Responsável pelo armazenamento e gerenciamento dos livros cadastrados.

Funcionalidades:

* Inserção de livros
* Busca por código
* Remoção de livros
* Listagem em ordem
* Listagem em pré-ordem
* Listagem em pós-ordem
* Balanceamento da árvore

---

### Fila de Reservas

Responsável pelo controle das reservas quando um livro não possui exemplares disponíveis.

Funcionalidades:

* Inserção de reservas (enqueue)
* Remoção de reservas (dequeue)
* Verificação de fila vazia
* Exibição da fila de reservas

---

### Lista Encadeada de Histórico

Responsável por armazenar o histórico dos empréstimos realizados.

Funcionalidades:

* Inserção de registros
* Listagem do histórico
* Verificação de lista vazia

---

## Funcionalidades do Sistema

* Cadastrar livros
* Buscar livro por código
* Listar livros cadastrados
* Realizar empréstimos
* Realizar devoluções
* Reservar livros indisponíveis
* Exibir fila de reservas
* Exibir histórico de empréstimos

---

## Estrutura do Projeto

```text
ProjetoBiblioteca/

├── main.c
├── livro.c
├── livro.h
├── arvore.c
├── arvore.h
├── fila.c
├── fila.h
├── lista.c
├── lista.h
└── README.md
```

---

## Compilação

### Utilizando CLion

1. Abrir o projeto no CLion.
2. Configurar o compilador C.
3. Executar o arquivo `main.c`.

### Utilizando GCC

```bash
gcc main.c livro.c arvore.c fila.c lista.c -o biblioteca
```

Execução:

```bash
./biblioteca
```

---

## Exemplo de Uso

1. Listar os livros cadastrados.
2. Buscar um livro pelo código.
3. Realizar empréstimos.
4. Registrar o empréstimo no histórico.
5. Caso não haja exemplares disponíveis, adicionar o usuário à fila de reservas.
6. Devolver livros e liberar reservas pendentes.

---

## Tecnologias Utilizadas

* Linguagem C
* CLion
* Estruturas de Dados

  * Árvore Binária de Busca
  * Fila
  * Lista Encadeada

---

## Objetivo Acadêmico

Este projeto foi desenvolvido com fins acadêmicos para aplicar conceitos de Estruturas de Dados, manipulação de memória dinâmica, modularização de código e integração entre diferentes estruturas em linguagem C.
