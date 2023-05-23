#ifndef _SERVER_H_
#define _SERVER_H_
#include "ranking.h"
void desconversorlcomp(ListaCompeticion* lcomp, char* frase);
void desconversorllug(ListaLugar* llug, char* frase);
void desconversorlmod(ListaModalidades* lmod, char* frase);
void desconversorlper(ListaPersona* lper, char* frase);
void desconversorlpais(ListaPais* lpais, char* frase);
void stringlpais(ListaPais lpais, char* stringfinal);
void stringcompeticion(ListaCompeticion lcompeticion, char* stringfinal);
void stringlugar(ListaLugar listalugar, char* stringfinal);
void stringlmodalidad(ListaModalidades lmodalidad, char* stringfinal);
void stringLper(ListaPersona lper, char* stringfinal);
void stringRanking(Ranking rank, char* stringfinal);

#endif