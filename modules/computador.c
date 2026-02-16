#include "computador.h"
#include "jogada.h"
#include "tabela.h"
#include <stdlib.h>
#include <time.h>

int jogadaFacil(){
    srand(time(NULL));
    int numCol = (rand() % 7) + 1;

    while(!(capturarJogada(2, numCol))){
        numCol = (rand() % 7) + 1;
    }
    return 1;
}

int jogadaMedia(){
    //Entrada das respostas:
    int horizontal = analiseCompHorizontal();
    int vertical = analiseCompVertical();
    int diagonal = analiseCompDiagonal();

    //analise da jogada
    //ambas as possibilidades dão negativa.
    if(horizontal == -1 && vertical == -1 && diagonal == -1){
        return jogadaFacil();
    }
    //alguma das possibilidades da True
    int qq = 0;
    int aux[3];
    if(horizontal != -1){
        aux[qq++] = horizontal;
    }
    if(vertical != -1){
        aux[qq++] = vertical;
    }
    if(diagonal != -1){
        aux[qq++] = diagonal;
    }

    int tentativa = 0;
    int maxTentativa = 5;
    while(tentativa < maxTentativa){
        int i = rand() % qq;
        if(capturarJogada(2,aux[i] + 1)){
            return 1;
        }
        tentativa++;
    }
    return 0;
}

int jogadaDificil(){
    //Análise de jogada
    //prioridade do modo dificil será defender(com isso é possivel utilizar o nivel medio) para depois atacar:
    //Analisando se posui algo para defender:
    int horizontal = analiseCompHorizontal();
    int vertical = analiseCompVertical();
    int diagonal = analiseCompDiagonal();
    if(horizontal || vertical || diagonal){
        jogadaMedia();
        return 1;
    }
    //Analise da jogada dificil:
}