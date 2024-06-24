#include <stdio.h>
#include "jsense.h"
#include "cidade.h"
#include "hash.h"
#include "avl.h"
#include "query.h"

#define NUM_CIDADES 5570

void percorre(t_no* no);

int main(){
    t_avl * avl_ddd = cria_avl(cmp_ddd);
    t_avl * avl_long = cria_avl(cmp_long);
    t_avl * avl_lat = cria_avl(cmp_lat);
    t_avl * avl_nome = cria_avl(cmp_nome);
    t_avl * avl_cod_uf = cria_avl(cmp_cod_UF);

    t_hash *hashC = criaHash(100 * 100, get_key);

    char itens[9][18];

    JSENSE *j = jse_from_file("test/municipios.json");

    int error;

    // Leitura do JSON

    for(int i = 0; i < NUM_CIDADES; i++){
    
        cidade* m = (cidade*) malloc(sizeof(cidade));
        c_ddd* m_ddd = (c_ddd*) malloc(sizeof(c_ddd));
        c_long* m_long = (c_long*) malloc(sizeof(c_long));
        c_lat* m_lat = (c_lat*) malloc(sizeof(c_lat));
        c_cod_UF* m_cod_UF = (c_cod_UF*) malloc(sizeof(c_cod_UF));
        c_nome* m_nome = (c_nome*) malloc(sizeof(c_nome));

        sprintf(itens[0], "[%d].codigo_ibge",i);
        sprintf(itens[1], "[%d].nome",i);
        sprintf(itens[2], "[%d].latitude",i);
        sprintf(itens[3], "[%d].longitude",i);
        sprintf(itens[4], "[%d].capital",i);
        sprintf(itens[5], "[%d].codigo_uf",i);
        sprintf(itens[6], "[%d].siafi_id",i);
        sprintf(itens[7], "[%d].ddd",i);
        sprintf(itens[8], "[%d].fuso_horario",i);

        m->codigo_ibge = jse_get(j, itens[0]);
        m->nome = jse_get(j, itens[1]);

        m->latitude = tec_string_to_double(jse_get(j, itens[2]), &error);
        m->longitude = tec_string_to_double(jse_get(j, itens[3]), &error);

        m->capital = tec_string_to_int(jse_get(j, itens[4]));
        m->codigo_uf = tec_string_to_int(jse_get(j, itens[5]));

        m->siafi_id = tec_string_to_int(jse_get(j, itens[6]));
        m->ddd = tec_string_to_int(jse_get(j, itens[7]));
        m->fuso_horario = jse_get(j, itens[8]);

        m_cod_UF->codigo_uf = m->codigo_uf;
        m_ddd->ddd = m->ddd;
        m_lat->latitude = m->latitude;
        m_long->longitude = m->longitude;
        m_nome->nome = m->nome;

        m_cod_UF->codigo_ibge = m->codigo_ibge;
        m_nome->codigo_ibge = m->codigo_ibge;
        m_long->codigo_ibge = m->codigo_ibge;
        m_lat->codigo_ibge = m->codigo_ibge;
        m_ddd->codigo_ibge = m->codigo_ibge;

        
        insereHash(hashC, m);
        insere_AVL(avl_ddd, m_ddd);
        // insere_AVL(avl_long, m_long);
        // insere_AVL(avl_lat, m_lat);
        // insere_AVL(avl_cod_uf, m_cod_UF);
        // insere_AVL(avl_nome, m_nome);
    }
    free(j);
    printf("Inseriu tudo\n");

    // percorre(avl_ddd->raiz);
    // printf("\n\n");

    // percorre(avl_long->raiz);
    // printf("\n\n");

    // percorre(avl_lat->raiz);
    // printf("\n\n");

    // percorre(avl_nome->raiz);
    // printf("\n\n");

    // percorre(avl_cod_uf->raiz);
    // printf("\n");

    range_query(avl_ddd, 66, 69);
}

