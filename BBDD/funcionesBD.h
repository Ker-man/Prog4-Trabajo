#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "../BBDD/sqlite3.h"
#include "../Usuario/user.h"
#include "../Empresa/peli.h"
#include "../Empresa/cine.h"
#include "../Empresa/sala.h"
#include "../Empresa/sesion.h"

int conectarBD(char base[],sqlite3** db);
int crearTablas(sqlite3* db);

int update(char* query, sqlite3* db);
void borrar(char* tabla, int id);



#endif  /* _FUNCIONESBD_H_ */