#ifndef _UTILIDADES_H_
#define _UTILIDADES_H_
#include "../Empresa/sesion.h"

int opcion(const char* pregunta, int num_opciones, const char** opciones);
void mascara(char password[30]);
int solapar(Sesion sesion, Sesion* sesiones, int cont);  //horas*60+minutos + duracion < horas*60 +minutos
#endif