#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um território
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para evitar que o usuário digite mais caracteres do que permitido
static void limpar_linha(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


/*
    Função responsável por cadastrar os territórios.
    Recebe:
    - mapa : ponteiro para o vetor dinâmico de territórios
    - qtd  : quantidade total de territórios
*/
void cadastrarTerritorios(Territorio* mapa, int qtd)
{
    printf("\n=== Cadastro de Territorios ===\n\n");

    // Esse loop percorre os territórios 
    for (int i = 0; i < qtd; i++)
    {
        printf("Territorio %d/%d\n", i + 1, qtd);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        limpar_linha();

        printf("Cor do exercito: ");
        scanf(" %9[^\n]", mapa[i].cor);
        limpar_linha();

        printf("Numero de tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1)
        {
            printf("Valor invalido. Digite novamente: ");
            limpar_linha();
        }
        limpar_linha();
        printf("\n");
    }
}

/*
    Função que exibe o estado atual dos territórios
    e exibe suas informações
*/
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

/*
    Função que simula um ataque entre dois territórios.
    Recebe ponteiros para:
    - atacante
    - defensor

    Por estarmos usando ponteiros, qualquer alteração feita nessa parte
    vai afetar diretamente os territórios originais.
*/
void atacar(Territorio* atacante, Territorio* defensor)
{
    // Aqui simulamos os dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Rolagem de dados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    // Se o atacante vencer
    if (dadoAtacante > dadoDefensor)
    {
        printf("✅ Ataque bem-sucedido!\n");

        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);
        atacante->tropas -= tropasTransferidas;
    }
    // Se o defensor vencer
    else
    {
        printf("❌ Ataque falhou!\n");
        if (atacante->tropas > 0)
            atacante->tropas--;
    }
}

/*
    Função responsável por liberar a memória alocada dinamicamente.
*/
void liberarMemoria(Territorio* mapa)
{
    free(mapa);
}

int main(void)
{
    int qtdTerritorios;
    int opcao;

    srand(time(NULL));

    printf("Quantidade de territorios: ");
    scanf("%d", &qtdTerritorios);
    limpar_linha();

    Territorio* mapa = calloc(qtdTerritorios, sizeof(Territorio));
    if (!mapa)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtdTerritorios);

    do
    {
        int a, d;

        exibirTerritorios(mapa, qtdTerritorios);

        printf("Escolha o atacante (0 para sair): ");
        scanf("%d", &a);

        if (a == 0)
            break;

        printf("Escolha o defensor: ");
        scanf("%d", &d);

        a--;
        d--;

        if (a < 0 || a >= qtdTerritorios || d < 0 || d >= qtdTerritorios)
        {
            printf("Indice invalido.\n");
        }
        else if (a == d)
        {
            printf("Nao e possivel atacar o mesmo territorio.\n");
        }
        else if (strcmp(mapa[a].cor, mapa[d].cor) == 0)
        {
            printf("Nao e permitido atacar territorio da mesma cor.\n");
        }
        else
        {
            atacar(&mapa[a], &mapa[d]);
        }

        printf("\nDeseja realizar outro ataque? (1 = sim / 0 = nao): ");
        scanf("%d", &opcao);

    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("\nSistema encerrado. Memoria liberada.\n");

    return 0;
}
