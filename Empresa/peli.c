#include "peli.h"
#include "../BBDD/funcionesBD.h"
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
	for (int i = 0; i<=getPelisCount(db); i++){
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
	int cont = IDMasAltoPe(getPeliculas(db), getPelisCount(db));
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


int IDMasAltoPe(Peli* pelis, int numPelis){
    int idMA = pelis[0].id_Peli;
    for (int i = 1; i<numPelis;i++){
        if (idMA>pelis[i].id_Peli){
            idMA = pelis[i].id_Peli;
        }
    }
    return idMA;
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
    for(int i = 1; i<=tamanyo; i++)
    {
        if(result.duracion < pelis[i].duracion)
        {
            result.id_Peli = pelis[i].id_Peli;
            result.duracion = pelis[i].duracion;
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
    result.id_Peli = pelis[1].id_Peli;
    result.duracion = pelis[1].duracion;
    strcpy(result.titulo, pelis[1].titulo);
    strcpy(result.genero, pelis[1].genero);
    for(int i = 1; i<=tamanyo; i++)
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

Peli buscarGenero(Peli *peliculas, int tamanyo, char* genero)
{
    Peli resulPelis;
    for(int i = 1; i<=tamanyo; i++)
    {
        if(strcmp(peliculas[i].genero, genero)==0){
           
            resulPelis.id_Peli = peliculas[i].id_Peli;
            resulPelis.duracion = peliculas[i].duracion;
            strcpy(resulPelis.titulo, peliculas[i].titulo);
            strcpy(resulPelis.genero, peliculas[i].genero);

        }
    }
    printf("Las pelis de ese genero son: \n");
    imprimirPelicula(resulPelis);
    return resulPelis;
}

Peli buscarTitulo(Peli *peliculas, int tamanyo, char* titulo)
{
    Peli result;
    for(int i = 1; i<=tamanyo; i++)
    {
        if(strcmp(peliculas[i].titulo, titulo)==0){

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


void escribirPeliculaFichero(Peli peli){

    FILE* ficheroPelis;
    ficheroPelis = fopen("UserBackup.txt", "a");
    fprintf(ficheroPelis,"%i;%s;%s;%i;",peli.id_Peli, peli.titulo, peli.genero, peli.duracion);
    //fprintf(ficheroPelis,"\n");
    fclose(ficheroPelis);
}

Peli* leerPeliculaFichero() {
    char c;
    int numPelis=8;
    int count = 0;
    int index = 0;
    char array[4][100];
    Peli* p = malloc(sizeof(Peli)*numPelis);

    FILE* f = fopen("UserBackup.txt", "r");
    if (f == NULL) {
        printf("El fichero está vacío o no se pudo abrir\n");
        exit(1);
    }

    while ((c = fgetc(f)) != EOF) {
        if (c == ';') {
            count++;
            if (count == 4) {
                printf("%s\n", array[3]);
                sscanf(array[0],"%i",&p[index].id_Peli);
                printf("a");
                strcpy(p[index].titulo, array[1]);
                printf("b");
                strcpy(p[index].genero, array[2]);
                printf("c");
                sscanf(array[3],"%i",&p[index].duracion);
                printf("d");
                for (int i = 0; i < 4; i++) {
                    printf("%s\n", array[i]);
                    array[i][0] = '\0';
                }
                index++;
                count = 0;
            }
        }else if(c=='\n'){
            continue;
        } else {
            printf("\n %c ",c);
            strncat(array[count], &c, 1);
            printf(array[count]);
            
        }
    }
    printf("\n");
    fclose(f);
    return p;
}



