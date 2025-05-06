#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define SHIP_SIZE   3
#define WATER        0
#define SHIP         3
#define EFFECT       5

int main() {
    //--- 1) Inicializa o tabuleiro 10×10 com água (0) ---
    int board[BOARD_SIZE][BOARD_SIZE];
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = WATER;
        }
    }

    //--- 2) Posiciona quatro navios de tamanho 3 (do desafio anterior) ---
    //formato: place_ship(linha_inicio, col_inicio, delta_linha, delta_coluna)
    void place_ship(int sr, int sc, int dr, int dc) {
        //verifica sobreposição
        for (int i = 0; i < SHIP_SIZE; i++) {
            int rr = sr + dr * i;
            int cc = sc + dc * i;
            if (rr < 0 || rr >= BOARD_SIZE || cc < 0 || cc >= BOARD_SIZE
             || board[rr][cc] != WATER) {
                fprintf(stderr, "Erro ao posicionar navio em (%d,%d)\n", rr, cc);
                exit(EXIT_FAILURE);
            }
        }
        //marca o navio
        for (int i = 0; i < SHIP_SIZE; i++) {
            board[sr + dr * i][sc + dc * i] = SHIP;
        }
    }
    //a) horizontal em (1,2)
    place_ship(1, 2, 0, 1);
    //b) vertical em (5,7)
    place_ship(5, 7, 1, 0);
    //c) diagonal ↘ em (3,0)
    place_ship(3, 0, 1, 1);
    //d) diagonal ↙ em (6,9)
    place_ship(6, 9, 1,-1);

    //--- 3) Define tamanho e centro das matrizes de habilidade ---
    const int SKILL_SIZE = 5;
    const int MID = SKILL_SIZE / 2;

    int cone   [SKILL_SIZE][SKILL_SIZE];
    int cross  [SKILL_SIZE][SKILL_SIZE];
    int diamond[SKILL_SIZE][SKILL_SIZE];

    //--- 4) Constrói dinamicamente cada matriz de habilidade ---
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            //CONE: abs(j–MID) <= i ?
            if (abs(j - MID) <= i)  cone[i][j] = 1;
            else                    cone[i][j] = 0;

            //CRUZ: i==MID ou j==MID ?
            if (i == MID || j == MID)  cross[i][j] = 1;
            else                        cross[i][j] = 0;

            //OCTAEDRO (diamond): abs(i–MID)+abs(j–MID) <= MID ?
            if (abs(i - MID) + abs(j - MID) <= MID)  diamond[i][j] = 1;
            else                                     diamond[i][j] = 0;
        }
    }

    //--- 5) Pontos de origem no tabuleiro para cada habilidade ---
    int coneR   = 2, coneC   = 2;
    int crossR  = 5, crossC  = 5;
    int diamR   = 7, diamC   = 3;

    //--- 6) Sobrepõe cada área de efeito no tabuleiro ---
    //marcando com EFFECT (5)
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            int dr = i - MID;
            int dc = j - MID;

            //Cone
            if (cone[i][j]) {
                int rr = coneR + dr, cc = coneC + dc;
                if (rr >= 0 && rr < BOARD_SIZE && cc >= 0 && cc < BOARD_SIZE)
                    board[rr][cc] = EFFECT;
            }

            //Cruz
            if (cross[i][j]) {
                int rr = crossR + dr, cc = crossC + dc;
                if (rr >= 0 && rr < BOARD_SIZE && cc >= 0 && cc < BOARD_SIZE)
                    board[rr][cc] = EFFECT;
            }

            //Octaedro
            if (diamond[i][j]) {
                int rr = diamR + dr, cc = diamC + dc;
                if (rr >= 0 && rr < BOARD_SIZE && cc >= 0 && cc < BOARD_SIZE)
                    board[rr][cc] = EFFECT;
            }
        }
    }

    //--- 7) Exibe o tabuleiro final:
    //0 = água, 3 = navio, 5 = área de efeito ---
    printf("Tabuleiro com Navios (3) e Áreas de Efeito (5):\n\n");
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            printf("%d ", board[r][c]);
        }
        printf("\n");
    }

    return 0;
}
