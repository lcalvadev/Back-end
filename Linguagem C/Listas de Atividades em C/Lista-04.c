// (a) Elaborar um programa que apresente os quadrados dos números inteiros existentes na
// faixa de valores de 15 a 200.

#include <stdio.h>

int main() {
    int i;
    int quadrado;

    for (i = 15; i <= 200; i++) {
        quadrado = i * i;
        printf("%d ao quadrado = %d\n", i, quadrado);
    }
    return 0;
}


// (b) Elaborar um programa que mostre os resultados da tabuada de um número qualquer, a
// qual deve ser apresentada de acordo com sua forma tradicional. Ex.: 1x1 = 1   1x2 = 2

#include <stdio.h>

int main() {
    int numero;
    int i;
    int resultado;

    printf("Digite um numero: ");
    scanf("%d", &numero);

    for (i = 1; i <= 10; i++) {
        resultado = i * numero;
        printf("%dx%d = %d\n", i, numero, resultado);
    }
    return 0;
}


// (c) Construir um programa que apresente a soma dos cem primeiros números naturais:
// (1+2+3+...+98+99+100).

#include <stdio.h>

int main() {
    int i;
    int soma = 0;

    for (i = 1; i <= 100; i++) {
        soma = soma + i;
    }

    printf("Soma dos 100 primeiros numeros naturais: %d\n", soma);
    return 0;
}


// (d) Escrever um programa que apresente como resultado a potência de uma base qualquer
// elevada a um expoente qualquer, ou seja, BS^EX, em que BS é o valor da base e EX o valor do
// expoente. Considere apenas a entrada de valores inteiros e positivos, ou seja, números
// naturais. Use a técnica de laço de repetição, em que o valor da base deve ser multiplicado o
// número de vezes determinado no expoente.

#include <stdio.h>

int main() {
    int bs;
    int ex;
    int i;
    double resultado = 1;

    printf("Digite o valor da base: ");
    scanf("%d", &bs);
    printf("Digite o valor do expoente: ");
    scanf("%d", &ex);

    for (i = 1; i <= ex; i++) {
        resultado = resultado * bs;
    }

    printf("%d elevado a %d = %.0f\n", bs, ex, resultado);
    return 0;
}


// (e) Escrever um programa que apresente os valores da sequência de Fibonacci até o décimo
// quinto termo. A sequência de Fibonacci é formada por 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89,
// 144, 233, 377, ... etc., obtendo-se o próximo termo a partir da soma do termo atual com o
// anterior sucessivamente até o infinite sa a sequência não for interrompida.

#include <stdio.h>

int main() {
    int anterior = 0;
    int atual = 1;
    int proximo;
    int i;

    printf("Sequencia de Fibonacci (15 termos):\n");

    for (i = 1; i <= 15; i++) {
        printf("%d\n", anterior);
        proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }
    return 0;
}


// (f) Construir um programa que apresente todos os valores numéricos divisíveis por 4 e
// menores que 200. A variável que controla o contador do laço de repetição deve ser iniciada
// com valor 1 e possuir passo 1.

#include <stdio.h>

int main() {
    int contador = 1;

    while (contador < 200) {
        if (contador % 4 == 0) {
            printf("%d\n", contador);
        }
        contador++;
    }
    return 0;
}


// (g) Elaborar um programa que apresente os valores de conversão de graus Celsius em graus
// Fahrenheit, de dez em dez graus, iniciando a contagem em dez graus Celsius e finalizando em
// cem graus Celsius. O programa deve apresentar os valores das duas temperaturas.

#include <stdio.h>

int main() {
    int celsius = 10;
    float fahrenheit;

    while (celsius <= 100) {
        fahrenheit = (9 * celsius + 160) / 5.0;
        printf("%d graus Celsius = %.1f graus Fahrenheit\n", celsius, fahrenheit);
        celsius = celsius + 10;
    }
    return 0;
}


// (h) Escrever um programa que calcule e apresente o somatório do número de grãos de trigo
// que se pode obter num tabuleiro de xadrez, obedecendo à seguinte regra: colocar um grão de
// trigo no primeiro quadro e nos quadros seguintes o dobro do quadro anterior. Ou seja, no
// primeiro quadro coloca-se um grão, no segundo quadro colocam-se dois grãos (neste momento
// têm-se três grãos), no terceiro quadro colocam-se quatro grãos (tendo neste momento sete
// grãos), no quarto quadro colocam-se oito grãos (tendo-se então 15 grãos) até atingira
// sexagésimo quarto quadro.

#include <stdio.h>

int main() {
    int quadro = 1;
    double graos_quadro = 1;
    double total = 0;

    while (quadro <= 64) {
        total = total + graos_quadro;
        graos_quadro = graos_quadro * 2;
        quadro++;
    }

    printf("Total de graos no tabuleiro: %.0f\n", total);
    return 0;
}


// (i) Elaborar um programa que leia dez valores numéricos reais e apresente no final o
// somatório e a média dos valores lidos.

#include <stdio.h>

int main() {
    float valor;
    float soma = 0;
    float media;
    int contador = 1;

    while (contador <= 10) {
        printf("Digite o %do valor: ", contador);
        scanf("%f", &valor);
        soma = soma + valor;
        contador++;
    }

    media = soma / 10;

    printf("Somatorio: %.2f\n", soma);
    printf("Media: %.2f\n", media);
    return 0;
}



// (j) Elaborar um programa que leia sucessivamente valores numéricos e apresente no final o
// somatório, a média e o total de valores lidos. O programa deve ler os valores enquanto o
// usuário estiver fornecendo valores positivos. Ou seja, o programa deve parar quando o
// usuário fornecer um valor negativo (menor que zero).

#include <stdio.h>

int main() {
    float valor;
    float soma = 0;
    float media = 0;
    int total = 0;

    printf("Digite um valor (negativo para parar): ");
    scanf("%f", &valor);

    while (valor >= 0) {
        soma = soma + valor;
        total++;
        printf("Digite um valor (negativo para parar): ");
        scanf("%f", &valor);
    }

    if (total > 0) {
        media = soma / total;
    }

    printf("Somatorio: %.2f\n", soma);
    printf("Media: %.2f\n", media);
    printf("Total de valores lidos: %d\n", total);
    return 0;
}



// (k) Construir um programa que apresente como resultado a fatorial dos valores ímpares
// situados na faixa numérica de 1 até 10.

#include <stdio.h>

int main() {
    int numero = 1;
    int i;
    double fatorial;

    do {
        fatorial = 1;
        i = 1;
        do {
            fatorial = fatorial * i;
            i++;
        } while (i <= numero);

        printf("Fatorial de %d = %.0f\n", numero, fatorial);
        numero = numero + 2;
    } while (numero <= 10);

    return 0;
}


// (l) Elaborar um programa que apresente os resultados da soma e da média aritmética dos
// valores pares situados na faixa numérica de 50 até 70.

#include <stdio.h>

int main() {
    int numero = 50;
    int soma = 0;
    int quantidade = 0;
    float media;

    do {
        soma = soma + numero;
        quantidade++;
        numero = numero + 2;
    } while (numero <= 70);

    media = (float) soma / quantidade;

    printf("Soma dos pares de 50 a 70: %d\n", soma);
    printf("Media dos pares de 50 a 70: %.2f\n", media);
    return 0;
}



// (m) Escrever um programa que possibilite calcular a área total em metros de uma residência
// com os cômodos sala, cozinha, banheiro, dois quartos, área de serviço, quintal, garagem, entre
// outros que podem ser fornecidos ao programa. O programa deve solicitar a entrada do nome,
// da largura e do comprimento de um determinado cômodo. Em seguida, deve apresentar a área
// do cômodo lido e também uma mensagem solicitando ao usuário a confirmação de continuar
// calculando novos cômodos. Caso o usuário responda "NÃO", o programa deve apresentar o
// valor total acumulado da área residencial.

#include <stdio.h>

int main() {
    char nome[50];
    float largura;
    float comprimento;
    float area;
    float area_total = 0;
    char resposta;

    do {
        printf("Digite o nome do comodo: ");
        scanf(" %[^\n]", nome);
        printf("Digite a largura (m): ");
        scanf("%f", &largura);
        printf("Digite o comprimento (m): ");
        scanf("%f", &comprimento);

        area = largura * comprimento;
        area_total = area_total + area;

        printf("Area de %s: %.2f m2\n", nome, area);

        printf("Deseja calcular outro comodo? (S/N): ");
        scanf(" %c", &resposta);
    } while (resposta == 'S' || resposta == 's');

    printf("Area total da residencia: %.2f m2\n", area_total);
    return 0;
}



// (n) Elaborar um programa que leia valores positivos inteiros até que um valor negativo seja
// informado. Ao final devem ser apresentados o maior e o menor valores informados pelo
// usuário.

#include <stdio.h>

int main() {
    int valor;
    int maior = 0;
    int menor = 0;
    int primeiro = 1;

    do {
        printf("Digite um valor inteiro (negativo para parar): ");
        scanf("%d", &valor);

        if (valor >= 0) {
            if (primeiro == 1) {
                maior = valor;
                menor = valor;
                primeiro = 0;
            } else {
                if (valor > maior) {
                    maior = valor;
                }
                if (valor < menor) {
                    menor = valor;
                }
            }
        }
    } while (valor >= 0);

    if (primeiro == 1) {
        printf("Nenhum valor positivo foi informado\n");
    } else {
        printf("Maior valor: %d\n", maior);
        printf("Menor valor: %d\n", menor);
    }
    return 0;
}



// (o) Elaborar um programa que apresente o resultado da divisão de dois números quaisquer,
// representando o dividendo e o divisor da divisão a ser processada. Para a elaboração do
// programa, não utilize o operador aritmético de divisão com quociente inteiro DIV. Use uma
// solução baseada em laço de repetição. O programa deve apresentar como resultado
// (quociente) quantas vezes o divisor cabe no dividendo.

#include <stdio.h>

int main() {
    int dividendo;
    int divisor;
    int resto;
    int quociente = 0;

    printf("Digite o dividendo: ");
    scanf("%d", &dividendo);
    printf("Digite o divisor: ");
    scanf("%d", &divisor);

    if (divisor <= 0 || dividendo < 0) {
        printf("Informe um dividendo positivo e um divisor maior que zero\n");
    } else {
        resto = dividendo;

        do {
            if (resto >= divisor) {
                resto = resto - divisor;
                quociente++;
            }
        } while (resto >= divisor);

        printf("Quociente: %d\n", quociente);
        printf("Resto: %d\n", resto);
    }
    return 0;
}



