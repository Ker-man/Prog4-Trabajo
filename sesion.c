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