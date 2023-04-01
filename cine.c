#include "cine.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirCine(Cine cine)
{
    printf("ID: %i  Nombre: %s  Ubicacion: %s\n", cine.id_Cine, cine.nom_Cine, cine.ubi_Cine);
    printf("Salas:\n");
    imprimirListaSalas(cine.listaSalas);
}