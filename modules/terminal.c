#include "terminal.h"
#include <stdio.h>

void resetarCor() {
    // imprime uma sequencia para retornar a cor original
    printf("\033[0m");
}

void mudarEstilo(int estilo,int cor){
    // imprime uma sequencia de estilo e cor

    printf("\033[%d;%dm", estilo, cor);
}

void moverCursor(int linha, int coluna) {
    //move o cursor para a linha e coluna desejada

    printf("\033[%d;%dH", linha, coluna);
}

void titulo(char *tit, int tam, int lin){
    //imprime um titulo na linha desejada
    //o tamanho é usado para calcular o centro da tela
    int coluna = (80-tam)/2;

    moverCursor(lin, coluna);

    printf("\033[%d;%dm", ESTILO_REVERSO, ESTILO_NEGRITO);
    printf("%s\n", tit);
    printf("\n");
    resetarCor();
}

void limparTela(){
    //limpa a tela e escreve o titulo do jogo
    printf("\033[2J");
    titulo("LIGUE4", 6, 2);
}