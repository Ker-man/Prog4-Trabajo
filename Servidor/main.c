#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
//#include <unistd.h>
//#include <io.h>
#include "cine.h"
#include "sala.h"
#include "sesion.h"
#include "peli.h"
#include "user.h"
#include "utilidades.h"
#include "funcionesBD.h"
#include "sqlite3.h"
#include "menus.h"



int main(void){
    //Inicialización de datos BBDD
    sqlite3 *db;
    conectarBD("bbdd.db", &db);  
    crearTablas(db);
    int salir = 0;
    Sesion* listSesiones;
    listSesiones = getSesionFromSalaYPeli(1, 1, db);
    for(int i = 0; i<getSesionesCountFromSalaYPeli(1, 1, db); i++){
        imprimirSesion(listSesiones[i]);
    }
    do{
        int i = menuRegistro(db);
        if (i == 1) {
            menuPrincipal(db);
        }else if (i == 3){
            menuUsuario(db);
        }else if (i == 0){
            salir = 1;
        }
    }while (salir == 0);
    //printf("Adios");


/*
    //Pelis
    Peli p1;
    p1.id_Peli = 1;
    p1.duracion = 103;
    strcpy(p1.titulo, "Avatar");
    strcpy(p1.genero, "Aventura");

    Peli p2;
    p1.id_Peli = 2;
    p1.duracion = 97;
    strcpy(p1.titulo, "IT");
    strcpy(p1.genero, "Terror");

    Peli *lp;
    int tamListaPelis = 2;
    lp= (Sala*)malloc(sizeof(Sala) *tamListaPelis);
    lp[0] = p1;
    lp[1] = p2;

    //Cines
    Cine c1;
    c1.id_Cine = 1;
    strcpy(c1.nom_Cine, "Ale");
    strcpy(c1.ubi_Cine, "Ole");
    c1.numSalas = 2;

    //Salas
    Sala s1;
    s1.id_Sala = 1;
    s1.capacidad = 10;
    s1.numSesiones =2;
    imprimirSala(s1);

    Sala s2;
    s2.id_Sala = 2;
    s2.capacidad = 6;
    s2.numSesiones = 3;
    imprimirSala(s2);

    Sala *ls;
    ls= (Sala*)malloc(sizeof(Sala) *c1.numSalas);
    ls[0] = s1;
    ls[1] = s2;

    //Sesiones
    Sesion se1;
    se1.precio = 10.0f;
    strcpy(se1.horario, "22:30");
    se1.peli = &lp[0];

    Sesion se2;
    se1.precio = 6.0f;
    strcpy(se1.horario, "17:00");
    se1.peli = &lp[1];

    Sesion *lsesion;
    lsesion= (Sesion*)malloc(sizeof(Sesion) *s1.numSesiones);
    lsesion[0] = se1;
    lsesion[1] = se2;    
    
    s1.sesiones = lsesion;
    
    //Cines
    c1.salas = ls;
    imprimirSalas(c1.salas, c1.numSalas);

    imprimirCine(c1);

    Cine c2;
    Cine c3;

    Cine* listaCines;
    int tamListaCines = 3;
    listaCines = (Cine*)malloc(sizeof(Cine)* tamListaCines);
    listaCines[0] = c1;
    listaCines[1] = c2;
    listaCines[2] = c3;



    //El administrador quiere abrir otro cine pulsa la opcion "Crear otro cine"
    //tamListaCines++;   Todos los cines estan en una lista creada con anterioridad
    //anadirCine();

    //El administrador quiere abrir otra sala en un cine elige el cine y pulsa la opcion "Crear otra sala"
    //anadirSala();

    //El administrador decide crear otra sesion para una sala entonces elige una sala y elige "Crear sesion"
    //anadirSesion();

    //El administrador quiere añadir una peli a su lista de pelis a ofrecer en sus cines, elige "Añadir peli"
    //tamListaPelis++;    Todos las pelis estan en una lista creada con anterioridad
    //anadirPeli();

    */

    return 0;
}