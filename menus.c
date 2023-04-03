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

// Primer menú al iniciar la app
menuRegistro() {

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
            //getpass("Introduce tu contraseña: \n", password);
            //IMPLEMENTAR COMPROBACION BBDD
            //User usuarioLogged = getUsuario(usuario, password, db); 
            menuPrincipal();
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
            //addUsuario(usuario, password,1, db);
            printf("Usuario creado correctamente, pulse cualquier tecla para continuar\n");
            menuPrincipal();
        }
        case 2:
        {
            printf("¡Hasta pronto!:\n");
            break;
        }
    }
}


menuPrincipal() {
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
            //CODIGO
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
            // CODIGO
            break;
        }
    }
}

void menuCines() {
    // TODO
}

void menuPeliculas() {
    // TODO
}

void menuOpciones() {
    // TODO
}