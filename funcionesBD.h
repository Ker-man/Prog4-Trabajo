#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"
#include "user.h"

int conectarBD(char base[],sqlite3* db);
int crearTablas(sqlite3* db);


User getUsuario(char* nombre, char* contrasena, sqlite3* db);
void addUsuario(char* nombre, char* contrasena, int admin, sqlite3* db);

#endif  /* _FUNCIONESBD_H_ */