

#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "funcionesBD.h"
#include "atleta.h"
#include "pais.h"
#include "modalidad.h"
#include "competicion.h"
#include "lugar.h"
#include "server.h"
#include "ranking.h"

//gcc funciones.c pais.c lugar.c modalidad.c funcionesBD.c competicion.c sqlite3.c atleta.c ranking.c server.c  -o testServer.exe -lws2_32
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define TAMAINO_SENDBUFF 1024
#define TAMAINO_RECVBUFF 512
#define BYTES 2
int main(int argc, char *argv[]) {
	FILE* ficherolog;
    ficherolog = fopen("loggerserver.txt", "w");
    

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[TAMAINO_SENDBUFF], recvBuff[TAMAINO_RECVBUFF];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");
	fprintf(ficherolog, "Server iniciado\n");
	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	fprintf(ficherolog, "Server inicializado\n");
	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");
	fprintf(ficherolog, "Conexion realizada\n");
	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	// BASE DE DATOS
	sqlite3 *db;
    int result = sqlite3_open("Basededatos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
	fprintf(ficherolog, "Base de datos cargada\n");
	//SEND and RECEIVE data
	printf("Waiting for incoming petition from Deustopic Client... \n");
	do {
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
        if(bytes > 0){
            printf("Code received: %s \n", recvBuff);
            if (strncmp(recvBuff, "00",BYTES) == 0) { // Close Server
				fprintf(ficherolog, "Servidor cerrado\n");
				break;

			} else if (strncmp(recvBuff, "01",BYTES) == 0){ //Envia una lista con los ATLETAS
                ListaPersona lper;
                result = cargarAtletas(db, &lper);
                stringLper(lper,sendBuff);
				fprintf(ficherolog, "Enviado: %s \n", sendBuff);
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
            } else if (strncmp(recvBuff, "02",2) == 0){ //Envia una lista con los PAISES
				ListaPais lpais;
				result = cargarPaises(db, &lpais);
				stringlpais(lpais, sendBuff);
				fprintf(ficherolog, "Enviado: %s \n", sendBuff);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			} else if(strncmp(recvBuff, "03",BYTES) == 0){ //Envia una lista con las COMPETICIONES
				ListaCompeticion lcomp;
				result = cargarCompeticiones(db, &lcomp);
				stringcompeticion(lcomp, sendBuff);
				fprintf(ficherolog, "Enviado: %s \n", sendBuff);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			} else if(strncmp(recvBuff, "04",BYTES) == 0){ //Envia una lista con las LUGAR
				ListaLugar llug;
				result = cargarLugares(db, &llug);
				stringlugar(llug,sendBuff);
				fprintf(ficherolog, "Enviado: %s \n", sendBuff);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			} else if(strncmp(recvBuff, "05",BYTES) == 0){ //Envia una lista con las MODALIDADES
				ListaModalidades lmod; 
				result = cargarModalidades(db, &lmod);
				stringlmodalidad(lmod, sendBuff);
				fprintf(ficherolog, "Enviado: %s \n", sendBuff);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			} else if(strncmp(recvBuff, "06",BYTES) == 0){ //Recive un CD_PAIS y envia las competiciones que 
				fprintf(ficherolog, "Recivido: %s \n", recvBuff);
				int cdPais = 0;
				char* lastchar = &recvBuff[0];
				char frase[TAMAINO_RECVBUFF];
				while(lastchar[0] != '$'){
					lastchar++;
				}
				lastchar++;
				int i = 0;
				while(lastchar[0] != '$'){
					frase[i] = lastchar[0];
					lastchar++;
					i++;
				}
				frase[i+1] = '\0';
				cdPais = atoi(frase);
				ListaCompeticion lcomp;
				cargarCompeticionesPorPais(db, &lcomp, cdPais);
				stringcompeticion(lcomp, sendBuff);
				printf(sendBuff);
				fprintf(ficherolog, "Enviado: %s \n", sendBuff);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			//Envia al servidor un CD_MOD y CD_COMP
            //CD$CD_MOD$CD_COMP$
			}else if(strncmp(recvBuff, "07",BYTES) == 0){//Recibe CD_MOD y CD_COMP y devuelve un Ranking
				char* lastchar = &recvBuff[0];
				char frase[TAMAINO_RECVBUFF];
				fprintf(ficherolog, "Recivido: %s \n", recvBuff);
				while(lastchar[0] != '$'){
					lastchar++;
				}
				lastchar++;
				int i = 0;
				while(lastchar[0] != '$'){
					frase[i] = lastchar[0];
					lastchar++;
					i++;
				}
				frase[i+1] = '\0';
				int cdmod = 0;
				cdmod = atoi(frase);
				i = 0;
				lastchar++;
				strcpy(frase, "");
				while(lastchar[0] != '$'){
					frase[i] = lastchar[0];
					lastchar++;
					i++;
				}
				frase[i+1] = '\0';
				int cdcomp = atoi(frase);
				Ranking rank;
				cargarRanking(db, &rank, cdmod, cdcomp);
				stringRanking(rank, sendBuff);
				fprintf(ficherolog, "Enviado: %s \n", sendBuff);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
				
			

        }
    }while (1);
	fclose(ficherolog);
}











/* Pasa un string con el contenido de una ListaPersona a un string
El orden y forma es este(usa $ como separador):

$numeroElementos&dni[0]$nombre[0]$telefono[1]$pais[0]$cdPais[0]&dni[1]$...$cdPais[numeroElementos -1]$
*/

void stringLper(ListaPersona lper, char* stringfinal) { 
    strcpy(stringfinal, "");
	strcat(stringfinal, "$");
    char casteo[15];
    strcpy(casteo,"");
    sprintf(casteo, "%d", lper.numero); // integer to string
    strcat(stringfinal, casteo);
    strcat(stringfinal, "$");
    for(int i = 0; i < lper.numero; i++){
        strcat(stringfinal, lper.persona[i].dni);
        strcat(stringfinal, "$");
        strcat(stringfinal, lper.persona[i].nombre);
        strcat(stringfinal, "$");
        strcpy(casteo,"");
        sprintf(casteo, "%d", lper.persona[i].telefono); // integer to string
        strcat(stringfinal, casteo);
        strcat(stringfinal, "$");
        strcat(stringfinal, lper.persona[i].pais);
        strcat(stringfinal, "$");
        strcpy(casteo,"");
        sprintf(casteo, "%d", lper.persona[i].cdPais); // integer to string
        strcat(stringfinal, casteo);
        strcat(stringfinal, "$");
    }
}

void stringlmodalidad(ListaModalidades lmodalidad, char* stringfinal){
	strcpy(stringfinal, "");
	strcat(stringfinal, "$");
    char casteo[15];
    strcpy(casteo,"");
    sprintf(casteo, "%d", lmodalidad.tamanyo); // integer to string
    strcat(stringfinal, casteo);
	strcat(stringfinal, "$");
	for(int i = 0; i < lmodalidad.tamanyo; i++){
		strcpy(casteo,"");
        sprintf(casteo, "%d", lmodalidad.modalidades[i].cd_mod); // integer to string
        strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		strcat(stringfinal, lmodalidad.modalidades[i].descripcion);
		strcat(stringfinal, "$");
		strcat(stringfinal, lmodalidad.modalidades[i].nom_modalidad);
		strcat(stringfinal, "$");
	}
}

void stringlugar(ListaLugar listalugar, char* stringfinal){
	strcpy(stringfinal, "");
	strcat(stringfinal, "$");
    char casteo[15];
    strcpy(casteo,"");
    sprintf(casteo, "%d", listalugar.tamanyo); // integer to string
    strcat(stringfinal, casteo);
	strcat(stringfinal, "$");
	for(int i = 0; i < listalugar.tamanyo; i++){
		strcpy(casteo,"");
        sprintf(casteo, "%d", listalugar.lugar[i].Cd_Lugar); // integer to string
        strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		strcat(stringfinal, listalugar.lugar[i].NOM_LUGAR);
		strcat(stringfinal, "$");
		strcat(stringfinal, listalugar.lugar[i].LOC_LUGAR);
		strcat(stringfinal, "$");
		sprintf(casteo, "%d", listalugar.lugar[i].Cd_Pais); // integer to string
		strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		printf(stringfinal, listalugar.lugar[i].pais);
		strcat(stringfinal, "$");

	}
}

void stringRanking(Ranking rank, char* stringfinal){
	strcpy(stringfinal, "");
	strcat(stringfinal, "$");
    char casteo[15];
    strcpy(casteo,"");
	sprintf(casteo, "%d", rank.tamanyo); // integer to string
	strcat(stringfinal, casteo);
	strcat(stringfinal, "$");
	for (int i = 0; i < rank.tamanyo; i++)
	{
		strcpy(casteo,"");
		strcat(stringfinal, rank.compite[i].dniPer);
		strcat(stringfinal, "$");
		strcat(stringfinal, rank.compite[i].nomPer);
		strcat(stringfinal, "$");
		strcat(stringfinal, rank.compite[i].nomCompeticion);
		strcat(stringfinal, "$");
		strcat(stringfinal, rank.compite[i].nomModalidad);
		strcat(stringfinal, "$");
		sprintf(casteo, "%d", rank.compite[i].codModalidad);
		strcat(stringfinal, casteo);
		strcpy(casteo, "");
		strcat(stringfinal, "$");
		sprintf(casteo, "%d", rank.compite[i].codCompeticion);
		strcat(stringfinal, casteo);
		strcpy(casteo, "");
		strcat(stringfinal, "$");
		sprintf(casteo, "%f", rank.compite[i].lanzamiento);
		strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
	}
	
}

void stringcompeticion(ListaCompeticion lcompeticion, char* stringfinal){
	strcpy(stringfinal, "");
	strcat(stringfinal, "$");
    char casteo[15];
    strcpy(casteo,"");
    sprintf(casteo, "%d", lcompeticion.tamanyo); // integer to string
    strcat(stringfinal, casteo);
	strcat(stringfinal, "$");
	for(int i = 0; i < lcompeticion.tamanyo; i++){
		strcpy(casteo,"");
        sprintf(casteo, "%d", lcompeticion.competicion[i].CdCompeticion); // integer to string
        strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		sprintf(casteo, "%d", lcompeticion.competicion[i].CdLugar); // integer to string
		strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		strcat(stringfinal, lcompeticion.competicion[i].lugar);
		strcat(stringfinal, "$");
		strcat(stringfinal, lcompeticion.competicion[i].organizador);
		strcat(stringfinal, "$");
		strcat(stringfinal, lcompeticion.competicion[i].nomCompeticion);
		strcat(stringfinal, "$");
		sprintf(casteo, "%d", lcompeticion.competicion[i].dia); // integer to string
		strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		sprintf(casteo, "%d", lcompeticion.competicion[i].mes); // integer to string
		strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		sprintf(casteo, "%d", lcompeticion.competicion[i].ano); // integer to string
		strcat(stringfinal, casteo);
		strcat(stringfinal, "$");

	}
}

/* Pasa un string con el contenido de una ListaPais a un string
El orden y forma es este(usa $ como separador):
$numeroElementos&codigo[0]$pais[0]$codigo[1]$...$pais[numeroElementos -1]$
*/
void stringlpais(ListaPais lpais, char* stringfinal){
	strcpy(stringfinal, "");
	strcat(stringfinal, "$");
    char casteo[15];
    strcpy(casteo,"");
    sprintf(casteo, "%d", lpais.tamanyo); // integer to string
    strcat(stringfinal, casteo);
	strcat(stringfinal, "$");
	for(int i = 0; i < lpais.tamanyo; i++){
		strcpy(casteo,"");
        sprintf(casteo, "%d", lpais.paises[i].codigo); // integer to string
        strcat(stringfinal, casteo);
		strcat(stringfinal, "$");
		strcat(stringfinal, lpais.paises[i].pais);
		strcat(stringfinal, "$");
	}
}

void desconversorlpais(ListaPais* lpais, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
	//while(strcmp(stringLeft, '$')){
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	lpais->tamanyo = atoi(temporal);
	lpais->paises = (Pais*) malloc(sizeof(Pais)*lpais->tamanyo);
	stringLeft++;
	for(int i = 0; i < lpais->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lpais->paises[i].codigo = atoi(temporal);

		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lpais->paises[i].pais, temporal);
		stringLeft++;
	}
	//lpais->tamanyo = (int) nfilas;
	//lpais->paises = (Pais*) malloc(sizeof(Pais)*nfilas);
	
}
//$numeroElementos&dni[0]$nombre[0]$telefono[1]$pais[0]$cdPais[0]&dni[1]$...$cdPais[numeroElementos -1]$

void desconversorlper(ListaPersona* lper, char* frase){
	char* stringLeft;
	char temporal[1024];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0; 
	strcpy(temporal, "");
	while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
	temporal[i] = '\0';
	lper ->numero = atoi(temporal);
	lper->persona = malloc(sizeof(Persona)*lper->numero);
	stringLeft++;
	for(int i = 0; i<lper->numero; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		strcpy(lper->persona[i].dni, temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		strcpy(lper->persona[i].nombre, temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		lper->persona[i].telefono = atoi(temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		strcpy(lper->persona[i].pais, temporal);
		stringLeft++;
		j =0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
		temporal[j] = '\0';
		lper->persona[i].cdPais = atoi(temporal);
		stringLeft++;
    }
}
void desconversorlmod(ListaModalidades* lmod, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	lmod->tamanyo = atoi(temporal);
	lmod->modalidades = malloc(sizeof(Modalidad)*lmod->tamanyo);
	stringLeft++;
	for(int i = 0; i < lmod->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lmod->modalidades[i].cd_mod = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lmod->modalidades[i].descripcion, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lmod->modalidades[i].nom_modalidad, temporal);
		stringLeft++;
	}
}

void desconversorllug(ListaLugar* llug, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	llug->tamanyo = atoi(temporal);
	llug->lugar = malloc(sizeof(Lugar)*llug->tamanyo);
	stringLeft++;
	for(int i = 0; i < llug->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		llug->lugar[i].Cd_Lugar = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(llug->lugar[i].NOM_LUGAR, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(llug->lugar[i].LOC_LUGAR, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		llug->lugar[i].Cd_Pais = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(llug->lugar[i].pais, temporal);
		stringLeft++;
	}
}

void desconversorlcomp(ListaCompeticion* lcomp, char* frase){
	char* stringLeft;
	char temporal[TAMAINO_SENDBUFF];
	stringLeft = strchr(frase, '$');
	stringLeft++;
	int i = 0;
	strcpy(temporal, "");
    while(stringLeft[0] != '$'){
		temporal[i] = stringLeft[0];
		stringLeft++;
		i++;
	}
    temporal[i] = '\0';
	lcomp->tamanyo = atoi(temporal);
	lcomp->competicion = malloc(sizeof(Competicion)*lcomp->tamanyo);
	stringLeft++;
	for(int i = 0; i < lcomp->tamanyo; i++){
		int j = 0;
		strcpy(temporal, "");
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].CdCompeticion = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].CdLugar = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lcomp->competicion[i].lugar, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lcomp->competicion[i].organizador, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		strcpy(lcomp->competicion[i].nomCompeticion, temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].dia = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].mes = atoi(temporal);
		j = 0;
		strcpy(temporal, "");
		stringLeft++;
		while(stringLeft[0] != '$'){
			temporal[j] = stringLeft[0];
			stringLeft++;
			j++;
		}
        temporal[j] = '\0';
		lcomp->competicion[i].ano = atoi(temporal);
		stringLeft++;
	}
}

