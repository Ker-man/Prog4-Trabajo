#include "sala.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirSala(Sala sala)
{
    printf("ID: %i  Capacidad: %i\n", sala.id_Sala, sala.capacidad);
}
void imprimirListaSalas(ListaSalas listaSalas)
{
    for(int i = 0; i<listaSalas.tamanyo; i++)
    {
        printf("%i- Codigo: %i    Capacidad: %i\n",i+1, listaSalas.sala[i].id_Sala, listaSalas.sala[i].capacidad);
    }
}