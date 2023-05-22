#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "funciones.h" 
//#include "pais.h"
//#include "atleta.h"
#include <winsock2.h>
#define CONTRASENA "admin"
#define BORRAR 8
#define ENTER 13
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

//g++ client.cpp funciones.cpp pais.c atleta.c competicion.c desconversor.c modalidad.c ranking.c -o testCliente.exe -lws2_32

using namespace std;


int main(void) {

    WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[1024];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	// SEND and RECEIVE data

	FILE* ficherolog;
    ficherolog = fopen("logger.txt", "w");
    fprintf(ficherolog, "Empezamos\n");
    fclose(ficherolog);
    ficherolog = fopen("logger.txt", "a");
    fprintf(ficherolog, "Comienzo de Programa:\n\n");
    fclose(ficherolog);
    char opcion;
    char opcionIntro;


        ficherolog = fopen("logger.txt", "a");
        fclose(ficherolog);
                system("cls");
                    menuPrincipal(s, sendBuff, recvBuff);
                    ficherolog = fopen("logger.txt", "a");
                    fprintf(ficherolog, "Menu principal mostrado y selecciona opcion %c\n", opcion);
                    fclose(ficherolog);
	

	// CLOSING the socket and cleaning Winsock...
	send(s, "00", 512, 0);
	closesocket(s);
	WSACleanup();

    return 0;
}