// (a) Efetuar leitura de dois valores numéricos inteiros e apresentar o resultado da
// diferença do maior valor pelo menor valor.

#include <stdio.h>

int main() {
    int a;
    int b;
    int diferenca;

    printf("Digite o primeiro valor: ");
    scanf("%d", &a);
    printf("Digite o segundo valor: ");
    scanf("%d", &b);

    if (a > b) {
        diferenca = a - b;
    } else {
        diferenca = b - a;
    }

    printf("Diferenca do maior pelo menor: %d\n", diferenca);
    return 0;
}

// (b) Ler os valores de quatro notas escolares bimestrais de um aluno. Calcular a média
// aritmética desse aluno e apresentar a mensagem "Aprovado" se a média obtida for maior ou
// igual a 7; caso contrário, o programa deve solicitar a quinta nota (nota de exame) do aluno
// e calcular uma nova média entre a nota de exame e a primeira média aritmética. Se o valor
// da nova média for maior ou igual a sete, apresentar a mensagem "Aprovado em exame"; caso
// contrário, apresentar a mensagem "Reprovado". Informar também, após a apresentação das
// mensagens, o valor da média obtida pelo aluno.

#include <stdio.h>

int main() {
    float nota1;
    float nota2;
    float nota3;
    float nota4;
    float nota_exame;
    float media;
    float nova_media;

    printf("Digite a nota do 1o bimestre: ");
    scanf("%f", &nota1);
    printf("Digite a nota do 2o bimestre: ");
    scanf("%f", &nota2);
    printf("Digite a nota do 3o bimestre: ");
    scanf("%f", &nota3);
    printf("Digite a nota do 4o bimestre: ");
    scanf("%f", &nota4);

    media = (nota1 + nota2 + nota3 + nota4) / 4;

    if (media >= 7) {
        printf("Aprovado\n");
    } else {
        printf("Digite a nota de exame: ");
        scanf("%f", &nota_exame);

        nova_media = (media + nota_exame) / 2;
        media = nova_media;

        if (nova_media >= 7) {
            printf("Aprovado em exame\n");
        } else {
            printf("Reprovado\n");
        }
    }

    printf("Media obtida: %.2f\n", media);
    return 0;
}


// (c) Efetuar a leitura de três valores numéricos e processar o cálculo da equação completa
// de segundo grau, utilizando a fórmula de Bhaskara (considerar para a solução do problema
// todas as possíveis condições para delta: delta < 0 - não há solução real, delta > 0 - há duas
// soluções reais e diferentes e delta = 0 - há apenas uma solução real). Lembre-se de que é a
// equação completa de segundo grau que possui todos os coeficientes A, B e C diferentes de
// zero. O programa deve apresentar respostas para todas as condições estabelecidas para delta.

#include <stdio.h>
#include <math.h>

int main() {
    float a;
    float b;
    float c;
    float delta;
    float x1;
    float x2;

    printf("Digite o valor de A: ");
    scanf("%f", &a);
    printf("Digite o valor de B: ");
    scanf("%f", &b);
    printf("Digite o valor de C: ");
    scanf("%f", &c);

    delta = b * b - 4 * a * c;

    if (delta < 0) {
        printf("Delta = %.2f: nao ha solucao real\n", delta);
    } else if (delta == 0) {
        x1 = -b / (2 * a);
        printf("Delta = 0: ha apenas uma solucao real\n");
        printf("x = %.2f\n", x1);
    } else {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);
        printf("Delta = %.2f: ha duas solucoes reais e diferentes\n", delta);
        printf("x1 = %.2f\n", x1);
        printf("x2 = %.2f\n", x2);
    }
    return 0;
}


// (d) Ler três valores inteiros e apresentar os valores lidos dispostos em ordem crescente.

#include <stdio.h>

int main() {
    int a;
    int b;
    int c;
    int aux;

    printf("Digite o primeiro valor: ");
    scanf("%d", &a);
    printf("Digite o segundo valor: ");
    scanf("%d", &b);
    printf("Digite o terceiro valor: ");
    scanf("%d", &c);

    if (a > b) {
        aux = a;
        a = b;
        b = aux;
    }
    if (a > c) {
        aux = a;
        a = c;
        c = aux;
    }
    if (b > c) {
        aux = b;
        b = c;
        c = aux;
    }

    printf("Valores em ordem crescente: %d, %d, %d\n", a, b, c);
    return 0;
}


// (e) Fazer a leitura de 4 valores numéricos inteiros. Apresentar apenas os valores que
// sejam divisíveis por 2 e 3.

#include <stdio.h>

int main() {
    int a;
    int b;
    int c;
    int d;

    printf("Digite o primeiro valor: ");
    scanf("%d", &a);
    printf("Digite o segundo valor: ");
    scanf("%d", &b);
    printf("Digite o terceiro valor: ");
    scanf("%d", &c);
    printf("Digite o quarto valor: ");
    scanf("%d", &d);

    if (a % 2 == 0 && a % 3 == 0) {
        printf("%d e divisivel por 2 e 3\n", a);
    }
    if (b % 2 == 0 && b % 3 == 0) {
        printf("%d e divisivel por 2 e 3\n", b);
    }
    if (c % 2 == 0 && c % 3 == 0) {
        printf("%d e divisivel por 2 e 3\n", c);
    }
    if (d % 2 == 0 && d % 3 == 0) {
        printf("%d e divisivel por 2 e 3\n", d);
    }
    return 0;
}


// (f) Ler cinco valores numéricos inteiros, identificar e apresentar o maior e o menor
// valores informados.

#include <stdio.h>

int main() {
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
    int maior;
    int menor;

    printf("Digite o primeiro valor: ");
    scanf("%d", &v1);
    printf("Digite o segundo valor: ");
    scanf("%d", &v2);
    printf("Digite o terceiro valor: ");
    scanf("%d", &v3);
    printf("Digite o quarto valor: ");
    scanf("%d", &v4);
    printf("Digite o quinto valor: ");
    scanf("%d", &v5);

    maior = v1;
    menor = v1;

    if (v2 > maior) maior = v2;
    if (v3 > maior) maior = v3;
    if (v4 > maior) maior = v4;
    if (v5 > maior) maior = v5;

    if (v2 < menor) menor = v2;
    if (v3 < menor) menor = v3;
    if (v4 < menor) menor = v4;
    if (v5 < menor) menor = v5;

    printf("Maior valor: %d\n", maior);
    printf("Menor valor: %d\n", menor);
    return 0;
}


// (g) Ler um valor numérico inteiro, apresentar uma mensagem informando se o valor
// fornecido é par ou ímpar.

#include <stdio.h>

int main() {
    int valor;

    printf("Digite um valor inteiro: ");
    scanf("%d", &valor);

    if (valor % 2 == 0) {
        printf("O valor %d e par\n", valor);
    } else {
        printf("O valor %d e impar\n", valor);
    }
    return 0;
}


// (h) Efetuar a leitura de um valor numérico inteiro que esteja na faixa de 1 até 9. O programa
// deve apresentar a mensagem "O valor está na faixa permitida", caso o valor informado esteja
// entre 1 e 9. Se o valor estiver fora da faixa, o programa deve apresentar a mensagem "O
// valor está fora da faixa permitida".

#include <stdio.h>

int main() {
    int valor;

    printf("Digite um valor inteiro: ");
    scanf("%d", &valor);

    if (valor >= 1 && valor <= 9) {
        printf("O valor esta na faixa permitida\n");
    } else {
        printf("O valor esta fora da faixa permitida\n");
    }
    return 0;
}


// (i) Efetuar a leitura do sexo de uma pessoa e apresentar como saída uma das seguintes
// mensagens: "Excelentíssimo Senhor,", caso seja informado o sexo masculino, ou
// "Excelentíssimo Senhora", caso seja informado o sexo feminino. O programa deve, após a
// entrada do sexo, verificar primeiramente se o sexo fornecido é realmente válido, ou seja, se
// é igual a "M" ou a "F". Não sendo essa condição verdadeira, o programa deve apresentar a
// mensagem "Sexo informado inválido".

#include <stdio.h>

int main() {
    char sexo;

    printf("Digite o sexo (M ou F): ");
    scanf(" %c", &sexo);

    if (sexo == 'M' || sexo == 'F') {
        if (sexo == 'M') {
            printf("Excelentissimo Senhor,\n");
        } else {
            printf("Excelentissima Senhora,\n");
        }
    } else {
        printf("Sexo informado invalido\n");
    }
    return 0;
}


// (j) Efetuar a leitura de três valores inteiros desconhecidos, somar os valores fornecidos e
// apresentar o resultado somente se for maior ou igual a 100.

#include <stdio.h>

int main() {
    int a;
    int b;
    int c;
    int soma;

    printf("Digite o primeiro valor: ");
    scanf("%d", &a);
    printf("Digite o segundo valor: ");
    scanf("%d", &b);
    printf("Digite o terceiro valor: ");
    scanf("%d", &c);

    soma = a + b + c;

    if (soma >= 100) {
        printf("Soma: %d\n", soma);
    }
    return 0;
}



// (k) Escreva um programa utilizando estruturas de múltipla escolha que imprima na tela o
// mês de acordo com o número digitado pelo usuário. Exemplo: Se escolhido 2 irá imprimir
// Fevereiro.

#include <stdio.h>

int main() {
    int mes;

    printf("Digite o numero do mes (1 a 12): ");
    scanf("%d", &mes);

    switch (mes) {
        case 1:
            printf("Janeiro\n");
            break;
        case 2:
            printf("Fevereiro\n");
            break;
        case 3:
            printf("Marco\n");
            break;
        case 4:
            printf("Abril\n");
            break;
        case 5:
            printf("Maio\n");
            break;
        case 6:
            printf("Junho\n");
            break;
        case 7:
            printf("Julho\n");
            break;
        case 8:
            printf("Agosto\n");
            break;
        case 9:
            printf("Setembro\n");
            break;
        case 10:
            printf("Outubro\n");
            break;
        case 11:
            printf("Novembro\n");
            break;
        case 12:
            printf("Dezembro\n");
            break;
        default:
            printf("Mes invalido\n");
    }
    return 0;
}


// (l) Crie um algoritmo, utilizando estruturas de múltipla escolha, que imprima na tela o
// sexo (Masculino ou Feminino) de uma pessoa. Utilize caracteres (M ou F) como entrada.

#include <stdio.h>

int main() {
    char sexo;

    printf("Digite o sexo (M ou F): ");
    scanf(" %c", &sexo);

    switch (sexo) {
        case 'M':
        case 'm':
            printf("Masculino\n");
            break;
        case 'F':
        case 'f':
            printf("Feminino\n");
            break;
        default:
            printf("Sexo invalido\n");
    }
    return 0;
}


// (m) As taxas de natalidade e mortalidade representam indicadores de desenvolvimento
// humano que analisam tanto o aumento da população quanto o seu declínio. Permitem analisar
// a dinâmica de uma população, segundo as variáveis que as influenciam, como qualidade de
// vida, renda, nível de desenvolvimento do país ou unidade federativa em questão. (Escola
// Kids, 2020).
// Sabendo disto, faça um programa, utilizando estruturas de múltipla escolha, que solicite ao
// usuário qual cálculo de taxa ele quer realizar. Utilize as fórmulas abaixo para o cálculo, sendo:
// Taxa de mortalidade = (nº de óbitos x 1000) / (nº de habitantes)
// Taxa de natalidade = (nº de nascimentos x 1000) / (nº de habitantes)

#include <stdio.h>

int main() {
    int opcao;
    float obitos;
    float nascimentos;
    float habitantes;
    float taxa;

    printf("Qual taxa deseja calcular?\n");
    printf("1 - Taxa de mortalidade\n");
    printf("2 - Taxa de natalidade\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite o numero de obitos: ");
            scanf("%f", &obitos);
            printf("Digite o numero de habitantes: ");
            scanf("%f", &habitantes);
            taxa = (obitos * 1000) / habitantes;
            printf("Taxa de mortalidade: %.2f\n", taxa);
            break;
        case 2:
            printf("Digite o numero de nascimentos: ");
            scanf("%f", &nascimentos);
            printf("Digite o numero de habitantes: ");
            scanf("%f", &habitantes);
            taxa = (nascimentos * 1000) / habitantes;
            printf("Taxa de natalidade: %.2f\n", taxa);
            break;
        default:
            printf("Opcao invalida\n");
    }
    return 0;
}


// (n) Uma escola fornece 5% de desconto para pagamento da mensalidade em dia. A escola
// ainda fornece, além deste desconto, um desconto adicional de 50% para filhos de
// funcionários. Faça um programa que receba os dados de matrícula, valor da mensalidade e se
// o pagamento foi feito em dia ou não. Após isto calcule o programa deverá ler um código que
// identifique se o aluno é filho de funcionário (1) ou aluno comum (2) e com base nisso, utilize
// uma estrutura de múltipla escolha para calcular o valor a ser pago na mensalidade.

#include <stdio.h>

int main() {
    int matricula;
    float mensalidade;
    int pagamento_em_dia;
    int tipo_aluno;
    float valor_pagar;

    printf("Digite a matricula: ");
    scanf("%d", &matricula);
    printf("Digite o valor da mensalidade: ");
    scanf("%f", &mensalidade);
    printf("Pagamento em dia? (1 - Sim, 2 - Nao): ");
    scanf("%d", &pagamento_em_dia);
    printf("Tipo de aluno (1 - Filho de funcionario, 2 - Aluno comum): ");
    scanf("%d", &tipo_aluno);

    valor_pagar = mensalidade;

    if (pagamento_em_dia == 1) {
        valor_pagar = mensalidade * 0.95;
    }

    switch (tipo_aluno) {
        case 1:
            if (pagamento_em_dia == 1) {
                valor_pagar = valor_pagar * 0.5;
            }
            break;
        case 2:
            break;
        default:
            printf("Codigo de aluno invalido\n");
    }

    printf("Matricula: %d\n", matricula);
    printf("Valor a pagar: R$ %.2f\n", valor_pagar);
    return 0;
}   