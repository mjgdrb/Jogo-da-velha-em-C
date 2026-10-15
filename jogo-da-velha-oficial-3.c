// DOCUMENTO DE APRESENTACAO DO JOGO:

// Integrantes do grupo: Lucas Lima e Maria Julia Gadelha.
// Regras e funcionamento do jogo: Um espaco de um quadrado 3x3 deve ser ppor um jogador por circulo e pelo outro por x, vence quem fechar 3 simboloes em horizontal, vertical ou diagonal.
//                                Caso o tabuleiro seja preenchido e nao forme essas condicoes, o jogo "velha" ou seja, empata.
// Estrutura de dados: Declaracao de variaveis, condicoes, intervalos de repeticao definidos, repeticoes por condicao, bibliotecas e funcoes.
// Principais Funcoes: iniciar o jogo, mostrar o tabuleiro, jogadad do jogador, jogada da maquina, funcao de validacao de vitoria e a funcao principal.
// Exemplos de execucao: Inicio de jogo, ( interface inicial):
// =======================================
//         ***Jogo da Velha***
//             1   2  3
//           1 [] [] []
//           2 [] [] []
//           3 [] [] []
//           Seu turno(X)!
//           Insira linha:
//           Insira coluna:
// =======================================
// Dificuldades: refletir a primeiro viez as funcionalidades do jogo, separar a ideia geral do jogo em blocos de funcoes e trascricao da ideia para o codigo.
// Solucoes: Trabalho em equipe, dedicacao ao projeto e revisao dos slides e dos materiais didaticos.

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

// VARIÁVEIS
char tabuleiro[3][3];
bool parar = false;
char rodada = 'X';
int jogadas = 0;
int linha = 0;
int coluna = 0;
int tempoPc = 1500; 
int tempoLeitura = 1200;

// ==========================================
// FUNÇÃO DE INICIAR O TABULEIRO
// ==========================================
void iniciarTabuleiro(){
    // Inicia o Tabuleiro com Espaços ' '
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            tabuleiro[i][j] = ' ';
        }
    }
}

// ==========================================
// FUNÇÃO DE MOSTRAR O TABULEIRO
// ==========================================
void mostrarTabuleiro(){
    // Printa o Tabuleiro Organizado
    printf("\n   1   2   3\n");
    for(int i = 0; i < 3; i++){
        printf("%d ", i+1);
        for(int j = 0; j < 3; j++){
            printf("[%c] ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// ==========================================
// FUNÇÃO DE JOGADA DO JOGADOR
// ==========================================
bool jogadaJogador(){
    printf("\n=> Seu turno (X)!\n");

    // Proteção para a linha
    printf("Insira a linha: ");
    if (scanf("%d", &linha) != 1) {
        printf("\n=== ENTRADA INVALIDA! DIGITE APENAS NUMEROS. ===\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        Sleep(tempoLeitura);
        return false;
    }
    linha -= 1;

    // Proteção para a coluna
    printf("Insira a coluna: ");
    if (scanf("%d", &coluna) != 1) {
        printf("\n=== ENTRADA INVALIDA! DIGITE APENAS NUMEROS. ===\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        Sleep(tempoLeitura);
        return false;
    }
    coluna -= 1;

    // Validação de limites
    if((linha < 0) || (linha > 2) || (coluna < 0) || (coluna > 2)){
        printf("\n=== POSICAO INVALIDA ===\n");
        Sleep(tempoLeitura); 
        return false;
    }
    
    // Validação de posição ocupada
    if(tabuleiro[linha][coluna] != ' '){
        printf("\n=== POSICAO JA OCUPADA ===\n");
        Sleep(tempoLeitura);
        return false;
    }
    
    return true;
}

// ==========================================
// FUNÇÃO DE JOGADA DA MÁQUINA
// ==========================================
void jogadaMaquina(){
    printf("\n=> Turno do Computador (O)...\n");
    Sleep(tempoPc);

    do{
        linha = rand() % 3;
        coluna = rand() % 3;
    } while(tabuleiro[linha][coluna] != ' ');
}

// ==========================================
// FUNÇÃO DE VALIDAÇÃO DE VITÓRIA
// ==========================================
void validarVitoria(char r){
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == r && tabuleiro[i][1] == r && tabuleiro[i][2] == r) parar = true;
        if (tabuleiro[0][i] == r && tabuleiro[1][i] == r && tabuleiro[2][i] == r) parar = true;
    }
    if (tabuleiro[0][0] == r && tabuleiro[1][1] == r && tabuleiro[2][2] == r) parar = true;
    if (tabuleiro[0][2] == r && tabuleiro[1][1] == r && tabuleiro[2][0] == r) parar = true;

    if (parar) {
        system("cls"); // Limpa para mostrar o tabuleiro final
        printf("*** JOGO DA VELHA ***\n");
        mostrarTabuleiro();
        if (r == 'X') {
            printf("\n==== VOCE (X) VENCEU! ====\n");
        } else {
            printf("\n==== O COMPUTADOR (O) VENCEU! ====\n");
        }
    }
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================
int main(){
    SetConsoleOutputCP(CP_UTF8);
    iniciarTabuleiro();
    srand(time(NULL));
    
    while(!parar){
        system("cls"); 
        
        printf("*** JOGO DA VELHA ***\n");
        mostrarTabuleiro();

        if(rodada == 'X'){
            // Se a jogada for inválida, reinicia o loop
            if(!jogadaJogador()){
                continue;
            }
        }
        else {
            jogadaMaquina();
        }

        tabuleiro[linha][coluna] = rodada;
        jogadas++;

        validarVitoria(rodada);

        if(parar){
            break;
        }

        if(jogadas == 9){                       
            system("cls");
            printf("*** JOGO DA VELHA ***\n");
            mostrarTabuleiro();
            printf("\n==== EMPATE! ====\n");
            break;
        }

        rodada = (rodada == 'X') ? 'O' : 'X';
    }
    
    return 0;
}
