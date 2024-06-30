#include <stdlib.h>
#include "query.h"
#include "cidade.h"
#include "avl.h"
#include "menus.h"

Query* cria_query(){

    Query* nova = malloc(sizeof(Query));
    nova->tam = 0;
    nova->inicio = NULL;
    return nova;
}
/**
 * Busca de um valor específico em uma AVL.
 * Retornará todos os elementos presentes no nó que contem a chave indicada.
*/
Query* equal_query(Avl *arv, void* chave){
    
    Query* res = cria_query();
    No* busca = busca_AVL(arv, chave);

    if(busca){
        fill_query(&res, busca->reg);
    }
    
    return res;
}

/**
 * Busca de valores em uma Avl em um dado intervalo.
 * @param min Limite inferior do intervalo a ser buscado. Apenas valores estritamente maiores serão retornados.
 * @param max Limite superior do intervalo a ser buscado. Apenas valores estritamente menores serão retornados.
*/
Query* range_query(Avl *arv, int min, int max)
{   
    Query* res = cria_query();
    Container** ret = (Container**)malloc(sizeof(Container*));
    *ret = NULL;
    No* atual;

    float minF = min;
    float maxF = max;
    void * minP = &min;
    void * maxP = &max;

    // Garantia que o tipo certo será passado para o comparador
    if(arv->tipo == FLOAT){
        minP = &minF;
        maxP = &maxF;
    }
    
    // Busca pelo valor menor ou igual ao mínimo indicado
    atual = busca_AVL_prox(arv, minP);
    
    // Garantia de que o valor da chave é maior que o mínimo
    while (atual && arv->cmp(atual->reg->chave, minP) <= 0)
    { 
        atual = sucessor(atual);
    }

    // Armazenamento de todos os elementos de todos os nós que possuem chave menor ao máximo
    while (atual && arv->cmp(atual->reg->chave, maxP) < 0)
    {
        fill_query(&res, atual->reg);
        atual = sucessor(atual);
    }
    
    return res;
}

/**
 * Interseção entre duas Querys.
*/
Query* merge_query(Query* q1, Query* q2){
    
    Query* res = cria_query();
    Container* atual;

    //Garantir que sempre comparará a menor query com a maior
    if(q1->tam > q2->tam){
        Query* aux = q1;
        q1 = q2;
        q2 = aux;
    }

    atual = q1->inicio;

    while (atual)
    {
        if(query_find(q2, atual->cod)){
            add_to_query(&res, atual);
        }
        atual = atual->prox;
    }

    return res;
}

/**
 * Realização da operação de query especificada com base no filtro montado.
*/
Query *do_query(Avl *arvores[])
{
    Query* res;
    Filtro *f = montar_filtro();
    
    void* chave;
    float chaveF;
    int chaveI;

    switch (arvores[f->campo -1]->tipo)
    {
    case STR:
        chave = f->chave;
        break;

    case INT:
        
        chaveI = strtol(f->chave, NULL, 0);
        chave = &chaveI;
        break;

    case FLOAT:
        chaveF = strtof(f->chave, NULL);
        chave = &chaveF;
        break;
    }

    switch (f->opr)
    {
    case EQUAL:
        res = equal_query(arvores[f->campo -1], chave);
        break;
    
    default:
        res = range_query(arvores[f->campo -1], f->min, f->max);
        break;
    }
    
    return res;
}

/**
 * Verifica se um elemento está presente na Query dada.
*/
Bool query_find(Query* query, char* cod){
    Container* atual = query->inicio;

    while (atual)
    {
        if(cmp_str(atual->cod, cod) == 0)
            return TRUE;
        atual = atual->prox;
    }

    return FALSE;
}

/**
 * Adição de um novo elemento a uma Query.
*/
void add_to_query(Query** query, Container* container){

    Container* novo = cria_reg(container->cod, container->chave);
    novo->prox = (*query)->inicio;
    (*query)->inicio = novo;
    
    (*query)->tam++;
}

/**
 * Inserção de todos os elementos de uma lista ligada em uma Query.
*/
void fill_query(Query** query, Container* container){

    while (container)
        {   
            add_to_query(query, container);
            container = container->prox;
        }
}

/**
 * Liberação de memória de uma Query.
*/
void free_query(Query* query){
    
    if(!query)
        return;

    Container* prox;

    while (query->inicio) {
        prox = query->inicio->prox;
        free(query->inicio);
        query->inicio = prox;
    }
    free(query);
}