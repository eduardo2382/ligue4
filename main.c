#include <stdio.h>

#define PRETO    30
#define VERMELHO 31
#define VERDE    32
#define AMARELO  33
#define AZUL     34
#define BRANCO   37
#define MAGENTA  35
#define CIANO    36

#define ESTILO_RESET      0
#define ESTILO_NEGRITO    1
#define ESTILO_SUBLINHADO 4
#define ESTILO_REVERSO    7

int jogadas[6][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0}
};

//Modificação utilizando typedef para deixar o codigo mais limpo.
typedef struct{
    char nome[128];
    int cor;
} Jogador;

char escolhasMenu[4][24] = {
    "Jogador vs Jogador",
    "Jogador vs Computador",
    "Computador vs Computador",
    "Sair do Jogo"
};

int cores[] = {
    VERMELHO,
    VERDE,
    AMARELO,
    AZUL,
    MAGENTA,
    CIANO
};

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
    printf("\033[H\033[J");
    titulo("LIGUE4", 6, 2);
};

void printMenuInicial(){
    //escreve o menu inicial na tela
    int linhaInicial = 5; 
    int colunaInicial = (80-26)/2;
    int tamLista = sizeof(escolhasMenu) / sizeof(escolhasMenu[0]);
    int quantLinhas = tamLista + 2; //quantidade total de linhas do menu(items da lista + topo e fim)

    for(int l = 0; l < quantLinhas; l++){ //cada linha do menu
        moverCursor(linhaInicial+l, colunaInicial);// move o cursor para a linha atual e coluna

        if(l == 0 || l == (quantLinhas-1)){
            //se for a primeira ou ultima linha imprime a linha padrao
            printf(" ----------------------------\n");
        }else{
            //imprime a linha de cada item com o numero de opcao no inicio
            printf("| %d.", l); 

            for(int k = 0; k < 24; k++){
                //percorre cada carac da string
                if(escolhasMenu[l-1][k] != '\0'){
                    printf("%c", escolhasMenu[l-1][k]); //imprime o carac
                }else{
                    printf(" "); //quando é vazio imprime um carac vazio para poder completar a linha
                }
            }
            printf(" |\n");//finaliza a linha dessa opcao
        }
    }


    printf("\n");
}

int menuInicial(){
    //funcao responsavel por chamar a funcao que imprime e por capturar a escolha do usuario

    int escolha = 0;
    int tamLista = sizeof(escolhasMenu) / sizeof(escolhasMenu[0]);
        
    printMenuInicial();//imprime o menu

    printf("Digite o numero da sua escolha: ");
    scanf("%d", &escolha);//captura a escolha do usuario

    while(!(escolha >= 1 && escolha <= tamLista)){ //caso a escolha nao esteja de acordo pede pro usuario repetir ate que alguma valida seja selecionada
        printf("Opcao errada, digite novamente: ");
        scanf("%d", &escolha);
    }

    return escolha;//retorna a escolha para o programa principal
}

Jogador jogador(char *tit, int corEscolhida){
    //funcao que captura escolhas do usuario relacionadas aos jogadores e retorna uma struct Jogador
    //param tit: nome que devera ser usado como subtitulo e em perguntas
    //param corEscolhida: se outro usuario ja tiver escolhido uma cor é possivel bloquear essa cor para nao haver duplica

    int tamCores = sizeof(cores)/sizeof(cores[0]);//numero de cores da lista
    int escolhaCor = 0;

    int tam = sizeof(tit)-1;
    Jogador jogador;

    titulo(tit, tam, 4);//escreve o subtitulo
    
    printf("Digite o nome do %s: ", tit);
    scanf("%s", jogador.nome);//recebe o nome do jogador

    limparTela();
    titulo(tit, tam, 4);
    //limpa a tela para a proxima pergunta e reescreve o subtitulo

    for(int i = 0; i < tamCores; i++){ 
        //laco que imprimira as cores disponiveis
        if(cores[i] == corEscolhida){
            //caso a cor atual ja tenha sido escolhida imprimira "1-X" para indicar
            printf("%d-X", i+1);
            printf(" ");
        }else{
            //imprime a cor junto com o seu numero para ser escolhida
            
            printf("%d-", i+1);//imprime o numero da cor
    
            mudarEstilo(ESTILO_REVERSO, cores[i]);
            printf(" ");
            //muda o terminal para a cor atual e imprime um espaco vazio para mostra-la
    
            resetarCor();
            printf(" ");
            //volta o terminal para a cor normal e imprime um espaco para separa as cores

        }

        }
    
    printf("\n");

    printf("Selecione a cor do jogador: ");
    scanf("%d", &escolhaCor);//captura a cor escolhida pelo usuario

    switch (escolhaCor)
    {
    case 1:
        jogador.cor = VERMELHO;
        break;

    case 2:
        jogador.cor = VERDE;
        break;

    case 3:
        jogador.cor = AMARELO;
        break;

    case 4:
        jogador.cor = AZUL;
        break;

    case 5:
        jogador.cor = MAGENTA;
        break;

    case 6:
        jogador.cor = CIANO;
        break;
    
    default:
        break;
    }

    while(!(escolhaCor >= 1 && escolhaCor <= tamCores) || jogador.cor == corEscolhida){ 
        //caso a opcao seja invalida ou a cor ja tenha sido escolhida pergunta de novo ao usuario
        printf("Opcao invalida, selecione uma opcao valida: ");
        scanf("%d", &escolhaCor);

        switch (escolhaCor)
        {
        case 1:
            jogador.cor = VERMELHO;
            break;

        case 2:
            jogador.cor = VERDE;
            break;

        case 3:
            jogador.cor = AMARELO;
            break;

        case 4:
            jogador.cor = AZUL;
            break;
        
        default:
            break;
        }
    }

    return jogador; //retorna a struct Jogador com os dados
}

void printVez( Jogador jogador1, Jogador jogador2, int vez){
    resetarCor();

    titulo("Vez da Jogada:", 14, 4);

    if(vez==1){
        moverCursor(6, 20);
        mudarEstilo(ESTILO_REVERSO, ESTILO_NEGRITO);

        mudarEstilo(ESTILO_REVERSO, jogador1.cor);
        printf("%s", jogador1.nome);

        moverCursor(6, 60);
        mudarEstilo(ESTILO_RESET, 0);
        printf("%s", jogador2.nome);
    }else{
        moverCursor(6, 20);

        printf("%s", jogador1.nome);

        moverCursor(6, 60);
        mudarEstilo(ESTILO_REVERSO, ESTILO_NEGRITO);
        mudarEstilo(ESTILO_REVERSO, jogador2.cor);
        printf("%s", jogador2.nome);
    }
    
    printf("\n");
    resetarCor();
};

void printTabela( Jogador jogador1, Jogador jogador2){
    int linhaInic = 9;
    int colunInic = 27;

    

    for(int l = 0; l < 6; l++){
        moverCursor(linhaInic, colunInic);
        for(int c = 0; c < 7; c++){
            switch (jogadas[l][c]){
                case 1:
                    if(c == 6){
                        mudarEstilo(ESTILO_REVERSO, jogador1.cor);
                        printf("  ");
                        resetarCor();
                    }else{
                        mudarEstilo(ESTILO_REVERSO, jogador1.cor);
                        printf("  ");
                        resetarCor();
                        mudarEstilo(ESTILO_REVERSO, PRETO);
                        printf("  ");
                    }
                    break;
                    
                case 2:
                    if(c == 6){
                        mudarEstilo(ESTILO_REVERSO, jogador2.cor);
                        printf("  ");
                        resetarCor();
                    }else{
                        mudarEstilo(ESTILO_REVERSO, jogador2.cor);
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

void capturarJogada(int vez, int col){
    if(!col){
        int coluna = 0;

        moverCursor(21, 2);

        printf("Escolha uma coluna de 1 a 7: ");
        scanf("%d", &coluna);

        while (!(coluna >= 1 && coluna <= 7)){
            moverCursor(21, 2);

            printf("Opcao errada! Escolha uma coluna de 1 a 7: ");
            scanf("%d", &coluna);
        }
        

        while(!(atualizarTabela(vez, (coluna-1)))){
            moverCursor(21, 2);
            printf("Coluna cheia, selecione outra coluna: ");
            scanf("%d", &coluna);
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

void modoJogadorJogador(Jogador jogador1,  Jogador jogador2){
    int vez = 1;
    
    while(1){
        int vencedor = 0;

        printVez(jogador1, jogador2, vez);

        printTabela(jogador1, jogador2);

        capturarJogada(vez, 0);

        printTabela(jogador1, jogador2);

        vencedor = analisarTabela();

        if(vencedor){
            moverCursor(21, 2);
            
            switch (vencedor){
                case 1:
                    printf("Jogo terminou! Vencedor: %s\n", jogador1.nome);
                    break;
                
                case 2:
                    printf("Jogo terminou! Vencedor: %s\n", jogador2.nome);
                    break;

                case 3:
                    printf("Jogo terminou! Empate!\n");
                    break;
            }
            
            break;
        }

        if(vez == 1 ){
            vez=2;
        }else{
            vez=1;
        }

        limparTela();
    }
}

int main(){ //programa principal
    Jogador jogador1;
    Jogador jogador2;

    limparTela();

    int escolha = menuInicial();//chama o menu inicial e salva a escolha do usuario

    limparTela();

    //Uma adaptação melhor do que if, else
    switch (escolha){
        case 1:
            //se o usuario escolheu o modo jogador vs jogador

            jogador1 = jogador("JOGADOR1", 0); //captura o primeiro jogador
            limparTela();
            jogador2 = jogador("JOGADOR2", jogador1.cor); //captura o segundo jogador

            limparTela();

            modoJogadorJogador(jogador1, jogador2);
            break;
    }
    
}