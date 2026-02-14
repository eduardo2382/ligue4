#ifndef TERMINAL_H
#define TERMINAL_H

#define ESTILO_RESET      0
#define ESTILO_NEGRITO    1
#define ESTILO_SUBLINHADO 4
#define ESTILO_REVERSO    7

void mudarEstilo(int estilo,int cor);
void resetarCor();
void moverCursor(int linha, int coluna);
void titulo(char *tit, int tam, int lin);
void limparTela();
void limparLinha(int linha);

#endif