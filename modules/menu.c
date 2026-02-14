#include "terminal.h"
#include "menu.h"
#include <stdio.h>

char escolhasMenuInic[4][24] = {
    "Jogador vs Jogador",
    "Jogador vs Computador",
    "Computador vs Computador",
    "Sair do Jogo"
};

char escolhasMenuComp[3][14] = {
    "Nivel Facil",
    "Nivel Medio",
    "Nivel Dificil"
};

void printMenuInicial(){
    //escreve o menu inicial na tela
    int linhaInicial = 5; 
    int colunaInicial = (80-30)/2;
    int tamLista = sizeof(escolhasMenuInic) / sizeof(escolhasMenuInic[0]);
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
                if(escolhasMenuInic[l-1][k] != '\0'){
                    printf("%c", escolhasMenuInic[l-1][k]); //imprime o carac
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
    int tamLista = sizeof(escolhasMenuInic) / sizeof(escolhasMenuInic[0]);
        
    printMenuInicial();//imprime o menu

    moverCursor(12, 2);

    printf("Digite o numero da sua escolha: ");
    while(!(scanf("%d", &escolha)) || !(escolha >= 1 && escolha <= tamLista)){ //caso a escolha nao esteja de acordo pede pro usuario repetir ate que alguma valida seja selecionada
        moverCursor(12, 2);
        printf("\033[2K"); // codigo ansii para limpar a linha
        scanf("%*[^\n]"); // codigo para descartar a linha bugada
        printf("Opcao errada, digite novamente: ");
        
    }

    return escolha;//retorna a escolha para o programa principal
}

void printMenuComputador(){
    limparTela();

    //escreve o menu dos niveis na tela
    int linhaInicial = 5; 
    int colunaInicial = (80-20)/2;
    int tamLista = sizeof(escolhasMenuComp) / sizeof(escolhasMenuComp[0]);
    int quantLinhas = tamLista + 2; //quantidade total de linhas do menu(items da lista + topo e fim)

    for(int l = 0; l < quantLinhas; l++){ //cada linha do menu
        moverCursor(linhaInicial+l, colunaInicial);// move o cursor para a linha atual e coluna

        if(l == 0 || l == (quantLinhas-1)){
            //se for a primeira ou ultima linha imprime a linha padrao
            printf(" ------------------\n");
        }else{
            //imprime a linha de cada item com o numero de opcao no inicio
            printf("| %d.", l); 

            for(int k = 0; k < 14; k++){
                //percorre cada carac da string
                if(escolhasMenuComp[l-1][k] != '\0'){
                    printf("%c", escolhasMenuComp[l-1][k]); //imprime o carac
                }else{
                    printf(" "); //quando é vazio imprime um carac vazio para poder completar a linha
                }
            }
            printf(" |\n");//finaliza a linha dessa opcao
        }
    }


    printf("\n");
}

int menuComputador(){
    //funcao responsavel por chamar a funcao que imprime e por capturar a escolha do usuario

    printf("ola");

    int escolha = 0;
    int tamLista = sizeof(escolhasMenuComp) / sizeof(escolhasMenuComp[0]);
        
    printMenuComputador();//imprime o menu

    moverCursor(12, 2);

    printf("Digite o numero da sua escolha: ");
    while(!(scanf("%d", &escolha)) || !(escolha >= 1 && escolha <= tamLista)){ //caso a escolha nao esteja de acordo pede pro usuario repetir ate que alguma valida seja selecionada
        moverCursor(12, 2);
        printf("\033[2K"); // codigo ansii para limpar a linha
        scanf("%*[^\n]"); // codigo para descartar a linha bugada
        printf("Opcao errada, digite novamente: ");
        
    }

    return escolha;//retorna a escolha para o programa principal
}