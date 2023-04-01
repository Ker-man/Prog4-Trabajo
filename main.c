#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h>
#include <io.h>
#include "cine.h"
#include "sala.h"
#include "sesion.h"
#include "pelicula.h"
#include "user.h"
#include "funcionesBD.h"
#include "sqlite3.h"


int main(void){
    //Inicialización de datos BBDD
    sqlite3 *db;
    conectarBD("bbdd.bd", db);   
    crearTablas(db);

    //Primer menú al iniciar la app
    char opcion;
    char usuario[30];
    char email[40];
    char password[30];
    printf("==========================\n");
    printf("MENU PRINCIPAL DEUSTOCINES\n");
    printf("==========================\n");
    printf("\n");
    printf("Bienvenido al programa de administracion de DeustoCines. Eliga una opcion\n");

    printf("1. Iniciar sesion\n");
    printf("2. Registrar usuario\n");
    printf("3. Salir\n");

    sscanf("%i", opcion);

    switch (opcion)
    {
        case '1':;
        {
            printf("================\n");
            printf("INICIO DE SESION\n");
            printf("================\n");
            printf("\n");

            printf("Introduzca el nombre de usuario:\n");
            sscanf("%29s", usuario);
            getpass("Introduce tu contraseña: \n", password);
            //IMPLEMENTAR COMPROBACION BBDD
        }
        case '2':;
        {

            printf("================\n");
            printf("REGISTRO USUARIO\n");
            printf("================\n");
            printf("\n");

            printf("Introduzca el nombre de usuario:\n");
            sscanf("%29s", usuario);
            printf("Introduzca el correo de usuario:\n");
            sscanf("%39s", email);
            getpass("Introduce tu contraseña: \n", password);
            printf("\n");
            //IMPLEMENTAR REGISTRO BBDD
            printf("Usuario creado correctamente, pulse cualquier tecla para continuar\n");
        }
        case '3':;
        {
            break;
        }
    }
    return 0;
    

}