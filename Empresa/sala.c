#include "sala.h"
#include "../BBDD/funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirSala(Sala sala)
{
    printf("Sala\n");
    printf("ID: %i  Capacidad: %i\n", sala.id_Sala, sala.capacidad);
}

int getSalasCount(sqlite3* db){
	sqlite3_stmt *stmt;
		if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM SALA", -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar la sala\n");
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

int getSalasCountFromCine(int idCine, sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT COUNT(*) FROM SALA WHERE ID_CINE = %i", idCine);
	return sqlite3_column_int(stmt, 0);
}

Sala getSalaFromID(int id, sqlite3* db){
	sqlite3_stmt *stmt;
    Sala sala;
	char seq[100];
	sprintf(seq, "SELECT * FROM SALA WHERE ID = %i", id);
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar la sala\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Sala){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Sala){'\0', 0, 0};
	}
	sala.id_Sala = sqlite3_column_int(stmt, 0);
	sala.capacidad = sqlite3_column_int(stmt, 1);
	sala.numSesiones = sqlite3_column_int(stmt, 2);
	return sala;
}
Sala* getSalasFromCine( int idCine, sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT * FROM SALA WHERE ID_CINE = %i", idCine);
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar las salas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	int cont = getSalasCountFromCine(idCine, db);
	Sala* salas = (Sala*)malloc(sizeof(Sala)* cont);
	for (int i = 0; i-1<cont && sqlite3_step(stmt) == SQLITE_ROW; i++){
		salas[i].id_Sala = sqlite3_column_int(stmt, 0);
		salas[i].capacidad = sqlite3_column_int(stmt, 1);
		salas[i].numSesiones = sqlite3_column_int(stmt, 2);
	}
	return salas;
}

Sala* getAllSalas(sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT * FROM SALA ");
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar las salas\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	int cont = getSalasCount(db);
	Sala* salas = (Sala*)malloc(sizeof(Sala)* cont);
	for (int i = 0; i-1<cont && sqlite3_step(stmt) == SQLITE_ROW; i++){
		salas[i].id_Sala = sqlite3_column_int(stmt, 0);
		salas[i].capacidad = sqlite3_column_int(stmt, 1);
		salas[i].numSesiones = sqlite3_column_int(stmt, 2);
	}
	return salas;
}

void addSala(int capacidad, int numSesiones, int idCine, sqlite3* db){
	int cont = getSalasCount(db);
	char seq[200];
	sprintf(seq, "INSERT INTO CINE(ID, NUMSALAS, NOM_CINE, UBI_CINE) VALUES (%i, %i, %i, %i)",cont+1, capacidad, numSesiones, idCine);
	update(seq, db);
}

void deleteSala(Sala s, sqlite3* db){
	int cont = getSalasCount(db);
	char seq[200];
	sprintf(seq, "DELETE FROM SALA WHERE ID = %i", s.id_Sala);
	update(seq, db);
}