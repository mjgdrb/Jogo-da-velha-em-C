#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>


char tabuleiro[3][3] = {{' ',' ',' '},
                        {' ',' ',' '},
                        {' ',' ',' '}};

bool parar = false;

char rodada = 'X';

int jogadas = 0;

int linha = 0;

int coluna = 0;

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
    if ((tabuleiro[0][0] == r && tabuleiro[0][1] == r && tabuleiro[0][2] == r) ||
        (tabuleiro[1][0] == r && tabuleiro[1][1] == r && tabuleiro[1][2] == r) ||
        (tabuleiro[2][0] == r && tabuleiro[2][1] == r && tabuleiro[2][2] == r) ||
        (tabuleiro[0][0] == r && tabuleiro[1][0] == r && tabuleiro[2][0] == r) || 
        (tabuleiro[0][1] == r && tabuleiro[1][1] == r && tabuleiro[2][1] == r) ||
        (tabuleiro[0][2] == r && tabuleiro[1][2] == r && tabuleiro[2][2] == r) || 
        (tabuleiro[0][0] == r && tabuleiro[1][1] == r && tabuleiro[2][2] == r) ||
        (tabuleiro[0][2] == r && tabuleiro[1][1] == r && tabuleiro[2][0] == r)){

        mostrarTabuleiro();   
        
        if(r == 'X'){
            printf("\n==== VOCE VENCEU! ====\n");
        }
        else{
            printf("\n==== COMPUTADOR VENCEU! ====\n");
        }
        parar = true;
    }
}


int main(){
    SetConsoleOutputCP(CP_UTF8);

    srand(time(NULL));
    
    while(!parar){
        mostrarTabuleiro();

        if(rodada == 'X'){

            printf("\n=> Seu turno (X)!\n");

            printf("\nInsira a linha: ");
            scanf("%d", &linha);

            linha-=1;

            printf("\nInsira a coluna: ");
            scanf("%d", &coluna);

            coluna-=1;

            if((tabuleiro[linha][coluna] != ' ') || (linha < 0) || (linha > 2) || (coluna < 0) ||( coluna > 2)){
                printf("\n=== POSICAO INVALIDA OU JA OCUPADA ===\n");
                continue;
            }
        }
        else{
            printf("\n=> Turno do Computador (O)!\n");
            Sleep(2000);

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
            mostrarTabuleiro();
            printf("\n==== EMPATE! ====\n");
            break;
        }

        rodada = (rodada == 'X') ? 'O' : 'X';
    }
    
    return 0;
}