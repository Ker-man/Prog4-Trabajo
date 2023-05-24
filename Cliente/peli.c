#include "peli.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirPelicula(Peli peli)
{
    printf("ID: %i  Titulo: %s  Duracion: %i\n", peli.id_Peli, peli.titulo, peli.duracion);
}