#ifndef _USER_H_
#define _USER_H_

class User
{
public:
    int id_User;
    char nom_User[30];
    char password[30];
    int tipo;

    void imprimirUser();
    void escribirCopiaSeguridad(int id, const char *nombre, const char *contrasena, int admin);
    void leerCopiaSeguridad();
};

#endif