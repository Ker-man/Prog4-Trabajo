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
    int tipo;
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
                int comp = 0;
                while(comp < 1){
                printf("\n");
                printf("Introduzca `1` si es de tipo administador y introduzca `2` si es de tipo administrador \n");
                printf("\n");
                char linea3[30];
                fgets(linea3, 30, stdin);
                sscanf(linea3, "%i", tipo);
                if(tipo == 1 || tipo == 2){
                    printf("Tipo correcto");
                    comp++;
                }else{
                    print("Tipo incorrecto");
                }
                }
                // IMPLEMENTAR REGISTRO BBDD
                addUsuario(usuario, password, tipo, db);
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

//Menu Sesiones
//Menu Salas

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

        int cont = getCinesCount(db);
        Cine* cines  = getCines(db);

        int cont2 = getPelisCount(db);
        Peli* peliculas  = getPeliculas(db);

        int IDcine;

        switch (o)
        {
            case 0:
            {
                printf("Mostrando todos los cines disponibles actualmente...\n");
                printf("\n");
                printf("\n");
                printf("\n");
                for(int i=0; i<cont; i++){
                    imprimirCine(cines[i]);
                }           
                break;
            }
            case 1:
            {   
                char linea2[30];
                printf("Introduce el ID del cine cuyas salas quieres ver: \n");
                fgets(linea2,30,stdin);
                sscanf(linea2, "%i", IDcine);
                printf("\n");
                printf("\n");
                printf("\n");
                getSalasCountFromCine(IDcine, db);
                break;
            }
            case 2:
            {
                char linea1[30];
                char cine[30];
                Cine cineSeleccionado;
                printf("Introduce el nombre del cine: \n");
                fgets(linea1,30,stdin);
                sscanf(linea1, "%s", cine);

                for(int i=0; i<cont; i++){
                    if(cines[i].nom_Cine==cine){
                        cineSeleccionado=cines[i];
                    }else{
                        printf("ese cine no esta en nuestro registro");
                    }
                }

                char linea2[30];
                char peli[30];
                Peli peliSeleccionada;
                printf("Introduce el nombre de la peli: \n");
                fgets(linea2,30,stdin);
                sscanf(linea2, "%s", peli);

                for(int i=0; i<cont2; i++){
                    if(peliculas[i].titulo==peli){
                        peliSeleccionada=peliculas[i];
                    }else{
                        printf("esa peli no esta en nuestro registro");
                    }
                }                  
                
                imprimirTicket(cineSeleccionado, peliSeleccionada);
            }
        }
    } while(o != 3);
    //menuPrincipal(db);
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

        int cont = getPelisCount(db);
        Peli* pelis = getPeliculas(db);
        char genero[30];
        char titulo[30];
        switch (o)
        {
            case 0:
            {
                printf("He aqui todas las peliculas:");
                printf("\n");
                printf("\n");
                printf("\n");
                for(int i=0; i<cont; i++){
                    imprimirPelicula(pelis[i]);
                }           
                break;
            }
            case 1:
            {   
                char linea[30];
                printf("Que genero quieres explorar\n");
                fgets(linea, 30, stdin);
                sscanf(linea, "%s", genero);
                printf("\n");
                printf("\n");
                printf("\n");
                buscarGenero(pelis, cont, genero);
                break;
            }
            case 2:
            {
                char linea2[30];
                printf("Introduce el titulo de la pelicula que quieres buscar\n");
                fgets(linea2,30,stdin);
                sscanf(linea2, "%s", titulo);
                printf("\n");
                printf("\n");
                printf("\n");
                buscarTitulo(pelis, cont, titulo);
                break;
            }
            case 3:
            {
                maxPelicula(pelis, cont);
                printf("\n");
                printf("\n");
                printf("\n");
                break;
            }
            case 4:
            {
                minPelicula(pelis, cont);
                printf("\n");
                printf("\n");
                printf("\n");
                break;
            }
        }
    } while(o != 5);
    //menuPrincipal(db);
}

int menuPrincipal(sqlite3 *db) //Menu admin
{
        printf("\n\n\n==========================\n");
        printf("MENU PRINCIPAL DEUSTOCINES\n");
        printf("==========================\n");
        printf("\n");

        const char *opciones[] = {"Menu cines", "Menu peliculas", "Cambiar datos de la cuenta", "Cerrar Sesion", "Salir"};
        int o;                      //Crear Pelicula  //Borrar Pelicula //
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
        //menuRegistro(db);
    
    
}
/*
Menu peliculas
    Ver todas las pelis
    Ver la peli mas larga
    Ticket
Menu Sesiones
    Ver sesiones
    Ver las sesiones ma largas

*/
int menuUsuario(sqlite3 *db)
{
        printf("\n\n\n==========================\n");
        printf("MENU USUARIO DEUSTOCINES\n");
        printf("==========================\n");
        printf("\n");

        const char *opciones[] = {"Menu peliculas", "Menu Cines", "Salir"};
        int o;
        do {
            o = opcion("Bienvenido a Desutocines. Que desea hacer ahora?", 3, opciones);

        switch (o)
            {
                case 0:
                {
                    menuPeliculas(db);
                    break;
                }
                case 1:
                {
                    menuCines(db);
                    break;
                }
            }
        }
        while(o != 2);
        printf("¡Hasta pronto!:\n");
        //menuRegistro(db);
    
    
}