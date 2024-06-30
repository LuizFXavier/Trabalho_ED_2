#include <stdio.h>
#include "jsense.h"
#include "cidade.h"
#include "hash.h"
#include "avl.h"
#include "query.h"
#include "menus.h"

#define NUM_CIDADES 5570

Cidade* read_json(JSENSE *file, int i);
void print_query(Query* query, Hash_table* hash);
void menu(Avl* arvores[], Query** query_p, Opcao opcao, Hash_table* hash);

int main(){
    Avl * avl_ddd = cria_avl(INT);
    Avl * avl_long = cria_avl(FLOAT);
    Avl * avl_lat = cria_avl(FLOAT);
    Avl * avl_nome = cria_avl(STR);
    Avl * avl_cod_uf = cria_avl(INT);

    Hash_table *hashC = criaHash(100 * 100, get_key);

    JSENSE *file = jse_from_file("test/municipios.json");

    // Leitura do JSON

    for(int i = 0; i < NUM_CIDADES; i++){
        Cidade* m = read_json(file, i);
        
        insereHash(hashC, m);
        insere_AVL(avl_nome, m->codigo_ibge, m->nome);
        insere_AVL(avl_long, m->codigo_ibge, &m->longitude);
        insere_AVL(avl_lat, m->codigo_ibge, &m->latitude);
        insere_AVL(avl_ddd, m->codigo_ibge, &m->ddd);
        insere_AVL(avl_cod_uf, m->codigo_ibge, &m->codigo_uf);
    }

    Avl* arvores[5] = {avl_nome, avl_long, avl_lat, avl_ddd, avl_cod_uf};

    Query* query_p = NULL;
    Opcao opcao;

    printf("Bem vindo a busca de municípios do Brasil!");
    do
    {
        opcao = menu_inicial();

        menu(arvores, &query_p, opcao, hashC);
        
    } while (opcao != ENCERRAR);
    
    free_query(query_p);
    apagaHash(hashC);

    return 0;
}

Cidade* read_json(JSENSE *file, int i){
    int error;
    char itens[9][18];

    sprintf(itens[0], "[%d].codigo_ibge",i);
    sprintf(itens[1], "[%d].nome",i);
    sprintf(itens[2], "[%d].latitude",i);
    sprintf(itens[3], "[%d].longitude",i);
    sprintf(itens[4], "[%d].capital",i);
    sprintf(itens[5], "[%d].codigo_uf",i);
    sprintf(itens[6], "[%d].siafi_id",i);
    sprintf(itens[7], "[%d].ddd",i);
    sprintf(itens[8], "[%d].fuso_horario",i);

    char* ibge = jse_get(file, itens[0]);
    char* nome = jse_get(file, itens[1]);

    float latitude = tec_string_to_double(jse_get(file, itens[2]), &error);
    float longitude = tec_string_to_double(jse_get(file, itens[3]), &error);

    int capital = tec_string_to_int(jse_get(file, itens[4]));
    int codigo_uf = tec_string_to_int(jse_get(file, itens[5]));

    int siafi_id = tec_string_to_int(jse_get(file, itens[6]));
    int ddd = tec_string_to_int(jse_get(file, itens[7]));
    char* fuso_horario = jse_get(file, itens[8]);

    return cria_cidade(ibge, nome, longitude, latitude, capital, codigo_uf, siafi_id, ddd, fuso_horario);
}

void menu(Avl* arvores[], Query** query_p, Opcao opcao, Hash_table* hash){
    
    Query* query_s;
    
    switch (opcao)
    {
    case FILTRAR:
        if(!(*query_p))
            *query_p = do_query(arvores);
        else{
            query_s = do_query(arvores);
            *query_p = merge_query(*query_p, query_s);
            free_query(query_s);
        }
        printf("Busca concluída!");
        break;
    case LIMPAR:
        free_query(*query_p);
        *query_p = NULL;
        system("clear || cls");
        printf("Filtro limpo!\n");
        break;
    case IMPRIMIR:
        print_query(*query_p, hash);
        break;
    }
    
}
void print_query(Query* query, Hash_table* hash){

    if(!query){
        system("clear || cls");
        printf("Não há resultados a serem vistos!\n");
        return;
    }
    Container *atual = query->inicio;

    while (atual)
    {   
        Cidade* mun = (Cidade*)buscaHash(hash, atual->cod);
        printf("-----------------------------\n");
        printf("Nome: %s\n", mun->nome);
        printf("Código IBGE: %s\n", mun->codigo_ibge);
        printf("DDD: %d\n", mun->ddd);
        printf("Capital: %d\n", mun->capital);
        printf("Longitude: %lf\n", mun->longitude);
        printf("Latitude: %lf\n", mun->latitude);
        printf("Código UF: %d\n", mun->codigo_uf);
        printf("Siafi ID: %d\n", mun->siafi_id);
        printf("Fuso horário: %s\n\n", mun->fuso_horario);
        printf("-----------------------------\n");
        atual = atual->prox;
    }

    printf("Número de correspondências:%d\n", query->tam);
    printf("-----------------------------\n");
}