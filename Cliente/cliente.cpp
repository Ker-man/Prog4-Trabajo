#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "../Client-Server/utilidades.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_LINEAS 15

using namespace std;

int main(void) 
{
    WSADATA wsaData;
    SOCKET s;
    struct sockaddr_in server;

    char sendBuff[512], recvBuff[512];
    cout << "----- CREACION DEL SOCKET ------" << endl;
    printf("\nINICIALIZANDO EL WINSOCK...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return -1;
    }
    cout << "\nINICIALIZADO CON EXITO." << endl;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
    {
        printf("\nNO SE HA PODIDO CREAR EL SOCKET : %d", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    printf("\nSOCKET CREADO CON EXITO.\n");

    server.sin_addr.s_addr = inet_addr(SERVER_IP); 
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if (connect(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) 
    {
        printf("\nERROR DE CONEXION: %d", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return -1;
    }

    printf("\n\nCONEXION ESTABLECIDA CON: %s (%d)\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

    char str[10];
    char c;
    do
    {
        printf("\n\n");
        printf("=======================\n");
        printf("MENU INICIO DEUSTOCINES\n");
        printf("=======================\n");
        printf("\n");
        c = ' ';
        printf("1. Registrar Usuario, 2. Iniciar Sesion, 3. Salir\n");
        cin >> c;

        if (c != '\n' && (c == '1' || c == '2' )) 
        {
            char dev;

            sprintf(sendBuff, "%c", c);
            send(s, sendBuff, sizeof(sendBuff), 0);

            strcpy(recvBuff, "");
            recv(s, recvBuff, sizeof(recvBuff), 0);
            sscanf(recvBuff, "%c", &dev);
            if(dev == '1')
            {
                char name[MAX_LINEAS];
                char pass[MAX_LINEAS];
                cout << "Nombre Usuario:\n";
                cin >> name;
                cout << "Contrasena Usuario:\n ";
                cin >> pass;
                cout << endl;
                sprintf(sendBuff, "%s", name);
                send(s, sendBuff, sizeof(sendBuff), 0);
                sprintf(sendBuff, "%s", pass);
                send(s, sendBuff, sizeof(sendBuff), 0);
                continue;
            } 
            else if(dev == '2')
            {
                char name[MAX_LINEAS];
                char pass[MAX_LINEAS];
                cout << "Nombre Usuario:\n";
                cin >> name;
                cout << "Contrasena Usuario:\n ";
                cin >> pass;
                cout << endl;
                sprintf(sendBuff, "%s", name);
                send(s, sendBuff, sizeof(sendBuff), 0);
                sprintf(sendBuff, "%s", pass);
                send(s, sendBuff, sizeof(sendBuff), 0);

                recv(s, recvBuff, sizeof(recvBuff), 0);
                sscanf(recvBuff, "%c", &dev);

                if (dev == '0') //Menu admin
                {
                    char opcion;
                    do
                    {   
                        printf("\n\n\n");
                        printf("==============================\n");
                        printf("MENU ADMINISTRADOR DEUSTOCINES\n");
                        printf("==============================\n");
                        printf("\n");
                        opcion = ' ';
                        printf("1. Anadir Cine 2. Borrar Cine 3.Gestionar Sesiones 4.Salir\n");
                        cin >> opcion;
                        cout << endl;
                        sprintf(sendBuff, "%c", opcion);
                        send(s, sendBuff, sizeof(sendBuff), 0);

                        if(opcion == '1')
                        {
                            printf("Nombre: ");
                            char nombre[MAX_LINEAS];
                            cin >>nombre;
                            cout <<endl;

                            printf("Ubicacion: ");
                            char ubicacion[MAX_LINEAS];
                            cin >>ubicacion;
                            cout <<endl;

                            printf("Numero de salas: ");
                            char numSalas[MAX_LINEAS];
                            cin >>numSalas;
                            printf("%s", numSalas);
                            cout <<endl;

                            sprintf(sendBuff, "%s", nombre);
                            send(s, sendBuff, sizeof(sendBuff), 0);
                            sprintf(sendBuff, "%s", ubicacion);
                            send(s, sendBuff, sizeof(sendBuff), 0);
                            sprintf(sendBuff, "%s", numSalas);                          
                            send(s, sendBuff, sizeof(sendBuff), 0);
                            continue;

                        }
                        else if(opcion == '2')
                        {
                            int n;
                            char cine[MAX_LINEAS];
                            char ubi[MAX_LINEAS];
                            recv(s, recvBuff, sizeof(recvBuff), 0);
                            sscanf(recvBuff, "%i", &n); 
                            printf("Cines en la base de Datos\n");
                            for(int i = 0; i<n; i++){
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                strcpy(cine, recvBuff);
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                strcpy(ubi, recvBuff);
                                printf("Cine: %s - %s\n", cine, ubi);
                            }
                            printf("Cual quieres borrar, escribe el nombre y ubicacion separados por un espacio (NOMBRE UBICACION):\n");
                            cin >> cine;
                            cout <<endl;
                            cin >> ubi;
                            cout <<endl;
                            sprintf(sendBuff, "%s", cine);
                            send(s, sendBuff, sizeof(sendBuff), 0);
                            sprintf(sendBuff, "%s", ubi);
                            send(s, sendBuff, sizeof(sendBuff), 0);

                        }
                        else if(opcion == '3')
                        {
                            char eleccion;
                            do{
                                printf("\n\n\n");
                                printf("==========================================\n");
                                printf("MENU ADMINISTRADOR DE SESIONES DEUSTOCINES\n");
                                printf("==========================================\n");
                                printf("\n");
                                eleccion = ' ';
                                printf("1. Anadir Sesion 2. Borrar Sesion 3.Salir\n");
                                cin >> eleccion;
                                cout << endl;
                                sprintf(sendBuff, "%c", eleccion);
                                send(s, sendBuff, sizeof(sendBuff), 0);
                                if(eleccion == '1'){
                                    printf("Horario: ");
                                    char horario[MAX_LINEAS];
                                    cin >> horario;
                                    cout << endl;

                                    printf("Precio: ");
                                    int precio;
                                    cin >> precio;
                                    cout << endl;

                                    printf("ID de la sala: ");
                                    int idSala;
                                    cin >> idSala;
                                    cout << endl;

                                    printf("ID de la Peli: ");
                                    int idPeli;
                                    cin >> idPeli;
                                    cout << endl;

                                    sprintf(sendBuff, "%s", horario);
                                    send(s, sendBuff, sizeof(sendBuff), 0);
                                    sprintf(sendBuff, "%i", precio);
                                    send(s, sendBuff, sizeof(sendBuff), 0);
                                    sprintf(sendBuff, "%i",idSala);
                                    send(s, sendBuff, sizeof(sendBuff), 0);
                                    sprintf(sendBuff, "%i", idPeli);
                                    send(s, sendBuff, sizeof(sendBuff), 0);
                                    continue;
                                }
                                else if(eleccion == '2'){
                                    int n;
                                    char horario[MAX_LINEAS];
                                    int idSesion;
                                    recv(s, recvBuff, sizeof(recvBuff), 0);
                                    sscanf(recvBuff, "%i", &n); 
                                    printf("Sesiones en la base de Datos\n");
                                    for(int i = 0; i<n; i++){
                                        recv(s, recvBuff, sizeof(recvBuff), 0);
                                        sscanf(recvBuff, "%s", horario);
                                        recv(s, recvBuff, sizeof(recvBuff), 0);
                                        sscanf(recvBuff, "%i", &idSesion);
                                        printf("Sesion: %i - %s\n", idSesion, horario);
                                    }
                                    printf("Cual quieres borrar, escribe el ID:\n");
                                    char idSesionD[MAX_LINEAS];
                                    cin >>idSesionD;
                                    cout <<endl;

                                    printf("\n\n%s",idSesionD);
                                    sprintf(sendBuff, "%s", idSesionD);
                                    send(s, sendBuff, sizeof(sendBuff), 0);
                                    
                                }
                            }while(eleccion != '3');
                        }
                    }
                    while(opcion != '4');


                } 
                else if(dev == '1')//Menu Cliente
                { 
                    char opcion;
                    do{
                        printf("\n\n\n");
                        printf("========================\n");
                        printf("MENU USUARIO DEUSTOCINES\n");
                        printf("========================\n");
                        printf("\n");
                        opcion = ' ';
                        printf("1. Menu Peliculas 2. Menu Cines 3. salir\n");
                        cin >> opcion;
                        cout << endl;
                        sprintf(sendBuff, "%c", opcion);
                        send(s, sendBuff, sizeof(sendBuff), 0);
                        if(opcion=='1')
                    {
                        char op;
                        do{
                            op = ' ';
                            printf("\nEntrando en menu Peliculas\n");
                            printf("1. Ver todas las peliculas 2. Buscar pelicula por nombre 3. Salir\n");
                            cin >> op;
                            cout << endl;
                            sprintf(sendBuff, "%c", op);
                            send(s, sendBuff, sizeof(sendBuff), 0);
                            if(op == '1'){
                                int n = 0;
                                int n2;
                                char nombre[MAX_LINEAS];
                                char genero[MAX_LINEAS];
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%i", &n);
                                n2 = n;
                                printf("Pelis en la base de Datos\n");
                                for(int i = 0; i<n2; i++){
                                    
                                    recv(s, recvBuff, sizeof(recvBuff), 0);
                                    strcpy(nombre, recvBuff);
                                    recv(s, recvBuff, sizeof(recvBuff), 0);
                                    strcpy(genero, recvBuff);
                                    printf("Pelicula: %s - %s\n", nombre, genero);

                                    
                                }
                                continue;
                                
                            }else if(op == '2'){
                                char titulo[MAX_LINEAS];
                                int idPeli;
                                int duracion;
                                char genero[MAX_LINEAS];
                                printf("Peli a buscar (Titulo):\n");
                                cin >> titulo;
                                cout << endl;
                                sprintf(sendBuff, "%s", titulo);
                                send(s, sendBuff, sizeof(sendBuff), 0);

                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%i", &idPeli);
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", titulo);
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%i", &duracion);
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%s", genero);
                                printf("La pelicula que buscas es: ID: %i, Titulo: %s, Duracion: %i, Genero: %s\n", idPeli, titulo, duracion, genero);                                
                                
                           }
                        }while(op != '3');
                    }
                    else if(opcion=='2')
                    {
                        char op;
                        do{
                            printf("Entrando en menu Cines\n");
                            printf("1. Ver cines 2. Comprar ticket 3. Salir\n");
                            cin >> op;
                            cout << endl;
                            sprintf(sendBuff, "%c", op);
                            send(s, sendBuff, sizeof(sendBuff), 0);
                            if(op == '1'){
                                //Cine cine;
                                int n;
                                char cine[MAX_LINEAS];
                                char ubi[MAX_LINEAS];
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%i", &n); 
                                printf("Cines en la base de Datos\n");
                                for(int i = 0; i<n; i++){
                                    recv(s, recvBuff, sizeof(recvBuff), 0);
                                    strcpy(cine, recvBuff);
                                    recv(s, recvBuff, sizeof(recvBuff), 0);
                                    strcpy(ubi, recvBuff);
                                    printf("Cine: %s - %s\n", cine, ubi);
                                }
                            }else if(op == '2'){
                                printf("\n\t\t\t -----------------------------------");
                                printf("\n\t\t\t ------- Sistema de Reservas -------");
                                printf("\n\t\t\t -----------------------------------");

                                char cine[MAX_LINEAS];
                                printf("\n\t\t\t\tIntroduce el nombre del cine: ");
                                cin >> cine;
                                cout << endl;
                                sprintf(sendBuff, "%s", cine);
                                send(s, sendBuff, sizeof(sendBuff), 0);
                               
                                char peli[MAX_LINEAS];
                                printf("\n\t\t\t\tIntroduce el nombre de la peli: ");
                                cin >> peli;
                                cout << endl;
                                sprintf(sendBuff, "%s", peli);
                                send(s, sendBuff, sizeof(sendBuff), 0);

                                char sesion[MAX_LINEAS];
                                printf("\n\t\t\t\tIntroduce la hora de la sesion (ej. 16:00): ");
                                cin >> sesion;
                                cout << endl;
                                sprintf(sendBuff, "%s", sesion);
                                send(s, sendBuff, sizeof(sendBuff), 0);

                                int validador;
                                recv(s, recvBuff, sizeof(recvBuff), 0);
                                sscanf(recvBuff, "%i", &validador); 

                                if(validador == 1)
                                {
                                    printf("Ticket creado con exito\n");
                                }
                                else
                                {
                                    printf("Algun dato introducido no era correcto, intentelo de nuevo\n");
                                }
                                
                                
                            }
                        }while(op != '3');
                    }
                    }while(opcion != '3');
                }
                else if(dev == '2')
                {
                    printf("Usuario o contrasenya incorrecta.");
                }
            printf("¡Hasta pronto!:\n");
            
            }
            else
            {
                printf("Else");
            }
        }
        
    
   }
   while(c != '3');
    sprintf(sendBuff, "%c", '3');
    send(s, sendBuff, sizeof(sendBuff), 0);
    printf("\n");
    printf("Hasta Pronto");
    printf("\n");
    closesocket(s);
    WSACleanup();

    return 0;

}