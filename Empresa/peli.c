#include "peli.h"
#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirPelicula(Peli peli)
{
    printf("ID: %i  Titulo: %s  Duracion: %i\n", peli.id_Peli, peli.titulo, peli.duracion);
}

int getPelisCount(sqlite3* db){
	sqlite3_stmt *stmt;
		if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM PELICULA", -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar las peliculas\n");
			printf("%s\n", sqlite3_errmsg(db));
			return 0;
		}
		int i =sqlite3_step(stmt);
		if(i != SQLITE_ROW){
			printf("Aún no hay datos generados\n");
			return 0;
		}
		return sqlite3_column_int(stmt, 0);
}

Peli getPeliFromID(int id, sqlite3* db){
	sqlite3_stmt *stmt;
    Peli peli;
	char seq[100];
	sprintf(seq, "SELECT * FROM PELICULA WHERE ID = %i", id);

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar la pelicula\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Peli){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Peli){'\0', 0, 0};
	}
	peli.id_Peli = sqlite3_column_int(stmt, 0);
	strcpy(peli.titulo, (char *) sqlite3_column_text(stmt, 1));
	peli.duracion = sqlite3_column_int(stmt, 2);
	strcpy(peli.genero, (char *) sqlite3_column_text(stmt, 3));
	return peli;
}

Peli* getPeliculas(sqlite3* db){
	Peli* peliculas = (Peli*)malloc(sizeof(Peli)* getPelisCount(db));
	for (int i = 0; i<getPelisCount(db); i++){
		peliculas[i] = getPeliFromID(i, db);
	}
	return peliculas;
}

Peli getPelicula(char* titulo, sqlite3* db){
	sqlite3_stmt *stmt;
    Peli peli;
	char seq[100];
	sprintf(seq, "SELECT * FROM PELICULA WHERE TITULO_PELI = '%s'", titulo);

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar la pelicula\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Peli){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Peli){'\0', 0, 0};
	}
	peli.id_Peli = sqlite3_column_int(stmt, 0);
	strcpy(peli.titulo, (char *) sqlite3_column_text(stmt, 1));
	peli.duracion = sqlite3_column_int(stmt, 2);
	strcpy(peli.genero, (char *) sqlite3_column_text(stmt, 3));
	return peli;
}


void addPelicula(char* titulo, char* genero, int duracion , sqlite3* db){
	int cont = getPelisCount(db);
	char seq[200];
	sprintf(seq, "INSERT INTO PELICULA(ID, TITULO_PELI, DURACION_PELI, GENERO_PELI) VALUES (%i, '%s', %i, '%s')",cont+1, titulo, duracion, genero);
	update(seq, db);
}

void deletePeli(Peli p, sqlite3* db){
	int cont = getSalasCount(db);
	char seq[200];
	sprintf(seq, "DELETE FROM PELICULA WHERE ID = %i", p.id_Peli);
	update(seq, db);
}

























/*

void anadirPeli(int id, int duracion, char titulo[30], char genero[30], Peli* listaPelis, int tamPelis)
{
    Peli peli;
    peli.id_Peli = id;
    peli.duracion = duracion;
    strcpy(peli.titulo, titulo);
    strcpy(peli.genero, genero);

    Peli* listaVieja = listaPelis;
    tamPelis++;
    for(int i=0; i<tamPelis-1; i++)
    {
        listaPelis[i] = listaVieja[i];
    }
    listaPelis[tamPelis-1] = peli;
    free(listaVieja);
}
*/

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

