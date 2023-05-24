#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_LINEAS 15

using namespace std;

int main(void) {
    WSADATA wsaData;
    SOCKET s;
    struct sockaddr_in server;

    char sendBuff[512], recvBuff[512];
    cout << "----- CREACION DEL SOCKET ------" << endl;
    printf("\nINICIALIZANDO EL WINSOCK...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return -1;
    }
    cout << "\nINICIALIZADO CON EXITO." << endl;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("\nNO SE HA PODIDO CREAR EL SOCKET : %d", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    printf("\nSOCKET CREADO CON EXITO.\n");

    server.sin_addr.s_addr = inet_addr(SERVER_IP); 
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if (connect(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("\nERROR DE CONEXION: %d", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return -1;
    }

    printf("\n\nCONEXION ESTABLECIDA CON: %s (%d)\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

    char str[10];
    char c;

    do{
        printf("\n\n==========================\n");
        printf("MENU PRINCIPAL DEUSTOCINES\n");
        printf("==========================\n");
        printf("\n");
        c = ' ';
        printf("1. Registrar Usuario", "2. Iniciar Sesion", "3. Salir");
        cin >> c;
        if (c != '\n' && (c == '1' || c == '2' || c == '3')) {
            char dev;

            sprintf(sendBuff, "%c", c);
            send(s, sendBuff, sizeof(sendBuff), 0);

            strcpy(recvBuff, "");
            recv(s, recvBuff, sizeof(recvBuff), 0);
            sscanf(recvBuff, "%c", &dev);
            if(dev == 1){
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
            } else if(dev == 2){
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

                
            }
        }
    }while(c != '3');

    closesocket(s);
    WSACleanup();

    return 0;

}