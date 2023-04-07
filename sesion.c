#include "sesion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void imprimirSesion(Sesion sesion)
{
    printf("Sesion con horario: %s\n", sesion.horario);
}
/*
void imprimirPelis(Sesion sesion)
{
    printf("aaaaaa");
}

void inicializarSesion(Sesion sesion)
{
    sesion.peli = (Peli*)malloc(sizeof(Peli));
}


void anadirSesion(float precio, char horario[15], Peli peli, Sesion** listaSesiones, int tamSesiones)
{
    Sesion sesion;
    sesion.precio = precio;
    strcpy(sesion.horario, horario);
    sesion.peli = peli; //

    Sesion* listaVieja = *listaSesiones;
    tamSesiones++;

    *listaSesiones = (Sesion*)malloc(sizeof(Sesion) * tamSesiones);
    for (int i=0; i<tamSesiones-1; i++)
    {
        listaSesiones[0][i] = listaVieja[i];
    }
    listaSesiones[0][tamSesiones-1] = sesion;

    free(listaVieja);
}

*/