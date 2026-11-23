// (1) Cabeçalho (Void/Sem Parâmetro): Crie uma função chamada cabecalho() que não recebe
// parâmetros e não retorna nada. Ela deve apenas imprimir uma linha de traços e o nome
// "SISTEMA DE ALUNOS" no meio. Chame-a na main.

#include <stdio.h>

void cabecalho() {
    printf("---------- SISTEMA DE ALUNOS ----------\n");
}

int main() {
    cabecalho();
    return 0;
}


// (2) Dobro (Void/Valor): Crie uma função que receba um número inteiro como parâmetro e
// imprima o dobro desse número. A função não deve retornar valor, apenas imprimir.

#include <stdio.h>

void dobro(int n) {
    printf("O dobro de %d e %d\n", n, n * 2);
}

int main() {
    int numero;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);

    dobro(numero);
    return 0;
}


// (3) Somar (Retorno/Valor): Crie uma função que receba dois números inteiros por valor,
// calcule a soma e retorne o resultado para a main, onde será impresso.

#include <stdio.h>

int somar(int a, int b) {
    int soma;

    soma = a + b;

    return soma;
}

int main() {
    int n1;
    int n2;
    int resultado;

    printf("Digite o primeiro numero: ");
    scanf("%d", &n1);
    printf("Digite o segundo numero: ");
    scanf("%d", &n2);

    resultado = somar(n1, n2);

    printf("Soma: %d\n", resultado);
    return 0;
}


// (4) Verificar Par (Retorno/Valor): Crie uma função que receba um inteiro. Se for par,
// retorne 1; se for ímpar, retorne 0. Na main, use um if para imprimir "Par" ou "Ímpar"
// baseado no retorno.

#include <stdio.h>

int verificarPar(int n) {
    if (n % 2 == 0) {
        return 1;
    }
    return 0;
}

int main() {
    int numero;

    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);

    if (verificarPar(numero) == 1) {
        printf("Par\n");
    } else {
        printf("Impar\n");
    }
    return 0;
}


// (5) Menu (Retorno/Sem Parâmetro): Crie uma função menu() que mostre 3 opções (1. Jogar,
// 2. Config, 3. Sair), leia a escolha do usuário e retorne esse valor inteiro para a main.

#include <stdio.h>

int menu() {
    int escolha;

    printf("1. Jogar\n");
    printf("2. Config\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    return escolha;
}

int main() {
    int opcao;

    opcao = menu();

    printf("Voce escolheu a opcao %d\n", opcao);
    return 0;
}


// (6) Tabuada Personalizada (Void/Valor): Crie uma função que receba um número N. A
// função deve imprimir a tabuada de 1 a 10 desse número.

#include <stdio.h>

void tabuada(int n) {
    int i;

    for (i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", n, i, n * i);
    }
}

int main() {
    int numero;

    printf("Digite um numero: ");
    scanf("%d", &numero);

    tabuada(numero);
    return 0;
}


// (7) Fatorial (Retorno/Valor): Implemente uma função que receba um número inteiro
// positivo e retorne o seu fatorial (Ex: 5! = 120).

#include <stdio.h>

double fatorial(int n) {
    double resultado = 1;
    int i;

    for (i = 1; i <= n; i++) {
        resultado = resultado * i;
    }

    return resultado;
}

int main() {
    int numero;
    double resultado;

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &numero);

    resultado = fatorial(numero);

    printf("%d! = %.0f\n", numero, resultado);
    return 0;
}



// (8) Troca de Valores (Void/Referência): Crie uma função chamada troca que receba dois
// ponteiros para inteiros (int *a, int *b). A função deve trocar os valores das variáveis
// originais criadas na main. Imprima os valores na main antes e depois de chamar a função
// para provar que a troca ocorreu.

#include <stdio.h>

void troca(int *a, int *b) {
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

int main() {
    int x;
    int y;

    printf("Digite o valor de x: ");
    scanf("%d", &x);
    printf("Digite o valor de y: ");
    scanf("%d", &y);

    printf("Antes da troca: x = %d e y = %d\n", x, y);

    troca(&x, &y);

    printf("Depois da troca: x = %d e y = %d\n", x, y);
    return 0;
}


// (9) Divisão com Resto (Void/Referência): Como uma função só retorna um valor, crie uma
// função que receba: o dividendo, o divisor, e dois ponteiros (um para guardar o resultado e
// outro para guardar o resto). A função deve calcular e armazenar os valores nos endereços de
// memória fornecidos.

#include <stdio.h>

void divisaoComResto(int dividendo, int divisor, int *quociente, int *resto) {
    *quociente = dividendo / divisor;
    *resto = dividendo % divisor;
}

int main() {
    int dividendo;
    int divisor;
    int quociente;
    int resto;

    printf("Digite o dividendo: ");
    scanf("%d", &dividendo);
    printf("Digite o divisor: ");
    scanf("%d", &divisor);

    if (divisor == 0) {
        printf("Nao existe divisao por zero\n");
    } else {
        divisaoComResto(dividendo, divisor, &quociente, &resto);

        printf("Quociente: %d\n", quociente);
        printf("Resto: %d\n", resto);
    }
    return 0;
}


// (10) Manipulação de Vetor (Referência implícita): Crie uma função que receba um vetor de
// inteiros e seu tamanho. A função deve percorrer o vetor e substituir todos os números
// negativos por zero. (Lembre-se: vetores são passados por referência automaticamente em C).

#include <stdio.h>

void zerarNegativos(int vetor[], int tamanho) {
    int i;

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] < 0) {
            vetor[i] = 0;
        }
    }
}

int main() {
    int numeros[5];
    int i;

    for (i = 0; i < 5; i++) {
        printf("Digite o %do numero: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    zerarNegativos(numeros, 5);

    printf("\nVetor depois da funcao:\n");
    for (i = 0; i < 5; i++) {
        printf("%d\n", numeros[i]);
    }
    return 0;
}



