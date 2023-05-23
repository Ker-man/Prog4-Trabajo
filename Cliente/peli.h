#ifndef _PELI_H_
#define _PELI_H_

class Peli
{
public:
    int id_Peli;
    char titulo[30];
    int duracion;
    char genero[30];

    void imprimirPelicula();
};

#endif