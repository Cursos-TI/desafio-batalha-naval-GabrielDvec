#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define SHIP_SIZE   3
#define WATER       0
#define SHIP        3

int main() {
    //1) Inicializa o tabuleiro 10x10 com água (0)
    int board[BOARD_SIZE][BOARD_SIZE];
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = WATER;
        }
    }

    //2) Define coordenadas iniciais dos navios (sem input do usuário)
    //a) Navio horizontal de tamanho 3, começando em (linha, coluna) = (1, 2)
    int hRow = 1;
    int hCol = 2;
    //b) Navio vertical de tamanho 3, começando em (linha, coluna) = (5, 7)
    int vRow = 5;
    int vCol = 7;

    // 3) Valida se cabem dentro dos limites do tabuleiro
    //Para horizontal: coluna inicial + SHIP_SIZE - 1 < BOARD_SIZE
    if (hRow < 0 || hRow >= BOARD_SIZE ||
        hCol < 0 || hCol + SHIP_SIZE - 1 >= BOARD_SIZE) {
        fprintf(stderr, "Erro: navio horizontal fora dos limites do tabuleiro.\n");
        return EXIT_FAILURE;
    }
    //Para vertical: linha inicial + SHIP_SIZE - 1 < BOARD_SIZE
    if (vCol < 0 || vCol >= BOARD_SIZE ||
        vRow < 0 || vRow + SHIP_SIZE - 1 >= BOARD_SIZE) {
        fprintf(stderr, "Erro: navio vertical fora dos limites do tabuleiro.\n");
        return EXIT_FAILURE;
    }

    //4) Verifica sobreposição: nenhuma posição dos navios deve já estar ocupada
    //a) Verifica navio horizontal
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (board[hRow][hCol + i] != WATER) {
            fprintf(stderr, "Erro: sobreposição detectada para navio horizontal.\n");
            return EXIT_FAILURE;
        }
    }
    //b) Verifica navio vertical
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (board[vRow + i][vCol] != WATER) {
            fprintf(stderr, "Erro: sobreposição detectada para navio vertical.\n");
            return EXIT_FAILURE;
        }
    }

    //5) Posiciona os navios no tabuleiro (marca com 3)
    //a) Navio horizontal
    for (int i = 0; i < SHIP_SIZE; i++) {
        board[hRow][hCol + i] = SHIP;
    }
    //b) Navio vertical
    for (int i = 0; i < SHIP_SIZE; i++) {
        board[vRow + i][vCol] = SHIP;
    }

    //6) Exibe o tabuleiro no console
    printf("Tabuleiro de Batalha Naval (0 = agua, 3 = navio):\n\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf("%d ", board[row][col]);
        }
        printf("\n");
    }

    return 0;
}
