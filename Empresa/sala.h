#ifndef _SALA_H_
#define _SALA_H_
#include "sesion.h"
#include "../BBDD/sqlite3.h"

typedef struct 
{
    int id_Sala;
    int capacidad;
    int numSesiones;
    Sesion *sesiones;
}Sala;


void imprimirSala(Sala sala);


int getSalasCount(sqlite3* db);
int getSalasCountFromCine(int idCine, sqlite3* db);
Sala getSalaFromID(int id, sqlite3* db);
Sala* getSalasFromCine(int idCine, sqlite3* db);
Sala* getAllSalas(sqlite3* db);
//Sala getSala(char* nombre, char* ubicacion, sqlite3* db);
void addSala(int capacidad, int numSesiones, int idCine, sqlite3* db);
void deleteSala(Sala s, sqlite3* db);

#endif