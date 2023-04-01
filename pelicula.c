#include "pelicula.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirPelicula(Pelicula pelicula)
{
    printf("ID: %i  Titulo: %s  Duracion: %i\n", pelicula.id_Peli, pelicula.titulo, pelicula.duracion);
}