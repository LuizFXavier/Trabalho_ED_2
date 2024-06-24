#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"

cidade* cria_cidade(double x, double y){
    cidade* nova = (cidade*) malloc(sizeof(cidade));

    nova->longitude = x;
    nova->latitude = y;

    return nova;
}
int cmp_ddd(const void* a, const void* b){
    return ((c_ddd*)a)->ddd - ((c_ddd*)b)->ddd;
}

int cmp_cod_UF(const void *a, const void *b)
{
    return ((c_cod_UF*)a)->codigo_uf - ((c_cod_UF*)b)->codigo_uf;
}

int cmp_lat(const void *a, const void *b)
{
    return (int)((c_lat*)a)->latitude - (int)((c_lat*)b)->latitude;
}

int cmp_long(const void *a, const void *b)
{
    return (int)((c_long*)a)->longitude - (int)((c_long*)b)->longitude;
}

int cmp_nome(const void *a, const void *b)
{
    return strcmp(((c_nome*)a)->nome, ((c_nome*)b)->nome);
}

char* get_key(const void* mun){

    cidade* m = (cidade*)mun;

    return m->codigo_ibge;
}