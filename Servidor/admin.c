#include "funciones.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcionesBD.h"
#include "pais.h"
#include <conio.h>
#include "atleta.h"
#include "pais.h"
#include "ranking.h"
#include "competicion.h"
#include "modalidad.h"
#define CONTRASENA "admin"
#define BORRAR 8
#define ENTER 13
//gcc main.c funciones.c funcionesBD.c sqlite3.c -o aaa.exe
//gcc atleta.c pais.c lugar.c competicion.c modalidad.c ranking.c funciones.c funcionesBD.c sqlite3.c admin.c -o admin.exe
int main(void){
    FILE* ficherolog;
    ficherolog = fopen("loggerAdmin.txt", "w");
    fprintf(ficherolog, "Empezamos\n");
    fclose(ficherolog);
    ficherolog = fopen("logger.txt", "a");
    fprintf(ficherolog, "Comienzo de Programa:\n\n");
    fclose(ficherolog);
    int fallo = 0;
    int acierto = 0;
    int maxFallo = 5;
    char contrasena[21];
    char encriptar;
    sqlite3 *db;
    int result = sqlite3_open("Basededatos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    crearTablas(db);
    ficherolog = fopen("logger.txt", "a");
    fprintf(ficherolog, "Base de datos cargada:\n\n");
    fclose(ficherolog);
    do {
        int i = 0;
        system("cls");
        printf("Contrasena: ");
        while (encriptar = getch()) {
            if (encriptar == ENTER) {
                contrasena[i] = '\0';
                break;
            }
            else if (encriptar == BORRAR) {
                if (i == 0) continue;
                i--;
                printf("\b \b");
            }
            else {
                printf("*");
                contrasena[i] = encriptar;
                i++;
            }
        }
       
        
        if (strcmp(CONTRASENA, contrasena) == 0) {
            fprintf(ficherolog, "Contraseña bien introducida, comenzando el programa\n\n");
            system("cls");
            ListaPersona lper;
            result = cargarAtletas(db, &lper);
            menuPrincipalAdmin(db);
            free(lper.persona);
            acierto++;
        }
        else {
            fprintf(ficherolog, "Contraseña incorrecta introducida\n\n");
            printf("\n");
            printf("Contrasena incorrecta");
            fallo++;
            getchar();
        }
    } while (acierto == 0 && fallo < maxFallo);
    sqlite3_close(db);
    fprintf(ficherolog, "Programa finalizado\n\n");
    fclose(ficherolog);
    return 0;
}