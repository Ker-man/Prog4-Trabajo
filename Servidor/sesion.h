#ifndef _SESION_H_
#define _SESION_H_
#include "peli.h"
#include "sqlite3.h"

typedef struct 
{
    int id_Sesion;
    float precio;
    char horario[15];
    Peli peli;
}Sesion;


void imprimirSesion(Sesion sesion);

int getSesionesCount(sqlite3* db);
int getSesionesCountFromSalaYPeli(int idSala, int idPeli, sqlite3* db);
Sesion getSesionFromID(int id, sqlite3* db);
Sesion* getSesionFromSalaYPeli(int idSala, int idPeli, sqlite3* db);
Sesion* getAllSesiones(sqlite3* db);
//Sala getSala(char* nombre, char* ubicacion, sqlite3* db);
void addSesion(char* horario, int idPeli, int idSala, int precio, sqlite3* db);
void deleteSesion(Sesion s, sqlite3* db);

#endif