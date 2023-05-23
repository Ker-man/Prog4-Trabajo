#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirUser(User user)
{
    printf("ID: %i  Nombre: %s Tipo: %i\n", user.id_User, user.nom_User, user.id_User);
}


//escribirCopiaSeguridad(cont+1, nombre, contrasena, admin);
void escribirCopiaSeguridad(int id,char* nombre, char* contrasena, int admin){

    FILE* f;
    f = fopen("UserBackup.txt", "a");
    fprintf(f,"%i;%s;%s;%i;",id, nombre, contrasena, admin);
    fprintf(f,"\n");
    fclose(f);
}

void leerCopiaSeguridad(){

    char c;
    FILE* f;

    f = fopen("UserBackup.txt", "r");
    if(f==NULL)
    {
        printf("El fichero esta vacio o no se pudo abrir");
        exit(1);
    }

    while(c!=EOF)
    {
        c=fgetc(f);
        printf("%c",c);
    }
    printf("\n");
    fclose(f);
}