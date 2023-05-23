#ifndef _SALA_H_
#define _SALA_H_
#include "sesion.h"

typedef struct 
{
    int id_Sala;
    int capacidad;
    int numSesiones;
    Sesion *sesiones;
}Sala;


void imprimirSala(Sala sala);

//void imprimirSesiones(Sala sala);

//void inicializarSala(Sala sala, int numSesiones);
//void anadirSala(int id_Sala, int capacidad, int numSesiones, Sesion* sesiones, Sala** listaSalas, int tamSalas);

#endif