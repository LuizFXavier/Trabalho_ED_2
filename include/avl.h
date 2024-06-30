#pragma once

typedef int Type;
#define INT 1
#define FLOAT 2
#define STR 3

// Estruturas utilizadas na Árvore

typedef struct container{
    char* cod;
    void* chave;
    struct container* prox;
}Container;

typedef struct no{

    Container* reg;
    int altura;
    struct no* esq;
    struct no* dir;
    struct no* pai;
}No;

typedef struct{
    No* raiz;
    Type tipo;
    int (*cmp)(const void*, const void*);
}Avl;

// Construtores de estruturas
Avl* cria_avl(Type tipo);
No* cria_no(Container* reg);
Container* cria_reg(char* cod, void* reg);

// Comparadores para cada tipo
int cmp_int(const void* a, const void* b);
int cmp_float(const void* a, const void* b);
int cmp_str(const void* a, const void* b);

// Funções utilitárias AVL
int max(int a, int b);
int altura_no(No* no);
No** percorre_esq(No** sub_arv);
No* _procura_esq(No* sub_arv);
No* sucessor(No* no);

// Lógica de rebalanceamento da AVL
void rebalanceia(No** sub_arv);
void rot_esq(No** sub_arv);
void rot_dir(No** sub_arv);

// Lógica de inserção na AVL
void insere_no(Avl* arv, No** no_atual, Container* reg);
void insere_AVL(Avl* arv, char* cod, void* chave);
void _insere_mesmo_no(No** no, Container* reg);

// Busca na AVL
No* busca_AVL(Avl* arv, void* chave);
No* _busca_no(Avl* arv, No* no_atual, void* chave);
No * busca_AVL_prox(Avl* arv, void* reg);
No * _busca_no_prox(Avl* arv, No* no_atual, void* reg);

// Remoção na AVL (não requisitado)
void * remove_AVL(Avl* arv, void* item);
void * _remove_no(Avl* arv, No** no, void* item);

// Liberação de memória
void destroi_AVL(No* no);