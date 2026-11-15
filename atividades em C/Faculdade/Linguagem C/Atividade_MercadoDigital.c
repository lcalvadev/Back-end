#include <stdio.h>
#include <string.h>   // para usar o strlen, que conta quantos caracteres tem um texto

struct telefones {
    char fixo[15];        // struct de registros dos telefones dos clientes (fixo e movel).
    char movel[16];
};

struct clientes {
    int codigo;         // o codigo do cliente é formado pelos 6 primeiros digitos do cpf do cliente
    char nome[50];       // struct que registra os dados de um cliente (codigo, nome, cpf, sexo, telefones).
    double cpf;
    char sexo;
    struct telefones tel;
};


struct modelos {
    char marca[20];       // struct de registro com marca e modelo de um produto (Dell/Precision).
    char modelo[20];
};

struct produtos {         // struct que registra os dados de um produto (codigo, nome, modelo, valor).
    int codigo;           // o codigo do produto é calculado pelo hash
    char nome[20];
    double valor;
    struct modelos modelo;
};

struct carrinhos {                 // registro da venda que esta sendo feita
    struct clientes cliente;       // cliente para quem a venda esta sendo feita
    struct produtos produto[3];    // ate 3 tipos de produto no carrinho
    int quantidade[3];             // quantidade de cada produto (mesma posicao do vetor produto)
    double subtotal;               // soma de (quantidade * valor) de todos os itens
    double desconto;               // desconto em porcentagem (10 significa 10%)
    double total;                  // valor final: subtotal menos o desconto
};                                 // fim da struct carrinhos

// Prototipo avisa ao compilador que a funcao existe, antes de ela ser escrita mais abaixo.

void mostraMenuInicial();                                   // funcao que mostra o menu
struct clientes cadastrarCliente();                         // struct que le os dados e devolve um cliente
int geraCodigoCliente(double cpf);                          // recebe o CPF e devolve o codigo
void listarClientes(struct clientes cliente[3]);            // mostra todos os clientes
struct produtos cadastrarProduto();                         // struct que le os dados e devolve um produto
int geraCodigoProduto(char nomeProduto[30]);                // recebe as 4 letras e devolve o codigo (hash)
void listarProdutos(struct produtos produto[10]);           // mostra todos os produtos
void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho); // void que monta a venda
struct clientes localizaCliente(int codigo, struct clientes cliente[3]);   // struct que procura cliente pelo codigo
struct produtos localizaProduto(int codigo, struct produtos produto[10]);  // struct que procura produto pelo codigo
void finalizarVenda(struct carrinhos carrinho);             // pede desconto, calcula e mostra os totais
void listarCarrinho(struct carrinhos carrinho);             // mostra cliente e itens do carrinho
double calculaSubtotal(struct carrinhos carrinho);          // soma os itens do carrinho
double calculaTotal(double subtotal, double desconto);      // aplica o desconto ao subtotal


void mostraMenuInicial() {                                  // só mostra as opções do menu na tela

    printf("  +========================+\n");
    printf("  |       MENU PRINCIPAL   |\n");
    printf("  +========================+\n");
    printf("  |  1 - Cadastrar cliente |\n");
    printf("  |  2 - Cadastrar produto |\n");
    printf("  |  3 - Listar clientes   |\n");
    printf("  |  4 - Listar produtos   |\n");
    printf("  |  5 - Efetuar venda     |\n");
    printf("  |  0 - Sair do programa  |\n");
    printf("  +========================+\n");
    printf("Selecione a opcao desejada: ");
}

// Estrutura clientes

int geraCodigoCliente(double cpf) {                          // recebe o CPF e devolve o código do cliente

    // o CPF tem 11 dígitos: dividir por 100000 deixa só os 6 primeiros, e o int descarta o resto
    int codigo = (int)(cpf / 100000);

    return codigo;
}

struct clientes cadastrarCliente() {                         // lê os dados do teclado, confere cada um e devolve o cliente pronto

    struct clientes c = {0};                                 // cliente começa com todos os campos zerados
    char cpf[20];                                            // CPF e telefones são lidos como texto para conferir se só têm números
    char numeros[16];                                        // texto temporário do telefone
    int valido;                                              // 1 se o que foi digitado está certo, 0 se está errado

    printf("\n--- CADASTRO DE CLIENTE ---\n");

    printf("Nome: ");
    scanf(" %49[^\n]", c.nome);                              // lê o nome inteiro, com espaços (o espaço antes do % ignora o Enter que sobrou)

    // repete até o CPF ter exatamente 11 caracteres e todos serem números
    do {
        valido = 1;
        printf("CPF (11 numeros, sem pontos e tracos): ");
        scanf("%19s", cpf);

        if (strlen(cpf) != 11) {                             // tamanho diferente de 11 deixa o CPF inválido
            valido = 0;
        }

        for (int i = 0; cpf[i] != '\0'; i++) {               // olha cada caractere digitado
            if (cpf[i] < '0' || cpf[i] > '9') {              // qualquer coisa fora de '0' a '9' (letra, ponto) deixa o CPF inválido
                valido = 0;
            }
        }

        if (valido == 0) {
            printf("CPF invalido!\n");
        }
    } while (valido == 0);

    sscanf(cpf, "%lf", &c.cpf);                              // CPF já conferido: converte o texto em número para guardar no campo double

    // só aceita M ou F (maiúsculo ou minúsculo), senão pede de novo
    do {
        printf("Sexo (M/F): ");
        scanf(" %c", &c.sexo);

        if (c.sexo != 'M' && c.sexo != 'F' && c.sexo != 'm' && c.sexo != 'f') {
            printf("Sexo invalido!\n");
        }
    } while (c.sexo != 'M' && c.sexo != 'F' && c.sexo != 'm' && c.sexo != 'f');

    // repete até o fixo ter 10 números (2 do DDD + 8 do número)
    do {
        valido = 1;
        printf("Telefone fixo (10 numeros, DDD + numero): ");
        scanf("%15s", numeros);

        if (strlen(numeros) != 10) {
            valido = 0;
        }

        for (int i = 0; numeros[i] != '\0'; i++) {
            if (numeros[i] < '0' || numeros[i] > '9') {
                valido = 0;
            }
        }

        if (valido == 0) {
            printf("Telefone invalido!\n");
        }
    } while (valido == 0);

    sprintf(c.tel.fixo, "(%.2s) %.4s-%.4s",                  // monta a máscara (11) 3210-1000 dentro do campo fixo
            numeros, numeros + 2, numeros + 6);              // pega 2 números do DDD, 4 do meio e 4 finais

    // repete até o móvel ter 11 números (2 do DDD + 9 do número)
    do {
        valido = 1;
        printf("Telefone movel (11 numeros, DDD + numero): ");
        scanf("%15s", numeros);

        if (strlen(numeros) != 11) {
            valido = 0;
        }

        for (int i = 0; numeros[i] != '\0'; i++) {
            if (numeros[i] < '0' || numeros[i] > '9') {
                valido = 0;
            }
        }

        if (valido == 0) {
            printf("Telefone invalido!\n");
        }
    } while (valido == 0);

    sprintf(c.tel.movel, "(%.2s) %.5s-%.4s",                 // monta a máscara (11) 98765-4321 dentro do campo movel
            numeros, numeros + 2, numeros + 7);              // pega 2 números do DDD, 5 do meio e 4 finais

    c.codigo = geraCodigoCliente(c.cpf);                     // gera o código do cliente a partir do CPF

    return c;                                                // devolve o cliente completo para quem chamou a função
}

void listarClientes(struct clientes cliente[3]) {            // mostra os clientes cadastrados

    printf("\n--- CLIENTES CADASTRADOS ---\n");

    for (int i = 0; i < 3; i++) {

        if (cliente[i].codigo != 0) {                        // só mostra posições preenchidas (as vazias têm código 0)

            printf("\nCodigo: %d\n", cliente[i].codigo);
            printf("Nome: %s\n", cliente[i].nome);
            printf("CPF: %.0f\n", cliente[i].cpf);           // %.0f mostra o CPF sem casas decimais
            printf("Sexo: %c\n", cliente[i].sexo);
            printf("Telefone fixo: %s\n", cliente[i].tel.fixo);
            printf("Telefone movel: %s\n", cliente[i].tel.movel);
        }
    }
}

struct clientes localizaCliente(int codigo, struct clientes cliente[3]) {  // procura o cliente pelo código e devolve ele

    for (int i = 0; i < 3; i++) {

        if (cliente[i].codigo == codigo) {                   // achou o código procurado: devolve esse cliente e encerra a função
            return cliente[i];
        }
    }

    struct clientes vazio = {0};                             // se não achou, devolve um cliente zerado (código 0 = não encontrado)

    return vazio;
}

// ===================== PRODUTOS =====================

int geraCodigoProduto(char nomeProduto[30]) {                // recebe 4 letras (2 da marca + 2 do modelo, ex.: "DEPR") e devolve o código

    // passo 1: cada letra vira o seu número da tabela ASCII
    int C1 = nomeProduto[0];                                 // 1ª letra (D = 68)
    int C2 = nomeProduto[1];                                 // 2ª letra (E = 69)
    int C3 = nomeProduto[2];                                 // 3ª letra (P = 80)
    int C4 = nomeProduto[3];                                 // 4ª letra (R = 82)

    // passo 2: cada número é multiplicado por uma potência de 31 (maior peso para as primeiras letras)
    int parte1 = C1 * 31 * 31 * 31;                          // C1 x 31^3
    int parte2 = C2 * 31 * 31;                               // C2 x 31^2
    int parte3 = C3 * 31;                                    // C3 x 31^1
    int parte4 = C4;                                         // C4 x 31^0 (que vale 1)

    // passo 3: a soma das 4 partes é o código do produto
    int hash = parte1 + parte2 + parte3 + parte4;

    return hash;
}

struct produtos cadastrarProduto() {                         // lê os dados do teclado, confere cada um e devolve o produto pronto

    struct produtos p = {0};                                 // produto começa com todos os campos zerados
    char letras[30] = {0};                                   // guarda as 4 letras usadas no hash (2 da marca e 2 do modelo)

    printf("\n--- CADASTRO DE PRODUTO ---\n");

    printf("Nome do produto: ");
    scanf(" %19[^\n]", p.nome);                              // lê até 19 letras, com espaços

    // repete até a marca ter pelo menos 2 letras (o hash usa as 2 primeiras)
    do {
        printf("Marca (minimo 2 letras): ");
        scanf(" %19[^\n]", p.modelo.marca);

        if (strlen(p.modelo.marca) < 2) {
            printf("Marca invalida!\n");
        }
    } while (strlen(p.modelo.marca) < 2);

    // repete até o modelo ter pelo menos 2 letras (o hash usa as 2 primeiras)
    do {
        printf("Modelo (minimo 2 letras): ");
        scanf(" %19[^\n]", p.modelo.modelo);

        if (strlen(p.modelo.modelo) < 2) {
            printf("Modelo invalido!\n");
        }
    } while (strlen(p.modelo.modelo) < 2);

    // repete até o valor ser um número maior que zero
    do {
        printf("Valor: R$ ");

        if (scanf("%lf", &p.valor) != 1) {                   // o scanf devolve 1 quando consegue ler um número
            scanf("%*s");                                    // não era número: descarta o que foi digitado
            p.valor = 0;                                     // zera o valor para cair na mensagem de erro e repetir
        }

        if (p.valor <= 0) {
            printf("Valor invalido!\n");
        }
    } while (p.valor <= 0);

    letras[0] = p.modelo.marca[0];                           // junta 2 primeiras letras da marca
    letras[1] = p.modelo.marca[1];
    letras[2] = p.modelo.modelo[0];                          // com as 2 primeiras letras do modelo
    letras[3] = p.modelo.modelo[1];

    p.codigo = geraCodigoProduto(letras);                    // calcula o código do produto com a fórmula do hash

    return p;                                                // devolve o produto completo para quem chamou a função
}

void listarProdutos(struct produtos produto[10]) {           // mostra os produtos cadastrados

    printf("\n--- PRODUTOS CADASTRADOS ---\n");

    for (int i = 0; i < 10; i++) {

        if (produto[i].codigo != 0) {                        // só mostra posições preenchidas (as vazias têm código 0)

            printf("\nCodigo: %d\n", produto[i].codigo);
            printf("Nome: %s\n", produto[i].nome);
            printf("Marca: %s\n", produto[i].modelo.marca);
            printf("Modelo: %s\n", produto[i].modelo.modelo);
            printf("Valor: R$ %.2f\n", produto[i].valor);
        }
    }
}

struct produtos localizaProduto(int codigo, struct produtos produto[10]) {  // procura o produto pelo código e devolve ele

    for (int i = 0; i < 10; i++) {

        if (produto[i].codigo == codigo) {                   // achou o código procurado: devolve esse produto e encerra a função
            return produto[i];
        }
    }

    struct produtos vazio = {0};                             // se não achou, devolve um produto zerado (código 0 = não encontrado)

    return vazio;
}

// ===================== VENDA =====================

double calculaSubtotal(struct carrinhos carrinho) {          // soma o valor de todos os itens do carrinho, ainda sem o desconto

    double soma = 0;                                         // acumulador começando do zero

    for (int i = 0; i < 3; i++) {
        soma += carrinho.quantidade[i] * carrinho.produto[i].valor;   // quantidade x valor de cada item (posições vazias valem 0)
    }

    return soma;
}

double calculaTotal(double subtotal, double desconto) {      // aplica o desconto percentual ao subtotal

    return subtotal - (subtotal * desconto / 100.0);         // subtotal menos a parte do desconto (10 vira 10%)
}

void listarCarrinho(struct carrinhos carrinho) {             // mostra o resumo do carrinho: cliente e itens

    printf("\n========== RESUMO DA COMPRA ==========\n");

    printf("Cliente: %s (codigo %d)\n",
           carrinho.cliente.nome,
           carrinho.cliente.codigo);

    for (int i = 0; i < 3; i++) {

        if (carrinho.quantidade[i] > 0) {                    // só mostra os itens que foram adicionados (quantidade maior que 0)

            printf("\nProduto: %s (%s %s)\n",
                   carrinho.produto[i].nome,
                   carrinho.produto[i].modelo.marca,
                   carrinho.produto[i].modelo.modelo);

            printf("Valor unitario: R$ %.2f\n", carrinho.produto[i].valor);
            printf("Quantidade: %d\n", carrinho.quantidade[i]);
            printf("Total do item: R$ %.2f\n",
                   carrinho.quantidade[i] * carrinho.produto[i].valor);
        }
    }
}

void finalizarVenda(struct carrinhos carrinho) {             // fecha a venda: mostra o carrinho, pede o desconto e calcula os totais

    listarCarrinho(carrinho);

    // repete até o desconto ficar entre 0 e 100
    do {
        printf("\nDesconto em porcentagem (0 a 100, ex.: 10 para 10%%): ");   // %% imprime o símbolo %

        if (scanf("%lf", &carrinho.desconto) != 1) {         // não digitou um número
            scanf("%*s");                                    // descarta o que foi digitado
            carrinho.desconto = -1;                          // desconto inválido de propósito, para cair na mensagem de erro e repetir
        }

        if (carrinho.desconto < 0 || carrinho.desconto > 100) {
            printf("Desconto invalido!\n");
        }
    } while (carrinho.desconto < 0 || carrinho.desconto > 100);

    carrinho.subtotal = calculaSubtotal(carrinho);           // soma dos itens, sem desconto

    carrinho.total = calculaTotal(carrinho.subtotal, carrinho.desconto);  // valor final já com o desconto aplicado

    printf("\nSubtotal: R$ %.2f\n", carrinho.subtotal);
    printf("Desconto: %.2f%% (R$ %.2f)\n",                   // mostra o desconto em % e também em reais
           carrinho.desconto,
           carrinho.subtotal * carrinho.desconto / 100.0);
    printf("Total: R$ %.2f\n", carrinho.total);

    printf("\nVenda finalizada!\n");
}

void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho) {  // monta a venda: escolhe o cliente e os produtos

    int codigo;                                              // código digitado (serve para o cliente e para os produtos)
    int quantidade;                                          // quantidade digitada de cada produto
    int item = 0;                                            // posição atual do carrinho (0, 1 ou 2)
    struct produtos p;                                       // produto encontrado pelo código digitado

    printf("\n--- EFETUAR VENDA ---\n");

    listarClientes(cliente);                                 // mostra os clientes para o usuário escolher

    printf("\nCodigo do cliente: ");
    if (scanf("%d", &codigo) != 1) {                         // não digitou um número
        scanf("%*s");                                        // descarta o que foi digitado
        codigo = 0;                                          // código 0 nunca existe, então cai em "cliente não encontrado"
    }

    carrinho.cliente = localizaCliente(codigo, cliente);     // busca o cliente e já coloca no carrinho

    if (carrinho.cliente.codigo == 0) {                      // código 0 significa que não achou o cliente
        printf("\nCliente nao encontrado!\n");
        return;                                              // volta ao menu sem fazer a venda
    }

    while (item < 3) {                                       // repete enquanto o carrinho tem espaço (máximo 3 tipos de produto)

        listarProdutos(produto);                             // mostra os produtos para o usuário escolher

        printf("\nCodigo do produto (0 para finalizar): ");
        if (scanf("%d", &codigo) != 1) {                     // não digitou um número
            scanf("%*s");                                    // descarta o que foi digitado
            codigo = -1;                                     // código -1 nunca existe, então cai em "produto não encontrado"
        }

        if (codigo == 0) {
            break;                                           // digitou 0: sai do laço e vai finalizar a venda
        }

        p = localizaProduto(codigo, produto);                // busca o produto pelo código

        if (p.codigo == 0) {                                 // código 0 significa que não achou o produto
            printf("\nProduto nao encontrado!\n");
            continue;                                        // volta ao início do laço para pedir outro código
        }

        // repete até a quantidade ser um número maior que zero
        do {
            printf("Quantidade: ");

            if (scanf("%d", &quantidade) != 1) {             // caso o usuario não digitou um número
                scanf("%*s");                                // descarta o que foi digitado
                quantidade = 0;                              // quantidade inválida de propósito, para cair na mensagem de erro e repetir
            }

            if (quantidade <= 0) {
                printf("Quantidade invalida!\n");
            }
        } while (quantidade <= 0);

        carrinho.produto[item] = p;                          // coloca o produto na posição atual do carrinho
        carrinho.quantidade[item] = quantidade;              // guarda a quantidade na mesma posição do produto

        item++;                                              // avança para a próxima posição do carrinho
    }

    if (item == 0) {                                         // se nenhum produto foi adicionado ao carrinho, imprime a mensagem e cancela a venda
        printf("\nCarrinho vazio. Venda cancelada.\n");
        return;
    }
    finalizarVenda(carrinho);                                // com ao menos 1 produto no carrinho, calcula e mostra os valores finais
}

// --------------------- Estrutura principal do programa ---------------------

int main() {

    struct clientes cliente[3] = {0};              // vetor de 3 clientes, iniciando com todos zerados
    struct produtos produto[10] = {0};            // vetor de 10 produtos, iniciando também com todos zerados
    struct carrinhos carrinho = {0};             // o carrinho zerado

    int qtdClientes = 0;
    int qtdProdutos = 0;                  // quantos clientes  e produtos ja foram cadastrados
    int opcao;

    do {

        mostraMenuInicial();

        if (scanf("%d", &opcao) != 1) {                      // não digitou um número
            scanf("%*s");                                    // descarta o que foi digitado
            opcao = -1;                                      // opção que não existe, então cai em "Opcao invalida!" mais abaixo
        }

        if (opcao == 1) {

            if (qtdClientes < 3) {                           // se ainda tem espaço no vetor, cadastra na próxima posição livre
                cliente[qtdClientes] = cadastrarCliente();
                qtdClientes++;                               // e conta mais um cliente cadastrado
            } else {
                printf("\nLimite de clientes atingido!\n");  // vetor cheio: avisa o usuário em vez de gravar fora do vetor
            }

        } else if (opcao == 2) {

            if (qtdProdutos < 10) {                          // se ainda tem espaço no vetor, cadastra na próxima posição livre
                produto[qtdProdutos] = cadastrarProduto();
                qtdProdutos++;                               // e conta mais um produto cadastrado
            } else {
                printf("\nLimite de produtos atingido!\n");  // vetor cheio: avisa o usuário em vez de gravar fora do vetor
            }

        } else if (opcao == 3) {

            listarClientes(cliente);

        } else if (opcao == 4) {

            listarProdutos(produto);

        } else if (opcao == 5) {

            efetuarVenda(cliente, produto, carrinho);

        } else if (opcao != 0) {

            printf("\nOpcao invalida!\n");                   // qualquer número fora do menu (ou texto digitado) cai aqui
        }

    } while (opcao != 0);                                    // volta ao menu enquanto a opção não for 0

    printf("\nFIM DO PROGRAMA!\n");

    return 0;
}