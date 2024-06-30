#pragma once

#define NOME 1
#define LONGIT 2
#define LAT 3
#define DDD 4
#define UF 5

#define EQUAL 1
#define MAIOR 2
#define MENOR 3
#define RANGE 4

#define FILTRAR 1
#define LIMPAR 2
#define IMPRIMIR 3
#define ENCERRAR 4

#define INFINITO 1000000
#define M_INFINITO -1000000

typedef int Campo;
typedef int Operacao;
typedef int Opcao;

typedef struct{
    char chave[50];
    int min;
    int max;
    Operacao opr;
    Campo campo;
}Filtro;

Opcao menu_inicial();
Opcao menu_campo();
Opcao menu_operacao(Campo campo);
void menu_valores(Filtro* f);
Filtro *montar_filtro();