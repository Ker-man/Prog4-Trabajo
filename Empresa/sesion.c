#include "sesion.h"
#include "../BBDD/funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void imprimirSesion(Sesion sesion)
{
    printf("\nSesion con ID: %i y horario: %s\n", sesion.id_Sesion, sesion.horario);
}

int getSesionesCount(sqlite3* db){
	sqlite3_stmt *stmt;
		if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM SESION", -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar la sesion\n");
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

int getSesionesCountFromSalaYPeli(int idSala, int idPeli, sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT COUNT(*) FROM SESION WHERE ID_SALA = %i AND ID_PELI = %i", idSala, idPeli);
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar la sesion\n");
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

Sesion getSesionFromID(int id, sqlite3* db){
	sqlite3_stmt *stmt;
    Sesion sesion;
	char seq[100];
	sprintf(seq, "SELECT * FROM SESION WHERE ID = %i", id);

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar la sesion\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Sesion){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (Sesion){'\0', 0, 0};
	}
	sesion.id_Sesion = sqlite3_column_int(stmt, 0);
	strcpy(sesion.horario, (char *) sqlite3_column_text(stmt, 1));
	sesion.peli = getPeliFromID(sqlite3_column_int(stmt, 2), db);
	sesion.precio = sqlite3_column_int(stmt, 3);
	return sesion;
}
Sesion* getSesionFromSalaYPeli(int idSala, int idPeli, sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT * FROM SESION WHERE ID_SALA = %i AND ID_PELI = %i", idSala, idPeli); 
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar las sesiones\n");
			printf("%s\n", sqlite3_errmsg(db));
			return 0;
		}
	int cont = getSesionesCountFromSalaYPeli(idSala, idPeli, db);
	//printf("\nFunciono"); 
	Sesion* sesiones = (Sesion*)malloc(sizeof(Sesion)* cont);
	//printf("\nFunciono2");
	for (int i = 0; i-1< cont && sqlite3_step(stmt) == SQLITE_ROW; i++){
			//printf("\nFunciono3"); 
			sesiones[i].id_Sesion = sqlite3_column_int(stmt, 0);
			strcpy(sesiones[i].horario, (char *) sqlite3_column_text(stmt, 1));
			sesiones[i].peli = getPeliFromID(sqlite3_column_int(stmt, 2), db);
			sesiones[i].precio = sqlite3_column_int(stmt, 3);
	}
	return sesiones;
}

Sesion* getAllSesiones(sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT * FROM SESION"); 
	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar las sesiones\n");
			printf("%s\n", sqlite3_errmsg(db));
			return 0;
		}
	int cont = getSesionesCount(db);
	//printf("\nFunciono"); 
	Sesion* sesiones = (Sesion*)malloc(sizeof(Sesion)* cont);
	//printf("\nFunciono2");
	for (int i = 0; i-1< cont && sqlite3_step(stmt) == SQLITE_ROW; i++){
			//printf("\nFunciono3"); 
			strcpy(sesiones[i].horario, (char *) sqlite3_column_text(stmt, 1));
			sesiones[i].id_Sesion = sqlite3_column_int(stmt, 0);
			sesiones[i].peli = getPeliFromID(sqlite3_column_int(stmt, 2), db);
			sesiones[i].precio = sqlite3_column_int(stmt, 3);
	}
	return sesiones;
}

void addSesion(char* horario, int idPeli, int idSala, int precio, sqlite3* db){
	int cont = IDMasAltoSes(getAllSesiones(db), getSesionesCount(db));
	char seq[200];
	sprintf(seq, "INSERT INTO SESION(ID, HORARIO, ID_PELI, ID_SALA, PRECIO) VALUES (%i,'%s', %i, %i, %i)",cont+1, horario, idPeli, idSala, precio);
	update(seq, db);
}

void deleteSesion(Sesion s, sqlite3* db){
	int cont = getSesionesCount(db);
	char seq[200];
	sprintf(seq, "DELETE FROM SESION WHERE ID = %i", s.id_Sesion);
	update(seq, db);
}

int IDMasAltoSes(Sesion* sesiones, int numSesiones){
    int idMA = sesiones[0].id_Sesion;
    for (int i = 1; i<numSesiones;i++){
        if (idMA>sesiones[i].id_Sesion){
            idMA = sesiones[i].id_Sesion;
        }
    }
    return idMA;
}