#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#include "Usuario/user.h"
#include "BBDD/funcionesBD.h"
#include "BBDD/sqlite3.h"
#include "Logger/logger.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define DATABASE 0
#define MAX_LINEAS 15

int main(void) {
	WSADATA wsaData;
	SOCKET conn_socket; 
	SOCKET comm_socket; 
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; 
	
    sqlite3 *db;
    conectarBD("bbdd.db", &db);  
    crearTablas(db);

	printf("\nINICIALIZANDO EL WINSOCK...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("INICIALIZADO CON EXITO.\n");

	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("NO SE HA PODIDO CREAR EL SOCKET : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("SOCKET CREADO CON EXITO.\n");
	
	server.sin_addr.s_addr = inet_addr(SERVER_IP); 
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	if (bind(conn_socket, (struct sockaddr*)&server,
		sizeof(server)) == SOCKET_ERROR) {
		printf("ERROR DE ENLACE CON CODIGO DE ERROR: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("ENLACE HECHO.\n"); 

	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Error de escucha con código de error: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("ESPERANDO LA CONEXION...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*)&client, &stsize);
	
	if (comm_socket == INVALID_SOCKET) {
		printf("ERROR DE ACEPTACION CON CODIGO : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("CONEXION PROCEDENTE DE: %s (%d)\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
	closesocket(conn_socket);
	
	iniciarLogger();
	loggear("Conexion realizada entre servidor y cliente\n");

	char dev;
	char name[MAX_LINEAS];
	char pass[MAX_LINEAS];

    while (dev != 3){
        recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		sscanf(recvBuff, "%c", &dev);
		if (dev == '1') {
			loggear("Registrar Usuario\n");
			printf("Registrar Usuario\n");
			sprintf(sendBuff, "%c", dev);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff, "%s", name);
			loggear("Nombre Usuario recibido: ");
			loggear(name);
			loggear("\n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff, "%s", pass);
			loggear("Contrasenya Usuario recibida: ");
			loggear(pass);
			loggear("\n");
            addUsuario(name, pass, 2, db);
			loggear("Usuario Registrado\n");
			printf("Usuario Registrado\n");
			continue;
		}
		else if (dev == '2') {
        	strcpy(name, "");
			strcpy(pass, "");
			loggear("Iniciar Sesion\n");
			printf("Inicio Sesion\n");
			sprintf(sendBuff, "%c", dev);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff, "%s", name);
			loggear("Nombre Usuario recibido: ");
			loggear(name);
			loggear("\n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff, "%s", pass);
			loggear("Contrasenya Usuario recibida: ");
			loggear(pass);
			loggear("\n");
            
    }

}