#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"

Cidade *cria_cidade(char *ibge, char *nome, float longi, float lat, int capital, int uf, int siafi, int ddd, char *fuso)
{
    Cidade* nova = (Cidade*) malloc(sizeof(Cidade));
    nova->codigo_ibge = ibge;
    nova->nome = nome;
    nova->longitude = longi;
    nova->latitude = lat;
    nova->capital = capital;
    nova->codigo_uf = uf;
    nova->siafi_id = siafi;
    nova->ddd = ddd;
    nova->fuso_horario = fuso;

    return nova;
}

char *get_key(const void *mun)
{

    Cidade* m = (Cidade*)mun;

    return m->codigo_ibge;
}