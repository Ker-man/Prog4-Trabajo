#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_
#include <winsock2.h>

#include "atleta.h"
#include "pais.h"
#include "lugar.h"
#include "modalidad.h"
#include "competicion.h"
#include "ranking.h"
#include "desconversor.h"
#ifdef __cplusplus
extern "C" {
#endif
//
// ... prototypes for C_library go here ...
//

#ifdef __cplusplus
}
#endif

char menuAdmin();
void menuPrincipal(SOCKET s, char sendBuff[512], char recvBuff[512]);
char menuPaises();
char mostrarMenu();
void menuPrincipalAdmin(SOCKET s, char sendBuff[512], char recvBuff[512]);
void cargarDatosPostu();
void monstrarLogo();
void limpiarFinales(char* str);


#endif  /* _FUNCIONES_H_ */