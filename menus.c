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


// Primer menú al iniciar la app
menuRegistro(sqlite3 *db)
{

    char usuario[30];
    char email[40];
    char password[30];
    printf("==========================\n");
    printf("MENU REGISTRO DEUSTOCINES\n");
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
            sscanf("%29s", usuario);
            // getpass("Introduce tu contraseña: \n", password);
            // IMPLEMENTAR COMPROBACION BBDD
            User usuarioLogged = getUsuario(usuario, password, db);
            menuPrincipal(db);
        }
        case 1:
        {

            printf("================\n");
            printf("REGISTRO USUARIO\n");
            printf("================\n");
            printf("\n");

            printf("Introduzca el nombre de usuario:\n");
            sscanf("%29s", usuario);
            printf("Introduzca el correo de usuario:\n");
            sscanf("%39s", email);
            //getpass("Introduce tu contraseña: \n", password);
            printf("\n");
            //IMPLEMENTAR REGISTRO BBDD
            addUsuario(usuario, password,1, db);
            printf("Usuario creado correctamente, pulse cualquier tecla para continuar\n");
            menuPrincipal(db);
        }
        case 2:
        {
            printf("¡Hasta pronto!:\n");
            break;
        }
    }
}

menuPrincipal(sqlite3 *db)
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
            // CODIGO
            break;
        }
        case 4:
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
            // CODIGO
            break;
    }
    case 4:
    {
            menuPrincipal(db);
            break;
    }
    }
}

void menuOpciones() {
    // TODO
}