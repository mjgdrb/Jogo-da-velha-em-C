#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

char tabuleiro[3][3];
bool parar = false;
char rodada = 'X';
int jogadas = 0;
int linha = 0;
int coluna = 0;
int tempoPc = 1500; 
int tempoLeitura = 1200;

void iniciarTabuleiro(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarTabuleiro(){
    printf("\n   1   2   3\n");
    for(int i = 0; i < 3; i++){
        printf("%d ", i+1);
        for(int j = 0; j < 3; j++){
            printf("[%c] ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void validarVitoria(char r){
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == r && tabuleiro[i][1] == r && tabuleiro[i][2] == r) parar = true;
        if (tabuleiro[0][i] == r && tabuleiro[1][i] == r && tabuleiro[2][i] == r) parar = true;
    }
    if (tabuleiro[0][0] == r && tabuleiro[1][1] == r && tabuleiro[2][2] == r) parar = true;
    if (tabuleiro[0][2] == r && tabuleiro[1][1] == r && tabuleiro[2][0] == r) parar = true;

    if (parar) {
        system("cls"); // Limpa para mostrar o tabuleiro final
        mostrarTabuleiro();
        if (r == 'X') {
            printf("\n==== VOCE (X) VENCEU! ====\n");
        } else {
            printf("\n==== O COMPUTADOR (O) VENCEU! ====\n");
        }
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    iniciarTabuleiro();
    srand(time(NULL));
    
    while(!parar){
        system("cls"); // Mantém o terminal limpo a cada jogada
        mostrarTabuleiro();

        if(rodada == 'X'){
            printf("\n=> Seu turno (X)!\n");

            printf("Insira a linha: ");
            scanf("%d", &linha);
            linha -= 1;

            printf("Insira a coluna: ");
            scanf("%d", &coluna);
            coluna -= 1;

            if((linha < 0) || (linha > 2) || (coluna < 0) || (coluna > 2)){
                printf("\n=== POSICAO INVALIDA ===\n");
                Sleep(tempoLeitura); // Dá tempo do jogador ler o aviso antes de limpar a tela
                continue;
            }
            if(tabuleiro[linha][coluna] != ' '){
                printf("\n=== POSICAO JA OCUPADA ===\n");
                Sleep(tempoLeitura);
                continue;
            }
        }
        else {
            printf("\n=> Turno do Computador (O)...\n");
            Sleep(tempoPc);

            do{
                linha = rand() % 3;
                coluna = rand() % 3;
            }while(tabuleiro[linha][coluna] != ' ');
        }

        tabuleiro[linha][coluna] = rodada;
        jogadas++;

        validarVitoria(rodada);

        if(parar){
            break;
        }

        if(jogadas == 9){
            system("cls");
            mostrarTabuleiro();
            printf("\n==== EMPATE! ====\n");
            break;
        }

        rodada = (rodada == 'X') ? 'O' : 'X';
    }
    
    return 0;
}
