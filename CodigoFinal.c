//    CODIGO:
// BIBLIOTECAS
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

// VARIÁVEIS
char tabuleiro[3][3]; // Matriz que representa o tabuleiro do jogo
bool parar = false; // Variável que controla o fim do loop principal do jogo
char rodada = 'X'; // Define de quem é a vez atual
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
            tabuleiro[i][j] = ' '; // Preenche todas as posições com espaços em branco
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
            printf("[%c] ", tabuleiro[i][j]); // Desenha cada casa do tabuleiro na tela
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
    if (scanf("%d", &linha) != 1) { // Verifica se a entrada não é um número
        printf("\n=== ENTRADA INVALIDA! DIGITE APENAS NUMEROS. ===\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada para evitar loop infinito
        Sleep(tempoLeitura);
        return false;
    }
    linha -= 1; // Ajusta a entrada do usuário (1-3) para os índices da matriz em C (0-2)

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
    if((linha < 0) || (linha > 2) || (coluna < 0) || (coluna > 2)){ // Impede jogadas fora do tabuleiro 3x3
        printf("\n=== POSICAO INVALIDA ===\n");
        Sleep(tempoLeitura); 
        return false;
    }
    
    // Validação de posição ocupada
    if(tabuleiro[linha][coluna] != ' '){ // Impede jogar onde já tem 'X' ou 'O'
        printf("\n=== POSICAO JA OCUPADA ===\n");
        Sleep(tempoLeitura);
        return false;
    }
    
    return true; // Retorna verdadeiro indicando que a jogada foi bem-sucedida
}

// ==========================================
// FUNÇÃO DE JOGADA DA MÁQUINA
// ==========================================
void jogadaMaquina(){
    printf("\n=> Turno do Computador (O)...\n");
    Sleep(tempoPc); // Simula o tempo de "pensamento" da máquina

    do{
        linha = rand() % 3; // Sorteia uma linha aleatória de 0 a 2
        coluna = rand() % 3; // Sorteia uma coluna aleatória de 0 a 2
    } while(tabuleiro[linha][coluna] != ' '); // Repete o sorteio até achar uma casa vazia
}

// ==========================================
// FUNÇÃO DE VALIDAÇÃO DE VITÓRIA
// ==========================================
void validarVitoria(char r){
    for (int i = 0; i < 3; i++) {
        // Verifica se há 3 símbolos iguais do jogador atual nas linhas ou colunas
        if (tabuleiro[i][0] == r && tabuleiro[i][1] == r && tabuleiro[i][2] == r) parar = true;
        if (tabuleiro[0][i] == r && tabuleiro[1][i] == r && tabuleiro[2][i] == r) parar = true;
    }
    // Verifica se há 3 símbolos iguais nas diagonais
    if (tabuleiro[0][0] == r && tabuleiro[1][1] == r && tabuleiro[2][2] == r) parar = true;
    if (tabuleiro[0][2] == r && tabuleiro[1][1] == r && tabuleiro[2][0] == r) parar = true;

    if (parar) { // Se a flag 'parar' virou true, alguém venceu
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
    SetConsoleOutputCP(CP_UTF8); // Permite exibição correta de caracteres especiais e acentos no console
    iniciarTabuleiro();
    srand(time(NULL)); // Inicializa a semente aleatória baseada no relógio do sistema para o PC não repetir jogadas
    
    while(!parar){ // Loop principal que roda até que haja um vencedor ou empate
        system("cls"); 
        
        printf("*** JOGO DA VELHA ***\n");
        mostrarTabuleiro();

        if(rodada == 'X'){
            // Se a jogada for inválida, reinicia o loop
            if(!jogadaJogador()){ // Chama a jogada do humano. Se retornar false, pede novamente na mesma rodada
                continue;
            }
        }
        else {
            jogadaMaquina(); // Chama a jogada da máquina
        }

        tabuleiro[linha][coluna] = rodada; // Registra a jogada validada no tabuleiro real
        jogadas++; // Conta quantas jogadas já foram feitas no total

        validarVitoria(rodada); // Checa se a última jogada resultou em vitória

        if(parar){
            break; // Encerra o jogo e sai do loop principal se alguém venceu
        }

        if(jogadas == 9){ // Se o tabuleiro lotou (9 casas) sem vencedor, é empate                       
            system("cls");
            printf("*** JOGO DA VELHA ***\n");
            mostrarTabuleiro();
            printf("\n==== EMPATE! ====\n");
            break;
        }

        rodada = (rodada == 'X') ? 'O' : 'X'; // Alterna a vez: se era 'X', vira 'O', e vice-versa
    }
    
    return 0;
}