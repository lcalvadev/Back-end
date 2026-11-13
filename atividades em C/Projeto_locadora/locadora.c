
#include <stdio.h> 
#include <string.h>

#define MAX_VEICULOS 50

typedef struct {
    char marca[20];
    char modelo[30];
    int ano;
    char cor[20];
    char placa[10];
    char categoria[20];
    float diaria;
    int alugado;
} Veiculo;

Veiculo veiculos[MAX_VEICULOS];
int quantidade = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void mostrarMenu() {
    printf("\n  +==============================+\n");
    printf("  |     LOCADORA DE VEICULOS     |\n");
    printf("  +==============================+\n");
    printf("  | 1 - Cadastrar veiculo       |\n");
    printf("  | 2 - Listar veiculos         |\n");
    printf("  | 3 - Alugar veiculo          |\n");
    printf("  | 4 - Devolver veiculo        |\n");
    printf("  | 5 - Sair                    |\n");
    printf("  +==============================+\n");
}

void cadastrarVeiculo() {
    if (quantidade >= MAX_VEICULOS) {
        printf("\nLimite maximo de veiculos atingido!\n");
        return;
    }

    printf("\n=== CADASTRO DE VEICULO ===\n");

    printf("Marca: ");
    scanf(" %19[^\n]", veiculos[quantidade].marca);
    limparBuffer();

    printf("Modelo: ");
    scanf(" %29[^\n]", veiculos[quantidade].modelo);
    limparBuffer();

    printf("Ano: ");
    while (scanf("%d", &veiculos[quantidade].ano) != 1) {
        printf("Ano invalido! Digite novamente: ");
        limparBuffer();
    }
    limparBuffer();

    printf("Cor: ");
    scanf(" %19[^\n]", veiculos[quantidade].cor);
    limparBuffer();

    printf("Placa: ");
    scanf(" %9s", veiculos[quantidade].placa);
    limparBuffer();

    printf("Categoria: ");
    scanf(" %19[^\n]", veiculos[quantidade].categoria);
    limparBuffer();

    printf("Valor da diaria (R$): ");
    while (scanf("%f", &veiculos[quantidade].diaria) != 1) {
        printf("Valor invalido! Digite novamente: ");
        limparBuffer();
    }
    limparBuffer();

    veiculos[quantidade].alugado = 0;
    quantidade++;

    printf("\nVeiculo cadastrado com sucesso!\n");
}

void listarVeiculos() {
    printf("\n--- VEICULOS CADASTRADOS ---\n");

    if (quantidade == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\n%d - %s %s\n", i + 1, veiculos[i].marca, veiculos[i].modelo);
        printf("    Ano: %d\n", veiculos[i].ano);
        printf("    Cor: %s\n", veiculos[i].cor);
        printf("    Placa: %s\n", veiculos[i].placa);
        printf("    Categoria: %s\n", veiculos[i].categoria);
        printf("    Diaria: R$ %.2f\n", veiculos[i].diaria);

        if (veiculos[i].alugado == 0) {
            printf("    Status: Disponivel\n");
        } else {
            printf("    Status: Alugado\n");
        }
    }
}

void alugarVeiculo() {
    int escolha;

    if (quantidade == 0) {
        printf("\nNenhum veiculo cadastrado.\n");
        return;
    }

    printf("\nDigite o numero do veiculo para alugar:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s %s\n", i + 1, veiculos[i].marca, veiculos[i].modelo);
    }

    printf("Escolha: ");
    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > quantidade) {
        printf("Opcao invalida! Digite novamente: ");
        limparBuffer();
    }
    limparBuffer();

    if (veiculos[escolha - 1].alugado == 0) {
        veiculos[escolha - 1].alugado = 1;
        printf("\nVeiculo alugado com sucesso!\n");
    } else {
        printf("\nVeiculo ja esta alugado!\n");
    }
}

void devolverVeiculo() {
    int escolha;

    if (quantidade == 0) {
        printf("\nNenhum veiculo cadastrado.\n");
        return;
    }

    printf("\nDigite o numero do veiculo para devolver:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s %s\n", i + 1, veiculos[i].marca, veiculos[i].modelo);
    }

    printf("Escolha: ");
    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > quantidade) {
        printf("Opcao invalida! Digite novamente: ");
        limparBuffer();
    }
    limparBuffer();

    if (veiculos[escolha - 1].alugado == 1) {
        veiculos[escolha - 1].alugado = 0;
        printf("\nVeiculo devolvido com sucesso!\n");
    } else {
        printf("\nEste veiculo nao esta alugado!\n");
    }
}

int main() {
    int opcao;

    do {
        mostrarMenu();
        printf("\nEscolha uma opcao: ");

        while (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida! Digite novamente: ");
            limparBuffer();
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarVeiculo();
                break;

            case 2:
                listarVeiculos();
                break;

            case 3:
                alugarVeiculo();
                break;

            case 4:
                devolverVeiculo();

            case 5:
                printf("\nFim do programa...\nVolte Sempre!\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 5);

    return 0;
}
