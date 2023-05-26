#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#include "../Usuario/user.h"
#include "../BBDD/funcionesBD.h"
#include "../BBDD/sqlite3.h"
#include "../Logger/logger.h"
#include "../Client-Server/utilidades.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9000
#define DATABASE 0
#define MAX_LINEAS 15

int main(void) 
{
	WSADATA wsaData;
	SOCKET conn_socket; 
	SOCKET comm_socket; 
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; 
	
    sqlite3 *db;
    conectarBD("bbdd.db", &db);  
    crearTablas(db);
	User usuarioLogged;

	printf("\nINICIALIZANDO EL WINSOCK...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("INICIALIZADO CON EXITO.\n");

	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
	{
		printf("NO SE HA PODIDO CREAR EL SOCKET : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("SOCKET CREADO CON EXITO.\n");
	
	server.sin_addr.s_addr = inet_addr(SERVER_IP); 
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	if (bind(conn_socket, (struct sockaddr*)&server,
		sizeof(server)) == SOCKET_ERROR) 
	{
		printf("ERROR DE ENLACE CON CODIGO DE ERROR: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("ENLACE HECHO.\n"); 

	if (listen(conn_socket, 1) == SOCKET_ERROR) 
	{
		printf("Error de escucha con código de error: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("ESPERANDO LA CONEXION...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*)&client, &stsize);
	
	if (comm_socket == INVALID_SOCKET) 
	{
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

    while (dev != '3')
	{
        recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		sscanf(recvBuff, "%c", &dev);
		if (dev == '1') 
		{
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
            addUsuario(name, pass, 0, db);
			loggear("Usuario Registrado\n");
			printf("Usuario Registrado\n");
			
			continue;
		}
		else if (dev == '2') 
		{
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
			usuarioLogged = getUsuario(name, db);
			printf("Aaaa");
			char c;

            if (strcmp(usuarioLogged.password, pass) == 0)//0=Admin 1=Cliente
			{ 
				printf("bbb");
				//send tipo 
				if(usuarioLogged.tipo == 0)
				{
					printf("ccc");
					sprintf(sendBuff, "%c",'0');
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					loggear("Iniciando Sesion como Administrador\n");
					printf("Iniciando Sesion como Administrador...\n");
					do
					{
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
						sscanf(recvBuff, "%c", &c);
						if (c == '1')
						{
							char nombre[MAX_LINEAS];
							char ubicacion[MAX_LINEAS];
							int numSalas;
							loggear("Esperando la introducción de parametros de cine...");
							
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							sscanf(recvBuff, "%s", nombre);
							loggear("Nombre Cine recibido: ");
							loggear(nombre);
							loggear("\n");

							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							sscanf(recvBuff, "%s", ubicacion);
							loggear("Ubicacion Cine recibido: ");
							loggear(ubicacion);
							loggear("\n");

							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							//printf(recvBuff);
							sscanf(recvBuff, "%d", &numSalas);					
							loggear("Numero de Salas Cine recibido: ");
							char numSalasL[MAX_LINEAS];
							//printf("%i", numSalas);
							sprintf(numSalasL, "%i", numSalas);
							loggear(numSalasL);
							loggear("\n");

							addCine(numSalas,nombre,ubicacion,db);
							loggear("Cine añadido a la base de datos");
						}
						else if(c == '2'){
							int cont = getCinesCount(db);
							char cineBorrarNom[MAX_LINEAS];
							char cineBorrarUbi[MAX_LINEAS];
							Cine cineA;
							sprintf(sendBuff, "%i",cont);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							Cine* cines = getCines(db);
							for(int i = 0; i<cont; i++){
								sprintf(sendBuff, "%s",cines[i].nom_Cine);
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);
								sprintf(sendBuff, "%s",cines[i].ubi_Cine);
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							}
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							strcpy(cineBorrarNom, recvBuff);
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							strcpy(cineBorrarUbi, recvBuff);
							cineA = getCine(cineBorrarNom, cineBorrarUbi, db);
							deleteCine(cineA, db);
						}
						else if(c == '3'){
							char op = ' '; 
							do{
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf(recvBuff, "%c", &op);
								if(op == '1'){
									char horario[MAX_LINEAS];
									int precio;
									int idSala;
									int idPeli;

									loggear("Esperando la introducción de parametros de sesion...");
							
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%s", horario);
									loggear("Horario Sesion recibido: ");
									loggear(horario);
									loggear("\n");


									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%d", &precio);					
									loggear("Precio de Sesion recibido: ");
									char precioL[MAX_LINEAS];
									sprintf(precioL, "%i", precio);
									loggear(precioL);
									loggear("\n");

									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%d", &idSala);					
									loggear("idSala de Sesion recibido: ");
									char idSalaL[MAX_LINEAS];
									sprintf(idSalaL, "%i", idSala);
									loggear(idSalaL);
									loggear("\n");

									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%d", &idPeli);					
									loggear("idPeli de Sesion recibido: ");
									char idPeliL[MAX_LINEAS];
									sprintf(idPeliL, "%i", idPeli);
									loggear(idPeliL);
									loggear("\n");

									addSesion(horario, idPeli, idSala, precio, db);
									
								}
								else if(op == '2'){
									int cont = getSesionesCount(db);
									int idSesion;
									Sesion sesionA;
									sprintf(sendBuff, "%i",cont);
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									Sesion* sesiones = getAllSesiones(db);
									for(int i = 0; i<cont; i++){
										sprintf(sendBuff, "%s",sesiones[i].horario);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
										sprintf(sendBuff, "%s",sesiones[i].id_Sesion);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									}
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%i", &idSesion);
									sesionA = getSesionFromID(idSesion, db);
									deleteSesion(sesionA, db);
								}
							}while(op == '3');
						}
					}while(c != '4');

				}
				else if(usuarioLogged.tipo == 1){
					printf("ddd");
					sprintf(sendBuff, "%c",'1');
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					loggear("Iniciando Sesion como Cliente\n");
					printf("Iniciando Sesion como Cliente...\n");
					continue;
				}
				printf("eee");
    		} 
			else 
			{
				sprintf(sendBuff, "%c", '2');
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

        //Menu admin  (Cambiar cosas) 
            //Menu Cines x
                //Crear Cine x
                //Borrar cine x
                //Gestionar Cine
                    //-Crear Sala
                    //-Borrar Sala
                    //-Salir
                //Menu Sesiones x
                    //-Crar Sesion para un sala
                    //-Borrar una sesion de una sala
					//-Salir
                //-Salir x
        
        //Menu Usuario
            //Menu Peliculas
				//-Ver todas las pelis
				//-Buscar por Nombre
				//BUscar por genero
			//Menu Cine
				//-Ver cines
				//Comprar ticket
			//-Salir

		
		//Menu Admin
				//Menu cine
					//-Crear Sala
					//-Borrar Sala
					//Elige un cine (Menu Sesiones)
						//-Crear sesion para una sala
						//-Crear sesion para todas las salas
						//-Borrar sesion para una sala
						//-Salir
					//-Salir
				//Menu Peliculas
					//Crear pelicula
					//Borrar Pelicula
				//-Salir


			//Menu Usuario
				//Ver peliculas(Menu peliculas)
					//-Ver todas
					//-Buscar por Nombre
					//-Buscar por Genero
				//Elegir Cine (Ver todos los cines)
					//-Ver sesiones
					//-Comprar ticket