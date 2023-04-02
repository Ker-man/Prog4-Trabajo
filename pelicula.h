#ifndef _PELICULA_H_
#define _PELICULA_H_

typedef struct 
{
    int id_Peli;
    char titulo[30];
    int duracion;
    char genero[30];
}Pelicula;

void imprimirPelicula(Pelicula pelicula);

#endif