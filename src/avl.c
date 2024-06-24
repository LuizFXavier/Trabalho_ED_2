#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include "cidade.h"

void percorre(t_no* no){
    
    printf("\n%d: ",no->altura);
    // if(no->pai){
    //     printf("Qual filho? %d:%d\n", no->pai->esq == no, no->pai->dir == no);
    // }

    t_cont* atual = no->reg;

    printf("%d, ", ((c_ddd*)(atual->reg))->ddd);
    // while (atual)
    // {
    //     atual = atual->prox;    
    // }
    
    if(no->esq){
        percorre(no->esq);
    }
    if(no->dir){
        percorre(no->dir);
    }
}

t_cont* cria_reg(void* reg){
    t_cont* novo = (t_cont*) malloc(sizeof(t_cont));
    novo->prox = NULL;
    novo->reg = reg;

    return novo;
}

t_avl* cria_avl(int (*cmp)(const void*, const void*)){
    t_avl* nova = malloc(sizeof(t_avl));

    nova->raiz = NULL;
    nova->cmp = cmp;

    return nova;
}
t_no* cria_no(void* reg){
    t_no* novo = malloc(sizeof(t_no));
    
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->reg = cria_reg(reg);

    return novo;
}

int max(int a, int b){
    return a > b ? a:b;
}

int altura_no(t_no* no){
    if(no == NULL){
        return -1;
    }
    return no->altura;
}

void rebalanceia(t_no** sub_arv){
    int fatorB;
    int fB_filho;
    t_no* filho;

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

void insere_no(t_avl* arv, t_no** no_atual, void* reg){
    

    if(arv->cmp((*no_atual)->reg->reg, reg) < 0){
        
        if((*no_atual)->dir){
            
            insere_no(arv, &(*no_atual)->dir, reg);
        }
        else{
            (*no_atual)->dir = cria_no(reg);
            (*no_atual)->dir->pai = (*no_atual);
        }
    }

    else if(arv->cmp((*no_atual)->reg->reg, reg) > 0){
        if((*no_atual)->esq){
            
            insere_no(arv, &(*no_atual)->esq, reg);
        }
        else{
            (*no_atual)->esq = cria_no(reg);
            (*no_atual)->esq->pai = (*no_atual);
        }
    }
    else{ //Inserção em um nó já ocupado
        
       _insere_mesmo_no(*no_atual, reg);
    }

    (*no_atual)->altura = max(altura_no((*no_atual)->esq), altura_no((*no_atual)->dir)) + 1;

    
    rebalanceia(no_atual);
}
void _insere_mesmo_no(t_no* no, void* reg){
    
    t_cont* item = cria_reg(reg);

    t_cont* bloco = no->reg;

    while (bloco->prox)
    {
        bloco = bloco->prox;
    }

    bloco->prox = item;
    
}

void insere_AVL(t_avl* arv, void* reg){

    if(arv->raiz == NULL){
        arv->raiz = cria_no(reg);
        return;
    }

    insere_no(arv, &arv->raiz, reg);
}

void rot_esq(t_no **sub_arv)
{
    t_no* X = *sub_arv;
    t_no* A = X->esq;
    t_no* Y = X->dir;
    t_no* B = Y->esq;
    t_no* C = Y->dir;
    // printf("Rot esquerda:\n");
    // if(X)
    // printf("X:%d\n",((c_ddd*)(X->reg->reg))->ddd);
    // if(Y)
    // printf("Y:%d\n",((c_ddd*)(Y->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->reg->reg))->ddd);
    // printf("\npais:\n");
    // if(X->pai)
    //     printf("X:%d\n",((c_ddd*)(X->pai->reg->reg))->ddd);
    
    // if(Y->pai)
    //     printf("Y:%d\n",((c_ddd*)(Y->pai->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->pai->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->pai->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->pai->reg->reg))->ddd);
    
    // printf("\n");
    if(B)
        B->pai = X;
    Y->pai = X->pai;
    X->pai = Y;

    X->dir = B;
    Y->esq = X;
    *sub_arv = Y;

    // if(X)
    // printf("X:%d\n",((c_ddd*)(X->reg->reg))->ddd);
    // if(Y)
    // printf("Y:%d\n",((c_ddd*)(Y->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->reg->reg))->ddd);
    // printf("\npais:\n");
    // if(X->pai)
    // printf("X:%d\n",((c_ddd*)(X->pai->reg->reg))->ddd);
    // if(Y->pai)
    // printf("Y:%d\n",((c_ddd*)(Y->pai->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->pai->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->pai->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->pai->reg->reg))->ddd);

    // printf("\n------------------\n");


    X->altura = max(altura_no(A), altura_no(B)) + 1;
    Y->altura = max(altura_no(X), altura_no(C)) + 1;
}

void rot_dir(t_no **sub_arv)
{
    t_no* Y = *sub_arv;
    t_no* X = Y->esq;
    t_no* A = X->esq;
    t_no* B = X->dir;
    t_no* C = Y->dir;
    // printf("Rot dir:\n");
    // if(X)
    // printf("X:%d\n",((c_ddd*)(X->reg->reg))->ddd);
    // if(Y)
    // printf("Y:%d\n",((c_ddd*)(Y->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->reg->reg))->ddd);
    // printf("\npais:\n");
    // if(X->pai)
    // printf("X:%d\n",((c_ddd*)(X->pai->reg->reg))->ddd);
    // if(Y->pai)
    // printf("Y:%d\n",((c_ddd*)(Y->pai->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->pai->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->pai->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->pai->reg->reg))->ddd);

    // printf("\n");


    if(B)
        B->pai = Y;
    X->pai = Y->pai;
    Y->pai = X;

    X->dir = Y;
    Y->esq = B;
    *sub_arv = X;

    // if(X)
    // printf("X:%d\n",((c_ddd*)(X->reg->reg))->ddd);
    // if(Y)
    // printf("Y:%d\n",((c_ddd*)(Y->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->reg->reg))->ddd);
    // printf("\npais:\n");
    // if(X->pai)
    // printf("X:%d\n",((c_ddd*)(X->pai->reg->reg))->ddd);
    // if(Y->pai)
    // printf("Y:%d\n",((c_ddd*)(Y->pai->reg->reg))->ddd);
    // if(A)
    //     printf("A:%d\n", ((c_ddd*)(A->pai->reg->reg))->ddd);
    // if(B)
    //     printf("B:%d\n",((c_ddd*)(B->pai->reg->reg))->ddd);
    // if(C)
    //     printf("C:%d\n",((c_ddd*)(C->pai->reg->reg))->ddd);

    // printf("\n------------------\n");

    Y->altura = max(altura_no(B), altura_no(C)) + 1;
    X->altura = max(altura_no(Y), altura_no(A)) + 1;

}

void *busca_AVL(t_avl *arv, void *reg)
{
    void * busca = busca_no(arv, arv->raiz, reg);
    return busca;
}

void destroi_AVL(t_no* no){
    if(no->esq){
        destroi_AVL(no->esq);
    }
    if(no->dir){
        destroi_AVL(no->dir);
    }
    free(no);   
}

void *busca_no(t_avl *arv, t_no *no_atual, void *reg)
{
    if(no_atual == NULL){
        return NULL;
    }
    else if(arv->cmp(no_atual->reg, reg) < 0){
        
        return busca_no(arv, no_atual->dir, reg);

    }
    else if(arv->cmp(no_atual->reg, reg) > 0){
        
        return busca_no(arv, no_atual->esq, reg);
    }
    else{
        return no_atual->reg;
    }
}

void * remove_AVL(t_avl* arv, void* item){
    
    return _remove_no(arv, &arv->raiz, item);
    
}

void * _remove_no(t_avl* arv, t_no** no, void* item){

    
    void* ret = NULL;
    t_no* aux = *no;

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
            
            t_no** sucessor = percorre_esq(&(*no)->dir);
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

t_no** percorre_esq(t_no** sub_arv){
    t_no** ret = sub_arv;

    while ((*ret)->esq)
    {
        printf("passando por: %d\n", ((c_ddd*)((*ret)->reg)->reg)->ddd);
        *ret = (*ret)->esq;
    }

    return ret;
    
}
t_no* _procura_esq(t_no* sub_arv){

    while (sub_arv->esq)
    {
        // printf("passando por: %d\n", ((c_ddd*)sub_arv->reg->reg)->ddd);
        sub_arv = sub_arv->esq;
    }

    return sub_arv;
}

t_no *sucessor(t_no *no)
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
