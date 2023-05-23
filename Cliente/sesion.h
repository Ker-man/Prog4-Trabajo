#ifndef _SESION_H_
#define _SESION_H_

#include "peli.h"

class Sesion
{
public:
    float precio;
    char horario[15];
    Peli peli;
    int id_sesion;

    void imprimirSesion();
};

#endif