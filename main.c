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



int main(void){
    //Inicialización de datos BBDD
    sqlite3 *db;
    conectarBD("bbdd.bd", db);   
    crearTablas(db);

    //Primer menú al iniciar la app
    char usuario[30];
    char email[40];
    char password[30];
    printf("==========================\n");
    printf("MENU PRINCIPAL DEUSTOCINES\n");
    printf("==========================\n");
    printf("\n");

    const char *opciones[] = {"Iniciar Sesion", "Registrar usuario", "Salir"};

    int o = opcion("Bienvenido al programa de administracion de DeustoCines. Eliga una opcion", 3, opciones);

    switch (o)
    {
        case 0:
        {
            printf("================\n");
            printf("INICIO DE SESION\n");
            printf("================\n");
            printf("\n");

            printf("Introduzca el nombre de usuario:\n");
            char linea[30];
            fgets(linea, 30, stdin);
            sscanf(linea, "%s", usuario);
            //getpass("Introduce tu contraseña: \n", password);
            //IMPLEMENTAR COMPROBACION CONTRASEÑA
            User usuarioLogged = getUsuario(usuario, db); 
        }
        case 1:
        {

            printf("================\n");
            printf("REGISTRO USUARIO\n");
            printf("================\n");
            printf("\n");

            printf("Introduzca el nombre de usuario:\n");
            char linea[30];
            fgets(linea, 30, stdin);
            sscanf(linea, "%s", usuario);
            printf("Introduzca el correo de usuario:\n");
            char linea[30];
            fgets(linea, 30, stdin);
            sscanf(linea, "%s", email);
            //getpass("Introduce tu contraseña: \n", password);
            printf("\n");
            //IMPLEMENTAR REGISTRO BBDD
            //addUsuario(usuario, password,1, db);
        }
        case 2:
        {
            printf("¡Hasta pronto!:\n");
            break;
        }
    }

/*
    Cine c1;
    c1.id_Cine = 1;
    strcpy(c1.nom_Cine, "Ale");
    strcpy(c1.ubi_Cine, "Ole");
    c1.numSalas = 2;

    Sala s1;
    s1.id_Sala = 1;
    s1.capacidad = 10;
    imprimirSala(s1);

    Sala s2;
    s2.id_Sala = 2;
    s2.capacidad = 6;
    imprimirSala(s2);

    Sala *ls;
    ls= (Sala*)malloc(sizeof(Sala) *c1.numSalas);
    ls[0] = s1;
    ls[1] = s2;

    c1.salas = ls;
    imprimirSalas(c1.salas, c1.numSalas);

    imprimirCine(c1);

    Cine c2;
    Cine c3;

    Cine* listaCines;
    listaCines = (Cine*)malloc(sizeof(Cine)*3);
    int tamLista = 3;
    listaCines[0] = c1;
    listaCines[1] = c2;
    listaCines[2] = c3;
*/
    //El administrador quiere abrir otro cine pulsa la opcion "Crear otro cine"
    //tamLista++;
    //añadirCine();

    //El administrador quiere abrir otra sala en un cine elige el cine y pulsa la opcion "Crear otra sala"
    //a



    return 0;
}