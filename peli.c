#include "peli.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirPelicula(Peli peli)
{
    printf("ID: %i  Titulo: %s  Duracion: %i\n", peli.id_Peli, peli.titulo, peli.duracion);
}

Peli maxPelicula(Peli *pelis, int tamanyo)
{
    Peli result;
        result.id_Peli = pelis[0].id_Peli;
        result.id_Peli = pelis[0].duracion;
        strcpy(result.titulo, pelis[0].titulo);
        strcpy(result.genero, pelis[0].genero);
    for(int i = 0; i<tamanyo; i++)
    {
        if(result.duracion < pelis[i].duracion)
        {
            result.id_Peli = pelis[i].id_Peli;
            result.id_Peli = pelis[i].duracion;
            strcpy(result.titulo, pelis[i].titulo);
            strcpy(result.genero, pelis[i].genero);
        }
    }
    printf("La pelicula con mayor duracion es: ");
    imprimirPelicula(result);
    return result;
}

Peli minPelicula(Peli *pelis, int tamanyo)
{
    Peli result;
    result.id_Peli = pelis[0].id_Peli;
    result.duracion = pelis[0].duracion;
    strcpy(result.titulo, pelis[0].titulo);
    strcpy(result.genero, pelis[0].genero);
    for(int i = 0; i<tamanyo; i++)
    {
        if(result.duracion > pelis[i].duracion)
        {
            result.id_Peli = pelis[i].id_Peli;
            result.duracion = pelis[i].duracion;
            strcpy(result.titulo, pelis[i].titulo);
            strcpy(result.genero, pelis[i].genero);
        }
    }
    printf("La pelicula con menor duracion es: ");
    imprimirPelicula(result);
    return result;
}

Peli* buscarGenero(Peli *peliculas, int tamanyo, char* genero)
{
    Peli *resulPelis;
    int cont = 0;
    for(int i = 0; i<tamanyo; i++)
    {
        int com1 = strcmp(peliculas[i].genero, genero);
        int com2 = 0;
        if(com1 = com2)
        {
            resulPelis[cont].id_Peli = peliculas[i].id_Peli;
            resulPelis[cont].duracion = peliculas[i].duracion;
            strcpy(resulPelis[cont].titulo, peliculas[i].titulo);
            strcpy(resulPelis[cont].genero, peliculas[i].genero);
            cont++;
        }
    }
    for(int i = 0; i<cont; i++)
    {
        printf("Las pelis de ese genero son: \n");
        imprimirPelicula(resulPelis[0]);
    }
    return resulPelis;
}

Peli buscarTitulo(Peli *peliculas, int tamanyo, char* titulo)
{
    Peli result;
    for(int i = 0; i<tamanyo; i++)
    {
        int com1 = strcmp(peliculas[i].titulo, titulo);
        int com2 = 0;
        if(com1 = com2)
        {
            result.id_Peli = peliculas[i].id_Peli;
            result.duracion = peliculas[i].duracion;
            strcpy(result.titulo, peliculas[i].titulo);
            strcpy(result.genero, peliculas[i].genero);
        }
    }
    printf("La peli que buscas es: \n");
    imprimirPelicula(result);
    return result;
}