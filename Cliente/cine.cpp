#include "cine.h"
#include <iostream>
#include <string>

void Cine::imprimirCine()
{
    std::cout << "Cine:" << std::endl;
    std::cout << "ID: " << id_Cine << "  Nombre: " << nom_Cine << "  Ubicacion: " << ubi_Cine << std::endl;
    std::cout << "Salas:" << std::endl;
}