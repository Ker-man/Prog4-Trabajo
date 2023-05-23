#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"
#include "user.h"
#include "peli.h"
#include "cine.h"
#include "sala.h"
#include "sesion.h"

int conectarBD(char base[],sqlite3** db);
int crearTablas(sqlite3* db);

int update(char* query, sqlite3* db);
void borrar(char* tabla, int id);



#endif  /* _FUNCIONESBD_H_ */