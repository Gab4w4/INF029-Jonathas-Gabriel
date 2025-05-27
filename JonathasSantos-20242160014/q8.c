#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

char tab[3][3], j='X';

void limpar() { for(int i=0;i<3;i++) for(int k=0;k<3;k++) tab[i][k]=' '; }
void mostrar() {
    printf("\n  1 2 3\n");
    for(int i=0;i<3;i++) {
        printf("%c ", 'A'+i);
        for(int k=0;k<3;k++) printf("%c%c",tab[i][k],k<2?'|':' ');
        if(i<2) printf("\n  -----\n");
    }
    printf("\n");
}

int ganhou(char c) {
    for(int i=0;i<3;i++) 
        if((tab[i][0]==c&&tab[i][1]==c&&tab[i][2]==c)||(tab[0][i]==c&&tab[1][i]==c&&tab[2][i]==c)) 
            return 1;
    return (tab[0][0]==c&&tab[1][1]==c&&tab[2][2]==c)||(tab[0][2]==c&&tab[1][1]==c&&tab[2][0]==c);
}

int cheio() { for(int i=0;i<3;i++) for(int k=0;k<3;k++) if(tab[i][k]==' ') return 0; return 1; }

void jogar() {
    char p[3]; int l,c;
    while(1) {
        printf("Jogador %c (ex: B2): ",j);
        scanf("%2s",p);
        l=toupper(p[0])-'A';
        c=p[1]-'1';
        if(l>=0&&l<3&&c>=0&&c<3&&tab[l][c]==' ') break;
        printf("Invalido! ");
    }
    tab[l][c]=j;
}

void computador() {
    int l,c;
    // Tenta ganhar ou bloquear
    for(l=0;l<3;l++) for(c=0;c<3;c++) 
        if(tab[l][c]==' ') {
            tab[l][c]=j;
            if(ganhou(j)) return;
            tab[l][c]=' ';
            
            tab[l][c]=j=='X'?'O':'X';
            if(ganhou(j=='X'?'O':'X')) { tab[l][c]=j; return; }
            tab[l][c]=' ';
        }
    // Jogada aleatória
    do { l=rand()%3; c=rand()%3; } while(tab[l][c]!=' ');
    tab[l][c]=j;
}

int main() {
    int modo,dif=0; char r;
    srand(time(0));
    
    printf("1-PvP\n2-PvC\nModo: ");
    scanf("%d",&modo);
    if(modo==2) { printf("1-Facil\n2-Dificil\nDificuldade: "); scanf("%d",&dif); }
    
    do {
        limpar();
        while(1) {
            mostrar();
            if(modo==2&&j=='O') { printf("PC joga:\n"); computador(); }
            else jogar();
            
            if(ganhou(j)) { mostrar(); printf("%c venceu!\n",j); break; }
            if(cheio()) { mostrar(); printf("Empate!\n"); break; }
            j=j=='X'?'O':'X';
        }
        printf("Jogar novamente? (S/N): ");
        scanf(" %c",&r);
    } while(toupper(r)=='S');
    
    return 0;
}