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
int menuUsuario(sqlite3 *db);

// Primer menú al iniciar la app
 int menuRegistro(sqlite3 *db)
{
    // Primer menú al iniciar la app
    char usuario[30];
    char email[40];
    char password[30];
    User usuarioLogged;
    printf("\n\n\n==========================\n");
    printf("MENU PRINCIPAL DEUSTOCINES\n");
    printf("==========================\n");
    printf("\n");

    const char *opciones[] = {"Iniciar Sesion", "Registrar usuario", "Salir"};

    int o = opcion("Bienvenido al programa de administracion de DeustoCines. Eliga una opcion", 3, opciones);

    switch (o)
    {
        case 0:
        {
            imprimirUser(usuarioLogged);
            printf("\n\n\n================\n");
            printf("INICIO DE SESION\n");
            printf("================\n");
            printf("\n");

            printf("Introduzca el nombre de usuario:\n");
            char linea[30];
            fgets(linea, 30, stdin);
            sscanf(linea, "%s", usuario); 
            // getpass("Introduce tu contraseña: \n", password);
            // IMPLEMENTAR COMPROBACION CONTRASEÑA
            usuarioLogged = getUsuario(usuario, db);
            if (usuarioLogged.id_User == -1){
                return 2;
            }else {
                mascara(password);  
                if (strcmp(usuarioLogged.password, password) == 0){
                    if(usuarioLogged.tipo=1)
                    {
                        return 1;//admin
                    }else{
                        return 3;//usuario estandar
                    }
                }else if (strcmp(usuarioLogged.password, password) != 0){
                    printf("\nLa contrasena introducida no es correcta\n");
                    return 2;
                }
            }
            
        }
        case 1:
        {

            printf("\n\n\n================\n");
            printf("REGISTRO USUARIO\n");
            printf("================\n");
            printf("\n");

            printf("Introduzca el nombre de usuario:\n");
            char linea[30];
            fgets(linea, 30, stdin);
            sscanf(linea, "%s", usuario);
            if (getUsuario(usuario, db).id_User != -1){
                printf("\nUsuario ya registrado, pruebe a iniciar sesion\n");
                return 2;
            }else{
                printf("Introduzca la contrasena de usuario:\n");
                char linea2[30];
                fgets(linea2, 30, stdin);
                sscanf(linea2, "%s", password);
                // getpass("Introduce tu contraseña: \n", password);
                printf("\n");
                // IMPLEMENTAR REGISTRO BBDD
                addUsuario(usuario, password, 1, db);
                return 1;
            }
        }
        case 2:
        {
            printf("\nHasta pronto!:\n");
            return 0;
        }
    }
}



void menuCines(sqlite3 *db)
{
    printf("\n\n\n=============\n");
    printf("MENU DE CINES\n");
    printf("=============\n");
    printf("\n");

    const char *opciones[] = {"Ver todos los cines", "Ver salas", "Crear ticket", "Volver al menu"};

     int o;
    do {
        o = opcion("Esta usted ahora en el menu de cines. Que desea hacer?", 4, opciones);

        switch (o)
        {
            case 0:
            {
                printf("Mostrando todos los cines disponibles actualmente...\n");
                printf("\n");
                printf("\n");
                printf("\n");
                //imprimirPelicula();            
                break;
            }
            case 1:
            {   
                /*
                char genero[20];
                printf("Que genero quieres explorar\n");
                fgets(genero,20,stdin);
                printf("\n");
                printf("\n");
                printf("\n");
                */
                //buscarGenero();
                break;
            }
            case 2:
            {
                /*
                char titulo[20];
                printf("Que genero quieres explorar\n");
                fgets(titulo,20,stdin);
                printf("\n");
                printf("\n");
                printf("\n");
                */
                //buscarTitulo();
                break;
            }
        }
    } while(o != 3);
    menuPrincipal(db);
}

void menuPeliculas(sqlite3 *db) {
    printf("\n\n\n=================\n");
    printf("MENU DE PELICULAS\n");
    printf("=================\n");
    printf("\n");

    const char *opciones[] = {"Ver todas las peliculas", "Buscar por genero", "Buscar por titulo", "Pelicula mas larga", "Pelicula mas corta", "Volver al menu"};
    int o;
    do {
        o = opcion("Bienvenido al menu peliculas Que desea hacer?", 6, opciones);

        switch (o)
        {
            case 0:
            {
                printf("He aqui todas las peliculas");
                printf("\n");
                printf("\n");
                printf("\n");                
                //imprimirPelicula();            
                break;
            }
            case 1:
            {   
                char genero[20];
                printf("Que genero quieres explorar\n");
                fgets(genero,20,stdin);
                printf("\n");
                printf("\n");
                printf("\n");
                //buscarGenero();
                break;
            }
            case 2:
            {
                char titulo[20];
                printf("Introduce el titulo de la pelicula que quieres buscar\n");
                fgets(titulo,20,stdin);
                printf("\n");
                printf("\n");
                printf("\n");
                //buscarTitulo();
                break;
            }
            case 3:
            {
                //maxPelicula();
                break;
            }
            case 4:
            {
                //minPelicula();
                break;
            }
        }
    } while(o != 5);
    menuPrincipal(db);
}

int menuPrincipal(sqlite3 *db)
{
        printf("\n\n\n==========================\n");
        printf("MENU PRINCIPAL DEUSTOCINES\n");
        printf("==========================\n");
        printf("\n");

        const char *opciones[] = {"Menu cines", "Menu peliculas", "Cambiar datos de la cuenta", "Cerrar Sesion", "Salir"};
        int o;
        do {
            o = opcion("Bienvenido a Desutocines. Que desea hacer ahora?", 5, opciones);

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
            }
        }
        while(o != 4);
        printf("¡Hasta pronto!:\n");
        menuRegistro(db);
    
    
}

int menuUsuario(sqlite3 *db)
{
        printf("\n\n\n==========================\n");
        printf("MENU USUARIO DEUSTOCINES\n");
        printf("==========================\n");
        printf("\n");

        const char *opciones[] = {"Menu peliculas", "Cambiar datos de la cuenta", "Cerrar Sesion", "Salir"};
        int o;
        do {
            o = opcion("Bienvenido a Desutocines. Que desea hacer ahora?", 4, opciones);

        switch (o)
            {
                case 0:
                {
                    menuPeliculas(db);
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
            }
        }
        while(o != 3);
        printf("¡Hasta pronto!:\n");
        menuRegistro(db);
    
    
}