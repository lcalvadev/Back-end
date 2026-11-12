
#include <stdio.h>

int main() {

    int opcao;
    int quantidade = 0;
    int alugado[50] = {0};
    char modelo[50][30];
    char placa[50][10];

    do {

        printf("  +==============================+\n");
        printf("  |     LOCADORA DE VEICULOS     |\n");
        printf("  +==============================+\n");
        printf("  |    1 - Cadastrar veiculo     |\n");
        printf("  |    2 - Listar veiculos       |\n");
        printf("  |    3 - Alugar veiculo        |\n");
        printf("  |    4 - Devolver veiculo      |\n");
        printf("  |    5 - Sair                  |\n");
        printf("  +==============================+\n");
        
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:

                printf("\nDigite o modelo: ");
                scanf(" %29[^\n]", modelo[quantidade]);

                printf("Digite a placa: ");
                scanf(" %9s", placa[quantidade]);

                alugado[quantidade] = 0;
                quantidade++;

                printf("\nVeiculo cadastrado!\n");

                break;

            case 2:

                printf("\n--- VEICULOS CADASTRADOS ---\n");

                for (int i = 0; i < quantidade; i++) {

                    printf("\nModelo: %s\n", modelo[i]);
                    printf("Placa: %s\n", placa[i]);

                    if (alugado[i] == 0) {
                        printf("Status: Disponivel\n");
                    } else {
                        printf("Status: Indisponivel / Alugado\n");
                    }
                }

                if (quantidade == 0) {
                    printf("Nenhum veiculo cadastrado.\n");
                }

                break;

            case 3:

                printf("\nDigite o numero do veiculo: ");
                for (int i = 0; i < quantidade; i++) {
                    printf("%d - %s\n", i + 1, modelo[i]);
                }

                int escolha;
                scanf("%d", &escolha);

                if (escolha >= 1 && escolha <= quantidade) {

                    if (alugado[escolha - 1] == 0) {
                        alugado[escolha - 1] = 1;
                        printf("Veiculo alugado com sucesso!\n");
                    } else {
                        printf("Veiculo ja esta alugado!\n");
                    }

                } else {
                    printf("Veiculo invalido!\n");
                }

                break;

            case 4:

                printf("\nDigite o numero do veiculo: ");

                for (int i = 0; i < quantidade; i++) {
                    printf("%d - %s\n", i + 1, modelo[i]);
                }

                scanf("%d", &escolha);

                if (escolha >= 1 && escolha <= quantidade) {

                    if (alugado[escolha - 1] == 1) {
                        alugado[escolha - 1] = 0;
                        printf("Veiculo devolvido com sucesso!\n");
                    } else {
                        printf("Este veiculo não esta alugado!\n");
                    }

                } else {
                    printf("Veiculo invalido!\n");
                }

                break;

            case 5:
                printf("\nFim do programa...\nVolte Sempre!\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 5);

    return 0;
}
