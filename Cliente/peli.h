#ifndef _PELI_H_
#define _PELI_H_

typedef struct
{
    int id_Peli;
    char titulo[30];
    int duracion;
    char genero[30];
} Peli;

void imprimirPelicula(Peli peli);

#endif