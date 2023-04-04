#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirUser(User user)
{
    printf("ID: %i  Nombre: %s\n", user.id_User, user.nom_User);
}

void copiaSeguridad(User user){

    FILE* f;
    f = fopen("UserBackup.txt", "w");
    fprintf(f,"%i;%s;%s;%i",user.id_User,user.nom_User,user.password,user.tipo);
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
        //printf("%c",c);
    }
    //printf("\n");
    fclose(f);
}