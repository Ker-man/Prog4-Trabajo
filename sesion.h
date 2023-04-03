#ifndef _SESION_H_
#define _SESION_H_
#include "peli.h"
#include "sala.h"

typedef struct 
{
    char horario[15];
    Peli* pelicula;
    Sala* sala;
    float precio;
}Sesion;


void imprimirSesion(Sesion sesion);
void imprimirTicket(Sesion sesion);

#endif