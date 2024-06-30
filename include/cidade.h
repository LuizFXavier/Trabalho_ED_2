#pragma once

typedef struct{
    char* codigo_ibge;
    char * nome;
    float latitude;
    float longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char * fuso_horario;
}Cidade;

Cidade* cria_cidade(char* ibge, char* nome, float longi, float lat, int capital, int uf, int siafi, int ddd, char* fuso);
char* get_key(const void* mun);