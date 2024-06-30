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
Query* range_query(Avl* arv, int min, int max);
Query* equal_query(Avl *arv, void* chave);
Query* merge_query(Query* q1, Query* q2);
Query* do_query(Avl* arvores[]);
Bool query_find(Query* query, char* cod);
void fill_query(Query** query, Container* container);
void add_to_query(Query** query, Container* container);

void free_query(Query* query);