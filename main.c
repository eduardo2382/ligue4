#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "modules/terminal.h"
#include "modules/menu.h"
#include "modules/tabela.h"
#include "modules/jogada.h"
#include "modules/computador.h"

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

//Modificação utilizando typedef para deixar o codigo mais limpo.
typedef struct{
    char nome[128];
    int cor;
} Jogador;


int cores[] = {
    VERMELHO,
    VERDE,
    AMARELO,
    AZUL,
    MAGENTA,
    CIANO
};

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
    while(!(scanf("%d", &escolhaCor))){
        //loop caso a entrada tenha sido em formato invalido
        moverCursor(7, 1);
        limparLinha(7);
        scanf("%*[^\n]"); // codigo para descartar a linha bugada
        printf("Opcao invalida, selecione uma opcao valida: ");
    }

    switch (escolhaCor){
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
        moverCursor(7, 1);
        limparLinha(7);
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

    limparLinha(6);

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

int modoJogadorJogador(){
    int vez = 1;

    Jogador jogador1;
    Jogador jogador2;

    jogador1 = jogador("JOGADOR1", 0); //captura o primeiro jogador
    limparTela();
    jogador2 = jogador("JOGADOR2", jogador1.cor); //captura o segundo jogador
    limparTela();

    
    while(1){
        int vencedor = 0;

        printVez(jogador1, jogador2, vez);

        printTabela(jogador1.cor, jogador2.cor);

        capturarJogada(vez, 0);

        printTabela(jogador1.cor, jogador2.cor);

        vencedor = analisarTabela();

        if(vencedor){
            limparLinha(21);
            
            switch (vencedor){
                case 1:
                    moverCursor(21, 23);
                    printf("Jogo terminou! Vencedor: ");
                    mudarEstilo(ESTILO_REVERSO, jogador1.cor);
                    printf("%s\n", jogador1.nome);
                    resetarCor();

                    break;
                
                case 2:
                    moverCursor(21, 23);
                    printf("Jogo terminou! Vencedor: ");
                    mudarEstilo(ESTILO_REVERSO, jogador2.cor);
                    printf("%s\n", jogador2.nome);
                    resetarCor();

                    break;

                case 3:
                    moverCursor(21, 27);
                    printf("Jogo terminou em ");
                    mudarEstilo(ESTILO_REVERSO, ESTILO_NEGRITO);
                    printf("empate!\n");
                    resetarCor();

                    break;
            }
            
            // lAlgoritimo para voltar ao menu
            int aux;
            printf("\nDeseja voltar para o menu principal? (1.Sim 2.Não): ");
            scanf("%d", &aux);
            while(!(scanf("%d", &aux)) || aux != 1 && aux != 2){
                moverCursor(23, 1);
                printf("\033[2K"); // codigo ansii para limpar a linha
                scanf("%*[^\n]"); // codigo para descartar a linha bugada
                printf("Resposta invalida, digite a opção correta (1.Sim 2.Não): ");
            }
            return (aux == 1);
        }

        if(vez == 1){
            vez=2;
        }else{
            vez=1;
        }

        limparTela();
    }
}

int modoComputadorJogador(){
    int nivel = menuComputador(); // exibe o menu de niveis e captura a escolha do usuario
    int vez = 1;

    Jogador jogador1;

    limparTela();

    jogador1 = jogador("JOGADOR1", 0);
    limparTela();

    int corComp = jogador1.cor;

    while(corComp == jogador1.cor){
        corComp = (rand() % 5) + 31;
    }

    Jogador computador = {"computador", corComp};

    while(1){
        int vencedor = 0;

        printVez(jogador1, computador, vez);

        printTabela(jogador1.cor, computador.cor);

        switch (vez){
            case 1:
                capturarJogada(1, 0);
                break;
        
            case 2:{
                    int comp = 0;
                    switch (nivel){
                        case 1:
                            comp = jogadaFacil(2);
                            break;
                        case 2:
                            comp = jogadaMedia(2);
                            break;
                        case 3:
                            comp = jogadaDificil(2);
                    }
                    if(!comp){
                        // Garante que o computador não pule a jogada para o jogador(gambiarra pq o computador não estava jogndo em alguns momentos)
                        jogadaFacil(2);
                }
                break;
            }
        }

        printTabela(jogador1.cor, computador.cor);

        vencedor = analisarTabela();

        if(vencedor){
            limparLinha(21);
            
            switch (vencedor){
                case 1:
                    moverCursor(21, 23);
                    printf("Jogo terminou! Vencedor: ");
                    mudarEstilo(ESTILO_REVERSO, jogador1.cor);
                    printf("%s\n", jogador1.nome);
                    resetarCor();

                    break;
                
                case 2:
                    moverCursor(21, 23);
                    printf("Jogo terminou! Vencedor: ");
                    mudarEstilo(ESTILO_REVERSO, computador.cor);
                    printf("%s\n", computador.nome);
                    resetarCor();

                    break;

                case 3:
                    moverCursor(21, 27);
                    printf("Jogo terminou em ");
                    mudarEstilo(ESTILO_REVERSO, ESTILO_NEGRITO);
                    printf("empate!\n");
                    resetarCor();

                    break;
            }
            
            //Algoritimo para voltar ao menu
            int aux;
            printf("\nDeseja voltar para o menu principal? (1.Sim 2.Não): ");
            while(!(scanf("%d", &aux)) || aux != 1 && aux != 2){
                moverCursor(23, 1);
                printf("\033[2K"); // codigo ansii para limpar a linha
                scanf("%*[^\n]"); // codigo para descartar a linha bugada
                printf("Resposta invalida, digite a opção correta (1.Sim 2.Não): ");
            }
            return (aux == 1);
        }

        if(vez == 1){
            vez=2;
        }else{
            vez=1;
        }

        limparTela();
    }
}

int modoComputadorComputador(){
    srand(time(NULL));
    int vez = 1;

    titulo("COMPUTADOR1", 11, 4);
    int nivelComp1 = menuComputador();
    //recebe o nivel do computador1

    int corComp1 = (rand() % 6) + 31; // escolhe uma cor para o computador1
    Jogador computador1 = {"computador1", corComp1}; // cria uma struct jogador para o computador1

    limparTela();

    titulo("COMPUTADOR2", 11, 4);
    int nivelComp2 = menuComputador();
    //recebe o nivel do computador2

    //resolvendo bug visual
    limparTela();


    int corComp2 = corComp1;

    while(corComp2 == corComp1){ //enquanto a cor do computador2 for igual a do computador1 escolhe outra cor
        corComp2 = (rand() % 6) + 31;
    }

    Jogador computador2 = {"computador2", corComp2}; //cria uma struct jogador para o computador2

    while(1){
        int vencedor = 0;

        printVez(computador1, computador2, vez);

        printTabela(computador1.cor, computador2.cor);

        switch (vez){
            case 1:{
                int flag = 0;
                // jogada do computador1
                switch(nivelComp1){
                    case 1:
                    flag = jogadaFacil(1);
                    break;
                    case 2:
                    flag = jogadaMedia(1);
                    break;
                    case 3:
                    flag = jogadaDificil(1);
                    break;
                }
                if(!flag){
                    jogadaFacil(1);
                }
                break;
                
            }
            case 2:{
                //joada do computador dois
                int flag = 0;
                switch(nivelComp2){
                    case 1:
                    flag = jogadaFacil(2);
                    break;
                    case 2:
                    flag = jogadaMedia(2);
                    break;
                    case 3:
                    flag = jogadaDificil(2);
                    break;
                }
                if(!flag){
                    jogadaFacil(2);
                }
            }
                break;
        }

        printTabela(computador1.cor, computador2.cor);
        //Pausa no terminal para dar tempo das jogadas
        //-------------
        vencedor = analisarTabela();

        if(vencedor){
            limparLinha(21);
            
            switch (vencedor){
                case 1:
                    moverCursor(21, 23);
                    printf("Jogo terminou! Vencedor: ");
                    mudarEstilo(ESTILO_REVERSO, computador1.cor);
                    printf("%s\n", computador1.nome);
                    resetarCor();
                    break;          
                case 2:
                    moverCursor(21, 23);
                    printf("Jogo terminou! Vencedor: ");
                    mudarEstilo(ESTILO_REVERSO, computador2.cor);
                    printf("%s\n", computador2.nome);
                    resetarCor();
                    break;
                case 3:
                    moverCursor(21, 27);
                    printf("Jogo terminou em ");
                    mudarEstilo(ESTILO_REVERSO, ESTILO_NEGRITO);
                    printf("empate!\n");
                    resetarCor();
                    break;
                }

                //algoritimo que retorna ao menu principal:
                int aux;
                printf("\nDeseja voltar para o menu principal? (1.Sim 2.Não): ");
                while(!(scanf("%d", &aux)) || aux != 1 && aux != 2){
                    moverCursor(23, 1);
                    printf("\033[2K"); // codigo ansii para limpar a linha
                    scanf("%*[^\n]"); // codigo para descartar a linha bugada
                    printf("Resposta invalida, digite a opção correta (1.Sim 2.Não): ");
                }
                return (aux == 1);
            }
            

        if(vez == 1){
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
    int flag = 0;
    do{
        zerarJogadas();
        limparTela();
    
        int escolha = menuInicial();//chama o menu inicial e salva a escolha do usuario
    
        limparTela();
    
        //Uma adaptação melhor do que if, else
        switch (escolha){
            case 1:
                //se o usuario escolheu o modo jogador vs jogador
    
                flag = modoJogadorJogador();
                break;
    
            case 2:
                //se o usuario escolheu o modo computador vs jogador
    
                flag = modoComputadorJogador();
                break;
    
            case 3:
                //se o usuario escolheu o modo computador vs computador
    
                flag = modoComputadorComputador();
                break;
            case 4:
                // Encerrar o jogo:
                printf("\nFim de jogo!");
                return 0;
        }
        if(flag == 0){
            limparTela();
            printf("\nFim de jogo!");
        }
        
    }while (flag);

    } 
    