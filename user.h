#ifndef _USER_H_
#define _USER_H_

typedef struct 
{
    int id_User;
    char nom_User[30];
    char password[30];
    char tipo[10];
}User;

void imprimirUser(User user);

#endif