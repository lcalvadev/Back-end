// (1) Definição Básica: Crie uma struct chamada Horario com os campos hora, minuto e
// segundo. Na main, declare uma variável desse tipo, leia os valores do usuário e imprima no
// formato "HH:MM:SS".

#include <stdio.h>

struct Horario {
    int hora;
    int minuto;
    int segundo;
};

int main() {
    struct Horario h;

    printf("Digite a hora: ");
    scanf("%d", &h.hora);
    printf("Digite o minuto: ");
    scanf("%d", &h.minuto);
    printf("Digite o segundo: ");
    scanf("%d", &h.segundo);

    printf("%02d:%02d:%02d\n", h.hora, h.minuto, h.segundo);
    return 0;
}



// (2) Cadastro de Livro: Crie uma struct Livro com título (string), autor (string) e paginas
// (int). Leia os dados de um livro e imprima.

#include <stdio.h>

struct Livro {
    char titulo[100];
    char autor[100];
    int paginas;
};

int main() {
    struct Livro livro;

    printf("Digite o titulo: ");
    scanf(" %[^\n]", livro.titulo);
    printf("Digite o autor: ");
    scanf(" %[^\n]", livro.autor);
    printf("Digite o numero de paginas: ");
    scanf("%d", &livro.paginas);

    printf("\nTitulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Paginas: %d\n", livro.paginas);
    return 0;
}


// (3) Distância entre Pontos: Crie uma struct Ponto com coordenadas x e y (float). Leia dois
// pontos (A e B) e calcule a distância entre eles (Fórmula: D = raiz de ((x2-x1)² + (y2-y1)²)).
// Se necessário use <math.h>.

#include <stdio.h>
#include <math.h>

struct Ponto {
    float x;
    float y;
};

int main() {
    struct Ponto a;
    struct Ponto b;
    float distancia;

    printf("Digite o x do ponto A: ");
    scanf("%f", &a.x);
    printf("Digite o y do ponto A: ");
    scanf("%f", &a.y);
    printf("Digite o x do ponto B: ");
    scanf("%f", &b.x);
    printf("Digite o y do ponto B: ");
    scanf("%f", &b.y);

    distancia = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));

    printf("Distancia entre A e B: %.2f\n", distancia);
    return 0;
}


// (4) Vetor de Estruturas: Crie uma struct Pessoa com nome e idade. Declare um vetor de
// Pessoa para 3 pessoas. Leia os dados de todas e, ao final, imprima apenas o nome da pessoa
// mais velha.

#include <stdio.h>

struct Pessoa {
    char nome[50];
    int idade;
};

int main() {
    struct Pessoa pessoas[3];
    int i;
    int mais_velha = 0;

    for (i = 0; i < 3; i++) {
        printf("Pessoa %d - Nome: ", i + 1);
        scanf(" %[^\n]", pessoas[i].nome);
        printf("Pessoa %d - Idade: ", i + 1);
        scanf("%d", &pessoas[i].idade);
    }

    for (i = 1; i < 3; i++) {
        if (pessoas[i].idade > pessoas[mais_velha].idade) {
            mais_velha = i;
        }
    }

    printf("Pessoa mais velha: %s\n", pessoas[mais_velha].nome);
    return 0;
}


// (5) Média de Alunos: Crie uma struct Aluno contendo nome e duas notas (n1, n2). Leia os
// dados de 3 alunos. Para cada um, calcule a média e imprima: "Nome: [Nome] - Média:
// [Média] - [Aprovado/Reprovado]" (Aprovado se média >= 7.0).

#include <stdio.h>

struct Aluno {
    char nome[50];
    float n1;
    float n2;
};

int main() {
    struct Aluno alunos[3];
    int i;
    float media;

    for (i = 0; i < 3; i++) {
        printf("Aluno %d - Nome: ", i + 1);
        scanf(" %[^\n]", alunos[i].nome);
        printf("Aluno %d - Nota 1: ", i + 1);
        scanf("%f", &alunos[i].n1);
        printf("Aluno %d - Nota 2: ", i + 1);
        scanf("%f", &alunos[i].n2);
    }

    printf("\n");

    for (i = 0; i < 3; i++) {
        media = (alunos[i].n1 + alunos[i].n2) / 2;

        if (media >= 7.0) {
            printf("Nome: %s - Media: %.2f - Aprovado\n", alunos[i].nome, media);
        } else {
            printf("Nome: %s - Media: %.2f - Reprovado\n", alunos[i].nome, media);
        }
    }
    return 0;
}


// (6) Struct Aninhada (Data de Nascimento): Crie uma struct Data (dia, mes, ano). Crie uma
// struct Funcionario que contenha nome, salario e uma variável do tipo Data chamada
// nascimento. Leia os dados de um funcionário e imprima sua data de nascimento formatada.

#include <stdio.h>

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Funcionario {
    char nome[50];
    float salario;
    struct Data nascimento;
};

int main() {
    struct Funcionario f;

    printf("Digite o nome: ");
    scanf(" %[^\n]", f.nome);
    printf("Digite o salario: ");
    scanf("%f", &f.salario);
    printf("Digite o dia de nascimento: ");
    scanf("%d", &f.nascimento.dia);
    printf("Digite o mes de nascimento: ");
    scanf("%d", &f.nascimento.mes);
    printf("Digite o ano de nascimento: ");
    scanf("%d", &f.nascimento.ano);

    printf("\nFuncionario: %s\n", f.nome);
    printf("Data de nascimento: %02d/%02d/%04d\n",
           f.nascimento.dia, f.nascimento.mes, f.nascimento.ano);
    return 0;
}



// (7) Gerenciamento de Estoque: Crie uma struct Produto (codigo, nome, preco, quantidade).
// Leia 3 produtos. Em seguida, o usuário deve informar um código. O programa deve procurar
// esse código no vetor e, se encontrar, imprimir o nome e o preço do produto.

#include <stdio.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};

int main() {
    struct Produto estoque[3];
    int i;
    int codigo_busca;
    int encontrado = 0;

    for (i = 0; i < 3; i++) {
        printf("Produto %d - Codigo: ", i + 1);
        scanf("%d", &estoque[i].codigo);
        printf("Produto %d - Nome: ", i + 1);
        scanf(" %[^\n]", estoque[i].nome);
        printf("Produto %d - Preco: ", i + 1);
        scanf("%f", &estoque[i].preco);
        printf("Produto %d - Quantidade: ", i + 1);
        scanf("%d", &estoque[i].quantidade);
    }

    printf("\nDigite o codigo que deseja procurar: ");
    scanf("%d", &codigo_busca);

    for (i = 0; i < 3; i++) {
        if (estoque[i].codigo == codigo_busca) {
            printf("Nome: %s\n", estoque[i].nome);
            printf("Preco: R$ %.2f\n", estoque[i].preco);
            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("Produto nao encontrado\n");
    }
    return 0;
}



// (8) Atualização Lógica: Utilizando a mesma struct do exercício anterior (Estoque),
// implemente uma lógica onde o usuário insere um código e uma quantidade vendida. O
// programa deve subtrair essa quantidade do estoque do produto correto. Se o estoque ficar
// negativo, avise que a venda não é possível.

#include <stdio.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};

int main() {
    struct Produto estoque[3];
    int i;
    int codigo_venda;
    int quantidade_vendida;
    int encontrado = 0;

    for (i = 0; i < 3; i++) {
        printf("Produto %d - Codigo: ", i + 1);
        scanf("%d", &estoque[i].codigo);
        printf("Produto %d - Nome: ", i + 1);
        scanf(" %[^\n]", estoque[i].nome);
        printf("Produto %d - Preco: ", i + 1);
        scanf("%f", &estoque[i].preco);
        printf("Produto %d - Quantidade: ", i + 1);
        scanf("%d", &estoque[i].quantidade);
    }

    printf("\nDigite o codigo do produto vendido: ");
    scanf("%d", &codigo_venda);
    printf("Digite a quantidade vendida: ");
    scanf("%d", &quantidade_vendida);

    for (i = 0; i < 3; i++) {
        if (estoque[i].codigo == codigo_venda) {
            encontrado = 1;

            if (estoque[i].quantidade - quantidade_vendida < 0) {
                printf("Venda nao e possivel: estoque insuficiente\n");
            } else {
                estoque[i].quantidade = estoque[i].quantidade - quantidade_vendida;
                printf("Venda realizada! Estoque atual de %s: %d\n",
                       estoque[i].nome, estoque[i].quantidade);
            }
        }
    }

    if (encontrado == 0) {
        printf("Produto nao encontrado\n");
    }
    return 0;
}



// (9) Ordenação de Structs: Crie uma struct Atleta com nome e altura. Leia 3 atletas. Ao final,
// o programa deve exibir os nomes dos atletas ordenados do mais baixo para o mais alto.

#include <stdio.h>

struct Atleta {
    char nome[50];
    float altura;
};

int main() {
    struct Atleta atletas[3];
    struct Atleta aux;
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        printf("Atleta %d - Nome: ", i + 1);
        scanf(" %[^\n]", atletas[i].nome);
        printf("Atleta %d - Altura (m): ", i + 1);
        scanf("%f", &atletas[i].altura);
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2 - i; j++) {
            if (atletas[j].altura > atletas[j + 1].altura) {
                aux = atletas[j];
                atletas[j] = atletas[j + 1];
                atletas[j + 1] = aux;
            }
        }
    }

    printf("\nDo mais baixo para o mais alto:\n");
    for (i = 0; i < 3; i++) {
        printf("%s (%.2f m)\n", atletas[i].nome, atletas[i].altura);
    }
    return 0;
}





// (10) Sistema Complexo (Aninhamento e Vetores): Crie uma struct Endereco (rua, numero,
// cidade). Crie uma struct Cliente que contenha nome, telefone e um struct Endereco.
// Cadastre 3 clientes. Ao final, solicite ao usuário o nome de uma cidade e liste todos os
// clientes que moram naquela cidade.

#include <stdio.h>
#include <string.h>

struct Endereco {
    char rua[50];
    int numero;
    char cidade[50];
};

struct Cliente {
    char nome[50];
    char telefone[20];
    struct Endereco endereco;
};

int main() {
    struct Cliente clientes[3];
    char cidade_busca[50];
    int i;
    int encontrado = 0;

    for (i = 0; i < 3; i++) {
        printf("Cliente %d - Nome: ", i + 1);
        scanf(" %[^\n]", clientes[i].nome);
        printf("Cliente %d - Telefone: ", i + 1);
        scanf(" %[^\n]", clientes[i].telefone);
        printf("Cliente %d - Rua: ", i + 1);
        scanf(" %[^\n]", clientes[i].endereco.rua);
        printf("Cliente %d - Numero: ", i + 1);
        scanf("%d", &clientes[i].endereco.numero);
        printf("Cliente %d - Cidade: ", i + 1);
        scanf(" %[^\n]", clientes[i].endereco.cidade);
    }

    printf("\nDigite o nome da cidade que deseja buscar: ");
    scanf(" %[^\n]", cidade_busca);

    printf("\nClientes que moram em %s:\n", cidade_busca);
    for (i = 0; i < 3; i++) {
        if (strcmp(clientes[i].endereco.cidade, cidade_busca) == 0) {
            printf("%s - Tel: %s - %s, %d\n", clientes[i].nome, clientes[i].telefone,
                   clientes[i].endereco.rua, clientes[i].endereco.numero);
            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("Nenhum cliente encontrado nessa cidade\n");
    }
    return 0;
}