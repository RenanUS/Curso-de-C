#include <stdio.h>
#include <stdlib.h>

#define TAM 3

char tabuleiro[TAM][TAM];

void inicializarTabuleiro() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarTabuleiro() {
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) printf("---+---+---\n");
    }
    printf("\n");
}

int verificarVitoria() {
    for (int i = 0; i < TAM; i++) {
        if (tabuleiro[i][0] != ' ' &&
            tabuleiro[i][0] == tabuleiro[i][1] &&
            tabuleiro[i][1] == tabuleiro[i][2])
            return 1;

        if (tabuleiro[0][i] != ' ' &&
            tabuleiro[0][i] == tabuleiro[1][i] &&
            tabuleiro[1][i] == tabuleiro[2][i])
            return 1;
    }

    if (tabuleiro[0][0] != ' ' &&
        tabuleiro[0][0] == tabuleiro[1][1] &&
        tabuleiro[1][1] == tabuleiro[2][2])
        return 1;

    if (tabuleiro[0][2] != ' ' &&
        tabuleiro[0][2] == tabuleiro[1][1] &&
        tabuleiro[1][1] == tabuleiro[2][0])
        return 1;

    return 0;
}

int verificarEmpate() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

int jogadaValida(int linha, int coluna) {
    if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM)
        return 0;

    if (tabuleiro[linha][coluna] != ' ')
        return 0;

    return 1;
}

int main() {
    int linha, coluna;
    char jogador = 'X';

    inicializarTabuleiro();

    while (1) {
        mostrarTabuleiro();

        printf("Jogador %c\n", jogador);
        printf("Digite linha e coluna (0-2): ");
        scanf("%d %d", &linha, &coluna);

        if (!jogadaValida(linha, coluna)) {
            printf("Jogada inválida! Tente novamente.\n");
            continue;
        }

        tabuleiro[linha][coluna] = jogador;

        if (verificarVitoria()) {
            mostrarTabuleiro();
            printf("Jogador %c venceu!\n", jogador);
            break;
        }

        if (verificarEmpate()) {
            mostrarTabuleiro();
            printf("Empate!\n");
            break;
        }

        jogador = (jogador == 'X') ? 'O' : 'X';
    }

    return 0;
}