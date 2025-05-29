#include <stdio.h>

#define TAM 10
#define MAX_NAVIOS 10

typedef struct {
    int tamanho;
    int vida;
} Navio;

typedef struct {
    char mapa[TAM][TAM];
    Navio navios[MAX_NAVIOS];
    int total_navios;
} Jogador;

const int NUM_NAVIOS = 6;
const int NAVIOS_TAMANHOS[MAX_NAVIOS] = {4, 3, 1, 1, 1, 2};

Jogador inicializar_tabuleiro() {
    Jogador j;
    j.total_navios = NUM_NAVIOS;
    for (int i = 0; i < TAM; i++)
        for (int k = 0; k < TAM; k++)
            j.mapa[i][k] = ' ';
    for (int i = 0; i < NUM_NAVIOS; i++) {
        j.navios[i].tamanho = NAVIOS_TAMANHOS[i];
        j.navios[i].vida = NAVIOS_TAMANHOS[i];
    }
    return j;
}

void mostrar_tabuleiro(Jogador j, int mostrar_navios) {
    printf("   ");
    for (int i = 0; i < TAM; i++) printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int k = 0; k < TAM; k++) {
            char c = j.mapa[i][k];
            if (!mostrar_navios && c == 'N') c = ' ';
            printf("[%c]", c);
        }
        printf("\n");
    }
}

Jogador posicionar_navio(Jogador j, int idx, int x, int y, char direcao, int* sucesso) {
    int tam = j.navios[idx].tamanho;
    *sucesso = 1;
    for (int i = 0; i < tam; i++) {
        int nx = x + (direcao == 'V' ? i : 0);
        int ny = y + (direcao == 'H' ? i : 0);
        if (nx >= TAM || ny >= TAM || j.mapa[nx][ny] != ' ') {
            *sucesso = 0;
            return j;
        }
    }
    for (int i = 0; i < tam; i++) {
        int nx = x + (direcao == 'V' ? i : 0);
        int ny = y + (direcao == 'H' ? i : 0);
        j.mapa[nx][ny] = 'N';
    }
    return j;
}

Jogador atirar(Jogador j, int x, int y, int* resultado) {
    *resultado = -1;
    if (x < 0 || x >= TAM || y < 0 || y >= TAM) return j;

    if (j.mapa[x][y] == 'N') {
        j.mapa[x][y] = '0';
        for (int i = 0; i < j.total_navios; i++) {
            if (j.navios[i].vida > 0) {
                j.navios[i].vida--;
                break;
            }
        }
        *resultado = 1;
    } else if (j.mapa[x][y] == ' ') {
        j.mapa[x][y] = 'X';
        *resultado = 0;
    }
    return j;
}

int navios_restantes(Jogador j) {
    int vivos = 0;
    for (int i = 0; i < j.total_navios; i++)
        if (j.navios[i].vida > 0)
            vivos++;
    return vivos;
}

Jogador posicionar_todos_navios(Jogador j, int id) {
    printf("\n======== POSICIONAMENTO: JOGADOR %d ========\n", id);
    for (int i = 0; i < j.total_navios; i++) {
        int x, y, sucesso;
        char d;
        mostrar_tabuleiro(j, 1);
        printf("Navio %d (tamanho %d):\n", i + 1, j.navios[i].tamanho);
        do {
            printf("Digite linha coluna e direção (H ou V): ");
            scanf("%d %d %c", &x, &y, &d);
            j = posicionar_navio(j, i, x, y, d, &sucesso);
        } while (!sucesso);
    }
    return j;
}

void jogar_com_menu(Jogador j1, Jogador j2) {
    int turno = 0;
    while (navios_restantes(j1) > 0 && navios_restantes(j2) > 0) {
        int id = (turno % 2 == 0) ? 1 : 2;
        printf("\n===== TURNO DO JOGADOR %d =====\n", id);
        int opcao, jogou = 0;

        while (!jogou) {
            printf("\nMenu:\n");
            printf("1 - Mostrar meu tabuleiro\n");
            printf("2 - Mostrar tabuleiro do oponente\n");
            printf("3 - Atirar\n");
            printf("4 - Sair do jogo\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            if (opcao == 1) {
                printf("\n--- Seu Tabuleiro ---\n");
                mostrar_tabuleiro((id == 1) ? j1 : j2, 1);
            } else if (opcao == 2) {
                printf("\n--- Tabuleiro do Oponente ---\n");
                mostrar_tabuleiro((id == 1) ? j2 : j1, 0);
            } else if (opcao == 3) {
                int x, y, res;
                printf("Digite coordenadas para atirar (linha coluna): ");
                scanf("%d %d", &x, &y);
                if (id == 1) {
                    j2 = atirar(j2, x, y, &res);
                } else {
                    j1 = atirar(j1, x, y, &res);
                }
                if (res == 1) printf("ACERTOU um navio!\n");
                else if (res == 0) printf("Errou o tiro.\n");
                else printf("Tiro inválido ou repetido. Tente novamente.\n");
                if (res != -1) jogou = 1;
            } else if (opcao == 4) {
                printf("Encerrando o jogo.\n");
                return;
            } else {
                printf("Opção inválida!\n");
            }
        }
        turno++;
    }

    if (navios_restantes(j1) == 0)
        printf("\nJOGADOR 2 venceu a batalha naval!\n");
    else
        printf("\nJOGADOR 1 venceu a batalha naval!\n");
}

int main() {
    Jogador j1 = inicializar_tabuleiro();
    Jogador j2 = inicializar_tabuleiro();

    j1 = posicionar_todos_navios(j1, 1);
    j2 = posicionar_todos_navios(j2, 2);

    jogar_com_menu(j1, j2);

    return 0;
}
