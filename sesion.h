#ifndef _SESION_H_
#define _SESION_H_

typedef struct 
{
    char horario[15];
    int id_Peli;
    int id_Sala;
}Sesion;


void imprimirSesion(Sesion sesion);

#endif