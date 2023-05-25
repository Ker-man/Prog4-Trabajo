#include <stdio.h>
#include <conio.h>
#include "utilidades.h"
#include "../Empresa/sesion.h"

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
    printf("Introduzca la contrasena: ");
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
    //printf("\nclave: %s",password);
}
int solapar(Sesion sesion, Sesion* sesiones, int cont){
    int posible = 0;

    char* horaini = sesion.horario[0] + sesion.horario[1];
    char* minini = sesion.horario[3] + sesion.horario[4];
    int finalTimeH;
    int finalTimeM;
    sscanf(horaini, "%d", &finalTimeH);
    sscanf(minini, "%d", &finalTimeM);

    do{
        for (int i = 0; i<cont; i++){
            char* horaini = sesiones[i].horario[0] + sesiones[i].horario[1];
            char* minini = sesiones[i].horario[3] + sesiones[i].horario[4];
            int h;
            int m;
            sscanf(horaini, "%d", &h);
            sscanf(minini, "%d", &m);
            
            if (h < finalTimeH){
                posible = 1;     
            }else{
                if (h == finalTimeH && m <= finalTimeM){
                    posible = 1; 
                }else{
                    m = m + sesion.peli.duracion;
                    finalTimeH = h + (m/60);
                    finalTimeM = m%60;   
                }
            }
        }
        return posible; //If posible == 0 la sesion no solapa
    }while (posible != 1); 
    
    return posible;//If posible == 1 la sesion solapa
}