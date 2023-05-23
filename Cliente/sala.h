#ifndef _SALA_H_
#define _SALA_H_

#include "sesion.h"

class Sala
{
public:
    int id_Sala;
    int capacidad;
    int numSesiones;
    Sesion *sesiones;

    void imprimirSala();
};

#endif