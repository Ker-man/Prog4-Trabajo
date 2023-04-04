#include "sala.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirSala(Sala sala)
{
    printf("Sala\n");
    printf("ID: %i  Capacidad: %i\n", sala.id_Sala, sala.capacidad);
}

void imprimirSesiones(Sala sala)
{
    printf("eeeeee");
}

void inicializarSala(Sala sala, int numSesiones)
{
    sala.sesiones = (Sesion*)malloc(sizeof(Sesion) * numSesiones);
}

void anadirSala(Sala sala, int id_Sala, int capacidad, int numSesiones, Sesion* sesiones, Sala** listaSalas, int tamSalas)
{
    sala.id_Sala = id_Sala;
    sala.capacidad = capacidad;
    sala.numSesiones = numSesiones;
    sala.sesiones = (Sesion*)malloc(sizeof(Sesion)*numSesiones);
    sala.sesiones = sesiones; //Revisar tanto en esta clase como en todas

    Sala* listaVieja = *listaSalas;
    tamSalas++;
    *listaSalas = (Sala*)malloc(sizeof(Sala) * tamSalas);
    for(int i=0; i<tamSalas-1; i++)
    {
        listaSalas[0][i] = listaVieja[i];
    }
    listaSalas[0][tamSalas-1] = sala;

    free(listaVieja);

}