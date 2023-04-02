#ifndef _SALA_H_
#define _SALA_H_

typedef struct 
{
    int id_Sala;
    int capacidad;
}Sala;

typedef struct
{
    int tamanyo;
    Sala* salas;
}ListaSalas;


void imprimirSala(Sala sala);
void imprimirListaSalas(ListaSalas listaSalas);

#endif