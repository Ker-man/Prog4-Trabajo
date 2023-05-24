#include "logger.h"

void iniciarLogger() { //Iniciar Logger
    FILE* f = fopen("Logger.txt", "a");
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
    fprintf(f, "%s\n", s);
    fprintf(f, "Usuario Logueado\n");
    fclose(f);
}

void loggear(char* text) { //Loggear
    FILE* f = fopen("Logger.txt", "a");
    fprintf(f, text);
    fclose(f);
}