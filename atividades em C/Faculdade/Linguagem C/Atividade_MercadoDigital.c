#include <stdio.h>   // biblioteca com printf, scanf e sprintf (entrada e saida)

// ===================== ESTRUTURAS =====================

struct telefones {        // registro que guarda os dois telefones do cliente
    char fixo[15];        // texto do telefone fixo com mascara: "(11) 3210-1000" (14 letras + '\0')
    char movel[16];       // texto do celular com mascara: "(11) 98765-4321" (15 letras + '\0')
};                        // fim da struct telefones

struct clientes {         // registro com os dados de um cliente
    int codigo;           // codigo do cliente (6 primeiros digitos do CPF)
    char nome[50];        // nome do cliente (ate 49 letras)
    double cpf;           // CPF guardado como numero grande (tem 11 digitos)
    char sexo;            // uma letra: M ou F
    struct telefones tel; // telefones do cliente (struct dentro de struct)
};                        // fim da struct clientes

struct modelos {          // registro com marca e modelo de um produto
    char marca[20];       // marca do produto (ex.: DELL)
    char modelo[20];      // modelo do produto (ex.: PRECISION)
};                        // fim da struct modelos

struct produtos {         // registro com os dados de um produto
    int codigo;           // codigo do produto (calculado pelo hash)
    char nome[20];        // nome do produto
    struct modelos modelo;// marca e modelo do produto
    double valor;         // preco unitario do produto
};                        // fim da struct produtos

struct carrinhos {                 // registro da venda que esta sendo feita
    struct clientes cliente;       // cliente para quem a venda esta sendo feita
    struct produtos produto[3];    // ate 3 tipos de produto no carrinho
    int quantidade[3];             // quantidade de cada produto (mesma posicao do vetor produto)
    double subtotal;               // soma de (quantidade * valor) de todos os itens
    double desconto;               // desconto em porcentagem (10 significa 10%)
    double total;                  // valor final: subtotal menos o desconto
};                                 // fim da struct carrinhos

// ===================== PROTOTIPOS =====================
// Prototipo avisa ao compilador que a funcao existe, antes de ela ser escrita mais abaixo.

void mostraMenuInicial();                                   // funcao que mostra o menu
struct clientes cadastrarCliente();                         // le os dados e devolve um cliente
int geraCodigoCliente(double cpf);                          // recebe o CPF e devolve o codigo
void listarClientes(struct clientes cliente[3]);            // mostra todos os clientes
struct produtos cadastrarProduto();                         // le os dados e devolve um produto
int geraCodigoProduto(char nomeProduto[30]);                // recebe as 4 letras e devolve o codigo (hash)
void listarProdutos(struct produtos produto[10]);           // mostra todos os produtos
void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho); // monta a venda
struct clientes localizaCliente(int codigo, struct clientes cliente[3]);   // procura cliente pelo codigo
struct produtos localizaProduto(int codigo, struct produtos produto[10]);  // procura produto pelo codigo
void finalizarVenda(struct carrinhos carrinho);             // pede desconto, calcula e mostra os totais
void listarCarrinho(struct carrinhos carrinho);             // mostra cliente e itens do carrinho
double calculaSubtotal(struct carrinhos carrinho);          // soma os itens do carrinho
double calculaTotal(double subtotal, double desconto);      // aplica o desconto ao subtotal

// ===================== MENU =====================

void mostraMenuInicial() {                                  // inicio da funcao do menu (nao devolve nada)

    printf("\n========== MENU PRINCIPAL ==========\n");      // mostra o titulo do menu
    printf("1 - Cadastrar cliente\n");                       // opcao 1
    printf("2 - Cadastrar produto\n");                       // opcao 2
    printf("3 - Listar clientes\n");                         // opcao 3
    printf("4 - Listar produtos\n");                         // opcao 4
    printf("5 - Efetuar venda\n");                           // opcao 5
    printf("0 - Sair do programa\n");                        // opcao 0 (encerra o programa)
    printf("Opcao: ");                                       // pergunta qual opcao o usuario quer
}                                                            // fim de mostraMenuInicial

// ===================== CLIENTES =====================

int geraCodigoCliente(double cpf) {                          // recebe o CPF e devolve um int

    // O CPF tem 11 digitos: dividir por 100000 deixa os 6 primeiros
    return (int)(cpf / 100000.0);                            // divide, converte para int (corta a parte decimal) e devolve
}                                                            // fim de geraCodigoCliente

struct clientes cadastrarCliente() {                         // le um cliente do teclado e devolve a struct pronta

    struct clientes c = {0};                                 // cria um cliente c com tudo zerado
    char numeros[16] = {0};                                  // texto temporario para guardar os digitos do telefone

    printf("\n--- CADASTRO DE CLIENTE ---\n");               // titulo da tela de cadastro

    printf("Nome: ");                                        // pede o nome
    scanf(" %49[^\n]", c.nome);                              // le ate 49 letras ate o Enter (aceita espacos; o espaco inicial ignora Enter antigo)

    printf("CPF (somente numeros): ");                       // pede o CPF
    scanf("%lf", &c.cpf);                                    // le o numero como double (%lf) e guarda em c.cpf

    printf("Sexo (M/F): ");                                  // pede o sexo
    scanf(" %c", &c.sexo);                                   // le uma letra (o espaco antes de %c ignora Enter antigo)

    printf("Telefone fixo (DDD + numero, somente numeros): ");   // pede o telefone fixo
    scanf("%15s", numeros);                                  // le ate 15 caracteres sem espaco para o texto temporario
    sprintf(c.tel.fixo, "(%.2s) %.4s-%.4s",                  // monta o texto com mascara dentro de c.tel.fixo
            numeros, numeros + 2, numeros + 6);              // 2 primeiros digitos (DDD), 4 do meio e 4 finais

    printf("Telefone movel (DDD + numero, somente numeros): ");  // pede o celular
    scanf("%15s", numeros);                                  // le os digitos do celular para o texto temporario
    sprintf(c.tel.movel, "(%.2s) %.5s-%.4s",                 // monta o texto com mascara dentro de c.tel.movel
            numeros, numeros + 2, numeros + 7);              // 2 do DDD, 5 do meio e 4 finais

    c.codigo = geraCodigoCliente(c.cpf);                     // calcula o codigo a partir do CPF e guarda

    return c;                                                // devolve o cliente completo para quem chamou
}                                                            // fim de cadastrarCliente

void listarClientes(struct clientes cliente[3]) {            // mostra os clientes do vetor

    printf("\n--- CLIENTES CADASTRADOS ---\n");              // titulo da listagem

    for (int i = 0; i < 3; i++) {                            // percorre as 3 posicoes do vetor

        if (cliente[i].codigo != 0) {                        // so mostra posicoes preenchidas (vazias tem codigo 0)

            printf("\nCodigo: %d\n", cliente[i].codigo);     // mostra o codigo
            printf("Nome: %s\n", cliente[i].nome);           // mostra o nome
            printf("CPF: %.0f\n", cliente[i].cpf);           // mostra o CPF sem casas decimais
            printf("Sexo: %c\n", cliente[i].sexo);           // mostra o sexo
            printf("Telefone fixo: %s\n", cliente[i].tel.fixo);    // mostra o fixo
            printf("Telefone movel: %s\n", cliente[i].tel.movel);  // mostra o celular
        }                                                    // fim do if
    }                                                        // fim do for
}                                                            // fim de listarClientes

struct clientes localizaCliente(int codigo, struct clientes cliente[3]) {  // procura um cliente pelo codigo

    for (int i = 0; i < 3; i++) {                            // percorre as 3 posicoes

        if (cliente[i].codigo == codigo) {                   // se o codigo da posicao for o procurado
            return cliente[i];                               // devolve esse cliente e encerra a funcao
        }                                                    // fim do if
    }                                                        // fim do for

    struct clientes vazio = {0};                             // se nao achou, cria um cliente zerado

    return vazio;                                            // e devolve ele
}                                                            // fim de localizaCliente

// ===================== PRODUTOS =====================

int geraCodigoProduto(char nomeProduto[30]) {                // recebe 4 letras e devolve o codigo do produto

    // nomeProduto traz os 2 primeiros caracteres da marca
    // seguidos dos 2 primeiros caracteres do modelo (ex.: "DEPR")

    int C1 = nomeProduto[0];                                 // 1a letra como numero da tabela ASCII
    int C2 = nomeProduto[1];                                 // 2a letra como numero ASCII
    int C3 = nomeProduto[2];                                 // 3a letra como numero ASCII
    int C4 = nomeProduto[3];                                 // 4a letra como numero ASCII

    return C1 * 31 * 31 * 31 + C2 * 31 * 31 + C3 * 31 + C4;  // formula do hash do enunciado: C1*31^3 + C2*31^2 + C3*31 + C4
}                                                            // fim de geraCodigoProduto

struct produtos cadastrarProduto() {                         // le um produto do teclado e devolve a struct pronta

    struct produtos p = {0};                                 // cria um produto p zerado
    char letras[30] = {0};                                   // texto que vai guardar as 4 letras para o hash

    printf("\n--- CADASTRO DE PRODUTO ---\n");               // titulo da tela de cadastro

    printf("Nome do produto: ");                             // pede o nome
    scanf(" %19[^\n]", p.nome);                              // le ate 19 letras (aceita espacos)

    printf("Marca: ");                                       // pede a marca
    scanf(" %19[^\n]", p.modelo.marca);                      // le a marca

    printf("Modelo: ");                                      // pede o modelo
    scanf(" %19[^\n]", p.modelo.modelo);                     // le o modelo

    printf("Valor: R$ ");                                    // pede o preco
    scanf("%lf", &p.valor);                                  // le o preco como double

    letras[0] = p.modelo.marca[0];                           // 1a letra da marca
    letras[1] = p.modelo.marca[1];                           // 2a letra da marca
    letras[2] = p.modelo.modelo[0];                          // 1a letra do modelo
    letras[3] = p.modelo.modelo[1];                          // 2a letra do modelo

    p.codigo = geraCodigoProduto(letras);                    // calcula o codigo (hash) e guarda

    return p;                                                // devolve o produto completo
}                                                            // fim de cadastrarProduto

void listarProdutos(struct produtos produto[10]) {           // mostra os produtos do vetor

    printf("\n--- PRODUTOS CADASTRADOS ---\n");              // titulo da listagem

    for (int i = 0; i < 10; i++) {                           // percorre as 10 posicoes

        if (produto[i].codigo != 0) {                        // so mostra posicoes preenchidas

            printf("\nCodigo: %d\n", produto[i].codigo);                 // mostra o codigo
            printf("Nome: %s\n", produto[i].nome);                       // mostra o nome
            printf("Marca: %s\n", produto[i].modelo.marca);              // mostra a marca
            printf("Modelo: %s\n", produto[i].modelo.modelo);            // mostra o modelo
            printf("Valor: R$ %.2f\n", produto[i].valor);                // mostra o valor com 2 casas decimais
        }                                                    // fim do if
    }                                                        // fim do for
}                                                            // fim de listarProdutos

struct produtos localizaProduto(int codigo, struct produtos produto[10]) {  // procura um produto pelo codigo

    for (int i = 0; i < 10; i++) {                           // percorre as 10 posicoes

        if (produto[i].codigo == codigo) {                   // se o codigo da posicao for o procurado
            return produto[i];                               // devolve esse produto e encerra a funcao
        }                                                    // fim do if
    }                                                        // fim do for

    struct produtos vazio = {0};                             // se nao achou, cria um produto zerado

    return vazio;                                            // e devolve ele
}                                                            // fim de localizaProduto

// ===================== VENDA =====================

double calculaSubtotal(struct carrinhos carrinho) {          // soma o valor de todos os itens do carrinho

    double soma = 0;                                         // acumulador comeca em zero

    for (int i = 0; i < 3; i++) {                            // percorre os 3 itens possiveis
        soma += carrinho.quantidade[i] * carrinho.produto[i].valor;   // soma quantidade * valor (itens vazios valem 0)
    }                                                        // fim do for

    return soma;                                             // devolve o subtotal
}                                                            // fim de calculaSubtotal

double calculaTotal(double subtotal, double desconto) {      // aplica o desconto percentual

    return subtotal - (subtotal * desconto / 100.0);         // subtotal menos a parte do desconto (10 vira 10%)
}                                                            // fim de calculaTotal

void listarCarrinho(struct carrinhos carrinho) {             // mostra o resumo do carrinho

    printf("\n========== RESUMO DA COMPRA ==========\n");    // titulo do resumo

    printf("Cliente: %s (codigo %d)\n",                      // mostra os dados do cliente da venda
           carrinho.cliente.nome,                            // nome do cliente (preenche o %s)
           carrinho.cliente.codigo);                         // codigo do cliente (preenche o %d)

    for (int i = 0; i < 3; i++) {                            // percorre os 3 itens possiveis

        if (carrinho.quantidade[i] > 0) {                    // so mostra itens que foram adicionados

            printf("\nProduto: %s (%s %s)\n",                // mostra nome, marca e modelo
                   carrinho.produto[i].nome,                 // nome do produto
                   carrinho.produto[i].modelo.marca,         // marca do produto
                   carrinho.produto[i].modelo.modelo);       // modelo do produto

            printf("Valor unitario: R$ %.2f\n", carrinho.produto[i].valor);   // valor de uma unidade
            printf("Quantidade: %d\n", carrinho.quantidade[i]);               // quantas unidades
            printf("Total do item: R$ %.2f\n",                                // total do item
                   carrinho.quantidade[i] * carrinho.produto[i].valor);       // quantidade * valor
        }                                                    // fim do if
    }                                                        // fim do for
}                                                            // fim de listarCarrinho

void finalizarVenda(struct carrinhos carrinho) {             // fecha a venda: desconto, subtotal e total

    listarCarrinho(carrinho);                                // primeiro mostra cliente e itens

    printf("\nDesconto em porcentagem (ex.: 10 para 10%%): ");   // pede o desconto (%% imprime o simbolo %)
    scanf("%lf", &carrinho.desconto);                        // le o desconto e guarda no carrinho

    carrinho.subtotal = calculaSubtotal(carrinho);           // calcula e guarda o subtotal

    carrinho.total = calculaTotal(carrinho.subtotal, carrinho.desconto);  // calcula e guarda o total com desconto

    printf("\nSubtotal: R$ %.2f\n", carrinho.subtotal);      // mostra o subtotal
    printf("Desconto: %.2f%% (R$ %.2f)\n",                   // mostra o desconto em % e em reais
           carrinho.desconto,                                // porcentagem do desconto
           carrinho.subtotal * carrinho.desconto / 100.0);   // valor do desconto em reais
    printf("Total: R$ %.2f\n", carrinho.total);              // mostra o total a pagar

    printf("\nVenda finalizada!\n");                         // avisa que acabou
}                                                            // fim de finalizarVenda

void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho) {  // monta a venda

    int codigo;                                              // guarda o codigo digitado (cliente e produtos)
    int item = 0;                                            // posicao atual do carrinho (0, 1 ou 2)

    printf("\n--- EFETUAR VENDA ---\n");                     // titulo da venda

    listarClientes(cliente);                                 // mostra os clientes para o usuario escolher

    printf("\nCodigo do cliente: ");                         // pede o codigo do cliente
    scanf("%d", &codigo);                                    // le o codigo

    carrinho.cliente = localizaCliente(codigo, cliente);     // busca o cliente e coloca no carrinho

    while (item < 3) {                                       // repete enquanto o carrinho tem espaco (max. 3 tipos)

        listarProdutos(produto);                             // mostra os produtos para escolher

        printf("\nCodigo do produto (0 para finalizar): ");  // pede o codigo do produto
        scanf("%d", &codigo);                                // le o codigo

        if (codigo == 0) {                                   // se digitou 0...
            break;                                           // ...sai do laco e vai finalizar a venda
        }                                                    // fim do if

        carrinho.produto[item] = localizaProduto(codigo, produto);   // busca o produto e coloca na posicao atual do carrinho

        printf("Quantidade: ");                              // pede a quantidade
        scanf("%d", &carrinho.quantidade[item]);             // le e guarda na mesma posicao do produto

        item++;                                              // avanca para a proxima posicao do carrinho
    }                                                        // fim do while

    finalizarVenda(carrinho);                                // calcula e mostra os valores finais
}                                                            // fim de efetuarVenda

// ===================== PROGRAMA PRINCIPAL =====================

int main() {                                                 // onde o programa comeca

    struct clientes cliente[3] = {0};                        // vetor de 3 clientes, todos zerados
    struct produtos produto[10] = {0};                       // vetor de 10 produtos, todos zerados
    struct carrinhos carrinho = {0};                         // um carrinho zerado

    int qtdClientes = 0;                                     // quantos clientes ja foram cadastrados
    int qtdProdutos = 0;                                     // quantos produtos ja foram cadastrados
    int opcao;                                               // opcao escolhida no menu

    do {                                                     // repete o menu pelo menos uma vez

        mostraMenuInicial();                                 // mostra o menu
        scanf("%d", &opcao);                                 // le a opcao digitada

        if (opcao == 1) {                                    // opcao 1: cadastrar cliente

            if (qtdClientes < 3) {                           // se ainda cabe cliente no vetor
                cliente[qtdClientes] = cadastrarCliente();   // cadastra na proxima posicao livre
                qtdClientes++;                               // conta mais um cliente
            } else {                                         // se o vetor esta cheio
                printf("\nLimite de clientes atingido!\n");  // avisa o usuario
            }                                                // fim do if/else interno

        } else if (opcao == 2) {                             // opcao 2: cadastrar produto

            if (qtdProdutos < 10) {                          // se ainda cabe produto no vetor
                produto[qtdProdutos] = cadastrarProduto();   // cadastra na proxima posicao livre
                qtdProdutos++;                               // conta mais um produto
            } else {                                         // se o vetor esta cheio
                printf("\nLimite de produtos atingido!\n");  // avisa o usuario
            }                                                // fim do if/else interno

        } else if (opcao == 3) {                             // opcao 3: listar clientes

            listarClientes(cliente);                         // mostra os clientes

        } else if (opcao == 4) {                             // opcao 4: listar produtos

            listarProdutos(produto);                         // mostra os produtos

        } else if (opcao == 5) {                             // opcao 5: efetuar venda

            efetuarVenda(cliente, produto, carrinho);        // inicia a venda

        } else if (opcao != 0) {                             // qualquer outro numero diferente de 0

            printf("\nOpcao invalida!\n");                   // avisa que a opcao nao existe
        }                                                    // fim da cadeia de if/else

    } while (opcao != 0);                                    // volta ao menu enquanto a opcao nao for 0

    printf("\nFIM DO PROGRAMA!\n");                          // mensagem ao sair

    return 0;                                                // informa ao sistema que terminou sem erro
}                                                            // fim de main