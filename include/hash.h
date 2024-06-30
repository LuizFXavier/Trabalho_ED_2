#pragma once
#include <stdint.h>

typedef struct hash
{
    void** tabela;
    int size;
    int max;
    void* deletado;
    char *(*get_key)(const void*);
}Hash_table;

Hash_table* criaHash(int tam, char *(*get_key)(const void*));
int insereHash(Hash_table* hash, void * bucket);
void apagaHash(Hash_table* hash);
int removeHash(Hash_table *hash, const char* key);
void * buscaHash(Hash_table *hash, const char* key);
uint32_t hash_f(const char* str, uint32_t h);
uint32_t hash_f2(const char* str, uint32_t h);