#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Exemplo: adiciona alguns navios (3) no tabuleiro
    tabuleiro[2][2] = 3;
    tabuleiro[3][3] = 3;
    tabuleiro[4][4] = 3;
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ "); // água
            } else if (tabuleiro[i][j] == 3) {
                printf("N "); // navio
            } else if (tabuleiro[i][j] == 5) {
                printf("* "); // área afetada
            } else {
                printf("? "); // erro/debug
            }
        }
        printf("\n");
    }
}

// Função para criar a matriz de habilidade em cone (5x5)
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= 2 - i && j <= 2 + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em cruz (5x5)
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == 2 || j == 2) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em octaedro (5x5)
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemX, int origemY) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int tabX = origemX - TAM_HABILIDADE / 2 + i;
            int tabY = origemY - TAM_HABILIDADE / 2 + j;

            if (tabX >= 0 && tabX < TAM_TABULEIRO && tabY >= 0 && tabY < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[tabX][tabY] == 0) {
                    tabuleiro[tabX][tabY] = 5; // marca como afetado
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidade[TAM_HABILIDADE][TAM_HABILIDADE];
    int escolha, x, y;

    inicializarTabuleiro(tabuleiro);

    printf("=== SELECIONE UMA HABILIDADE ===\n");
    printf("1 - Cone\n");
    printf("2 - Cruz\n");
    printf("3 - Octaedro\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            criarCone(habilidade);
            break;
        case 2:
            criarCruz(habilidade);
            break;
        case 3:
            criarOctaedro(habilidade);
            break;
        default:
            printf("Habilidade inválida!\n");
            return 1;
    }

    printf("Digite a coordenada de origem (linha coluna): ");
    scanf("%d %d", &x, &y);

    aplicarHabilidade(tabuleiro, habilidade, x, y);

    printf("\n=== TABULEIRO FINAL ===\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
