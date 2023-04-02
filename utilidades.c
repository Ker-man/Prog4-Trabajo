#include <stdio.h>
#include <conio.h>
#include "utilidades.h"

/*
int main(void) {
    const char *opciones[] = {"Si", "No", "Tal vez"};
    int o = opcion("Prueba?", 3, opciones);
    return 0;
}
*/

int opcion(const char *pregunta, int num_opciones, const char **opciones)
{
    printf("%s:\n", pregunta);
    for (int i = 0; i < num_opciones; i++)
    {
        printf(" %i. %s\n", i + 1, opciones[i]);
    }
    int eleccion = 0;
    do
    {
        printf("Opcion: (1 - %i): ", num_opciones);
        char linea[20];
        fgets(linea, 20, stdin);
        sscanf(linea, "%i", &eleccion);
    } while (eleccion < 1 || eleccion > num_opciones);
    return eleccion - 1;
    }

void mascara(char password[30])
{
    int i=0;
    char ch;
    while(ch=getch()){
        if (ch==13)
        {
            password[i]='\0';
            break;
        }else{
            printf("*");
            password[i]=ch;
            i++;
        }
    }
    //printf("clave: %s",password); DESCOMENTAR PARA COMPROBAR QUE EL METODO FUNCIONA
}