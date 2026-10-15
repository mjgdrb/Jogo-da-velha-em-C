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

//    CODIGO:
#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída (para printf, scanf, etc.)
#include <windows.h> // Inclui a biblioteca do Windows (para usar as funções Sleep e system("cls"))
#include <stdbool.h> // Inclui a biblioteca para o uso de variáveis booleanas (true e false)
#include <time.h> // Inclui a biblioteca de tempo (necessária para gerar números aleatórios com time())

// VARIÁVEIS
char tabuleiro[3][3]; // Declara uma matriz 3x3 de caracteres para representar o tabuleiro do jogo
bool parar = false; // Declara e inicializa uma variável booleana para controlar o fim do loop do jogo
char rodada = 'X'; // Variável que define de quem é a vez (começa com o jogador 'X')
int jogadas = 0; // Contador de jogadas (usado para verificar se o jogo deu empate ao chegar em 9)
int linha = 0; // Variável que armazenará a linha escolhida durante a jogada
int coluna = 0; // Variável que armazenará a coluna escolhida durante a jogada
int tempoPc = 1500; // Define o tempo de espera (em milissegundos) para simular o "pensamento" da máquina
int tempoLeitura = 1200; // Define o tempo de espera (em milissegundos) para exibir mensagens de erro na tela

// ========================================== // Divisória visual
// FUNÇÃO DE INICIAR O TABULEIRO // Comentário original: Título da função
// ========================================== // Divisória visual
void iniciarTabuleiro(){ // Função que limpa as posições da matriz no início do programa
    // Inicia o Tabuleiro com Espaços ' ' // Comentário original
    for(int i = 0; i<3; i++){ // Loop para percorrer as 3 linhas do tabuleiro (0 a 2)
        for(int j = 0; j<3; j++){ // Loop para percorrer as 3 colunas do tabuleiro (0 a 2)
            tabuleiro[i][j] = ' '; // Atribui um espaço em branco (' ') à posição atual, indicando casa vazia
        } // Fim do loop das colunas
    } // Fim do loop das linhas
} // Fim da função iniciarTabuleiro

// ========================================== // Divisória visual
// FUNÇÃO DE MOSTRAR O TABULEIRO // Comentário original: Título da função
// ========================================== // Divisória visual
void mostrarTabuleiro(){ // Função responsável por desenhar o tabuleiro na tela do terminal
    // Printa o Tabuleiro Organizado // Comentário original
    printf("\n   1   2   3\n"); // Imprime o cabeçalho numérico das colunas para orientar o jogador
    for(int i = 0; i < 3; i++){ // Loop que iterará por cada uma das 3 linhas
        printf("%d ", i+1); // Imprime o número da linha na lateral esquerda (i+1 exibe 1, 2, 3 em vez de 0, 1, 2)
        for(int j = 0; j < 3; j++){ // Loop que iterará por cada coluna da linha atual
            printf("[%c] ", tabuleiro[i][j]); // Imprime o caractere da posição entre colchetes (ex: [X], [O] ou [ ])
        } // Fim do loop das colunas
        printf("\n"); // Quebra a linha após imprimir as 3 colunas para passar para a próxima linha do tabuleiro
    } // Fim do loop das linhas
} // Fim da função mostrarTabuleiro

// ========================================== // Divisória visual
// FUNÇÃO DE JOGADA DO JOGADOR // Comentário original: Título da função
// ========================================== // Divisória visual
bool jogadaJogador(){ // Função que gerencia a entrada de dados do jogador; retorna um booleano (verdadeiro se jogada for válida)
    printf("\n=> Seu turno (X)!\n"); // Informa na tela que é a vez do jogador humano

    // Proteção para a linha // Comentário original
    printf("Insira a linha: "); // Pede para o usuário digitar a linha desejada
    if (scanf("%d", &linha) != 1) { // Lê a entrada; se o scanf não ler 1 número inteiro válido (ex: digitar letra), entra no if
        printf("\n=== ENTRADA INVALIDA! DIGITE APENAS NUMEROS. ===\n"); // Exibe mensagem de erro de formatação
        while (getchar() != '\n'); // Limpa o buffer do teclado para evitar loop infinito com entradas corrompidas
        Sleep(tempoLeitura); // Pausa a execução para dar tempo de o usuário ler o erro
        return false; // Retorna falso para sinalizar à função main que a jogada falhou e precisa ser repetida
    } // Fim da proteção de entrada da linha
    linha -= 1; // Subtrai 1 da entrada do usuário para ajustar ao índice da matriz em C (que começa em 0)

    // Proteção para a coluna // Comentário original
    printf("Insira a coluna: "); // Pede para o usuário digitar a coluna desejada
    if (scanf("%d", &coluna) != 1) { // Lê a entrada e verifica se não foi digitado um número inteiro válido
        printf("\n=== ENTRADA INVALIDA! DIGITE APENAS NUMEROS. ===\n"); // Exibe mensagem de erro
        while (getchar() != '\n'); // Limpa o buffer de entrada
        Sleep(tempoLeitura); // Pausa a execução para leitura do erro
        return false; // Retorna falso para refazer a jogada
    } // Fim da proteção de entrada da coluna
    coluna -= 1; // Subtrai 1 para alinhar o número escolhido (1-3) com os índices do vetor (0-2)

    // Validação de limites // Comentário original
    if((linha < 0) || (linha > 2) || (coluna < 0) || (coluna > 2)){ // Verifica se o jogador digitou coordenadas fora do 1 a 3
        printf("\n=== POSICAO INVALIDA ===\n"); // Avisa que a casa não existe no tabuleiro
        Sleep(tempoLeitura); // Pausa a execução
        return false; // Retorna falso invalidando a jogada
    } // Fim da verificação de limites
    
    // Validação de posição ocupada // Comentário original
    if(tabuleiro[linha][coluna] != ' '){ // Verifica se a coordenada escolhida já possui 'X' ou 'O'
        printf("\n=== POSICAO JA OCUPADA ===\n"); // Avisa que a jogada não é permitida naquela casa
        Sleep(tempoLeitura); // Pausa a execução
        return false; // Retorna falso invalidando a jogada
    } // Fim da verificação de casa ocupada
    
    return true; // Se passar por todas as validações sem erro, retorna verdadeiro para confirmar a jogada
} // Fim da função jogadaJogador

// ========================================== // Divisória visual
// FUNÇÃO DE JOGADA DA MÁQUINA // Comentário original: Título da função
// ========================================== // Divisória visual
void jogadaMaquina(){ // Função que faz o computador escolher uma posição aleatória no tabuleiro
    printf("\n=> Turno do Computador (O)...\n"); // Informa na tela que o PC está jogando
    Sleep(tempoPc); // Cria um pequeno atraso proposital para simular "raciocínio" da máquina e melhorar a experiência

    do{ // Inicia um loop de tentativa de jogada (fará pelo menos uma vez)
        linha = rand() % 3; // Usa a função rand() para gerar um número aleatório (de 0 a 2) e atribui à variável linha
        coluna = rand() % 3; // Usa a função rand() para gerar um número aleatório (de 0 a 2) e atribui à variável coluna
    } while(tabuleiro[linha][coluna] != ' '); // Continua sorteando posições enquanto a coordenada sorteada não for um espaço vazio (' ')
} // Fim da função jogadaMaquina

// ========================================== // Divisória visual
// FUNÇÃO DE VALIDAÇÃO DE VITÓRIA // Comentário original: Título da função
// ========================================== // Divisória visual
void validarVitoria(char r){ // Função que checa se o jogador atual ('r', podendo ser 'X' ou 'O') completou uma trinca
    for (int i = 0; i < 3; i++) { // Loop que itera pelos índices de 0 a 2 para avaliar as retas
        if (tabuleiro[i][0] == r && tabuleiro[i][1] == r && tabuleiro[i][2] == r) parar = true; // Checa as três colunas da linha 'i'; se forem iguais ao jogador atual, ativa a flag de vitória (parar)
        if (tabuleiro[0][i] == r && tabuleiro[1][i] == r && tabuleiro[2][i] == r) parar = true; // Checa as três linhas da coluna 'i'; se forem iguais, ativa a flag de vitória (parar)
    } // Fim do loop de verificação de linhas e colunas
    if (tabuleiro[0][0] == r && tabuleiro[1][1] == r && tabuleiro[2][2] == r) parar = true; // Checa a diagonal principal; se tudo for 'r', aciona a vitória
    if (tabuleiro[0][2] == r && tabuleiro[1][1] == r && tabuleiro[2][0] == r) parar = true; // Checa a diagonal secundária; se tudo for 'r', aciona a vitória

    if (parar) { // Se a variável booleana 'parar' tiver virado true (alguém ganhou)
        system("cls"); // Limpa para mostrar o tabuleiro final // Comentário original e comando que limpa a tela do console Windows
        printf("*** JOGO DA VELHA ***\n"); // Imprime o letreiro do jogo
        mostrarTabuleiro(); // Imprime a matriz com a posição vitoriosa
        if (r == 'X') { // Avalia quem foi o vencedor
            printf("\n==== VOCE (X) VENCEU! ====\n"); // Se foi 'X', imprime a mensagem parabenizando o humano
        } else { // Caso contrário (só pode ser 'O')
            printf("\n==== O COMPUTADOR (O) VENCEU! ====\n"); // Imprime a mensagem de derrota para a máquina
        } // Fim do condicional de impressão de quem venceu
    } // Fim da condicional de acionamento de fim de jogo
} // Fim da função validarVitoria

// ========================================== // Divisória visual
// FUNÇÃO PRINCIPAL // Comentário original: Ponto de partida do código C
// ========================================== // Divisória visual
int main(){ // Função main, onde a execução real do código começa
    SetConsoleOutputCP(CP_UTF8); // Configura o terminal para UTF-8, garantindo que acentos e caracteres especiais funcionem direito
    iniciarTabuleiro(); // Executa a função que preenche todo o tabuleiro com espaços brancos
    srand(time(NULL)); // Inicializa a semente geradora de números aleatórios com a hora do sistema (evita que o PC repita as mesmas jogadas sempre)
    
    while(!parar){ // Inicia o loop principal do jogo que continuará rodando enquanto 'parar' for false (!false = true)
        system("cls"); // Limpa o terminal para redesenhar o quadro e não encher a tela de histórico
        
        printf("*** JOGO DA VELHA ***\n"); // Imprime o cabeçalho
        mostrarTabuleiro(); // Chama a função que desenha a grade no estado atual

        if(rodada == 'X'){ // Verifica se é a vez do jogador humano
            // Se a jogada for inválida, reinicia o loop // Comentário original
            if(!jogadaJogador()){ // Executa a função do jogador e se retornar false (deu erro na entrada)
                continue; // Pula todo o código abaixo e reinicia o loop do while na mesma rodada para pedir novamente
            } // Fim da checagem de jogada inválida
        } // Fim do bloco da vez do jogador
        else { // Se não for a vez de 'X', então é 'O'
            jogadaMaquina(); // Executa a função de inteligência aleatória do PC
        } // Fim do bloco de vez do PC

        tabuleiro[linha][coluna] = rodada; // Grava no tabuleiro real o caractere da rodada ('X' ou 'O') na coordenada escolhida (e validada)
        jogadas++; // Incrementa a contagem geral de jogadas no tabuleiro

        validarVitoria(rodada); // Verifica se a jogada que acabou de ser feita resultou em uma vitória no jogo

        if(parar){ // Após validar vitória, se a flag 'parar' ficou true
            break; // Quebra e encerra imediatamente o loop while principal do jogo, pulando o restante
        } // Fim do break de vitória

        if(jogadas == 9){ // Se ninguém venceu (pois não parou acima) e o limite de 9 casas preenchidas for atingido                       
            system("cls"); // Limpa a tela uma última vez
            printf("*** JOGO DA VELHA ***\n"); // Título do jogo
            mostrarTabuleiro(); // Desenha a configuração final completa
            printf("\n==== EMPATE! ====\n"); // Anuncia o empate ("Deu velha")
            break; // Quebra o loop principal para encerrar o programa
        } // Fim do bloco de empate

        rodada = (rodada == 'X') ? 'O' : 'X'; // Operador ternário (se/senão curto): altera a variável 'rodada' de 'X' para 'O' ou de 'O' para 'X' ao fim do turno
    } // Fim do laço while do jogo
    
    return 0; // Finaliza o programa retornando código de sucesso (0) para o sistema
} // Fim da função main
    return 0;
}
