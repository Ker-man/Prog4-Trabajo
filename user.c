#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirUser(User user)
{
    printf("ID: %i  Nombre: %s\n", user.id_User, user.nom_User);
}