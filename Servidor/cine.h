#ifndef _CINE_H_
#define _CINE_H_
#include "peli.h"
#include "user.h"
#include "sesion.h"
#include "sqlite3.h"

typedef struct 
{
    int id_Cine;
    int numSalas;
    char nom_Cine[20];
    char ubi_Cine[30];
    Sala* salas;
}Cine;


void imprimirCine(Cine cine);

int getCinesCount(sqlite3* db);
Cine getCineFromID(int id, sqlite3* db);
Cine* getCines(sqlite3* db);
Cine getCine(char* nombre, char* ubicacion, sqlite3* db);
void addCine(int numSalas, char* nombre, char* ubicacion, sqlite3* db);
void deleteCine(Cine c, sqlite3* db);
void imprimirTicket(User usuarioLogged, Cine cineSeleccionado, Peli peliSeleccionada, Sesion sesionSeleccionada);


#endif