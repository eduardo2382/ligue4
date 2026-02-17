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
    //a prioridade vai ser o ataque, caso n haja ataque ele defende, caso n tenha nenhum dos dois ele faz uma jogada aleatoria:
    int ataqueH = analiseAtaqueHorizontal();
    int ataqueV = analiseAtaqueVertical();
    //analise e a jogada do ataque!
    if(ataqueH == -1 && ataqueV == -1){
        jogadaMedia();
        return 1;
    }
    
    int qq = 0;
    int aux[3];
    if(ataqueH != -1){
        aux[qq++] = ataqueH;
    }
    if(ataqueV != -1){
        aux[qq++] = ataqueV;
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