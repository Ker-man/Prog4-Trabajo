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



int menuPrincipal(sqlite3 *db);

// Primer menú al iniciar la app
 int menuRegistro(sqlite3 *db)
{
    // Primer menú al iniciar la app
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
            // getpass("Introduce tu contraseña: \n", password);
            // IMPLEMENTAR COMPROBACION CONTRASEÑA
            User usuarioLogged = getUsuario(usuario, db);
            printf(usuarioLogged.nom_User);
            return 1;
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
            char linea2[30];
            fgets(linea2, 30, stdin);
            sscanf(linea2, "%s", password);
            // getpass("Introduce tu contraseña: \n", password);
            printf("\n");
            // IMPLEMENTAR REGISTRO BBDD
            addUsuario(usuario, password, 1, db);
            return 1;
        }
        case 2:
        {
            printf("¡Hasta pronto!:\n");
            return 0;
        }
    }
}



void menuCines(sqlite3 *db)
{
    printf("=============\n");
    printf("MENU DE CINES\n");
    printf("=============\n");
    printf("\n");


    //funcion de ver cines

    const char *opciones[] = {"Ver mas cines", "Anadir cine?", "Eliminar cine?", "Volver al menu",};

    int o = opcion("Estos son los cines ¿Que desea hacer?", 4, opciones);

        switch (o)
        {
        case 0:
        {
            // CODIGO
            break;
        }
        case 1:
        {
            // CODIGO
            break;
        }
        case 2:
        {
            // CODIGO
            break;
        }
        case 3:
        {
            menuPrincipal(db);
            break;
        }
    }
}

void menuPeliculas(sqlite3 *db) {
    printf("=================\n");
    printf("MENU DE PELICULAS\n");
    printf("=================\n");
    printf("\n");

    // funcion de ver cines

    const char *opciones[] = {"Ver mas pelculas", "Anadir pelicula?", "Eliminar peliculas?", "Volver al menu"};

    int o = opcion("Estos son los cines ¿Que desea hacer?", 4, opciones);

    switch (o)
    {
        case 0:
        {
            // CODIGO
            break;
        }
        case 1:
        {   
            // CODIGO
            break;
        }
        case 2:
        {
            // CODIGO
            break;
        }
        case 3:
        {
            menuPrincipal(db);
            break;
        }
    }
}

void menuOpciones() {
    // TODO
}

int menuPrincipal(sqlite3 *db)
{
    printf("==========================\n");
    printf("MENU PRINCIPAL DEUSTOCINES\n");
    printf("==========================\n");
    printf("\n");

    const char *opciones[] = {"Ver cines", "Ver peliculas", "Cambiar datos de la cuenta", "Cerrar Sesion", "Salir"};

    int o = opcion("Bienvenido a Desutocines. Que desea hacer ahora?", 5, opciones);

    switch (o)
    {
        case 0:
        {
            menuCines(db);
            break;
        }
        case 1:
        {
            menuPeliculas(db);
            break;
        }
        case 2:
        {
            // CODIGO
            break;
        }
        case 3:
        {
            // CODIGO
            break;
        }
        case 4:
        {
            printf("¡Hasta pronto!:\n");
            break;
        }
    }
}