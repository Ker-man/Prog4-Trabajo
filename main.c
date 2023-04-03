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
            sscanf("%29s", usuario);
            //getpass("Introduce tu contraseña: \n", password);
            //IMPLEMENTAR COMPROBACION BBDD
            User usuarioLogged = getUsuario(usuario, password, db); 
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
        }
        case 2:
        {
            printf("¡Hasta pronto!:\n");
            break;
        }
    }
 
    Sala s1;
    s1.id_Sala = 1;
    s1.capacidad = 10;
    imprimirSala(s1);
    Sala s2;
    s2.id_Sala = 2;
    s2.capacidad = 6;
    imprimirSala(s2);

    ListaSalas ls;
    ls.tamanyo =2;
    ls.salas = (Sala*)malloc(sizeof(Sala) * ls.tamanyo);
    ls.salas[0] = s1;
    ls.salas[1] = s2;

    imprimirListaSalas(ls);

    Cine c1;
    c1.id_Cine = 1;
    strcpy(c1.nom_Cine, "Ale");
    strcpy(c1.ubi_Cine, "Ole");
    c1.listaSalas = ls;

    imprimirCine(c1);
   return 0;
}