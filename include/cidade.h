#pragma once

typedef struct{
    char* codigo_ibge;
    char * nome;
    double latitude;
    double longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char * fuso_horario;
}cidade;

typedef struct{
    char* codigo_ibge;
    char* nome;
}c_nome;

typedef struct{
    char* codigo_ibge;
    int ddd;
}c_ddd;

typedef struct{
    char* codigo_ibge;
    double longitude;
}c_long;

typedef struct{
    char* codigo_ibge;
    int latitude;
}c_lat;

typedef struct{
    char* codigo_ibge;
    int codigo_uf;
}c_cod_UF;

cidade* cria_cidade(double x, double y);
int cmp_ddd(const void* a, const void* b);
int cmp_cod_UF(const void* a, const void* b);
int cmp_lat(const void* a, const void* b);
int cmp_long(const void* a, const void* b);
int cmp_nome(const void* a, const void* b);
char* get_key(const void* mun);