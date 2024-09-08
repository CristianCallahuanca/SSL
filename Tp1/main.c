#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"

int main(int argc, char *argv[]){

    if(argc < 3){
        printf("ERROR: Ingresar como minimo 2 parametros(inicio/fin)");
        return 1;
    }

    double inicio = atof(argv[1]);
    double fin = atof(argv[2]);

    double incremento = (argc >= 4) ? atof(argv[3]) : 1.0;

    mostrarTabla(inicio, fin, incremento);

    return 0;
}










