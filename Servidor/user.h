#ifndef _USER_H_
#define _USER_H_

typedef struct 
{
    int id_User;
    char nom_User[30];
    char password[30];
    int tipo;
}User;

void imprimirUser(User user);
void escribirCopiaSeguridad(int id,char* nombre, char* contrasena, int admin);
void leerCopiaSeguridad();

#endif