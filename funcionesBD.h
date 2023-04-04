#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"
#include "user.h"
#include "peli.h"

int conectarBD(char base[],sqlite3** db);
int crearTablas(sqlite3* db);

void borrar(char* tabla, int id);
int getUsuarioCount(sqlite3* db);
User* getAllUsers(sqlite3* db);
User getUsuario(char* nombre, sqlite3* db);
User getUsuarioFromID(int id, sqlite3* db);
void addUsuario(char* nombre, char* contrasena, int admin, sqlite3* db);
Peli getPelicula(char* titulo, sqlite3* db);
void addPelicula(char* titulo, char* genero, int duracion , sqlite3* db);


#endif  /* _FUNCIONESBD_H_ */