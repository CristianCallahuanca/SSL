#include "scanner.h"
#include <string.h>



// Tabla de transición
static Estado tablaTransicion[8][9] = {
    // Letra, Dígito, Operador, Puntuación, Espacio, ':', '=', Otro, EOF
    { ESTADO_ID, ESTADO_CONSTANTE, ESTADO_OPERADOR, ESTADO_PUNTUACION, ESTADO_INICIAL, ESTADO_ASIGNACION_INICIO, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_EOF },  // ESTADO_INICIAL
    { ESTADO_ID, ESTADO_ID, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_ERROR_GENERAL, ESTADO_INICIAL },  // ESTADO_ID
    { ESTADO_INICIAL, ESTADO_CONSTANTE, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_ERROR_GENERAL, ESTADO_INICIAL },  // ESTADO_CONSTANTE
    { ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_ERROR_GENERAL, ESTADO_INICIAL },  // ESTADO_OPERADOR
    { ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_ERROR_GENERAL, ESTADO_INICIAL },  // ESTADO_PUNTUACION
    { ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ASIGNACION_FINAL, ESTADO_ERROR_GENERAL, ESTADO_INICIAL },  // ESTADO_ASIGNACION_INICIO
    { ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_INICIAL, ESTADO_ERROR_GENERAL, ESTADO_INICIAL },  // ESTADO_ASIGNACION_FINAL
    { ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_ERROR_GENERAL, ESTADO_INICIAL }  // ESTADO_ERROR_GENERAL
};

int esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int esDigito(char c) {
    return c >= '0' && c <= '9';
}

int esEspacio(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

int esOperador(char c) {
    return strchr("+-*/%", c) != NULL;
}

int esPuntuacion(char c) {
    return strchr(";,()", c) != NULL;
}

int esDospuntos(char c) {
    return c == ':';
}

int esIgual(char c) {
    return c == '=';
}

Columna obtenerColumna(char c) {
    if (esLetra(c)) return COL_LETRA;
    if (esDigito(c)) return COL_DIGITO;
    if (esOperador(c)) return COL_OPERADOR;
    if (esPuntuacion(c)) return COL_PUNTUACION;
    if (esEspacio(c)) return COL_ESPACIO;
    if (esDospuntos(c)) return COL_DOSPUNTOS;
    if (esIgual(c)) return COL_IGUAL;
    if (c == EOF) return COL_EOF;
    return COL_OTRO;
}

Token obtenerToken() {
    Token token = {TOKEN_ERROR_GENERAL, {0}};
    Estado estadoActual = ESTADO_INICIAL;
    char c;
    int pos = 0;

    while (1) {
        c = getchar();
        Columna col = obtenerColumna(c);
        Estado nuevoEstado = tablaTransicion[estadoActual][col];

        if (nuevoEstado == ESTADO_INICIAL) {
            if (estadoActual != ESTADO_INICIAL) {
                ungetc(c, stdin);
                token.lexema[pos] = '\0';

                switch (estadoActual) {
                    case ESTADO_ID: token.tipo = TOKEN_IDENTIFICADOR; break;
                    case ESTADO_CONSTANTE: token.tipo = TOKEN_CONSTANTE; break;
                    case ESTADO_OPERADOR: token.tipo = TOKEN_OPERADOR; break;
                    case ESTADO_PUNTUACION: token.tipo = TOKEN_PUNTUACION; break;
                    case ESTADO_ASIGNACION_FINAL: token.tipo = TOKEN_ASIGNACION; break;
                    default: token.tipo = TOKEN_ERROR_GENERAL; break;
                }

                return token;
            }
            continue;
        }

        if (nuevoEstado == ESTADO_ASIGNACION_FINAL) {
            token.lexema[pos++] = c;
            token.lexema[pos] = '\0';
            token.tipo = TOKEN_ASIGNACION;
            return token;
        }

        if (nuevoEstado == ESTADO_ERROR_GENERAL) {
            token.lexema[pos++] = c;
            token.tipo = TOKEN_ERROR_GENERAL;
            token.lexema[pos] = '\0';
            return token;
        }

        if (nuevoEstado == ESTADO_EOF) {
            token.tipo = TOKEN_EOF;
            token.lexema[0] = '\0';
            return token;
        }

        token.lexema[pos++] = c;
        estadoActual = nuevoEstado;
    }
}
