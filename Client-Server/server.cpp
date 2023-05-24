#include <stdio.h>
#include <winsock2.h>
#include <string.h>

//#include "Usuario/usuario.h"
//#include "Barco/barco.h"
//#include "BBDD/bbdd.h"
//#include "BBDD/sqlite3.h"
//#include "Logger/logger.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define DATABASE 0

int main(void) {
	WSADATA wsaData;
	SOCKET conn_socket; 
	SOCKET comm_socket; 
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; 
	
	if (DATABASE == 1) {
		crearTablas();
	}

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

	while (dev != '3') {
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
			registrar(name, pass);
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
			if (iniSesion(name, pass) == 0) {
				sprintf(sendBuff, "%c",'0');
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				loggear("Inicio Sesion Exitoso\n");
				printf("Inicio Partida\n");
				Casilla cas[100];
				Barco bar[3];
				char tipoTablero[MAX_LINEAS];
				generarTablero(cas);
				generarBarcos(bar, tipoTablero);
				loggear("Inicio Partida\n");
				int intentos = 25;
				while (intentos > 0 || intentos <= 0) {
					intentos -= 1;
					int boo = 0;
					char letra;
					int num;
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					sscanf(recvBuff, "%c", &letra);
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					sscanf(recvBuff, "%i", &num);
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							if (bar[i].piezas[j].letra == letra && bar[i].piezas[j].num == num) {
								bar[i].piezas[j].estado = -1;
								boo = 1;
							}
						}
						if ((bar[i].piezas[0].estado + bar[i].piezas[1].estado + bar[i].piezas[2].estado) == -3) {
							bar[i].estado = 1;
						}
					}
					for (int i = 0; i < 100; i++) {
						if (cas[i].letra == letra && cas[i].num == num) {
							if (boo == 1) {
								cas[i].estado = -1;
							}
							else {
								cas[i].estado = 1;
							}
						}
					}
					int cont = 0;
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (cas[cont].estado == 0) {
								sprintf(sendBuff, "%s", "~");
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							}
							else if (cas[cont].estado < 0) {
								sprintf(sendBuff, "%s", "x");
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							}
							else {
								sprintf(sendBuff, "%s", "o");
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							}
							cont += 1;
						}
					}
					if (!(((bar[1].estado + bar[0].estado + bar[2].estado) != 3) && intentos > 0)) {
						sprintf(sendBuff, "%c", 'F');
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						break;
					}
					sprintf(sendBuff, "%c", 'P');
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}
				printf("Fin de Partida\n");
				loggear("Fin Partida\nPartida Cargada\n");
				insertPart(tipoTablero, name);
				continue;
			} else {
				sprintf(sendBuff, "%c", '1');
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				loggear("Inicio Sesion Fallido\n");
				continue;
			}
		}
	}
	loggear("Programa Finalizado\n\n");
	printf("Programa Finalizado\n");
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}