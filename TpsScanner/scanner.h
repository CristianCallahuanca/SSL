#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

typedef enum {
    TOKEN_IDENTIFICADOR,
    TOKEN_CONSTANTE,
    TOKEN_OPERADOR,
    TOKEN_PUNTUACION,
    TOKEN_ASIGNACION,
    TOKEN_ERROR,
    TOKEN_EOF
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[1024];
} Token;

Token obtenerToken();

#endif
