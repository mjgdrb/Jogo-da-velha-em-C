#include <stdio.h>    // Biblioteca padrão para entrada e saída de dados (ex: printf, scanf)
#include <windows.h>  // Biblioteca para funções específicas do Windows (ex: system("cls"), Sleep)
#include <stdbool.h>  // Biblioteca para habilitar o uso de variáveis booleanas (true e false)
#include <time.h>     // Biblioteca para funções de tempo (necessária para gerar números aleatórios diferentes)

// VARIÁVEIS GLOBAIS
char tabuleiro[3][3];     // Matriz 3x3 que armazena os estados do jogo (' ', 'X', 'O')
bool parar = false;       // Variável de controle para indicar o fim do jogo (vitória)
char rodada = 'X';        // Define o jogador atual ('X' para humano, 'O' para computador)
int jogadas = 0;          // Conta o total de jogadas realizadas (máximo 9 para empate)
int linha = 0;            // Armazena a linha escolhida pelo jogador ou computador
int coluna = 0;           // Armazena a coluna escolhida pelo jogador ou computador
int tempoPc = 1500;       // Tempo de espera (em milissegundos) para simular o computador "pensando"
int tempoLeitura = 1200;  // Tempo de espera (em milissegundos) para o usuário ler mensagens de erro

// ==========================================
// FUNÇÃO DE INICIAR O TABULEIRO
// ==========================================
void iniciarTabuleiro(){
    // Percorre todas as linhas e colunas da matriz preenchendo com espaços vazios
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tabuleiro[i][j] = ' ';
        }
    }
}

// ==========================================
// FUNÇÃO DE MOSTRAR O TABULEIRO
// ==========================================
void mostrarTabuleiro(){
    // Exibe o cabeçalho com as colunas numeradas de 1 a 3
    printf("\n   1   2   3\n");
    for(int i = 0; i < 3; i++){
        printf("%d ", i + 1); // Exibe o número da linha correspondente (1 a 3)
        for(int j = 0; j < 3; j++){
            printf("[%c] ", tabuleiro[i][j]); // Exibe o conteúdo atual de cada célula da matriz
        }
        printf("\n");
    }
}

// ==========================================
// FUNÇÃO DE JOGADA DO JOGADOR
// ==========================================
bool jogadaJogador(){
    printf("\n=> Seu turno (X)!\n");

    // Solicita e valida a entrada da linha com proteção contra caracteres inválidos (letras)
    printf("Insira a linha: ");
    if (scanf("%d", &linha) != 1) {
        printf("\n=== ENTRADA INVALIDA! DIGITE APENAS NUMEROS. ===\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada do teclado
        Sleep(tempoLeitura);
        return false;
    }
    linha -= 1; // Ajusta para o índice da matriz (converte de 1-3 para 0-2)

    // Solicita e valida a entrada da coluna com proteção contra caracteres inválidos
    printf("Insira a coluna: ");
    if (scanf("%d", &coluna) != 1) {
        printf("\n=== ENTRADA INVALIDA! DIGITE APENAS NUMEROS. ===\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada do teclado
        Sleep(tempoLeitura);
        return false;
    }
    coluna -= 1; // Ajusta para o índice da matriz (converte de 1-3 para 0-2)

    // Validação de limites: verifica se a escolha está fora do tabuleiro (0 a 2)
    if((linha < 0) || (linha > 2) || (coluna < 0) || (coluna > 2)){
        printf("\n=== POSICAO INVALIDA ===\n");
        Sleep(tempoLeitura); 
        return false;
    }
    
    // Validação de posição ocupada: impede jogar onde já existe 'X' ou 'O'
    if(tabuleiro[linha][coluna] != ' '){
        printf("\n=== POSICAO JA OCUPADA ===\n");
        Sleep(tempoLeitura);
        return false;
    }
    
    return true; // Retorna verdadeiro indicando que a jogada é válida
}

// ==========================================
// FUNÇÃO DE JOGADA DA MÁQUINA
// ==========================================
void jogadaMaquina(){
    printf("\n=> Turno do Computador (O)...\n");
    Sleep(tempoPc); // Pausa a execução para simular o tempo de raciocínio da máquina

    // Laço de repetição que sorteia posições aleatórias até encontrar uma célula vazia
    do{
        linha = rand() % 3; // Sorteia entre 0 e 2 para a linha
        coluna = rand() % 3; // Sorteia entre 0 e 2 para a coluna
    } while(tabuleiro[linha][coluna] != ' ');
}

// ==========================================
// FUNÇÃO DE VALIDAÇÃO DE VITÓRIA
// ==========================================
void validarVitoria(char r){
    // Verifica todas as linhas e colunas em busca de 3 símbolos iguais
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == r && tabuleiro[i][1] == r && tabuleiro[i][2] == r) parar = true;
        if (tabuleiro[0][i] == r && tabuleiro[1][i] == r && tabuleiro[2][i] == r) parar = true;
    }
    // Verifica a diagonal principal
    if (tabuleiro[0][0] == r && tabuleiro[1][1] == r && tabuleiro[2][2] == r) parar = true;
    // Verifica a diagonal secundária
    if (tabuleiro[0][2] == r && tabuleiro[1][1] == r && tabuleiro[2][0] == r) parar = true;

    // Se a variável 'parar' mudou para verdadeira, alguém venceu a partida
    if (parar) {
        system("cls"); // Limpa o console para exibir o estado final do tabuleiro
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
    SetConsoleOutputCP(CP_UTF8); // Configura o terminal do Windows para suportar acentuação gráfica
    iniciarTabuleiro();          // Preenche a matriz com espaços vazios para começar o jogo
    srand(time(NULL));           // Inicializa a semente aleatória com base no horário do sistema
    
    // Loop principal da partida: continua rodando enquanto ninguém vencer
    while(!parar){
        system("cls");  // Limpa a tela no início de cada turno
        
        printf("*** JOGO DA VELHA ***\n");
        mostrarTabuleiro(); // Desenha o tabuleiro atual na tela

        // Estrutura de decisão para alternar o fluxo entre o jogador e o computador
        if(rodada == 'X'){
            // Se a jogada do usuário for inválida, reinicia o loop para pedir de novo
            if(!jogadaJogador()){
                continue;
            }
        }
        else {
            jogadaMaquina(); // Executa o turno automatizado da máquina
        }

        // Aplica o símbolo ('X' ou 'O') na coordenada escolhida dentro da matriz
        tabuleiro[linha][coluna] = rodada;
        jogadas++; // Incrementa o contador total de jogadas realizadas

        // Verifica se a jogada atual preencheu uma condição de vitória
        validarVitoria(rodada);

        // Se o jogo terminou com vitória, sai do loop principal
        if(parar){
            break;
        }

        // Condição de empate: se todas as 9 casas foram preenchidas sem vencedor
        if(jogadas == 9){                        
            system("cls");
            printf("*** JOGO DA VELHA ***\n");
            mostrarTabuleiro();
            printf("\n==== EMPATE! ====\n");
            break;
        }

        // Operador ternário para alternar o turno entre o jogador ('X') e o computador ('O')
        rodada = (rodada == 'X') ? 'O' : 'X';
    }
    
    return 0; // Encerra o programa com sucesso
}
