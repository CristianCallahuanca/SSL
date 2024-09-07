#include "scanner.h"
#include <string.h>


int esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int esDigito(char c) {
    return c >= '0' && c <= '9';
}

int esEspacio(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}


Token obtenerToken() {
    static int charActual = ' ';
    int charSig;
    Token token = {TOKEN_ERROR, {0}};
    int pos = 0;

    // Saltar espacios en blanco
    while (esEspacio(charActual)) {
        charActual = getchar();
    }

        token.tipo = TOKEN_EOF;
    if (charActual == EOF) {
        return token;
    }

    if (esLetra(charActual)) {
        token.tipo = TOKEN_IDENTIFICADOR;
        while (esLetra(charActual) || esDigito(charActual) || charActual == '_') {
            token.lexema[pos++] = charActual;
            charActual = getchar();
        }
    } else if (esDigito(charActual)) {
        token.tipo = TOKEN_CONSTANTE;
        while (esDigito(charActual)) {
            token.lexema[pos++] = charActual;
            charActual = getchar();
        }
    } else if (strchr("+-*/%", charActual)) {
        token.tipo = TOKEN_OPERADOR;
        token.lexema[pos++] = charActual;
        charActual = getchar();
    } else if (strchr(";,()", charActual)) {
        token.tipo = TOKEN_PUNTUACION;
        token.lexema[pos++] = charActual;
        charActual = getchar();
    } else if (charActual == ':') {
        charSig = getchar();
        if (charSig == '=') {
            token.tipo = TOKEN_ASIGNACION;
            token.lexema[pos++] = charActual;
            token.lexema[pos++] = charSig;
            charActual = getchar();
        } else {
            token.tipo = TOKEN_ERROR;
            token.lexema[pos++] = charActual;
            token.lexema[pos++] = charSig;
            charActual = charSig;
        }
    } else {
        token.tipo = TOKEN_ERROR;
        token.lexema[pos++] = charActual;
        charActual = getchar();
    }

    token.lexema[pos] = '\0';
    return token;
}
