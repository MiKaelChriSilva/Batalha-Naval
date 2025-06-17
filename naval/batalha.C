#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 

#define TAM_TAB 10     
#define TAM_NAVIO 3      
#define TAM_HABILIDADE 5 


#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5


void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]);
bool posicionarNavioHorizontal(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna);
bool posicionarNavioVertical(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna);
bool posicionarNavioDiagonal(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna, bool principal);
void criarHabilidadeCone(int hab[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeCruz(int hab[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeOctaedro(int hab[TAM_HABILIDADE][TAM_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int hab[TAM_HABILIDADE][TAM_HABILIDADE], int centro_linha, int centro_coluna);
void exibirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]);


int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    
    inicializarTabuleiro(tabuleiro);

    
    posicionarNavioHorizontal(tabuleiro, 2, 3);   
    posicionarNavioVertical(tabuleiro, 5, 7);    
    posicionarNavioDiagonal(tabuleiro, 1, 1, true); 
    posicionarNavioDiagonal(tabuleiro, 2, 8, false); 

  
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

   
    aplicarHabilidade(tabuleiro, cone, 4, 4);     
    aplicarHabilidade(tabuleiro, cruz, 7, 2);     
    aplicarHabilidade(tabuleiro, octaedro, 3, 6); 

 
    exibirTabuleiro(tabuleiro);

    return 0;
}


void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}


bool posicionarNavioHorizontal(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha < 0 || linha >= TAM_TAB || coluna + i < 0 || coluna + i >= TAM_TAB || tabuleiro[linha][coluna + i] != AGUA) {
            return false; 
        }
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
    return true;
}


bool posicionarNavioVertical(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha + i < 0 || linha + i >= TAM_TAB || coluna < 0 || coluna >= TAM_TAB || tabuleiro[linha + i][coluna] != AGUA) {
            return false;
        }
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
    return true;
}


bool posicionarNavioDiagonal(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna, bool principal) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i;
        int c = principal ? coluna + i : coluna - i;
        if (l < 0 || l >= TAM_TAB || c < 0 || c >= TAM_TAB || tabuleiro[l][c] != AGUA) {
            return false; 
        }
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i;
        int c = principal ? coluna + i : coluna - i;
        tabuleiro[l][c] = NAVIO;
    }
    return true;
}


void criarHabilidadeCone(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            hab[i][j] = (j >= i && j < TAM_HABILIDADE - i) ? 1 : 0;
        }
    }
}


void criarHabilidadeCruz(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            hab[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}


void criarHabilidadeOctaedro(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int dist = abs(i - centro) + abs(j - centro);
            hab[i][j] = (dist <= centro) ? 1 : 0;
        }
    }
}


void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int hab[TAM_HABILIDADE][TAM_HABILIDADE], int centro_linha, int centro_coluna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int l = centro_linha - offset + i;
            int c = centro_coluna - offset + j;
            if (l >= 0 && l < TAM_TAB && c >= 0 && c < TAM_TAB && hab[i][j] == 1) {
                tabuleiro[l][c] = HABILIDADE;
            }
        }
    }
}


void exibirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("\n=== BATALHA NAVAL ===\n");
    printf("   ");
    for (int j = 0; j < TAM_TAB; j++) printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAM_TAB; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TAB; j++) {
            switch (tabuleiro[i][j]) {
                case AGUA: printf(" ~ "); break;
                case NAVIO: printf(" N "); break;
                case HABILIDADE: printf(" * "); break;
                default: printf(" ? ");
            }
        }
        printf("\n");
    }
}