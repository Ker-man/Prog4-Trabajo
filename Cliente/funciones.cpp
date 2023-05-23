#include "funciones.h"
//#include "pais.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
//#include "atleta.h"
//#include "competicion.h"
//#include "modalidad.h"
//#include "lugar.h"
//#include "ranking.h"
#include <winsock2.h>
#include <iostream>


// para linux usar #include <unistd.h>

using namespace std;


void limpiarLineas(char *texto, int capacidadaxima)
{
	if ((strlen(texto) == capacidadaxima-1) && (texto[capacidadaxima-2] != '\n'))
		while (getchar() != '\n');
}

void menuPrincipal(SOCKET s, char sendBuff[512], char recvBuff[512]) {
    char nextCommand[512];
    char nextCommandNum[512];
    int opcionInt = 0;
    while (opcionInt != 3)
    {
    cout << "Elija lo que quiere hacer: \n" << endl;
    cout << "    1-Ensenar Atletas \n" << endl;
    cout << "    2-Ver ranking por paises\n" << endl;
    cout << "    3-Salir\n" << endl;
    cout << "Seleccione opcion: \n" << endl;
	cin >> opcionInt;
    cout << "la opcion seleccionada es: " << opcionInt << endl;

    switch (opcionInt)
    {
        case 1:;
            send(s, "01", 512, 0);
            recv(s, recvBuff, 1024, 0);
            ListaPersona lPer;
            desconversorlper(&lPer, recvBuff);
            imprimirAtletas(lPer);
            break;
        case 2:;
            char opcionPais[512];
            char opcionModalidad[1024];
            char opcionCompeticion[1024];

            send(s, "02", 512, 0);
            recv(s, recvBuff, 1024, 0);
            ListaPais lPais;
            desconversorlpais(&lPais, recvBuff);
            imprimirPais(lPais);

            cin >> opcionPais;
            strcpy(nextCommand, "06$");
            //sscanf(nextCommandNum, "%i", opcionPais);
            strcat(nextCommand, opcionPais);
            strcat(nextCommand, "$");

            send(s, nextCommand, 512, 0);
            recv(s, recvBuff, 1024, 0);
            ListaCompeticion lComp;
            desconversorlcomp(&lComp, recvBuff);
            imprimirCompeticiones(lComp);

            cin >> opcionCompeticion;
            send(s, "05", 512, 0);
            recv(s, recvBuff, 1024, 0);
            ListaModalidades lMod;
            desconversorlmod(&lMod, recvBuff);
            imprimirModalidades(lMod);
            cin >> opcionModalidad;

            strcpy(nextCommand, "07$");
            strcat(nextCommand, opcionModalidad);
            strcat(nextCommand, "$");
            strcat(nextCommand, opcionCompeticion);
            strcat(nextCommand, "$");

            send(s, nextCommand, 512, 0);
            recv(s, recvBuff, 1024, 0);
            Ranking rank;
            desconversorRanking(&rank, recvBuff);
            imprimirRanking(rank);

            break;
        case 3:;
            break;
    }
    }
}

char menuAdmin(){
    cout << "Es usted Admistrador o Usuario?\n" << endl;
    cout << "   1-Administrador\n" << endl;
    cout << ("   2-Usuario\n") << endl;
	char linea[3];
	cin >> linea;
	return *linea;
}

void menuPrincipalAdmin(SOCKET s, char sendBuff[512], char recvBuff[512]) {

    int opcionint=0;
    while(opcionint != 7){
        //system("cls");
        cout << "\nElija lo que quiere hacer: \n" << endl;
        cout << "    1-Gestionar atletas \n" << endl;
        cout << "    2-Gestionar paises \n" << endl;
        cout << "    3-Gestionar modalidades \n" << endl;
        cout << "    4-Gestionar lugares\n" << endl;
        cout << "    5-Gestionar competiciones\n" << endl;
        cout << "    6-Gestionar rankings\n" << endl;
        cout << "    7-Salir \n" << endl;
        char linea[3];
	    cin >> opcionint;
        //sscanf(linea, "%i", &opcionint);
        cout << "la opcion seleccionada es: " << opcionint << endl;
        switch (opcionint)
        {
        case 1:;
            send(s, "01", 512, 0);
            recv(s, recvBuff, 1024, 0);
            break;
        case 2:
            //menuPais(db);
            break;
        case 3:
            //menuModalidades(db);
        case 4:
            //menuLugares(db);
            break;
        case 5:
            //menuCompeticiones(db);
            break;
        case 6:
            //menuRanking(db);
            break;
        case 7:;//SALIR
            break;
        default:
            cout << "Caso no contemplado\n" << endl;
            break;
        }
    }

}



void cargarDatosPostu(){
    printf("Cargando \n");
    int porcentaje = 0;
    for (int i = 0; i <= 20; i++)
    {
        printf("Lleva un %i porciento\n",porcentaje);
        Sleep(100);
        porcentaje += 5;
    }
    printf("Se ha completado la carga de datos");
}

void monstrarLogo(){
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXxlc:cdXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWd.    .oNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNK0NWMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWk.    .cXMMMMMMMMMMWWWMMMMMMMMMMMMMMWWWNNNXKk;..:0MM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKd:.    .:k000KXXXX0dccdO00K000000000000000000x;..:0MM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNd'.  .   ........''''...,dkO00KKKXXNNWWWMMMMMMMMNKKNMMM \n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMK; .  .    ...';cccok00OkOKWMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX:.....   .:OKXWWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMXc. .     .xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMK:.   .  .:KMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWMMMMMMMMK; . ..  .dWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKxcxWMMMMMMM0,       .lNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMWO:'',xWMMMMMMM0, ..   . .ckKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMNXK0NMWx''dXWWMMMMMMMMXo..       ...:dKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMKc.'oXXo.;KMMMMMMMMMMMMMNOl,... . ..  .'oKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMWo   .:;.cKMMMMMMMMMMMMMMMMWXxc,..  .   ..'xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMWK:      '0MMMMMMMMMMMMMMMMMNk:'.. ..:l:.. .oNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMNOxkd;.   .xWMMMMMMMMMMMMMMWKl.. ..;o0WMK;. .kMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMXxkXXd,     .kWMMMMMMMMMMMMWO;..';lOXWMMMK;  .kMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMW0x0NO;        ,0MMMMMMMMWXOx:..:xXNWMMMMMMX:. 'OMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMNkxkkc. .'.      oWMMMMMMM0:...:ONMMMMMMMMMMWd..:KMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMNO:,:;',:d0NXx'    ,0MMMMMMNo. .oXMMMMMMMMMMMMMO'.,kWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMWx,;xOKXNWMMMMMx.   .xMMMMMMXc.'xWMMMMMMMMMMMMMM0, ..;lodKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMXOOKNMMMMMMMMMMMO.    :KWMMMMW0x0WMMMMMMMMMMMMMMMO,.....,:OWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMWKOXWMMMMMMMMMMMMMK;     'xNMMMMMMMMMMMMMMMMMMMMMMMN0OO0KKNWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMN00NMMMMMMMMMMMMMMMWd.      cKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMWX0KWMMMMMMMMMMMMMMMMMk.       'kWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWK0KXWMMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMWK0NMMMMMMMMMMMMMMMMMMM0,  ,dl.  .oNMMMMMMMMMWWWWNWWMMMMMMMMMMMMMMNl...lXMMMMMMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMNKXWMMMMMMMMMMMMMMMMMMMMN:  :XWXk:..cKMMMMMMWXkxxddxkXWMMWWNWMMMMMMWd.  ,OX0Oxocclx00OkkKWMMMMMMM\n");
    Sleep(10);
    printf("MWXKNMMMMMMMMMMMMMMMMMMMMMNk,  oWMMMNo. ,kWMN0KWWWWWNNWWWMMXkdllddoodddl,. .'.  .,ldoddlldkKWMMMMMMM\n");
    Sleep(10);
    printf("WXXWMMMMMMMMMMMMMMMMMMMWKo'   :KMMMMMNx' .lkl.lNMMMMMMMMMMMWNXXK0Oxolc;.       .dNMMMMMWWWMMMMMMMMMM\n");
    Sleep(10);
    printf("XNMMMMMMMMMMMMMMMMMMMMXd.  'lONMMMMMMMMXkc.  'OMMMMMMMMMMMMMMMMMMMMMMMWXOo,     :KMMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("WMMMMMMMMMMMMMMMMMMMNk,..ckNMMMMMMMMMMMMMWO;.oWMMMMMMMMMMMMMMMMMMMMMMMMMMMXo.    cXMMMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMWk. ;KWMMMMMMMMMMMMMMMMMXOKMMMMMMMMMMMMMMMMMMMMMMMMMMMMNk'    .cONMMMMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMK: ,OWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMW0o,. .';,. .,dXWMMMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMXo:xWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMK,.,ld0NWWKko:'':xXMMMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWd.:XMMMMMMMMMWXx;.,xNMMMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX:;0MMMMMMMMMMMMMN0d::xNMMMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKx;.:XMMMMMMMMMMMMMMMMKl';xNMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN0xddONMMMMMMMMMMMMMMMMMWKxkNMMMM\n");
    Sleep(10);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
}

void limpiarFinales(char* str) {
    while((str[strlen(str)-1]=='\n'||str[strlen(str)-1]=='\r')&&strlen(str)>0)str[strlen(str)-1]='\0';
}