#include "tabela.h"
#include "terminal.h"
#include <stdio.h>

int jogadas[6][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0}
};

void printTabela(int corJogador1, int corJogador2){
    int linhaInic = 9;
    int colunInic = 27;

    

    for(int l = 0; l < 6; l++){
        moverCursor(linhaInic, colunInic);
        for(int c = 0; c < 7; c++){
            switch (jogadas[l][c]){
                case 1:
                    if(c == 6){
                        mudarEstilo(ESTILO_REVERSO, corJogador1);
                        printf("  ");
                        resetarCor();
                    }else{
                        mudarEstilo(ESTILO_REVERSO, corJogador1);
                        printf("  ");
                        resetarCor();
                        mudarEstilo(ESTILO_REVERSO, PRETO);
                        printf("  ");
                    }
                    break;
                    
                case 2:
                    if(c == 6){
                        mudarEstilo(ESTILO_REVERSO, corJogador2);
                        printf("  ");
                        resetarCor();
                    }else{
                        mudarEstilo(ESTILO_REVERSO, corJogador2);
                        printf("  ");
                        resetarCor();
                        mudarEstilo(ESTILO_REVERSO, PRETO);
                        printf("  ");
                    }

                    break;

                default:
                    if(c == 6){
                        mudarEstilo(ESTILO_REVERSO, BRANCO);
                        printf("  ");
                        resetarCor();
                    }else{
                        mudarEstilo(ESTILO_REVERSO, BRANCO);
                        printf("  ");
                        resetarCor();
                        mudarEstilo(ESTILO_REVERSO, PRETO);
                        printf("  ");
                    }
                    
                    break;
            }
        }
        
        if(l != 5){
            moverCursor(linhaInic+1, colunInic);
            mudarEstilo(ESTILO_REVERSO, PRETO);
            printf("                          ");
            resetarCor();
        }

        linhaInic = linhaInic + 2;
    }

    printf("\n");
}

int atualizarTabela(int vez, int coluna){
    for(int l = 0; l < 6; l++){
        if(jogadas[l][coluna] != 0){
            return 0;
        }

        if(l==5 || jogadas[l+1][coluna] != 0){
            jogadas[l][coluna] = vez;
            return 1;
        }
    }
}

int analisarLinhas(){
    for(int l = 0; l < 6; l++){ 
        //percorre as linhas da matriz

        int primeiroElem = 0;
        //inicializa o contador de elementos

        for(int c = 0; c < 4; c++){
            //percorre as colunas da matrz

            for(int i = c; i <= c+3; i++){
                //percorre uma janela de 4 elementos a partir da coluna atual

                if(i==c){//se for o primeiro elemento
                    if(jogadas[l][i] == 0){ 
                        //se for o primeiro elemento e for igual a 0 ja quebra o laco e desliza a janela
                        break;
                    }else{
                        primeiroElem = jogadas[l][i];
                        //se nao for igual a 0 define o valor parametro como o elemento atual
                    }

                }else if(i == c+3 && jogadas[l][i] == primeiroElem){
                    //se estiver no ultimo elemento da janela significa que todos os outros foram iguais ao primeiro
                    //se esse tambem for, quebra a funcao e retorna o que foi igual
                    return primeiroElem;

                }else if(jogadas[l][i] != primeiroElem){
                    //se o elemento atual for diferente do primeiro quebra o laco e desliza a janela
                    break;
                }
                
            }
        }
    }

    return 0;
};

int analisarColunas(){
    for(int c = 0; c < 7; c++){ 
        //percorre as colunas da matriz

        int primeiroElem = 0;
        //inicializa o contador de elementos

        for(int l = 0; l < 3; l++){
            //percorre as linhas da matrz

            for(int i = l; i <= l+3; i++){
                //percorre uma janela de 4 elementos a partir da linha atual

                if(i==l){//se for o primeiro elemento
                    if(jogadas[i][c] == 0){ 
                        //se for o primeiro elemento e for igual a 0 ja quebra o laco e desliza a janela
                        break;
                    }else{
                        primeiroElem = jogadas[i][c];
                        //se nao for igual a 0 define o valor parametro como o elemento atual
                    }

                }else if(i == l+3 && jogadas[i][c] == primeiroElem){
                    //se estiver no ultimo elemento da janela significa que todos os outros foram iguais ao primeiro
                    //se esse tambem for, quebra a funcao e retorna o que foi igual
                    return primeiroElem;

                }else if(jogadas[i][c] != primeiroElem){
                    //se o elemento atual for diferente do primeiro quebra o laco e desliza a janela
                    break;
                }
                
            }
        }
    }

    return 0;
};

int analisarDiagonal(){
    //declarando as linhas e colunas.
    int n = 6;
    int m = 7;
    //loop de leitura(leitura da direção principal da matriz, parte alta):
    for(int coluna = 0; coluna < m; coluna++){
        int i = 0;
        int j = coluna;
        int aux1 = 0;
        int aux2 = 0;

        while(i < n && j < m){
            if(jogadas[i][j] == 1){
                aux1++;
                aux2 = 0;
            }else if(jogadas[i][j] == 2){
                aux2++;
                aux1 = 0;
            } else{
                aux1 = 0;
                aux2 = 0;
            }

            if(aux1 == 4){
                return 1;
            }
            if(aux2 == 4){
                return 2;
            }

            i++;
            j++;
        }
    }
    //lopping que analisa a parte baixa(na mesma direção da anterior, no caso tirando o celula (0,0))
    for(int linha = 0; linha < n; linha++){
        int i = linha;
        int j = 0;
        int aux1 = 0;
        int aux2 = 0;

        while(i < n && j < m){
             if(jogadas[i][j] == 1){
                aux1++;
                aux2 = 0;
            }else if(jogadas[i][j] == 2){
                aux2++;
                aux1 = 0;
            } else{
                aux1 = 0;
                aux2 = 0;
            }

            if(aux1 == 4){
                return 1;
            }
            if(aux2 == 4){
                return 2;
            }
            
            i++;
            j++;
        }
    }
//Analisando as diagonais de forma espelhada:
    for(int coluna = 0; coluna < m; coluna++){
        int i = 0;
        int j = coluna;
        int aux1 = 0;
        int aux2 = 0;

        while(i < n && j >= 0){
           if(jogadas[i][j] == 1){
                aux1++;
                aux2 = 0;
            }else if(jogadas[i][j] == 2){
                aux2++;
                aux1 = 0;
            } else{
                aux1 = 0;
                aux2 = 0;
            }

            if(aux1 == 4){
                return 1;
            }
            if(aux2 == 4){
                return 2;
            }

            i++;
            j--;
        }
    }
    //loop espelhado
    for(int linha = 0; linha < n; linha++){
        int i = linha; 
        int j = m - 1;
        int aux1 = 0;
        int aux2 = 0;

        while(i < n && j >= 0){
              if(jogadas[i][j] == 1){
                aux1++;
                aux2 = 0;
            }else if(jogadas[i][j] == 2){
                aux2++;
                aux1 = 0;
            } else{
                aux1 = 0;
                aux2 = 0;
            }

            if(aux1 == 4){
                return 1;
            }
            if(aux2 == 4){
                return 2;
            }
            
            i++;
            j--;
        }
    }
    
}

int analisarEmpate(){
    for(int l = 0; l < 6; l++){
        for(int c = 0; c < 7; c++){
            if(jogadas[l][c] == 0){
                return 0;
            }
        }
    }

    return 1;
}

int analisarTabela(){
    switch(analisarDiagonal()){
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
    }

    switch (analisarLinhas()){
        case 1:
            return 1;
            break;
        
        case 2:
            return 2;
            break;
    }

    switch (analisarColunas()){
    case 1:
        return 1;
        break;
    
    case 2:
        return 2;
        break;
    }

    switch (analisarEmpate()){
        case 1:
            return 3;
            break;
    }
}
//funções de analise do computador:
int analiseCompHorizontal(){
    //Leitura da direita para esquerda:
    for(int i = 5; i >= 0; i--){
        int aux = 0;
        for(int j = 0; j < 7; j++){
            //Analise de jogada:
            if(aux == 2 && jogadas[i][j+1] == 1 && jogadas[i][j] == 0 && j != 6){
                return j; 
            }
            //Analise da linha:
            if(jogadas[i][j] == 1){
                aux++;
            }else{
                aux = 0;
            }
            if(aux == 3 && jogadas[i][j+1] == 0 && j != 6){
                return j + 1;
            }
        }
    }

        //leitura da esquerda para direita:
        for(int i = 5; i >= 0; i--){
            int aux = 0;
            for(int j = 6; j >= 0; j--){
                //analise da jogada
                if(aux == 2 && jogadas[i][j - 1] == 1 && jogadas[i][j] == 0 && j != 0){
                    return j;
                }
                //avaliação:
                if(jogadas[i][j] == 1){
                    aux++;
                }else{
                    aux = 0;
                }
                if(aux == 3 && jogadas[i][j-1] == 0 && j != 0){
                    return j - 1;
                }
            }
        }
        return -1;
}
int analiseCompVertical(){
    for(int j = 0; j < 7; j++){
        int aux = 0;
        for(int i = 5; i >= 0; i--){
            if(jogadas[i][j] == 1){
                aux++;
            }else{
                aux = 0;
            }
            if(aux == 3 && jogadas[i-1][j] == 0 && i != 0){
                return j;
            }
        }
    }
    return -1;
}
int analiseCompDiagonal() {
    int n = 6;
    int m = 7;
    
    // ===== DIAGONAIS PRINCIPAIS (\) =====
    // Parte superior (começando na primeira linha)
    for(int coluna = 0; coluna < m; coluna++){
        int i = 0;
        int j = coluna;
        int auxJogador = 0;  // Contador para peças do jogador (1)
        
        while(i < n && j < m){
            if(jogadas[i][j] == 1){
                auxJogador++;
                
                // Encontrou 3 peças do jogador
                if(auxJogador == 3){
                    // Verifica se pode bloquear antes
                    int ant_i = i - 3;
                    int ant_j = j - 3;
                    if(ant_i >= 0 && ant_j >= 0 && jogadas[ant_i][ant_j] == 0){
                        return ant_j;  // Bloqueia no início
                    }
                    
                    // Verifica se pode bloquear depois
                    int prox_i = i + 1;
                    int prox_j = j + 1;
                    if(prox_i < n && prox_j < m && jogadas[prox_i][prox_j] == 0){
                        return prox_j;  // Bloqueia no final
                    }
                }
            } else {
                auxJogador = 0;  // Reset se encontrar peça do PC ou vazio
            }
            
            i++;
            j++;
        }
    }
    
    // Parte inferior (começando na primeira coluna, ignorando (0,0))
    for(int linha = 1; linha < n; linha++){
        int i = linha;
        int j = 0;
        int auxJogador = 0;
        
        while(i < n && j < m){
            if(jogadas[i][j] == 1){
                auxJogador++;
                
                if(auxJogador == 3){
                    // Verifica início
                    int ant_i = i - 3;
                    int ant_j = j - 3;
                    if(ant_i >= 0 && ant_j >= 0 && jogadas[ant_i][ant_j] == 0){
                        return ant_j;
                    }
                    
                    // Verifica final
                    int prox_i = i + 1;
                    int prox_j = j + 1;
                    if(prox_i < n && prox_j < m && jogadas[prox_i][prox_j] == 0){
                        return prox_j;
                    }
                }
            } else {
                auxJogador = 0;
            }
            
            i++;
            j++;
        }
    }
    
    // ===== DIAGONAIS SECUNDÁRIAS (/) =====
    // Parte superior (começando na primeira linha)
    for(int coluna = 0; coluna < m; coluna++){
        int i = 0;
        int j = coluna;
        int auxJogador = 0;
        
        while(i < n && j >= 0){
            if(jogadas[i][j] == 1){
                auxJogador++;
                
                if(auxJogador == 3){
                    // Verifica início (direita superior)
                    int ant_i = i - 3;
                    int ant_j = j + 3;
                    if(ant_i >= 0 && ant_j < m && jogadas[ant_i][ant_j] == 0){
                        return ant_j;
                    }
                    
                    // Verifica final (esquerda inferior)
                    int prox_i = i + 1;
                    int prox_j = j - 1;
                    if(prox_i < n && prox_j >= 0 && jogadas[prox_i][prox_j] == 0){
                        return prox_j;
                    }
                }
            } else {
                auxJogador = 0;
            }
            
            i++;
            j--;
        }
    }
    
    // Parte inferior (começando na última coluna)
    for(int linha = 1; linha < n; linha++){
        int i = linha;
        int j = m - 1;
        int auxJogador = 0;
        
        while(i < n && j >= 0){
            if(jogadas[i][j] == 1){
                auxJogador++;
                
                if(auxJogador == 3){
                    // Verifica início (direita superior)
                    int ant_i = i - 3;
                    int ant_j = j + 3;
                    if(ant_i >= 0 && ant_j < m && jogadas[ant_i][ant_j] == 0){
                        return ant_j;
                    }
                    
                    // Verifica final (esquerda inferior)
                    int prox_i = i + 1;
                    int prox_j = j - 1;
                    if(prox_i < n && prox_j >= 0 && jogadas[prox_i][prox_j] == 0){
                        return prox_j;
                    }
                }
            } else {
                auxJogador = 0;
            }
            
            i++;
            j--;
        }
    }
    
    return -1;  // Nenhuma ameaça diagonal
}