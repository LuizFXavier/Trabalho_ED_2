#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"

int menu_inicial(){

    int opcao = 0;
    char c[5];
    do{
        printf("\n\n");
        printf("O que desejas fazer?\n");
        printf("1)Adicionar parâmetro de busca\n");
        printf("2)Limpar filtro\n");
        printf("3)Imprimir resultado\n");
        printf("4)Encerrar\n");
        printf(":");

        fgets(c, sizeof(c), stdin);
        
        opcao = strtol(c, NULL, 0);
        // system("clear || cls");
        printf("\n");

    }while(opcao <= 0 || opcao > 5);

    return opcao;
}

int menu_campo()
{
    int opcao = 0;
    char c[5];
    do{
        printf("Qual campo deve ser usado como referência?\n");
        printf("1)Nome\n");
        printf("2)Longitude\n");
        printf("3)Latitude\n");
        printf("4)DDD\n");
        printf("5)Código UF\n:");

        fgets(c, sizeof(c), stdin);
        strtok(c, "\n");

        opcao = strtol(c, NULL, 0);

        system("clear || cls");
        // printf("\n");
        
    }while(opcao <= 0 || opcao > 5);

    return opcao;
}

int menu_operacao(Campo campo){
    char c[5];
    int opcao;
    char* campoT;

    switch (campo)
    {
    case LONGIT:
        campoT = "longitude";
        break;
    case LAT:
        campoT = "latitude";
        break;
    case DDD:
        campoT = "DDD";
        break;
    case UF:
        campoT = "código UF";
        break;
    }

    do{
        printf("Busca por %s\n\n", campoT);
        printf("Como será a busca?\n");
        printf("1)Igual a\n");
        printf("2)Maior que\n");
        printf("3)Menor que\n");
        printf("4)Intervalo\n");
        printf(":");

        fgets(c, sizeof(c), stdin);
        strtok(c, "\n");

        opcao = strtol(c, NULL, 0);
        
        printf("\n");
    }while(opcao <= 0 || opcao > 4);

    return opcao;
}

void menu_valores(Filtro* f){
    char c[50];

    if(f->opr == EQUAL){
        printf("Insira a chave a ser procurada: ");
        fgets(c, 50, stdin);
        strtok(c, "\n");
        strcpy(f->chave, c);

    }

    if(f->opr == MAIOR || f->opr == RANGE){
        printf("Valor mínimo a ser buscado: ");
        fgets(c, 50, stdin);
        strtok(c, "\n");
        f->min = strtol(c, NULL, 0);
    }

    if(f->opr == MENOR || f->opr == RANGE){
        printf("Valor máximo a ser buscado: ");
        fgets(c, 50, stdin);
        strtok(c, "\n");
        f->max = strtol(c, NULL, 0);
    }

}

Filtro* montar_filtro(){
    Filtro* filtro = (Filtro*)malloc(sizeof(Filtro));
    
    filtro->campo = menu_campo();

    if(filtro->campo == NOME)
        filtro->opr = EQUAL;

    else
        filtro->opr = menu_operacao(filtro->campo);

    menu_valores(filtro);

    if(filtro->opr == MAIOR)
        filtro->max = INFINITO;
    
    if(filtro->opr == MENOR)
        filtro->min = M_INFINITO;
    
    return filtro;
}