#ifndef _SESION_H_
#define _SESION_H_
#include "pelicula.h"
#include "sala.h"

typedef struct 
{
    char horario[15];
    Pelicula* pelicula;
    Sala* sala;
}Sesion;


void imprimirSesion(Sesion sesion);

#endif