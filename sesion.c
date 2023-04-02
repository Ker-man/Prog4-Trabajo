#include "sesion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void imprimirSesion(Sesion sesion)
{
    printf("Sesion con horario: %s\n", sesion.horario);
    imprimirPelicula(sesion.pelicula[0]);
    imprimirSala(sesion.sala[0]);
}

void imprimirTicket(Sesion sesion)
{
    FILE* f;
    f = fopen("recibo.txt", "w");
    fprintf(f, "Entrada para la pelicula %s para la sala %i (sesion de las: %s)\n Precio: %f", sesion.pelicula->titulo, sesion.sala->id_Sala, sesion.horario, sesion.precio);
    fclose(f);
}