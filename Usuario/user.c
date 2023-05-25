#include "user.h"
#include "../BBDD/funcionesBD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirUser(User user)
{
    printf("ID: %i  Nombre: %s Tipo: %i\n", user.id_User, user.nom_User, user.id_User);
}


//escribirCopiaSeguridad(cont+1, nombre, contrasena, admin);
void escribirCopiaSeguridad(int id,char* nombre, char* contrasena, int admin){

    FILE* f;
    f = fopen("UserBackup.txt", "a");
    fprintf(f,"%i;%s;%s;%i;",id, nombre, contrasena, admin);
    fprintf(f,"\n");
    fclose(f);
}

void leerCopiaSeguridad(){

    char c;
    FILE* f;

    f = fopen("UserBackup.txt", "r");
    if(f==NULL)
    {
        printf("El fichero esta vacio o no se pudo abrir");
        exit(1);
    }

    while(c!=EOF)
    {
        c=fgetc(f);
        printf("%c",c);
    }
    printf("\n");
    fclose(f);
}


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
	escribirCopiaSeguridad(cont+1, nombre, contrasena, admin);

	printf("Usuario creado correctamente, pulse cualquier tecla para continuar\n");
}

void deleteUsuario(User u, sqlite3* db){
	int cont = getUsuarioCount(db);
	char seq[200];
	sprintf(seq, "DELETE FROM USUARIO WHERE ID = '%i'", u.id_User);
	update(seq, db);

	printf("Usuario eliminado correctamente, pulse cualquier tecla para continuar\n");
}

void cambiarUsuario(User u, char* nombre, char* pass, sqlite3* db){
	int cont = getUsuarioCount(db);
	char seq[200];
	sprintf(seq, "UPDATE USUARIO SET NOM_USER = '%s', PASSWORD_USER = '%s' WHERE ID = %i",nombre, pass, u.id_User);
	update(seq, db);

	printf("Usuario actualizado correctamente, pulse cualquier tecla para continuar\n");
}