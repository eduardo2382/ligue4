#include "jogada.h"
#include <stdio.h>
#include "terminal.h"
#include "tabela.h"

int capturarJogada(int vez, int col){
    if(!col){
        int coluna = 0;
        limparLinha(21);

        moverCursor(21, 2);

        printf("Escolha uma coluna de 1 a 7: ");

        while (!(scanf("%d", &coluna)) || !(coluna >= 1 && coluna <= 7)){
            moverCursor(21, 2);
            limparLinha(21); // codigo ansii para limpar a linha
            scanf("%*[^\n]"); // codigo para descartar a linha bugada
            printf("Opcao errada! Escolha uma coluna de 1 a 7: ");
        }
        

        while(!(atualizarTabela(vez, (coluna-1)))){
            moverCursor(21, 2);
            printf("Coluna cheia, selecione outra coluna: ");
            while (!(scanf("%d", &coluna)) || !(coluna >= 1 && coluna <= 7)){
                moverCursor(21, 2);
                printf("\033[2K"); // codigo ansii para limpar a linha
                scanf("%*[^\n]"); // codigo para descartar a linha bugada
                printf("Opcao errada! Escolha uma coluna de 1 a 7: ");
            }
        }

        return 1;
    }else{
        if(!atualizarTabela(vez, col)){
            return 0;
        }
    }
}