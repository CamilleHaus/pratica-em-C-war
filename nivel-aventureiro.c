#include <stdio.h>   // printf, scanf
#include <stdlib.h>  // malloc, calloc, free, rand
#include <string.h>  // strcpy, strcmp, strstr
#include <time.h>    // time (para o srand)

// ========================
// Struct principal do jogo
// Cada território tem nome, cor do exército e número de tropas
// ========================
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ========================
// Função auxiliar só pra limpar o buffer do teclado
// Evita bug quando o usuário digita coisa errada
// ========================
static void limpar_linha(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// ========================
// Função que cadastra todos os territórios
// Aqui o usuário define tudo manualmente
// ========================
void cadastrarTerritorios(Territorio* mapa, int qtd)
{
    printf("\n=== Cadastro de Territorios ===\n\n");

    for (int i = 0; i < qtd; i++)
    {
        printf("Territorio %d/%d\n", i + 1, qtd);

        // Nome do território
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        limpar_linha();

        // Cor do exército que domina esse território
        printf("Cor do exercito: ");
        scanf(" %9[^\n]", mapa[i].cor);
        limpar_linha();

        // Quantidade de tropas (não pode ser inválida)
        printf("Numero de tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 1)
        {
            printf("Valor invalido. Digite novamente: ");
            limpar_linha();
        }
        limpar_linha();
        printf("\n");
    }
}

// ========================
// Mostra o estado atual do mapa
// Serve pra o jogador saber quem domina o quê
// ========================
void exibirTerritorios(Territorio* mapa, int qtd)
{
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < qtd; i++)
    {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
    printf("\n");
}

// ========================
// Função que simula um ataque
// Usa dados aleatórios (1 a 6) estilo WAR
// ========================
void atacar(Territorio* atacante, Territorio* defensor)
{
    // Simulação da rolagem dos dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Rolagem de dados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    // Se o atacante ganhou no dado
    if (dadoAtacante > dadoDefensor)
    {
        printf("✅ Ataque bem-sucedido!\n");

        // Transfere metade das tropas
        int tropasTransferidas = atacante->tropas / 2;

        // Garantia de pelo menos 1 tropa
        if (tropasTransferidas < 1)
            tropasTransferidas = 1;

        // Defensor muda de dono
        defensor->tropas = tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);

        // Atacante perde as tropas transferidas
        atacante->tropas -= tropasTransferidas;
    }
    else
    {
        // Ataque falhou
        printf("❌ Ataque falhou!\n");

        // Penalidade simples
        if (atacante->tropas > 1)
            atacante->tropas--;
    }
}

// ========================
// Sorteia uma missão aleatória
// Copia a missão sorteada para o jogador
// ========================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes)
{
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// ========================
// Mostra a missão do jogador
// Só aparece uma vez no início do jogo
// ========================
void exibirMissao(char* missao)
{
    printf("\n🎯 SUA MISSAO:\n%s\n\n", missao);
}

// ========================
// Verifica se a missão foi cumprida
// Essa checagem acontece de forma silenciosa
// ========================
int verificarMissao(char* missao, Territorio* mapa, int tamanho)
{
    int territoriosDominados = 0;
    int tropasInimigas = 0;

    // Consideramos o jogador como dono da cor do primeiro território
    char corJogador[10];
    strcpy(corJogador, mapa[0].cor);

    // Percorre o mapa inteiro
    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(mapa[i].cor, corJogador) == 0)
            territoriosDominados++;
        else
            tropasInimigas += mapa[i].tropas;
    }

    // Missão: conquistar 3 territórios
    if (strstr(missao, "3 territorios") && territoriosDominados >= 3)
        return 1;

    // Missão: dominar o mapa inteiro
    if (strstr(missao, "todos os territorios") && territoriosDominados == tamanho)
        return 1;

    // Missão: eliminar todas as tropas inimigas
    if (strstr(missao, "Eliminar") && tropasInimigas == 0)
        return 1;

    return 0;
}

// ========================
// Libera toda a memória alocada
// Importantíssimo pra não dar vazamento
// ========================
void liberarMemoria(Territorio* mapa, char* missao)
{
    free(mapa);
    free(missao);
}

// ========================
// Função principal
// Onde tudo começa e termina
// ========================
int main(void)
{
    int qtdTerritorios;
    int opcao;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Vetor de missões possíveis
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Dominar todos os territorios do mapa",
        "Eliminar todas as tropas inimigas",
        "Conquistar territorios consecutivos",
        "Eliminar um exercito adversario"
    };

    printf("Quantidade de territorios: ");
    scanf("%d", &qtdTerritorios);
    limpar_linha();

    // Aloca dinamicamente o mapa
    Territorio* mapa = calloc(qtdTerritorios, sizeof(Territorio));
    if (!mapa)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Aloca memória para armazenar a missão do jogador
    char* missa*
