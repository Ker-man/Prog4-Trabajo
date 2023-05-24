#ifndef _SESION_H_
#define _SESION_H_
#include "peli.h"

typedef struct
{
    float precio;
    char horario[15];
    Peli peli;
    int id_sesion;
} Sesion;

void imprimirSesion(Sesion sesion);

#endif