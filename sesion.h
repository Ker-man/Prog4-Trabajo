#ifndef _SESION_H_
#define _SESION_H_
#include "peli.h"
#include "sala.h"

typedef struct 
{
    float precio;
    char horario[15];
    int numPelis;
    Peli* pelis;
}Sesion;


void imprimirSesion(Sesion sesion);
void imprimirPelis(Sesion sesion);

#endif