#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../BBDD/sqlite3.h"

int conectarBD(char base[],sqlite3 **db){
	printf(base);
    int result = sqlite3_open(base, db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    printf("Base de datos conectada\n") ;
	return result;
}

int crearTablas(sqlite3* db) {
	sqlite3_stmt *stmt;

	char sql1[] = "CREATE TABLE IF NOT EXISTS CINE (\
		ID INTEGER NOT NULL UNIQUE,\
		NUMSALAS	INTEGER NOT NULL,\
		NOM_CINE	TEXT NOT NULL,\
		UBI_CINE	TEXT NOT NULL,\
		PRIMARY KEY(ID_CINE)\
	);";

	char sql2[] = "CREATE TABLE IF NOT EXISTS PELICULA (\
	ID INTEGER NOT NULL UNIQUE,\
	TITULO_PELI	TEXT NOT NULL,\
	DURACION_PELI INTEGER NOT NULL,\
	GENERO_PELI	TEXT NOT NULL,\
	PRIMARY KEY(ID_PELI)\
);";

	char sql3[] = "CREATE TABLE IF NOT EXISTS SALA (\
	ID INTEGER NOT NULL UNIQUE,\
	CAPACIDAD_SALA	INTEGER NOT NULL,\
	NUMSESIONES	INTEGER NOT NULL,\
	ID_CINE	INTEGER NOT NULL,\
	PRIMARY KEY(ID_SALA)\
	);";

	char sql4[] = "CREATE TABLE IF NOT EXISTS SESION (\
	ID	INTEGER NOT NULL,\
	HORARIO	TEXT NOT NULL,\
	ID_PELI	INTEGER NOT NULL,\
	ID_SALA	INTEGER NOT NULL,\
	PRECIO	INTEGER NOT NULL\
	);";

	char sql5[] = "CREATE TABLE IF NOT EXISTS USUARIO (\
	ID	INTEGER NOT NULL UNIQUE,\
	NOM_USER	TEXT NOT NULL,\
	PASSWORD_USER	TEXT NOT NULL,\
	TIPO_USER	INTEGER NOT NULL,\
	PRIMARY KEY(ID_USER)\
	);";
	
	int result;
	result = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);


	if (result != SQLITE_OK) {
		printf("Error al introducir cine\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	int result2;
	result2 = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);

	if (result2 != SQLITE_OK) {
		printf("Error al introducir pelicula\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result2;
	}

	result2 = sqlite3_step(stmt);
	if (result2 != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result2;
	}

	result2 = sqlite3_finalize(stmt);
	if (result2 != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result2;
	}

	int result3;
	result3 = sqlite3_prepare_v2(db, sql3, -1, &stmt, NULL);

	if (result3 != SQLITE_OK) {
		printf("Error al introducir sala\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result3;
	}

	result3 = sqlite3_step(stmt);
	if (result3 != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result3;
	}
	result3 = sqlite3_finalize(stmt);
	if (result3 != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result3;
	}

	int result4;
	result4 = sqlite3_prepare_v2(db, sql4, -1, &stmt, NULL);

	if (result4 != SQLITE_OK) {
		printf("Error al introducir sesion\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result4;
	}

	result4 = sqlite3_step(stmt);
	if (result4 != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result4;
	}
	result4 = sqlite3_finalize(stmt);
	if (result4 != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result4;
	}

	int result5;
	result5 = sqlite3_prepare_v2(db, sql5, -1, &stmt, NULL);

	if (result5 != SQLITE_OK) {
		printf("Error al introducir usuario\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result5;
	}

	result5 = sqlite3_step(stmt);
	if (result5 != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result5;
	}
	result5 = sqlite3_finalize(stmt);
	if (result5 != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result5;
	}
	
	return SQLITE_OK;
}

int update(char* query, sqlite3* db){
	sqlite3_stmt *stmt;
	int i = sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL) ;
	if(i != SQLITE_OK)
		printf("%s\n", sqlite3_errmsg(db));
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return i;
}

void borrar(char* tabla, int id){
	char seq[100];
	sprintf(seq, "DELETE FROM '%s' WHERE ID = %i", tabla, id);
}

//_________________________________________________________________________________________________________________________________________________________________________________

//Funciones Usuario

//_________________________________________________________________________________________________________________________________________________________________________________

//Funciones Peli

//_________________________________________________________________________________________________________________________________________________________________________________

//Funciones Cine
//_________________________________________________________________________________________________________________________________________________________________________________
//Funciones Sala

//_________________________________________________________________________________________________________________________________________________________________________________

//Funciones Sesiones