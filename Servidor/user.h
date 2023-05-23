#ifndef _USER_H_
#define _USER_H_
#include "sqlite3.h"

typedef struct 
{
    int id_User;
    char nom_User[30];
    char password[30];
    int tipo;
}User;

void imprimirUser(User user);
void escribirCopiaSeguridad(int id,char* nombre, char* contrasena, int admin);
void leerCopiaSeguridad();


int getUsuarioCount(sqlite3* db);
User* getAllUsers(sqlite3* db);
User getUsuario(char* nombre, sqlite3* db);
User getUsuarioFromID(int id, sqlite3* db);
void addUsuario(char* nombre, char* contrasena, int admin, sqlite3* db);


#endif