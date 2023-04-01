#ifndef _FUNCIONESBD_H_
#define _FUNCIONESBD_H_
#include "sqlite3.h"

int conectarBD(char base[],sqlite3* db);
int crearTablas(sqlite3* db);

#endif  /* _FUNCIONESBD_H_ */