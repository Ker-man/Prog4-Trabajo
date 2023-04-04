#ifndef _CINE_H_
#define _CINE_H_
#include "sala.h"

typedef struct 
{
    int id_Cine;
    int numSalas;
    char nom_Cine[20];
    char ubi_Cine[30];
    Sala* salas;
}Cine;


void imprimirCine(Cine cine);
void imprimirSalas(Sala *salas, int numSalas);
void imprimirTicket(Cine cine);

void inicializarCine(Cine cine, int numSalas);
void anadirCine(int id_Cine, int numSalas, char nom_Cine[20], char ubi_Cine[30], Sala* salas, Cine** listaCines, int tamNewLista);

#endif