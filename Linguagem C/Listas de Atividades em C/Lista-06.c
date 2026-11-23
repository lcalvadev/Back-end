// (1) Leitura Simples: Faça um programa que leia o primeiro nome de uma pessoa e, em
// seguida, imprima uma mensagem de boas-vindas: "Olá, [Nome]! Seja bem-vindo.". Use a
// função de leitura adequada para strings.

#include <stdio.h>

int main() {
    char nome[50];

    printf("Digite seu primeiro nome: ");
    scanf("%s", nome);

    printf("Ola, %s! Seja bem-vindo.\n", nome);
    return 0;
}


// (2) Tamanho Manual: Sem utilizar a função strlen(), elabore um programa que leia uma string
// e calcule quantos caracteres ela possui (desconsiderando o terminador nulo \0).

#include <stdio.h>

int main() {
    char texto[100];
    int tamanho;

    printf("Digite um texto: ");
    scanf(" %[^\n]", texto);

    tamanho = 0;
    while (texto[tamanho] != '\0') {
        tamanho++;
    }

    printf("O texto possui %d caracteres\n", tamanho);
    return 0;
}


// (3) Cópia sem Biblioteca: Sem usar strcpy(), leia uma string chamada origem e copie seu
// conteúdo para outra string chamada destino. Imprima a destino ao final.

#include <stdio.h>

int main() {
    char origem[100];
    char destino[100];
    int i;

    printf("Digite um texto: ");
    scanf(" %[^\n]", origem);

    i = 0;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';

    printf("Destino: %s\n", destino);
    return 0;
}


// (4) Contador de Vogais: Leia uma frase e conte quantas vogais (a, e, i, o, u) existem nela. O
// programa deve contar tanto maiúsculas quanto minúsculas.

#include <stdio.h>

int main() {
    char frase[200];
    char letra;
    int i;
    int vogais;

    printf("Digite uma frase: ");
    scanf(" %[^\n]", frase);

    vogais = 0;
    for (i = 0; frase[i] != '\0'; i++) {
        letra = frase[i];

        if (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u' ||
            letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U') {
            vogais++;
        }
    }

    printf("A frase possui %d vogais\n", vogais);
    return 0;
}


// (5) Impressão Inversa: Leia uma palavra e imprima-a de trás para frente. (Ex: "JAVA" ->
// "AVAJ").

#include <stdio.h>
#include <string.h>

int main() {
    char palavra[50];
    int tamanho;
    int i;

    printf("Digite uma palavra: ");
    scanf("%s", palavra);

    tamanho = strlen(palavra);

    for (i = tamanho - 1; i >= 0; i--) {
        printf("%c", palavra[i]);
    }
    printf("\n");
    return 0;
}


// (6) Comparação de Senha: Crie um programa que defina uma senha interna (ex:
// "admin123"). Solicite ao usuário que digite a senha. Use strcmp() para verificar. Se for igual,
// imprima "Acesso Liberado"; caso contrário, "Acesso Negado".

#include <stdio.h>
#include <string.h>

int main() {
    char senha[20] = "admin123";
    char senha_digitada[20];

    printf("Digite a senha: ");
    scanf("%s", senha_digitada);

    if (strcmp(senha, senha_digitada) == 0) {
        printf("Acesso Liberado\n");
    } else {
        printf("Acesso Negado\n");
    }
    return 0;
}


// (7) Concatenação Manual: Sem usar strcat(), leia duas palavras separadas. Crie uma
// terceira string que seja a junção da primeira com a segunda e imprima o resultado.

#include <stdio.h>

int main() {
    char palavra1[50];
    char palavra2[50];
    char resultado[100];
    int i;
    int j;

    printf("Digite a primeira palavra: ");
    scanf("%s", palavra1);
    printf("Digite a segunda palavra: ");
    scanf("%s", palavra2);

    i = 0;
    while (palavra1[i] != '\0') {
        resultado[i] = palavra1[i];
        i++;
    }

    j = 0;
    while (palavra2[j] != '\0') {
        resultado[i] = palavra2[j];
        i++;
        j++;
    }
    resultado[i] = '\0';

    printf("Resultado: %s\n", resultado);
    return 0;
}



// (8) Conversão para Maiúsculas (Lógica ASCII): Sem usar a função strupr() ou toupper(), leia
// uma string contendo apenas letras minúsculas e converta-a inteiramente para letras
// maiúsculas subtraindo o valor adequado na tabela ASCII.

#include <stdio.h>

int main() {
    char texto[100];
    int i;

    printf("Digite um texto em minusculas: ");
    scanf(" %[^\n]", texto);

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] >= 'a' && texto[i] <= 'z') {
            texto[i] = texto[i] - 32;
        }
    }

    printf("Em maiusculas: %s\n", texto);
    return 0;
}


// (9) Palíndromo: Um palíndromo é uma palavra que se lê da mesma forma de trás para frente
// (ex: "ARARA", "RADAR"). Escreva um programa que leia uma string e diga se ela é ou não um
// palíndromo.

#include <stdio.h>
#include <string.h>

int main() {
    char palavra[50];
    int tamanho;
    int i;
    int eh_palindromo;

    printf("Digite uma palavra: ");
    scanf("%s", palavra);

    tamanho = strlen(palavra);
    eh_palindromo = 1;

    for (i = 0; i < tamanho / 2; i++) {
        if (palavra[i] != palavra[tamanho - 1 - i]) {
            eh_palindromo = 0;
        }
    }

    if (eh_palindromo == 1) {
        printf("%s e um palindromo\n", palavra);
    } else {
        printf("%s nao e um palindromo\n", palavra);
    }
    return 0;
}



// (10) Contador de Palavras: Escreva um programa que leia uma frase completa (contendo
// espaços). O programa deve contar quantas palavras existem na frase. Considere que as
// palavras são separadas por um ou mais espaços em branco.

#include <stdio.h>

int main() {
    char frase[200];
    int i;
    int palavras;
    int dentro_de_palavra;

    printf("Digite uma frase: ");
    scanf(" %[^\n]", frase);

    palavras = 0;
    dentro_de_palavra = 0;

    for (i = 0; frase[i] != '\0'; i++) {
        if (frase[i] != ' ') {
            if (dentro_de_palavra == 0) {
                palavras++;
                dentro_de_palavra = 1;
            }
        } else {
            dentro_de_palavra = 0;
        }
    }

    printf("A frase possui %d palavras\n", palavras);
    return 0;
}



