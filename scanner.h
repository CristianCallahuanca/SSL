#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

typedef enum {
    TOKEN_IDENTIFICADOR,
    TOKEN_CONSTANTE,
    TOKEN_OPERADOR,
    TOKEN_PUNTUACION,
    TOKEN_ASIGNACION,
    TOKEN_ERROR_GENERAL,
    TOKEN_ERROR_ASIGNACION,
    TOKEN_EOF
} TipoToken;


// Definición de los estados
typedef enum {
    ESTADO_INICIAL,
    ESTADO_ID,
    ESTADO_CONSTANTE,
    ESTADO_OPERADOR,
    ESTADO_PUNTUACION,
    ESTADO_ASIGNACION_INICIO,
    ESTADO_ASIGNACION_FINAL,
    ESTADO_ERROR_GENERAL,
    ESTADO_EOF
} Estado;

// Definición de las columnas para la tabla de transición
typedef enum {
    COL_LETRA,
    COL_DIGITO,
    COL_OPERADOR,
    COL_PUNTUACION,
    COL_ESPACIO,
    COL_DOSPUNTOS,
    COL_IGUAL,
    COL_OTRO,
    COL_EOF
} Columna;

typedef struct {
    TipoToken tipo;
    char lexema[1024];
} Token;

// Función para obtener el siguiente token
Token obtenerToken();

#endif
