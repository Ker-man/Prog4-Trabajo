#include "cine.h"
#include "../BBDD/funcionesBD.h"
#include "peli.h"
#include "../Usuario/user.h"
#include "sesion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void imprimirCine(Cine cine)
{
    printf("Cine:\n");
    printf("ID: %i  Nombre: %s  Ubicacion: %s\n", cine.id_Cine, cine.nom_Cine, cine.ubi_Cine);
    printf("Salas:\n");
}

int getCinesCount(sqlite3* db){
	sqlite3_stmt *stmt;
		if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM CINE", -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar el cine\n");
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

Cine getCineFromID(int id, sqlite3* db){
	sqlite3_stmt *stmt;
    Cine cine;
	char seq[100];
	sprintf(seq, "SELECT * FROM CINE WHERE ID = %i", id);

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar el cine\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Cine){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Cine){'\0', 0, 0};
	}
	cine.id_Cine = sqlite3_column_int(stmt, 0);
	cine.numSalas = sqlite3_column_int(stmt, 1);
	strcpy(cine.nom_Cine, (char *) sqlite3_column_text(stmt, 2));
	strcpy(cine.ubi_Cine, (char *) sqlite3_column_text(stmt, 3));
	return cine;
}

Cine* getCines(sqlite3* db){
	Cine* cines = (Cine*)malloc(sizeof(Cine)* getCinesCount(db));
	for (int i = 0; i<=getCinesCount(db); i++){
		cines[i] = getCineFromID(i, db);
	}
	return cines;
}

Cine getCine(char* nombre, char* ubicacion, sqlite3* db){
	sqlite3_stmt *stmt;
    Cine cine;
	char seq[100];
	sprintf(seq, "SELECT * FROM CINE WHERE NOM_CINE = '%s' AND UBI_CINE = '%s", nombre, ubicacion);

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar el cine\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Cine){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Cine){'\0', 0, 0};
	}
	cine.id_Cine = sqlite3_column_int(stmt, 0);
	cine.numSalas = sqlite3_column_int(stmt, 1);
	strcpy(cine.nom_Cine, (char *) sqlite3_column_text(stmt, 2));
	strcpy(cine.ubi_Cine, (char *) sqlite3_column_text(stmt, 3));
	return cine;
}

Cine getCineN(char* nombre, sqlite3* db){
	sqlite3_stmt *stmt;
    Cine cine;
	char seq[100];
	sprintf(seq, "SELECT * FROM CINE WHERE NOM_CINE = '%s'", nombre);

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar el cine\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Cine){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Cine){'\0', 0, 0};
	}
	cine.id_Cine = sqlite3_column_int(stmt, 0);
	strcpy(cine.nom_Cine, (char *) sqlite3_column_text(stmt, 2));
	return cine;
}

void addCine(int numSalas, char* nombre, char* ubicacion, sqlite3* db){
	int cont = getCinesCount(db);
	printf("empiezo\n");
	char seq[200];
	sprintf(seq, "INSERT INTO CINE(ID, NUMSALAS, NOM_CINE, UBI_CINE) VALUES (%i, %i, '%s', '%s')",cont+1, numSalas, nombre, ubicacion);
	printf("acabo\n");
	printf(seq);
	update(seq, db);
}

void deleteCine(Cine c, sqlite3* db){
	int cont = getSalasCount(db);
	char seq[200];
	sprintf(seq, "DELETE FROM CINE WHERE ID = %i", c.id_Cine);
	update(seq, db);
}


void imprimirTicket(User usuarioLogged, Cine cineSeleccionado, Peli peliSeleccionada)
{
    FILE* f;
    f = fopen("ticket.txt", "w");
    fprintf(f, "Gracias por su compra %s!\n", usuarioLogged.nom_User);
	fprintf(f, "Entrada para el cine: %s para la pelicula: %s (%i)", cineSeleccionado.nom_Cine, peliSeleccionada.titulo, peliSeleccionada.id_Peli);
	fprintf(f, "Le esperamos!\n");
    fclose(f);
}