#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"
#include "cidade.h"

void percorre(No* no){
    
    printf("\n%d: ",no->altura);
    // if(no->pai){
    //     printf("Qual filho? %d:%d\n", no->pai->esq == no, no->pai->dir == no);
    // }

    Container* atual = no->reg;

    while (atual)
    {
        printf("%d, ", *((int*)(atual->chave)));
        atual = atual->prox;    
    }
    
    if(no->esq){
        percorre(no->esq);
    }
    if(no->dir){
        percorre(no->dir);
    }
}

Container* cria_reg(char* cod, void* chave){
    Container* novo = (Container*) malloc(sizeof(Container));
    // printf("chave: %f\n",*((float*)chave));
    novo->cod = malloc(sizeof(char*));
    strcpy(novo->cod, cod);
    novo->prox = NULL;
    novo->chave = chave;

    return novo;
}

Avl* cria_avl(Type tipo){
    Avl* nova = malloc(sizeof(Avl));

    nova->raiz = NULL;
    nova->tipo = tipo;

    switch (tipo)
    {
    case INT:
        nova->cmp = cmp_int;
        break;
    
    case FLOAT:
        nova->cmp = cmp_float;
        break;
    
    case STR:
        nova->cmp = cmp_str;
        break;

    default:
        nova->cmp = cmp_int;
        break;
    }

    return nova;
}

No* cria_no(Container* reg){
    No* novo = malloc(sizeof(No));
    
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->reg = cria_reg(reg->cod, reg->chave);

    return novo;
}

int cmp_int(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}
int cmp_float(const void* a, const void* b){
    return (int)(*((float*)a)) - (int)(*((float*)b));
    
}
int cmp_str(const void* a, const void* b){
    return strcmp((char*)a, (char*)b);
}

int max(int a, int b){
    return a > b ? a:b;
}

int altura_no(No* no){
    if(no == NULL){
        return -1;
    }
    return no->altura;
}

void rebalanceia(No** sub_arv){
    int fatorB;
    int fB_filho;
    No* filho;

    fatorB = altura_no((*sub_arv)->esq) - altura_no((*sub_arv)->dir);

    if(fatorB == -2){ //Lado direito mais pesado
        filho = (*sub_arv)->dir;
        fB_filho = altura_no(filho->esq) - altura_no(filho->dir);

        if(fB_filho <= 0){
            rot_esq(sub_arv);
        }
        else{
            rot_dir(&((*sub_arv)->dir));
            rot_esq(sub_arv);
        }
    }
    if(fatorB == 2){
        filho = (*sub_arv)->esq;
        fB_filho = altura_no(filho->esq) - altura_no(filho->dir);

        if(fB_filho > 0){
            rot_dir(sub_arv);
        }
        else{
            rot_esq(&((*sub_arv)->esq));
            rot_dir(sub_arv);
        }
    }
    
}

/**
 * Função recursiva que inserirá o novo registro no nó correto.
 * @param reg Registro a ser armazenado.
*/
void insere_no(Avl* arv, No** no_atual, Container* reg){
    
    if(arv->cmp((*no_atual)->reg->chave, reg->chave) < 0){
        if((*no_atual)->dir){
            
            insere_no(arv, &(*no_atual)->dir, reg);
        }
        else{
            (*no_atual)->dir = cria_no(reg);
            (*no_atual)->dir->pai = (*no_atual);
        }
    }

    else if(arv->cmp((*no_atual)->reg->chave, reg->chave) > 0){
        
        if((*no_atual)->esq){
            
            insere_no(arv, &(*no_atual)->esq, reg);
        }
        else{
            (*no_atual)->esq = cria_no(reg);
            (*no_atual)->esq->pai = (*no_atual);
        }
    }
    else{ //Inserção em um nó já ocupado
        
       _insere_mesmo_no(no_atual, reg);
    }

    (*no_atual)->altura = max(altura_no((*no_atual)->esq), altura_no((*no_atual)->dir)) + 1;
    
    rebalanceia(no_atual);
}
/**
 * Dado um nó, coloca o novo registro no início da lista ligada presente nele.
*/
void _insere_mesmo_no(No** no, Container* reg){

    Container* item = cria_reg(reg->cod, reg->chave);

    item->prox = (*no)->reg;
    
    (*no)->reg = item;

}

void insere_AVL(Avl* arv, char* cod, void* chave){

    Container reg = *cria_reg(cod, chave);

    if(arv->raiz == NULL){
        arv->raiz = cria_no(&reg);
        return;
    }

    insere_no(arv, &arv->raiz, &reg);

    // free(reg);
}

void rot_esq(No **sub_arv)
{
    No* X = *sub_arv;
    No* A = X->esq;
    No* Y = X->dir;
    No* B = Y->esq;
    No* C = Y->dir;

    if(B)
        B->pai = X;
    Y->pai = X->pai;
    X->pai = Y;

    X->dir = B;
    Y->esq = X;
    *sub_arv = Y;

    X->altura = max(altura_no(A), altura_no(B)) + 1;
    Y->altura = max(altura_no(X), altura_no(C)) + 1;
}

void rot_dir(No **sub_arv)
{
    No* Y = *sub_arv;
    No* X = Y->esq;
    No* A = X->esq;
    No* B = X->dir;
    No* C = Y->dir;

    if(B)
        B->pai = Y;
    X->pai = Y->pai;
    Y->pai = X;

    X->dir = Y;
    Y->esq = B;
    *sub_arv = X;

    Y->altura = max(altura_no(B), altura_no(C)) + 1;
    X->altura = max(altura_no(Y), altura_no(A)) + 1;

}

/**
 * Busca na AVL por um elemento exato
 * @return Nó com a chave especificada ou NULL caso não a encontre;
*/
No* busca_AVL(Avl* arv, void* chave){

    No * busca = NULL;

    if(arv->raiz)
        busca = _busca_no(arv, arv->raiz, chave);

    return busca;
}

No * _busca_no(Avl* arv, No* no_atual, void* chave){
    
    if(!no_atual)
        return NULL;

    if(arv->cmp(no_atual->reg->chave, chave) < 0){

        return _busca_no(arv, no_atual->dir, chave);
    }
    else if(arv->cmp(no_atual->reg->chave, chave) > 0){

        return _busca_no(arv, no_atual->esq, chave);
    }
    else{
        return no_atual;
    }
}
/**
 * Busca pelo nó com o valor mais próximo ao fornecido.
 * @param chave Valor a ser procurado.
 * @return Nó com a chave especificada ou nó folha com chave menor ou igual a chave.
*/
No *busca_AVL_prox(Avl *arv, void *chave)
{
    No * busca = NULL;

    if(arv->raiz)
        busca = _busca_no_prox(arv, arv->raiz, chave);
    
    return busca;
}

No *_busca_no_prox(Avl *arv, No *no_atual, void *chave)
{ 
    if(arv->cmp(no_atual->reg->chave, chave) < 0){
        
        if(!no_atual->dir)
            return no_atual;
        return _busca_no_prox(arv, no_atual->dir, chave);

    }
    else if(arv->cmp(no_atual->reg->chave, chave) > 0){

        if(!no_atual->esq)
            return no_atual;
        return _busca_no_prox(arv, no_atual->esq, chave);
    }
    else{
        return no_atual;
    }
}

void * remove_AVL(Avl* arv, void* item){
    
    return _remove_no(arv, &arv->raiz, item);
    
}

void * _remove_no(Avl* arv, No** no, void* item){

    
    void* ret = NULL;
    No* aux = *no;

    if(arv->cmp((*no)->reg, item) < 0){
        if((*no)->dir){

            ret = _remove_no(arv, &((*no)->dir), item);
        }
    }
    else if(arv->cmp((*no)->reg, item) > 0){
        
        if((*no)->esq){

            ret = _remove_no(arv, &((*no)->esq), item);
        }
    }
    else{
        ret = (*no)->reg;

        if(!(*no)->esq && !(*no)->dir){
            free(*no);
            *no = NULL;
            
        }

        else if(!(*no)->esq || !(*no)->dir){
            
            if((*no)->esq){
                *no = (*no)->esq;
            }
            else{
                *no = (*no)->dir;
            }
            free(aux);
        }else{
            
            No** sucessor = percorre_esq(&(*no)->dir);
            (*no)->reg = (*sucessor)->reg;
            _remove_no(arv, &(*no)->dir, (*sucessor)->reg);
        }

    }
    if(*no != NULL){
        (*no)->altura = max(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
        rebalanceia(no);
    }


    return ret;
}

No** percorre_esq(No** sub_arv){
    No** ret = sub_arv;

    while ((*ret)->esq)
    {
        *ret = (*ret)->esq;
    }

    return ret;
    
}

/**
 * Busca por nó mais a esquerda de uma sub-árvore fornecida.
*/
No* _procura_esq(No* sub_arv){

    while (sub_arv->esq)
    {
        sub_arv = sub_arv->esq;
    }

    return sub_arv;
}

/**
 * Função que retorna o sucessor de um nó especificado
 * @return Nó sucessor se o encontrar ou NULL caso não.
*/
No *sucessor(No *no)
{
    //Caso tenha sub-árvore direita, percorra a esquerda nesta para achar o sucessor
    if(no->dir){
        return _procura_esq(no->dir);
    }

    //Caso não tenha direita e seja a raíz, retorne nada
    if(!no->pai) 
        return NULL;

    //Caso não tenha direita e seja um filho à esquerda de seu pai, retorne este
    if(no->pai->esq == no){
        return no->pai;
    }

    //Faz a iteração reversa na árvore enquanto o nó atual for filho a direita de seu pai
    
    while (no->pai && no == no->pai->dir)
    {   
        no = no->pai;
    }

    return no->pai;
}

/**
 * Liberação de memória da AVL
 * @param no Raiz da sub-árvore a ser deletada.
*/
void destroi_AVL(No* no){

    Container* prox;

    while (no->reg) {
        prox = no->reg->prox;
        free(no->reg);
        no->reg = prox;
    }

    if(no->esq){
        destroi_AVL(no->esq);
    }
    if(no->dir){
        destroi_AVL(no->dir);
    }
    free(no);   
}