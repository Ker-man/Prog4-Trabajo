#ifndef _PELI_H_
#define _PELI_H_

typedef struct 
{
    int id_Peli;
    int duracion;
    char titulo[30];
    char genero[30];
}Peli;

void imprimirPelicula(Peli peli);

void anadirPeli(Peli peli, int id, int duracion, char titulo[30], char genero[30], Peli* listaPelis, int tamPelis);


Peli maxPelicula(Peli *pelis, int tamanyo);
Peli minPelicula(Peli *pelis, int tamanyo);
Peli* buscarGenero(Peli *peliculas, int tamanyo, char* genero);
Peli buscarTitulo(Peli *peliculas, int tamanyo, char* titulo);


#endif