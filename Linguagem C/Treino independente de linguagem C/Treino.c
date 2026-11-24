// Projeto 1: Boletim da Turma
// Crie um programa que cadastre 5 alunos. Para cada aluno, guarde nome, matrícula e 3 notas.
// Depois de cadastrar, o programa deve:
// 1. Calcular a média de cada aluno e imprimir: "Nome: [Nome] - Média: [Média] - [Situação]".
//    Média >= 7 é Aprovado, entre 5 e 6,99 é Recuperação e abaixo de 5 é Reprovado.
// 2. Mostrar o nome do aluno com a maior média e o do aluno com a menor média.
// 3. Mostrar a média geral da turma e quantos alunos estão em cada situação.
// 4. Ordenar os alunos da maior para a menor média e exibir a lista (Bubble Sort).

#include <stdio.h>

struct Aluno {
    char nome[50];
    int matricula;
    float notas[3];
};

float calcularMedia(struct Aluno a) {
    float media;

    media = (a.notas[0] + a.notas[1] + a.notas[2]) / 3;

    return media;
}

void situacao(float media) {
    if (media >= 7) {
        printf("Aprovado\n");
    } else if (media >= 5) {
        printf("Recuperacao\n");
    } else {
        printf("Reprovado\n");
    }
}

int main() {
    struct Aluno alunos[5];
    struct Aluno aux;
    float medias[5];
    float soma = 0;
    float media_turma;
    int aprovados = 0;
    int recuperacao = 0;
    int reprovados = 0;
    int pos_maior = 0;
    int pos_menor = 0;
    int i;
    int j;

    // Leitura dos dados
    for (i = 0; i < 5; i++) {
        printf("Aluno %d - Nome: ", i + 1);
        scanf(" %[^\n]", alunos[i].nome);

        printf("Aluno %d - Matricula: ", i + 1);
        scanf("%d", &alunos[i].matricula);

        for (j = 0; j < 3; j++) {
            printf("Aluno %d - Nota %d: ", i + 1, j + 1);
            scanf("%f", &alunos[i].notas[j]);
        }
    }

    // 1. Media e situacao de cada aluno
    printf("\n--- Medias e situacao ---\n");
    for (i = 0; i < 5; i++) {
        medias[i] = calcularMedia(alunos[i]);

        printf("Nome: %s - Media: %.2f - ", alunos[i].nome, medias[i]);
        situacao(medias[i]);
    }

    // 2. Maior e menor media
    for (i = 1; i < 5; i++) {
        if (medias[i] > medias[pos_maior]) {
            pos_maior = i;
        }
        if (medias[i] < medias[pos_menor]) {
            pos_menor = i;
        }
    }

    printf("\n--- Maior e menor media ---\n");
    printf("Maior media: %s (%.2f)\n", alunos[pos_maior].nome, medias[pos_maior]);
    printf("Menor media: %s (%.2f)\n", alunos[pos_menor].nome, medias[pos_menor]);

    // 3. Media da turma e contagem por situacao
    for (i = 0; i < 5; i++) {
        soma = soma + medias[i];

        if (medias[i] >= 7) {
            aprovados++;
        } else if (medias[i] >= 5) {
            recuperacao++;
        } else {
            reprovados++;
        }
    }

    media_turma = soma / 5;

    printf("\n--- Resumo da turma ---\n");
    printf("Media da turma: %.2f\n", media_turma);
    printf("Aprovados: %d\n", aprovados);
    printf("Em recuperacao: %d\n", recuperacao);
    printf("Reprovados: %d\n", reprovados);

    // 4. Ordenacao da maior para a menor media (Bubble Sort)
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4 - i; j++) {
            if (calcularMedia(alunos[j]) < calcularMedia(alunos[j + 1])) {
                aux = alunos[j];
                alunos[j] = alunos[j + 1];
                alunos[j + 1] = aux;
            }
        }
    }

    printf("\n--- Ranking (da maior para a menor media) ---\n");
    for (i = 0; i < 5; i++) {
        printf("%do lugar: %s (matricula %d) - Media: %.2f\n",
               i + 1, alunos[i].nome, alunos[i].matricula, calcularMedia(alunos[i]));
    }

    return 0;
}



// Crie uma struct chamada Produto com os campos nome (texto) e preco (numero com casas decimais).
// Na main, crie uma variavel do tipo Produto, leia o nome e o preco digitados pelo usuario
// e mostre os dois na tela.
// Depois, mostre a mensagem "Situacao: Caro" se o preco for maior que 100,
// ou "Situacao: Barato" caso contrario.


#include <stdio.h>

struct Produto {
    char nome [50];
    float preco;
};

int main(){

    struct Produto produto;

    printf("Digite o nome do produto escolhido: ");
    scanf("%s", produto.nome);
    
    printf("digite o valor do produto: ");
    scanf("%f", &produto.preco);

if (produto.preco >100){
    printf("produto mt caro");
} 
    else {
        printf("produto barato");
    }
    return 0;
}