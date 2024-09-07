#include "scanner.h"
#include <stdio.h>

int main() {
    Token token;
    do {
        token = obtenerToken();
        printf("Token: %s ('%s')\n", 
            token.tipo == TOKEN_IDENTIFICADOR ? "Identificador" :
            token.tipo == TOKEN_CONSTANTE ? "Constante" :
            token.tipo == TOKEN_OPERADOR ? "Operador" :
            token.tipo == TOKEN_PUNTUACION ? "Puntuacion" :
            token.tipo == TOKEN_ASIGNACION ? "Asignacion" : "Error", token.lexema);
    } while (token.tipo != TOKEN_EOF);
    return 0;
}
