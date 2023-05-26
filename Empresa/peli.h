#ifndef _PELI_H_
#define _PELI_H_
#include "../BBDD/sqlite3.h"

typedef struct 
{
    int id_Peli;
    char titulo[30];
    int duracion;
    char genero[30];
}Peli;

void imprimirPelicula(Peli peli);


int getPelisCount(sqlite3* db);
Peli getPeliFromID(int id, sqlite3* db);
Peli* getPeliculas(sqlite3* db);
Peli getPelicula(char* titulo, sqlite3* db);
void addPelicula(char* titulo, char* genero, int duracion , sqlite3* db);
void deletePeli(Peli p, sqlite3* db);
int IDMasAltoPe(Peli* pelis, int numPelis);




//void anadirPeli(int id, int duracion, char titulo[30], char genero[30], Peli* listaPelis, int tamPelis);
Peli maxPelicula(Peli *pelis, int tamanyo);
Peli minPelicula(Peli *pelis, int tamanyo);
Peli buscarGenero(Peli *peliculas, int tamanyo, char* genero);
Peli buscarTitulo(Peli *peliculas, int tamanyo, char* titulo);

void escribirPeliculaFichero(Peli peli);
Peli* leerPeliculaFichero();



#endif