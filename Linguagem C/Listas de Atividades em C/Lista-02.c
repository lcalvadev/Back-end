// (a) Ler uma temperatura em graus Celsius e apresentá-la convertida em graus Fahrenheit.
// A fórmula de conversão é F:=(9*C+160)/5, sendo F a temperatura em Fahrenheit e C a
// temperatura em Celsius.

#include <stdio.h>

int main() {
    float c;
    float f;

    printf("Digite a temperatura em Celsius: ");
    scanf("%f", &c);

    f = (9 * c + 160) / 5;

    printf("Temperatura em Fahrenheit: %.2f\n", f);
    return 0;
}


// (b) Efetuar o cálculo da quantidade de litros de combustível gasta em uma viagem,
// utilizando um automóvel que faz 12 quilômetros por litro. Para obter o cálculo, o usuário
// deve fornecer o tempo gasto e a velocidade média durante a viagem. Desta forma, será
// possível obter a distância percorrida com a fórmula DISTANCIA:= TEMPO * VELOCIDADE.
// A partir do valor da distância, basta calcular a quantidade de litros de combustível
// utilizada na viagem com a fórmula LITROS_USADOS := DISTANCIA/12. O programa deve
// apresentar os valores da velocidade média, tempo gasto na viagem, a distância percorrida
// e a quantidade de litros utilizada na viagem.

#include <stdio.h>

int main() {
    float velocidade;
    float tempo;
    float distancia;
    float litros_usados;

    printf("Digite a velocidade media (km/h): ");
    scanf("%f", &velocidade);
    printf("Digite o tempo gasto na viagem (h): ");
    scanf("%f", &tempo);

    distancia = tempo * velocidade;
    litros_usados = distancia / 12;

    printf("Velocidade media: %.2f km/h\n", velocidade);
    printf("Tempo gasto: %.2f h\n", tempo);
    printf("Distancia percorrida: %.2f km\n", distancia);
    printf("Litros usados: %.2f\n", litros_usados);
    return 0;
}


// (c) Efetuar o cálculo e apresentar o valor de uma prestação de um bem em atraso,
// utilizando a fórmula PRESTAÇÃO:=VALOR + (VALOR*(TAXA/100)*TEMPO).

#include <stdio.h>

int main() {
    float valor;
    float taxa;
    float tempo;
    float prestacao;

    printf("Digite o valor da prestacao: ");
    scanf("%f", &valor);
    printf("Digite a taxa de juros (%%): ");
    scanf("%f", &taxa);
    printf("Digite o tempo de atraso: ");
    scanf("%f", &tempo);

    prestacao = valor + (valor * (taxa / 100) * tempo);

    printf("Valor da prestacao com atraso: %.2f\n", prestacao);
    return 0;
}

// (d) Os dois valores para as variáveis A e B devem ser lidos e efetuar a troca dos valores
// de forma que a variável A passe a possuir o valor da variável B e a variável B passe a
// possuir o valor da variável A. Apresentar os valores após a efetivação do processamento
// da troca.

#include <stdio.h>

int main() {
    int a;
    int b;
    int aux;

    printf("Digite o valor de A: ");
    scanf("%d", &a);
    printf("Digite o valor de B: ");
    scanf("%d", &b);

    aux = a;
    a = b;
    b = aux;

    printf("Apos a troca: A = %d e B = %d\n", a, b);
    return 0;
}


// (e) Ler quatro valores numéricos inteiros e apresentar o resultado das adições e das
// multiplicações para a máxima combinação possível entre os quatro variáveis. Considerando
// a leitura de valores para as variáveis A, B, C e D, devem ser feitas seis adições e seis
// multiplicações, ou seja, deve ser combinada a variável A com a variável B, a variável A com
// a variável C, a variável A com a variável D. Depois é necessário combinar a variável B com
// a variável C e a variável B com a variável D e, por fim, a variável C será combinada com a
// variável D.

#include <stdio.h>

int main() {
    int a;
    int b;
    int c;
    int d;

    printf("Digite o valor de A: ");
    scanf("%d", &a);
    printf("Digite o valor de B: ");
    scanf("%d", &b);
    printf("Digite o valor de C: ");
    scanf("%d", &c);
    printf("Digite o valor de D: ");
    scanf("%d", &d);

    printf("A + B = %d\n", a + b);
    printf("A + C = %d\n", a + c);
    printf("A + D = %d\n", a + d);
    printf("B + C = %d\n", b + c);
    printf("B + D = %d\n", b + d);
    printf("C + D = %d\n", c + d);

    printf("A * B = %d\n", a * b);
    printf("A * C = %d\n", a * c);
    printf("A * D = %d\n", a * d);
    printf("B * C = %d\n", b * c);
    printf("B * D = %d\n", b * d);
    printf("C * D = %d\n", c * d);
    return 0;
}




// (f) Efetuar a leitura de um valor numérico inteiro e apresentar o resultado do valor lido
// elevado ao quadrado.

#include <stdio.h>

int main() {
    int valor;
    int quadrado;

    printf("Digite um valor inteiro: ");
    scanf("%d", &valor);

    quadrado = valor * valor;

    printf("%d elevado ao quadrado = %d\n", valor, quadrado);
    return 0;
}




// (g) Elaborar um programa que apresente o valor da conversão em real (R$) de um valor
// lido em dólar (US$). O programa deve solicitar o valor da cotação do dólar e também a
// quantidade de dólares disponível com o usuário.

#include <stdio.h>

int main() {
    float cotacao;
    float dolares;
    float reais;

    printf("Digite a cotacao do dolar: ");
    scanf("%f", &cotacao);
    printf("Digite a quantidade de dolares disponivel: ");
    scanf("%f", &dolares);

    reais = dolares * cotacao;

    printf("US$ %.2f equivalem a R$ %.2f\n", dolares, reais);
    return 0;
}



// (h) Elaborar um programa que leia o valor numérico correspondente ao salário mensal de
// um trabalhador e também faça a leitura do valor do percentual de reajuste que será
// atribuído. Apresentar o valor do novo salário.

#include <stdio.h>

int main() {
    float salario;
    float percentual;
    float novo_salario;

    printf("Digite o salario atual: ");
    scanf("%f", &salario);
    printf("Digite o percentual de reajuste (%%): ");
    scanf("%f", &percentual);

    novo_salario = salario + (salario * percentual / 100);

    printf("Novo salario: R$ %.2f\n", novo_salario);
    return 0;
}



// (i) Em uma eleição sindical concorreram ao cargo de presidente três candidatos. Durante a
// apuração dos votos foram computados votos nulos e em branco, além dos votos válidos para
// cada candidato. Deve ser criado um programa de computador que faça a leitura da quantidade
// de votos válidos para cada candidato, além de ler também a quantidade de votos nulos e em
// branco. Ao final o programa deve apresentar o número total de eleitores, considerando votos
// válidos, nulos e em branco; o percentual correspondente de votos válidos em relação à
// quantidade de eleitores; o percentual correspondente de votos válidos do candidato A em
// relação à quantidade de eleitores; o percentual correspondente de votos válidos do candidato
// B em relação à quantidade de eleitores; o percentual correspondente de votos válidos do
// candidato C em relação à quantidade de eleitores; o percentual correspondente de votos nulos
// em relação à quantidade de eleitores; e por último o percentual correspondente de votos em
// branco em relação à quantidade de eleitores.

#include <stdio.h>

int main() {
    int votos_a;
    int votos_b;
    int votos_c;
    int nulos;
    int brancos;
    int validos;
    int eleitores;
    float perc_validos;
    float perc_a;
    float perc_b;
    float perc_c;
    float perc_nulos;
    float perc_brancos;

    printf("Votos validos do candidato A: ");
    scanf("%d", &votos_a);
    printf("Votos validos do candidato B: ");
    scanf("%d", &votos_b);
    printf("Votos validos do candidato C: ");
    scanf("%d", &votos_c);
    printf("Votos nulos: ");
    scanf("%d", &nulos);
    printf("Votos em branco: ");
    scanf("%d", &brancos);

    validos = votos_a + votos_b + votos_c;
    eleitores = validos + nulos + brancos;

    perc_validos = (float) validos / eleitores * 100;
    perc_a = (float) votos_a / eleitores * 100;
    perc_b = (float) votos_b / eleitores * 100;
    perc_c = (float) votos_c / eleitores * 100;
    perc_nulos = (float) nulos / eleitores * 100;
    perc_brancos = (float) brancos / eleitores * 100;

    printf("Total de eleitores: %d\n", eleitores);
    printf("Percentual de votos validos: %.2f%%\n", perc_validos);
    printf("Percentual de votos do candidato A: %.2f%%\n", perc_a);
    printf("Percentual de votos do candidato B: %.2f%%\n", perc_b);
    printf("Percentual de votos do candidato C: %.2f%%\n", perc_c);
    printf("Percentual de votos nulos: %.2f%%\n", perc_nulos);
    printf("Percentual de votos em branco: %.2f%%\n", perc_brancos);
    return 0;
}


// (j) Elaborar um programa que leia dois valores numéricos reais desconhecidos. Calcular e
// apresentar os resultados das quatro operações aritméticas básicas.

#include <stdio.h>

int main() {
    float a;
    float b;

    printf("Digite o primeiro valor: ");
    scanf("%f", &a);
    printf("Digite o segundo valor: ");
    scanf("%f", &b);

    printf("Soma: %.2f\n", a + b);
    printf("Subtracao: %.2f\n", a - b);
    printf("Multiplicacao: %.2f\n", a * b);
    printf("Divisao: %.2f\n", a / b);
    return 0;
}