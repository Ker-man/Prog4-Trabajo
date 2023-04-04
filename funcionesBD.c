#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"

int conectarBD(char base[],sqlite3 **db){
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
	CINE_SALA	INTEGER NOT NULL,\
	PRIMARY KEY(ID_SALA)\
	);";

	char sql4[] = "CREATE TABLE IF NOT EXISTS SESION (\
	HORARIO	TEXT NOT NULL,\
	ID_PELI	INTEGER NOT NULL,\
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

void borrar(char* tabla, int id){
	char seq[100];
	sprintf(seq, "DELETE FROM '%s' WHERE ID = %i", tabla, id);
}

int getUsuarioCount(sqlite3* db){
	sqlite3_stmt *stmt;
	printf("heyo");
		if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM USUARIO", -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar el usuario\n");
			printf("cualquier cosa");
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

User* getAllUsers(sqlite3* db){
	User* allUsers = (User*)malloc(sizeof(User)* getUsuarioCount(db));
	for (int i = 0; i<getUsuarioCount(db); i++){
		allUsers[i] = getUsuarioFromID(i, db);
	}
	return allUsers;
}
User getUsuario(char* nombre, sqlite3* db){
	sqlite3_stmt *stmt;
    User usu;
	char seq[100];
	sprintf(seq, "SELECT * FROM USUARIO WHERE NOM_USER = '%s'", nombre);

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

User getUsuarioFromID(int id, sqlite3* db){
	sqlite3_stmt *stmt;
    User usu;
	char seq[100];
	sprintf(seq, "SELECT * FROM USUARIO WHERE ID = %i", id);

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
	int cont = getUsuarioCount(db);
	printf("no llego %i\n", cont);
	for (int i = 0; i<cont; i++){
		printf("HOLA\n");
		if (getAllUsers(db)[i].nom_User == nombre){
			printf("Usuario ya registrado\n");
			printf("%s\n", sqlite3_errmsg(db)); //comprobar y sino comentar
		}else{
			char seq[200];
			sprintf(seq, "INSERT INTO USUARIO(ID, NOM_USER, PASSWORD_USER, TIPO_USER) VALUES (%i, '%s', '%s', %i)",getUsuarioCount(db), nombre, contrasena, admin);
			//update(seq);
			printf("Usuario creado correctamente, pulse cualquier tecla para continuar\n");
		}
	}	
	free(getAllUsers(db));
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
	char seq[200];
	sprintf(seq, "INSERT INTO PELICULA(ID, TITULO_PELI, DURACION_PELI, GENERO_PELI) VALUES ('%s', '%s', %i, %d)",getUsuarioCount(db), titulo, duracion, genero);
	//update(seq);
}

