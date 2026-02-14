#include "computador.h"
#include "jogada.h"
#include "tabela.h"
#include <stdlib.h>
#include <time.h>

void jogadaFacil(){
    srand(time(NULL));
    int numCol = (rand() % 6)+1;

    while(!(capturarJogada(2, numCol))){
        numCol = (rand() % 6)+1;
    }
}

