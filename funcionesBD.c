#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"

int conectarBD(char base[],sqlite3 *db){
    int result = sqlite3_open(base, &db);
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
		ID_CINE	INTEGER NOT NULL UNIQUE,\
		NOM_CINE	TEXT NOT NULL,\
		UBI_CINE	TEXT NOT NULL,\
		PRIMARY KEY(ID_CINE)\
	);";

	char sql2[] = "CREATE TABLE IF NOT EXISTS PELICULA (\
	ID_PELI	INTEGER NOT NULL UNIQUE,\
	TITULO_PELI	TEXT NOT NULL,\
	DURACION_PELI	INTEGER NOT NULL,\
	GENERO_PELI	TEXT NOT NULL,\
	PRIMARY KEY(ID_PELI)\
);";

	char sql3[] = "CREATE TABLE IF NOT EXISTS SALA (\
	ID_SALA	INTEGER NOT NULL UNIQUE,\
	CAPACIDAD_SALA	INTEGER NOT NULL,\
	CINE_SALA	INTEGER NOT NULL,\
	PRIMARY KEY(ID_SALA)\
	);";

	char sql4[] = "CREATE TABLE IF NOT EXISTS SESION (\
	HORARIO	TEXT NOT NULL,\
	ID_SALA	INTEGER NOT NULL,\
	ID_PELI	INTEGER NOT NULL\
	PRECIO	INTEGER NOT NULL\
	);";

	char sql5[] = "CREATE TABLE USUARIO (\
	ID_USER	INTEGER NOT NULL UNIQUE,\
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

	result = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir pelicula\n");
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

	result = sqlite3_prepare_v2(db, sql3, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir sala\n");
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

	result = sqlite3_prepare_v2(db, sql4, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir sesion\n");
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

	result = sqlite3_prepare_v2(db, sql5, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		printf("Error al introducir usuario\n");
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
	
	return SQLITE_OK;
}

User getUsuario(char* nombre, char* contrasena, sqlite3* db){
	sqlite3_stmt *stmt;
    User usu;
	char seq[100];
	sprintf(seq, "SELECT * FROM USUARIO WHERE NOM_USER = '%s' AND PASSWORD_USER = '%s'", nombre, encrypt(contrasena));

	if (sqlite3_prepare_v2(db, seq, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al cargar el usuario\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (User){'\0', 0, 0};
	}
	int i =sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		return (User){'\0', 0, 0};
	}
	usu.id_User = sqlite3_column_int(stmt, 0);
	strcpy(usu.nom_User, (char *) sqlite3_column_text(stmt, 1));
	strcpy(usu.password, (char *) sqlite3_column_text(stmt, 2));
	usu.tipo = sqlite3_column_int(stmt, 3);
	return usu;
}

void addUsuario(char* nombre, char* contrasena, int admin, sqlite3* db){
	char seq[200];
	sprintf(seq, "INSERT INTO USUARIO(ID_USER, NOM_USER, PASSWORD_USER, TIPO_USER) VALUES (%i, '%s', '%s', %d)",getUsuarioCount(), nombre, encrypt(contrasena), admin);
	update(seq);
}

