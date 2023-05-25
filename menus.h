#ifndef _MENUS_H_
#define _MENUS_H_
#include "../BBDD/sqlite3.h"

int menuRegistro(sqlite3 *db);
void menuPrincipal(sqlite3 *db);
void menuUsuario(sqlite3 *db);
void menuCines(sqlite3 *db);
void menuPeliculas(sqlite3 *db);
//Mas menus que podemos meter como el de comprar ticket o busqueda personalizada

#endif