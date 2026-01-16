#include <stdio.h>
#include <string.h>

#define TERRITORIOS_MAX 5

// Struct que representa um territorio do jogo/sistema.
// - nome: até 29 caracteres + '\0'
// - cor : até 9 caracteres + '\0'
// - tropas: quantidade de tropas no territorio

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


// Função auxiliar que foi criada para limpar o restante da memória caso o usuário digite alem do tamanho permitido
static void limpar_linha(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int main(void)
{
    // Declaração de um array baseado na "tipagem" do struct
    Territorio territorios[TERRITORIOS_MAX];

    printf("=== Cadastro de Territorios (%d) ===\n\n", TERRITORIOS_MAX);

    // Entrada dos dados (cadastro) usando um laco for
    for (int i = 0; i < TERRITORIOS_MAX; i++)
    {
        printf("Territorio %d/%d\n", i + 1, TERRITORIOS_MAX);

        // Le o nome permitindo espacos (ate 29 caracteres)
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);
        limpar_linha();

        // Le a cor do exercito (ate 9 caracteres, sem espacos)
        printf("Digite a cor do exercito: ");
        scanf(" %9[^\n]", territorios[i].cor);
        limpar_linha();

        // Le o numero de tropas
        printf("Digite o numero de tropas: ");
        while (scanf("%d", &territorios[i].tropas) != 1)
        {
            printf("Numero invalido. Tente novamente: ");
            limpar_linha();
        }
        limpar_linha();

        printf("\n");
    }

    // Exibicao dos dados apos o cadastro
    printf("=== Territorios Registrados ===\n");
    for (int i = 0; i < TERRITORIOS_MAX; i++)
    {
        printf("Territorio %d\n", i + 1);
        printf("  Nome  : %s\n", territorios[i].nome);
        printf("  Cor   : %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("------------------------------\n");
    }

    return 0;
}
