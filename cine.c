#include "cine.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirCine(Cine cine)
{
    printf("Cine:\n");
    printf("ID: %i  Nombre: %s  Ubicacion: %s\n", cine.id_Cine, cine.nom_Cine, cine.ubi_Cine);
    printf("Salas:\n");
}

void imprimirSalas(Sala *salas, int numSalas)
{
    for(int i = 0; i<numSalas; i++)
    {
        printf("Sala %i- Codigo: %i    Capacidad: %i\n",i+1, salas[i].id_Sala, salas[i].capacidad);
    }
}

void imprimirTicket(Cine cine)
{
    FILE* f;
    f = fopen("recibo.txt", "w");
    fprintf(f, "Entrada para la pelicula %s para la sala %i (sesion de las: %s)\n Precio: %f", cine.salas->sesiones->pelis->titulo, cine.salas->id_Sala, cine.salas->sesiones->horario, cine.salas->sesiones->precio);
    fclose(f);
}