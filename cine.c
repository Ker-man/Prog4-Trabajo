#include "cine.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Metodos de IMPRIMIR
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
    fprintf(f, "%s \n Entrada para la pelicula: %s \n para la sala: %i (sesion de las: %s)\n Precio: %f €",cine.nom_Cine, cine.salas->sesiones->peli.titulo, cine.salas->id_Sala, cine.salas->sesiones->horario, cine.salas->sesiones->precio);
    fclose(f);
}

//Metodos de crear
void inicializarCine(Cine cine, int numSalas)
{
    cine.salas = (Sala*)malloc(sizeof(Sala)*numSalas);
}

void anadirCine(int id_Cine, int numSalas, char nom_Cine[20], char ubi_Cine[30], Sala* salas, Cine** listaCines, int tamNewLista)
{
    Cine cine;
    cine.id_Cine = id_Cine;
    cine.numSalas = numSalas;
    strcpy(cine.nom_Cine, nom_Cine);
    strcpy(cine.ubi_Cine, ubi_Cine);
    cine.salas = (Sala*)malloc(sizeof(Sala)*numSalas);
    cine.salas = salas;
    Cine* listaVieja = *listaCines;
    *listaCines = (Cine*)malloc(sizeof(Cine) * tamNewLista);

    for(int i=0; i<tamNewLista-1;i++)
	{
		listaCines[0][i] = listaVieja[i];
	}
	listaCines[0][tamNewLista-1] = cine;

	free(listaVieja);

}