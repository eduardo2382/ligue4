#ifndef TABELA_H
#define TABELA_H

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

void printTabela(int corJogador1, int corJogador2);
int atualizarTabela(int vez, int coluna);
int analisarLinhas();
int analisarColunas();
int analisarDiagonal();
int analisarEmpate();
int analisarTabela();
int analiseCompHorizontal();
int analiseCompVertical();
int analiseCompDiagonal();
int analiseAtaqueVertical();
int analiseAtaqueHorizontal();
int analiseAtaqueDiagonal();
#endif