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
	leerPeliculaFichero(db);
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
			loggear("Contrasenya Usuario recibida ");
			loggear("\n");
            addUsuario(name, pass, 1, db);
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
			loggear("Contrasenya Usuario recibida ");
			loggear("\n");
			usuarioLogged = getUsuario(name, db);
			char c;

            if (strcmp(usuarioLogged.password, pass) == 0)//0=Admin 1=Cliente
			{ 
				//send tipo 
				if(usuarioLogged.tipo == 0)
				{
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
							sscanf(recvBuff, "%d", &numSalas);					
							loggear("Numero de Salas Cine recibido: ");
							char numSalasL[MAX_LINEAS];
							sprintf(numSalasL, "%i", numSalas);
							loggear(numSalasL);
							loggear("\n");

							addCine(numSalas,nombre,ubicacion,db);
							loggear("Cine añadido a la base de datos");
						}
						else if(c == '2'){
							loggear("Mostrando todos los cines de la base de datos...\n");
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
							free(cines);
							loggear("Esperando a recibir el cine a borrar... \n");
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							strcpy(cineBorrarNom, recvBuff);
							loggear("Nombre del cine a borrar: \n");
							loggear(cineBorrarNom);
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							strcpy(cineBorrarUbi, recvBuff);
							loggear("Ubicacion del cine a borrar: \n");
							loggear(cineBorrarUbi);
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
									loggear("Mostrando todas las sesiones de la base de datos...\n");
									int cont = getSesionesCount(db);
									int idSesion;
									Sesion sesionA;
									sprintf(sendBuff, "%i",cont);
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									Sesion* sesiones = getAllSesiones(db);
									for(int i = 0; i<cont; i++){
										sprintf(sendBuff, "%s",sesiones[i].horario);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
										sprintf(sendBuff, "%i",sesiones[i].id_Sesion);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									}
									free(sesiones);
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%d", &idSesion);
									loggear("idSesion de la sesion recibido");
									char idSesionL[MAX_LINEAS];
									sprintf(idSesionL, "%i", idSesion);
									loggear(idSesionL);
									sesionA = getSesionFromID(idSesion, db);
									imprimirSesion(sesionA);
									deleteSesion(sesionA, db);
								}
							}while(op != '3');
						}
					}while(c != '4');

				}
				else if(usuarioLogged.tipo == 1){
					sprintf(sendBuff, "%c",'1');
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					loggear("Iniciando Sesion como Cliente\n");
					printf("Iniciando Sesion como Cliente...\n");
					char o;
					do{
						o = ' ';
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
						sscanf(recvBuff, "%c", &o);
						if(o == '1'){
							char op = ' ';
							do{
								
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf(recvBuff, "%c", &op);
								
								if(op == '1'){
									loggear("Mostrando todas las peliculas de la base de datos... \n");
									int cont = 8;
									sprintf(sendBuff, "%i",cont);
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									Peli* pelis = getPeliculas(db);
									for(int i = 0; i<cont; i++){
										sprintf(sendBuff, "%s",pelis[i].titulo);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
										sprintf(sendBuff, "%s",pelis[i].genero);
										send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									}
									free(pelis);
								}else if(op == '2'){
									int cont = 8;
									char titulo[MAX_LINEAS];
									Peli* pelis = getPeliculas(db);
									Peli pelicula;
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%s", titulo);
									loggear("Titulo de la pelicula a buscar: \n");
									loggear(titulo);
									for(int i=0; i<cont; i++){
										if(strcmp(pelis[i].titulo, titulo) == 0){
											pelicula.id_Peli = pelis[i].id_Peli;
											strcpy(pelicula.titulo, pelis[i].titulo);
											pelicula.duracion=pelis[i].duracion;
											strcpy(pelicula.genero, pelis[i].genero);
											break;
										}
									}
									sprintf(sendBuff, "%i",pelicula.id_Peli);
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									sprintf(sendBuff, "%s",pelicula.titulo);
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									sprintf(sendBuff, "%i",pelicula.duracion);
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									sprintf(sendBuff, "%s",pelicula.genero);
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									free(pelis);
                                } 
							}while(op != '3');
						}else if(o == '2'){
							char op;
							do{
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf(recvBuff, "%s", &op);
								if(op == '1'){
									loggear("Mostrando todos los cines de la base de datos... \n");
									int cont = getCinesCount(db);
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
									free(cines);
								}else if(op == '2'){
									int CineCorrecto = 0;
									int PeliCorrecta = 0;
									int HoraCorrecta = 0;
									char cine[MAX_LINEAS];
									Cine cineSeleccionado;
									int cont = getCinesCount(db);
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%s", cine);
									loggear("Nombre del cine a añadir al ticket: \n");
									loggear(cine);
									Cine* cines = getCines(db);
									for(int i = 0; i<cont; i++)
									{
										if(strcmp(cines[i].nom_Cine, cine) == 0) {
											cineSeleccionado = cines[i];
											CineCorrecto = 1;
										}
									}



									char peli[MAX_LINEAS];
									Peli peliSeleccionada;
									int cont1 = getPelisCount(db);
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%s", peli);
									loggear("Nombre de la peli a añadir al ticket: \n");
									loggear(peli);
									Peli* pelis = getPeliculas(db);
									for(int i = 0; i<cont1; i++)
									{
										if(strcmp(pelis[i].titulo, peli) == 0) {
											peliSeleccionada = pelis[i];
											PeliCorrecta = 1;
										}
									}


									char sesion[MAX_LINEAS];
									Sesion sesionSeleccionada;
									int cont2 = getSesionesCount(db);
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%s", sesion);
									loggear("Horario de la sesion a añadir al ticket: \n");
									loggear(sesion);
									Sesion* sesiones = getAllSesiones(db);
									for(int i = 0; i<cont2; i++)
									{
										if(strcmp(sesiones[i].horario, sesion) == 0) {
											sesionSeleccionada = sesiones[i];
											HoraCorrecta = 1;
										}
									}
									int validador = 0;
									if(CineCorrecto == 1 && PeliCorrecta == 1 && HoraCorrecta == 1)
									{	
										imprimirTicket(usuarioLogged, cineSeleccionado, peliSeleccionada, sesionSeleccionada);
										loggear("Ticket imprimido con exito!\n");
										validador = 1;
										sprintf(sendBuff, "%i", validador);
                                		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									}
									else
									{
										loggear("Algun dato introducido no se encuentra en la base de datos, intentelo de nuevo");
										validador = 0;
										sprintf(sendBuff, "%i", validador);
                                		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									}
								}

							}while(op != '3');
						}
					}while(o != '3');
				}			
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
