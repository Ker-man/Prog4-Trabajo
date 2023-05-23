#ifndef _CINE_H_
#define _CINE_H_

#include "sala.h"

class Cine
{
public:
    int id_Cine;
    int numSalas;
    char nom_Cine[20];
    char ubi_Cine[30];
    Sala *salas;

    void imprimirCine();
};

#endif