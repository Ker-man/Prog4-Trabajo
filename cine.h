#ifndef _CINE_H_
#define _CINE_H_
#include "sala.h"

typedef struct 
{
    int id_Cine;
    char nom_Cine[20];
    char ubi_Cine[30];
    ListaSalas listaSalas;
}Cine;

/*
typedef struct
{
    int tamanyo;
    Cine* cine;
}ListaCines;
*/

void imprimirCine(Cine cine);

#endif