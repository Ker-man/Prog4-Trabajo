#include "user.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

void User::imprimirUser()
{
    printf("ID: %i  Nombre: %s Tipo: %i\n", id_User, nom_User, tipo);
}

void User::escribirCopiaSeguridad(int id, const char *nombre, const char *contrasena, int admin)
{
    FILE *f;
    f = fopen("UserBackup.txt", "a");
    fprintf(f, "%i;%s;%s;%i;", id, nombre, contrasena, admin);
    fprintf(f, "\n");
    fclose(f);
}

void User::leerCopiaSeguridad()
{
    char c;
    FILE *f;
    f = fopen("UserBackup.txt", "r");
    if (f == NULL)
    {
        printf("El fichero está vacío o no se pudo abrir");
        std::exit(1);
    }
    while ((c = fgetc(f)) != EOF)
    {
        printf("%c", c);
    }
    printf("\n");
    fclose(f);
}