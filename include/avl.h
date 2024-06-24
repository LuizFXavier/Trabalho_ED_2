#pragma once

typedef struct container{
    void* reg;
    struct container* prox;
}t_cont;

typedef struct no{

    t_cont* reg;
    int altura;
    struct no* esq;
    struct no* dir;
    struct no* pai;
}t_no;

typedef struct{
    t_no* raiz;
    int (*cmp)(const void*, const void*);
}t_avl;

t_avl* cria_avl(int (*cmp)(const void*, const void*));
t_no* cria_no(void* reg);

int max(int a, int b);
int altura_no(t_no* no);

// void percorre(t_no* no);

void rebalanceia(t_no** sub_arv);
void rot_esq(t_no** sub_arv);
void rot_dir(t_no** sub_arv);
t_no** percorre_esq(t_no** sub_arv);
t_no* sucessor(t_no* no);
t_no* _procura_esq(t_no* sub_arv);

void insere_no(t_avl* arv, t_no** no_atual, void* reg);
void insere_AVL(t_avl* arv, void* reg);
void _insere_mesmo_no(t_no* no, void* reg);

void * busca_AVL(t_avl* arv, void* reg);
void * busca_no(t_avl* arv, t_no* no_atual, void* reg);

void * remove_AVL(t_avl* arv, void* item);
void * _remove_no(t_avl* arv, t_no** no, void* item);

void destroi_AVL(t_no* no);