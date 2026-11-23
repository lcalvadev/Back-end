// (a) Elaborar um programa que efetue a leitura de dez idades de pessoas em uma matriz A do
// tipo vetor e apresentá-los em seguida.

#include <stdio.h>

int main() {
    int a[10];
    int i;

    for (i = 0; i < 10; i++) {
        printf("Digite a idade %d: ", i + 1);
        scanf("%d", &a[i]);
    }

    printf("\nIdades lidas:\n");
    for (i = 0; i < 10; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}

// (b) Escrever um programa que leia duas matrizes A e B do tipo vetor com 20 elementos com
// números reais. Construir uma matriz C, sendo cada elemento da matriz C a subtração de um
// elemento correspondente da matriz A com um elemento correspondente da matriz B. Ao final,
// apresentar os elementos da matriz C.

#include <stdio.h>

int main() {
    float a[20];
    float b[20];
    float c[20];
    int i;

    for (i = 0; i < 20; i++) {
        printf("Digite o elemento %d de A: ", i + 1);
        scanf("%f", &a[i]);
    }

    for (i = 0; i < 20; i++) {
        printf("Digite o elemento %d de B: ", i + 1);
        scanf("%f", &b[i]);
    }

    for (i = 0; i < 20; i++) {
        c[i] = a[i] - b[i];
    }

    printf("\nMatriz C (A - B):\n");
    for (i = 0; i < 20; i++) {
        printf("C[%d] = %.2f\n", i, c[i]);
    }
    return 0;
}


// (c) Elaborar um programa que leia uma matriz A do tipo vetor com 15 elementos com
// números inteiros. Construir uma matriz B de mesmo tipo, e cada elemento da matriz B deve ser
// o resultado do fatorial correspondente de cada elemento da matriz A. Apresentar as
// matrizes A e B.

#include <stdio.h>

int main() {
    int a[15];
    double b[15];
    double fatorial;
    int i;
    int j;

    for (i = 0; i < 15; i++) {
        printf("Digite o elemento %d de A: ", i + 1);
        scanf("%d", &a[i]);
    }

    for (i = 0; i < 15; i++) {
        fatorial = 1;
        for (j = 1; j <= a[i]; j++) {
            fatorial = fatorial * j;
        }
        b[i] = fatorial;
    }

    printf("\nMatriz A:\n");
    for (i = 0; i < 15; i++) {
        printf("A[%d] = %d\n", i, a[i]);
    }

    printf("\nMatriz B (fatoriais):\n");
    for (i = 0; i < 15; i++) {
        printf("B[%d] = %.0f\n", i, b[i]);
    }
    return 0;
}


// (d) Elaborar um programa que leia duas matrizes do tipo vetor para o armazenamento de
// cpf de pessoas, sendo a matriz A com 20 elementos e a matriz B com 30 elementos.
// Construir uma matriz C, sendo esta a junção das matrizes A e B. Desta forma, a matriz C deve
// ter a capacidade de armazenar 50 elementos. Apresentar os elementos da matriz C.

#include <stdio.h>
#include <string.h>

int main() {
    char a[20][12];
    char b[30][12];
    char c[50][12];
    int i;

    for (i = 0; i < 20; i++) {
        printf("Digite o CPF %d de A (so numeros): ", i + 1);
        scanf("%11s", a[i]);
    }

    for (i = 0; i < 30; i++) {
        printf("Digite o CPF %d de B (so numeros): ", i + 1);
        scanf("%11s", b[i]);
    }

    for (i = 0; i < 20; i++) {
        strcpy(c[i], a[i]);
    }

    for (i = 0; i < 30; i++) {
        strcpy(c[20 + i], b[i]);
    }

    printf("\nMatriz C (CPFs):\n");
    for (i = 0; i < 50; i++) {
        printf("C[%d] = %s\n", i, c[i]);
    }
    return 0;
}



// (e) Escrever um programa que leia três matrizes (A, B e C) de uma dimensão do tipo vetor
// com cinco elementos cada sejam do tipo real. Construir uma matriz D, sendo esta o resultado
// da junção das três matrizes (A, B e C). Desta forma, a matriz D deve ter o triplo de elementos
// das matrizes A, B e C, ou seja, 15 elementos. Apresentar os elementos da matriz D.

#include <stdio.h>

int main() {
    float a[5];
    float b[5];
    float c[5];
    float d[15];
    int i;

    for (i = 0; i < 5; i++) {
        printf("Digite o elemento %d de A: ", i + 1);
        scanf("%f", &a[i]);
    }

    for (i = 0; i < 5; i++) {
        printf("Digite o elemento %d de B: ", i + 1);
        scanf("%f", &b[i]);
    }

    for (i = 0; i < 5; i++) {
        printf("Digite o elemento %d de C: ", i + 1);
        scanf("%f", &c[i]);
    }

    for (i = 0; i < 5; i++) {
        d[i] = a[i];
        d[i + 5] = b[i];
        d[i + 10] = c[i];
    }

    printf("\nMatriz D:\n");
    for (i = 0; i < 15; i++) {
        printf("D[%d] = %.2f\n", i, d[i]);
    }
    return 0;
}


// (f) Elaborar um programa que leia duas matrizes A e B, cada uma de duas dimensões com
// cinco linhas e três colunas para valores inteiros. Construir uma matriz C de mesma dimensão,
// que seja formada pela soma dos elementos da matriz A com os elementos da matriz B.
// Apresentar os elementos da matriz C.

#include <stdio.h>

int main() {
    int a[5][3];
    int b[5][3];
    int c[5][3];
    int i;
    int j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            printf("Digite A[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            printf("Digite B[%d][%d]: ", i, j);
            scanf("%d", &b[i][j]);
        }
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    printf("\nMatriz C (A + B):\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}


// (g) Elaborar um programa que leia duas matrizes A e B cada uma com uma dimensão para 12
// elementos reais. Construir uma matriz C de duas dimensões, sendo a primeira coluna da matriz
// C formada pelos elementos da matriz A multiplicados por 2 e a segunda coluna formada pelos
// elementos da matriz B subtraídos de 5. Apresentar separadamente as matrizes A, B e C.

#include <stdio.h>

int main() {
    float a[12];
    float b[12];
    float c[12][2];
    int i;

    for (i = 0; i < 12; i++) {
        printf("Digite o elemento %d de A: ", i + 1);
        scanf("%f", &a[i]);
    }

    for (i = 0; i < 12; i++) {
        printf("Digite o elemento %d de B: ", i + 1);
        scanf("%f", &b[i]);
    }

    for (i = 0; i < 12; i++) {
        c[i][0] = a[i] * 2;
        c[i][1] = b[i] - 5;
    }

    printf("\nMatriz A:\n");
    for (i = 0; i < 12; i++) {
        printf("%.2f\n", a[i]);
    }

    printf("\nMatriz B:\n");
    for (i = 0; i < 12; i++) {
        printf("%.2f\n", b[i]);
    }

    printf("\nMatriz C (coluna 1 = A*2, coluna 2 = B-5):\n");
    for (i = 0; i < 12; i++) {
        printf("%.2f   %.2f\n", c[i][0], c[i][1]);
    }
    return 0;
}



// (h) Elaborar um programa que leia uma matriz A de duas dimensões com quatro linhas e
// cinco colunas, armazenando nessa matriz os valores das temperaturas em graus Celsius.
// Construir a matriz B de mesma dimensão, em que cada elemento seja o valor da temperatura
// em graus Fahrenheit de cada elemento correspondente da matriz A. Apresentar ao final as
// matrizes A e B.

#include <stdio.h>

int main() {
    float a[4][5];
    float b[4][5];
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            printf("Digite a temperatura A[%d][%d] (Celsius): ", i, j);
            scanf("%f", &a[i][j]);
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            b[i][j] = (9 * a[i][j] + 160) / 5;
        }
    }

    printf("\nMatriz A (Celsius):\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            printf("%.1f ", a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatriz B (Fahrenheit):\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            printf("%.1f ", b[i][j]);
        }
        printf("\n");
    }
    return 0;
}



// (i) Elaborar um programa que leia uma matriz A do tipo inteira de duas dimensões com sete
// linhas e sete colunas. Construir a matriz B de mesma dimensão em que cada elemento seja o
// somatório de 1 até o valor armazenado na posição da matriz A, com exceção dos valores
// situados nos índices ímpares da diagonal principal (B[1,1]; B[3,3]; B[5,5] e B[7,7]), os
// quais devem ser o fatorial de cada elemento correspondente da matriz A. Apresentar ao final
// a matriz B.

#include <stdio.h>

int main() {
    int a[7][7];
    double b[7][7];
    double resultado;
    int i;
    int j;
    int k;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            printf("Digite A[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if (i == j && i % 2 == 0) {
                resultado = 1;
                for (k = 1; k <= a[i][j]; k++) {
                    resultado = resultado * k;
                }
            } else {
                resultado = 0;
                for (k = 1; k <= a[i][j]; k++) {
                    resultado = resultado + k;
                }
            }
            b[i][j] = resultado;
        }
    }

    printf("\nMatriz B:\n");
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            printf("%.0f ", b[i][j]);
        }
        printf("\n");
    }
    return 0;
}



// (j) Elaborar um programa que leia uma matriz A do tipo real de duas dimensões com quatro
// linhas e quatro colunas. Apresentar o somatório dos elementos situados na diagonal principal
// da referida matriz.

#include <stdio.h>

int main() {
    float a[4][4];
    float soma = 0;
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("Digite A[%d][%d]: ", i, j);
            scanf("%f", &a[i][j]);
        }
    }

    for (i = 0; i < 4; i++) {
        soma = soma + a[i][i];
    }

    printf("Somatorio da diagonal principal: %.2f\n", soma);
    return 0;
}


