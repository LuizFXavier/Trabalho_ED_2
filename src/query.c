#include "query.h"
#include "cidade.h"
#include "avl.h"

void range_query(t_avl *arv, int min, int max)
{   
    //(t_cont**)malloc(sizeof(t_cont*))
    t_cont** ret = (t_cont**)malloc(sizeof(t_cont*));
    *ret = NULL;
    t_no* atual = arv->raiz;
    t_no* filhoProx = atual;
    c_ddd c;
    c.ddd = min;
    
    while (1)
    {
        printf("Nesse no: %d\n", ((c_ddd*)(atual->reg->reg))->ddd);
        if(arv->cmp(atual->reg->reg, &c) > 0){
            // printf("esq\n");
            filhoProx = atual->esq;
        }
        
        else if(arv->cmp(atual->reg->reg, &c) < 0){
            // printf("dir\n");
            filhoProx = atual->dir;
        }

        else
            break;
        
        if(!filhoProx)
            break;

        atual = filhoProx;   
    }
    while (atual && arv->cmp(atual->reg->reg, &c) <= 0)
    { 
        atual = sucessor(atual);
    }
    // printf("%d, %d\n", min, ((c_ddd*)(atual->reg->reg))->ddd);
    
    while (atual && ((c_ddd*)(atual->reg->reg))->ddd < max)
    {
        t_cont* container = (atual->reg);

        while (container)
        {   
            t_cont* novo = (t_cont*)malloc(sizeof(t_cont));
            novo->reg = container->reg;
            novo->prox = *ret;
            *ret = novo;
            container = container->prox;
        }
        
        
        printf("ddd: %d\n", ((c_ddd*)(atual->reg->reg))->ddd);
        
        // percorre(*atual);
        // printf("\n\n");
        atual = sucessor(atual);
        
    }
    printf("Guardou tudo!\n");
    
    while (*ret)
    {
        printf("ddd: %s\n", ((c_ddd*)((*ret)->reg))->codigo_ibge);
        *ret = (*ret)->prox;
    }
    
    
}