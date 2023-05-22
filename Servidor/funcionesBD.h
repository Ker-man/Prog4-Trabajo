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

int getUsuarioCount(sqlite3* db);
User* getAllUsers(sqlite3* db);
User getUsuario(char* nombre, sqlite3* db);
User getUsuarioFromID(int id, sqlite3* db);
void addUsuario(char* nombre, char* contrasena, int admin, sqlite3* db);

int getPelisCount(sqlite3* db);
Peli getPeliFromID(int id, sqlite3* db);
Peli* getPeliculas(sqlite3* db);
Peli getPelicula(char* titulo, sqlite3* db);
void addPelicula(char* titulo, char* genero, int duracion , sqlite3* db);

int getCinesCount(sqlite3* db);
Cine getCineFromID(int id, sqlite3* db);
Cine* getCines(sqlite3* db);
Cine getCine(char* nombre, char* ubicacion, sqlite3* db);
void addCine(int numSalas, char* nombre, char* ubicacion, sqlite3* db);

int getSalasCount(sqlite3* db);
int getSalasCountFromCine(int idCine, sqlite3* db);
Sala getSalaFromID(int id, sqlite3* db);
Sala* getSalasFromCine(int idCine, sqlite3* db);
//Sala getSala(char* nombre, char* ubicacion, sqlite3* db);
void addSala(int capacidad, int numSesiones, int idCine, sqlite3* db);

int getSesionesCount(sqlite3* db);
int getSesionesCountFromSalaYPeli(int idSala, int idPeli, sqlite3* db);
Sesion getSesionFromID(int id, sqlite3* db);
Sesion* getSesionFromSalaYPeli(int idSala, int idPeli, sqlite3* db);
//Sala getSala(char* nombre, char* ubicacion, sqlite3* db);
void addSesion(char* horario, int idPeli, int idSala, int precio, sqlite3* db);
#endif  /* _FUNCIONESBD_H_ */