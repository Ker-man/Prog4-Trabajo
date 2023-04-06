#include "funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"

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

int getUsuarioCount(sqlite3* db){
	sqlite3_stmt *stmt;
		if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM USUARIO", -1, &stmt, NULL) != SQLITE_OK) {
			printf("Error al cargar el usuario\n");
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
		return (User){0,'\0', 0, 0};
	}
	int i = sqlite3_step(stmt);
	if(i != SQLITE_ROW){
		printf("\nEste usuario no se encuentra registrado\n");
		return (User){-1,"USER_ERROR", "ERROR"};
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
	char seq[200];
	sprintf(seq, "INSERT INTO USUARIO(ID, NOM_USER, PASSWORD_USER, TIPO_USER) VALUES (%i, '%s', '%s', %i)",cont+1, nombre, contrasena, admin);
	update(seq, db);
	//escribirCopiaSeguridad(cont+1, nombre, contrasena, admin);

	printf("Usuario creado correctamente, pulse cualquier tecla para continuar\n");
}

//_________________________________________________________________________________________________________________________________________________________________________________

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

//_________________________________________________________________________________________________________________________________________________________________________________

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
	for (int i = 0; i<getCinesCount(db); i++){
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
void addCine(int numSalas, char* nombre, char* ubicacion, sqlite3* db){
	int cont = getCinesCount(db);
	char seq[200];
	sprintf(seq, "INSERT INTO CINE(ID, NUMSALAS, NOM_CINE, UBI_CINE) VALUES (%i, %i, '%s', '%s')",cont+1, numSalas, nombre, ubicacion);
	update(seq, db);
}
//_________________________________________________________________________________________________________________________________________________________________________________
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
Sala* getSalasCine( int idCine, sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT * FROM SALA WHERE ID_CINE = %i", idCine);
	Sala* salas = (Sala*)malloc(sizeof(Sala)* getSalasCountFromCine(idCine, db));
	for (int i = 0; i<getSalasCountFromCine( idCine, db); i++){
		salas[i].id_Sala = sqlite3_column_int(stmt, 0);
		salas[i].capacidad = sqlite3_column_int(stmt, 1);
		salas[i].numSesiones = sqlite3_column_int(stmt, 2);
		update(seq, db);
	}
	return salas;
}

void addSala(int capacidad, int numSesiones, int idCine, sqlite3* db){
	int cont = getSalasCount(db);
	char seq[200];
	sprintf(seq, "INSERT INTO CINE(ID, NUMSALAS, NOM_CINE, UBI_CINE) VALUES (%i, %i, %i, %i)",cont+1, capacidad, numSesiones, idCine);
	update(seq, db);
}

//_________________________________________________________________________________________________________________________________________________________________________________

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
	strcpy(sesion.horario, (char *) sqlite3_column_text(stmt, 1));
	sesion.peli = getPeliFromID(sqlite3_column_int(stmt, 2), db);
	sesion.precio = sqlite3_column_int(stmt, 3);
	return sesion;
}
Sesion* getSesionFromSalaYPeli(int idSala, int idPeli, sqlite3* db){
	sqlite3_stmt *stmt;
	char seq[100];
	sprintf(seq, "SELECT * FROM SESION WHERE ID_SALA = %i AND ID_PELI = %i", idSala, idPeli);
	Sesion* sesiones = (Sesion*)malloc(sizeof(Sesion)* getSesionesCountFromSalaYPeli(idSala, idPeli, db));
	for (int i = 0; i<getSesionesCountFromSalaYPeli(idSala, idPeli, db); i++){
		strcpy(sesiones[i].horario, (char *) sqlite3_column_text(stmt, 1));
		sesiones[i].peli = getPeliFromID(sqlite3_column_int(stmt, 2), db);
		sesiones[i].precio = sqlite3_column_int(stmt, 3);
		update(seq, db);
	}
	return sesiones;
}

void addSesion(char* horario, int idPeli, int idSala, int precio, sqlite3* db){
	int cont = getSesionesCount(db);
	char seq[200];
	sprintf(seq, "INSERT INTO SESION(ID, HORARIO, ID_PELI, ID_SALA, PRECIO) VALUES (%i,'%s', %i, %i, %i)",cont+1, horario, idPeli, idSala, precio);
	update(seq, db);
}