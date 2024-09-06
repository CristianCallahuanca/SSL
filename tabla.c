#include <stdio.h>
#include <assert.h>
#include "tabla.h"
#include "conversion.h"


void mostrarTabla(int inicio, int fin, int incremento){
    assert(inicio < fin);
    assert(incremento >0);

    printf("| Nudos  | Km/h   \n");
    printf("--------------------");

    for(double nudos=inicio; nudos<=fin; nudos+=incremento){

        double kmh = conversionNudosAKm(nudos);
        printf("| %.2f  | %.4f  |\n", nudos, kmh);
    }

}