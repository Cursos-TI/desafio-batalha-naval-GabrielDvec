#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define SHIP_SIZE   3
#define WATER        0
#define SHIP         3

int main() {
    //1) Criar e inicializar o tabuleiro 10x10 com água (0)
    int board[BOARD_SIZE][BOARD_SIZE];
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = WATER;
        }
    }

    //2) Definir coordenadas iniciais dos quatro navios (tamanho fixo = 3)
    //a) Horizontal em (1,2) para a direita
    int hRow = 1, hCol = 2;
    //b) Vertical em (5,7) para baixo
    int vRow = 5, vCol = 7;
    //c) Diagonal descendo para a direita, início em (3,0)
    int d1Row = 3, d1Col = 0;
    //d) Diagonal descendo para a esquerda, início em (6,9)
    int d2Row = 6, d2Col = 9;

    //3) Validar limites e sobreposição de todos os navios
    //Helper lambda-like macro para checar dentro do tabuleiro
    #define IN_BOUNDS(r,c) ((r)>=0 && (r)<BOARD_SIZE && (c)>=0 && (c)<BOARD_SIZE)

    //a) horizontal
    if (!IN_BOUNDS(hRow, hCol + SHIP_SIZE - 1)) {
        fprintf(stderr, "Erro: horizontal fora dos limites\n");
        return EXIT_FAILURE;
    }
    //b) vertical
    if (!IN_BOUNDS(vRow + SHIP_SIZE - 1, vCol)) {
        fprintf(stderr, "Erro: vertical fora dos limites\n");
        return EXIT_FAILURE;
    }
    //c) diagonal direita
    if (!IN_BOUNDS(d1Row + SHIP_SIZE - 1, d1Col + SHIP_SIZE - 1)) {
        fprintf(stderr, "Erro: diagonal direita fora dos limites\n");
        return EXIT_FAILURE;
    }
    //d) diagonal esquerda
    if (!IN_BOUNDS(d2Row + SHIP_SIZE - 1, d2Col - (SHIP_SIZE - 1))) {
        fprintf(stderr, "Erro: diagonal esquerda fora dos limites\n");
        return EXIT_FAILURE;
    }

    //Função inline para checar overlap e marcar
    auto place_ship = [&](int r, int c, int dr, int dc) {
        for (int i = 0; i < SHIP_SIZE; i++) {
            int rr = r + dr * i;
            int cc = c + dc * i;
            if (board[rr][cc] != WATER) {
                fprintf(stderr, "Erro: sobreposição em (%d,%d)\n", rr, cc);
                exit(EXIT_FAILURE);
            }
        }
        for (int i = 0; i < SHIP_SIZE; i++) {
            board[r + dr * i][c + dc * i] = SHIP;
        }
    };

    //4) Posicionar cada navio (dr,dc = delta row/col)
    place_ship(hRow, hCol, 0,  1);  //horizontal: mesma linha, col +1
    place_ship(vRow, vCol, 1,  0);  //vertical: row +1, mesma coluna
    place_ship(d1Row, d1Col, 1,  1);  //diagonal direita: row+1,col+1
    place_ship(d2Row, d2Col, 1, -1);  //diagonal esquerda: row+1,col-1

    //5) Exibir o tabuleiro
    printf("Tabuleiro 10x10 (0=agua,3=navio):\n\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf("%d ", board[row][col]);
        }
        printf("\n");
    }

    return 0;
}
