#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define TRUE 1
#define FALSE 0

typedef unsigned int Bool; 

typedef struct{
    Container* inicio;
    int tam;
}Query;

Query* cria_query();

// Busca de elementos na AVL com base em parâmetros
Query* do_query(Avl* arvores[]);
Query* range_query(Avl* arv, int min, int max);
Query* equal_query(Avl *arv, void* chave);

// Junção de duas Querys
Query* merge_query(Query* q1, Query* q2);
Bool query_find(Query* query, char* cod);

// Adição de elementos em uma Query
void fill_query(Query** query, Container* container);
void add_to_query(Query** query, Container* container);

void free_query(Query* query);