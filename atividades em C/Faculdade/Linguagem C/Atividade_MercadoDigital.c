
#include <stdio.h>

#define MAX_CLIENTES 3
#define MAX_PRODUTOS 10
#define MAX_ITENS 3

// ===================== ESTRUTURAS =====================

struct telefones {
    char fixo[15];
    char movel[16];
};

struct clientes {
    int codigo;
    char nome[50];
    double cpf;
    char sexo;
    struct telefones tel;
};

struct modelos {
    char marca[20];
    char modelo[20];
};

struct produtos {
    int codigo;
    char nome[20];
    struct modelos modelo;
    double valor;
    int estoque;
};

struct carrinhos {
    struct clientes cliente;
    struct produtos produto[MAX_ITENS];
    int quantidade[MAX_ITENS];
    double subtotal;
    double desconto;
    double total;
};

// ===================== PROTOTIPOS =====================

void menu_inicial();

struct clientes cadastro_cliente();
struct produtos cadastro_produto();

int gerar_codcliente(double cpf);
int gerar_codproduto(char marca[], char modelo[]);

void lista_clientes(struct clientes cliente[]);
void lista_produtos(struct produtos produto[]);

struct clientes loc_cliente(int codigo, struct clientes cliente[]);
struct produtos loc_produtos(int codigo, struct produtos produto[]);

void efetuarvendas(struct clientes cliente[],
                   struct produtos produto[],
                   struct carrinhos *carrinho);

void finalizar_vendas(struct carrinhos *carrinho);
void listar_carrinho(struct carrinhos *carrinho);

double calculo_sub(struct carrinhos *carrinho);
double calculo_total(double subtotal, double desconto);

int itens_carrinho(struct carrinhos *carrinho);

// ===================== FUNCOES AUXILIARES =====================

char maiuscula(char caractere) {

    if (caractere >= 'a' && caractere <= 'z') {
        return caractere - 32;
    }

    return caractere;
}

int contarCaracteres(char texto[]) {

    int quantidade = 0;

    while (texto[quantidade] != '\0') {
        quantidade++;
    }

    return quantidade;
}

void lerTexto(char mensagem[], char destino[], int tamanho) {

    printf("%s", mensagem);

    if (fgets(destino, tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    int quantidade = contarCaracteres(destino);

    if (quantidade > 0 && destino[quantidade - 1] == '\n') {
        destino[quantidade - 1] = '\0';
    } else {

        int caractere;

        while ((caractere = getchar()) != '\n' && caractere != EOF);
    }
}

int lerInt(char mensagem[]) {

    char linha[64];
    int valor;

    while (1) {

        printf("%s", mensagem);

        if (fgets(linha, 64, stdin) == NULL) {
            return 0;
        }

        if (sscanf(linha, "%d", &valor) == 1) {
            return valor;
        }

        printf("Entrada invalida!\n");
    }
}

double lerDouble(char mensagem[]) {

    char linha[64];
    double valor;

    while (1) {

        printf("%s", mensagem);

        if (fgets(linha, 64, stdin) == NULL) {
            return 0;
        }

        if (sscanf(linha, "%lf", &valor) == 1) {
            return valor;
        }

        printf("Entrada invalida!\n");
    }
}

void lerTelefone(char mensagem[], char destino[], int digitos) {

    char linha[64];
    char numeros[16];
    int quantidade;

    while (1) {

        printf("%s", mensagem);

        if (fgets(linha, 64, stdin) == NULL) {
            destino[0] = '\0';
            return;
        }

        quantidade = 0;

        for (int i = 0; linha[i] != '\0' && quantidade < 15; i++) {

            if (linha[i] >= '0' && linha[i] <= '9') {

                numeros[quantidade] = linha[i];
                quantidade++;
            }
        }

        numeros[quantidade] = '\0';

        if (quantidade == digitos) {
            break;
        }

        printf("Telefone invalido!\n");
    }

    if (digitos == 10) {

        sprintf(destino, "(%.2s) %.4s-%.4s",
                numeros, numeros + 2, numeros + 6);

    } else {

        sprintf(destino, "(%.2s) %.5s-%.4s",
                numeros, numeros + 2, numeros + 7);
    }
}

// ===================== MENU =====================

void menu_inicial() {

    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Cadastrar produto\n");
    printf("3 - Listar clientes\n");
    printf("4 - Listar produtos\n");
    printf("5 - Efetuar compra\n");
    printf("0 - Sair do programa\n");
}

// ===================== CLIENTES =====================

int gerar_codcliente(double cpf) {

    return (int)(cpf / 100000.0);
}

struct clientes cadastro_cliente() {

    struct clientes c = {0};

    printf("\n--- CADASTRO DE CLIENTE ---\n");

    do {

        lerTexto("Nome: ", c.nome, 50);

        if (contarCaracteres(c.nome) == 0) {
            printf("O nome nao pode ficar vazio!\n");
        }

    } while (contarCaracteres(c.nome) == 0);

    do {

        c.cpf = lerDouble("CPF (somente numeros): ");

        if (c.cpf < 100000 || c.cpf >= 100000000000.0) {
            printf("CPF invalido!\n");
        }

    } while (c.cpf < 100000 || c.cpf >= 100000000000.0);

    char linha[16];

    do {

        lerTexto("Sexo (M/F): ", linha, 16);

        c.sexo = maiuscula(linha[0]);

        if (c.sexo != 'M' && c.sexo != 'F') {
            printf("Sexo invalido!\n");
        }

    } while (c.sexo != 'M' && c.sexo != 'F');

    lerTelefone("Telefone fixo (DDD + numero): ",
                c.tel.fixo, 10);

    lerTelefone("Telefone movel (DDD + numero): ",
                c.tel.movel, 11);

    c.codigo = gerar_codcliente(c.cpf);

    return c;
}

void lista_clientes(struct clientes cliente[]) {

    int achou = 0;

    printf("\n--- CLIENTES CADASTRADOS ---\n");

    for (int i = 0; i < MAX_CLIENTES; i++) {

        if (cliente[i].codigo > 0) {

            achou = 1;

            printf("\nCodigo: %d\n", cliente[i].codigo);
            printf("Nome: %s\n", cliente[i].nome);
            printf("CPF: %.0f\n", cliente[i].cpf);
            printf("Sexo: %c\n", cliente[i].sexo);
            printf("Telefone fixo: %s\n", cliente[i].tel.fixo);
            printf("Telefone movel: %s\n", cliente[i].tel.movel);
        }
    }

    if (!achou) {
        printf("Nenhum cliente cadastrado.\n");
    }
}

struct clientes loc_cliente(int codigo, struct clientes cliente[]) {

    struct clientes naoEncontrado = {0};

    naoEncontrado.codigo = -1;

    for (int i = 0; i < MAX_CLIENTES; i++) {

        if (cliente[i].codigo == codigo && codigo > 0) {
            return cliente[i];
        }
    }

    return naoEncontrado;
}

// ===================== PRODUTOS =====================

int gerar_codproduto(char marca[], char modelo[]) {

    // Pega os quatro caracteres

    int C1 = maiuscula(marca[0]);
    int C2 = maiuscula(marca[1]);

    int C3 = maiuscula(modelo[0]);
    int C4 = maiuscula(modelo[1]);

    // Calcula cada parte da formula

    int parte1 = C1 * 31 * 31 * 31;

    int parte2 = C2 * 31 * 31;

    int parte3 = C3 * 31;

    int parte4 = C4;

    // Soma todas as partes

    int hash = parte1 + parte2 + parte3 + parte4;

    // Exibe o calculo completo

    printf("\n========== CALCULO DO HASH ==========\n");

    printf("C1 = %d\n", C1);
    printf("C2 = %d\n", C2);
    printf("C3 = %d\n", C3);
    printf("C4 = %d\n", C4);

    printf("\n");

    printf("%d * 31 * 31 * 31 = %d\n", C1, parte1);

    printf("%d * 31 * 31 = %d\n", C2, parte2);

    printf("%d * 31 = %d\n", C3, parte3);

    printf("%d = %d\n", C4, parte4);

    printf("\n");

    printf("Hash = %d + %d + %d + %d\n",
           parte1, parte2, parte3, parte4);

    printf("Codigo final do produto: %d\n", hash);

    printf("=====================================\n");

    return hash;
}

struct produtos cadastro_produto() {

    struct produtos p = {0};

    printf("\n--- CADASTRO DE PRODUTO ---\n");

    do {

        lerTexto("Nome do produto: ", p.nome, 20);

        if (contarCaracteres(p.nome) == 0) {
            printf("O nome nao pode ficar vazio!\n");
        }

    } while (contarCaracteres(p.nome) == 0);

    do {

        lerTexto("Marca (minimo 2 caracteres): ",
                 p.modelo.marca, 20);

        if (contarCaracteres(p.modelo.marca) < 2) {
            printf("Marca invalida!\n");
        }

    } while (contarCaracteres(p.modelo.marca) < 2);

    do {

        lerTexto("Modelo (minimo 2 caracteres): ",
                 p.modelo.modelo, 20);

        if (contarCaracteres(p.modelo.modelo) < 2) {
            printf("Modelo invalido!\n");
        }

    } while (contarCaracteres(p.modelo.modelo) < 2);

    do {

        p.valor = lerDouble("Valor do produto: R$ ");

        if (p.valor <= 0) {
            printf("O valor deve ser maior que zero!\n");
        }

    } while (p.valor <= 0);

    do {

        p.estoque = lerInt("Quantidade em estoque: ");

        if (p.estoque <= 0) {
            printf("A quantidade deve ser maior que zero!\n");
        }

    } while (p.estoque <= 0);

    // Gera o codigo utilizando as duas primeiras letras
    // da marca e as duas primeiras letras do modelo.

    p.codigo = gerar_codproduto(p.modelo.marca,
                                p.modelo.modelo);

    return p;
}

void lista_produtos(struct produtos produto[]) {

    int achou = 0;

    printf("\n--- PRODUTOS CADASTRADOS ---\n");

    for (int i = 0; i < MAX_PRODUTOS; i++) {

        if (produto[i].codigo > 0) {

            achou = 1;

            printf("\nCodigo: %d\n", produto[i].codigo);
            printf("Nome: %s\n", produto[i].nome);
            printf("Marca: %s\n", produto[i].modelo.marca);
            printf("Modelo: %s\n", produto[i].modelo.modelo);
            printf("Valor: R$ %.2f\n", produto[i].valor);
            printf("Estoque: %d\n", produto[i].estoque);
        }
    }

    if (!achou) {
        printf("Nenhum produto cadastrado.\n");
    }
}

struct produtos loc_produtos(int codigo, struct produtos produto[]) {

    struct produtos naoEncontrado = {0};

    naoEncontrado.codigo = -1;

    for (int i = 0; i < MAX_PRODUTOS; i++) {

        if (produto[i].codigo == codigo && codigo > 0) {
            return produto[i];
        }
    }

    return naoEncontrado;
}

// ===================== CARRINHO / VENDA =====================

int itens_carrinho(struct carrinhos *carrinho) {

    int quantidade = 0;

    for (int i = 0; i < MAX_ITENS; i++) {

        if (carrinho->produto[i].codigo > 0) {
            quantidade++;
        }
    }

    return quantidade;
}

double calculo_sub(struct carrinhos *carrinho) {

    double soma = 0;

    for (int i = 0; i < itens_carrinho(carrinho); i++) {

        soma += carrinho->quantidade[i] *
                carrinho->produto[i].valor;
    }

    return soma;
}

double calculo_total(double subtotal, double desconto) {

    return subtotal - (subtotal * desconto / 100.0);
}

void listar_carrinho(struct carrinhos *carrinho) {

    printf("\n========== RESUMO DA COMPRA ==========\n");

    printf("Cliente: %s (codigo %d)\n",
           carrinho->cliente.nome,
           carrinho->cliente.codigo);

    for (int i = 0; i < itens_carrinho(carrinho); i++) {

        printf("\nProduto: %s (%s %s)\n",
               carrinho->produto[i].nome,
               carrinho->produto[i].modelo.marca,
               carrinho->produto[i].modelo.modelo);

        printf("Quantidade: %d x R$ %.2f = R$ %.2f\n",
               carrinho->quantidade[i],
               carrinho->produto[i].valor,
               carrinho->quantidade[i] *
               carrinho->produto[i].valor);
    }

    printf("\nSubtotal: R$ %.2f\n", carrinho->subtotal);

    printf("Desconto: %.2f%%\n", carrinho->desconto);

    printf("Total: R$ %.2f\n", carrinho->total);
}

void finalizar_vendas(struct carrinhos *carrinho) {

    carrinho->subtotal = calculo_sub(carrinho);

    carrinho->total = calculo_total(
        carrinho->subtotal,
        carrinho->desconto
    );

    listar_carrinho(carrinho);

    printf("\nVenda finalizada com sucesso!\n");
}

void efetuarvendas(struct clientes cliente[],
                   struct produtos produto[],
                   struct carrinhos *carrinho) {

    printf("\n--- EFETUAR COMPRA ---\n");

    int temCliente = 0;
    int temProduto = 0;

    for (int i = 0; i < MAX_CLIENTES; i++) {

        if (cliente[i].codigo > 0) {
            temCliente = 1;
        }
    }

    for (int i = 0; i < MAX_PRODUTOS; i++) {

        if (produto[i].codigo > 0) {
            temProduto = 1;
        }
    }

    if (!temCliente || !temProduto) {

        printf("Cadastre pelo menos um cliente e um produto antes de vender.\n");

        return;
    }

    // Inicializa o carrinho

    *carrinho = (struct carrinhos){0};

    // 1 - Escolher cliente

    lista_clientes(cliente);

    int codigo = lerInt("\nDigite o codigo do cliente: ");

    struct clientes c = loc_cliente(codigo, cliente);

    if (c.codigo == -1) {

        printf("Cliente nao encontrado!\n");

        return;
    }

    carrinho->cliente = c;

    printf("Cliente selecionado: %s\n", c.nome);

    // 2 - Inserir produtos

    while (1) {

        lista_produtos(produto);

        codigo = lerInt("\nCodigo do produto (0 para finalizar): ");

        if (codigo == 0) {
            break;
        }

        struct produtos p = loc_produtos(codigo, produto);

        if (p.codigo == -1) {

            printf("Produto nao encontrado!\n");

            continue;
        }

        int quantidade = lerInt("Quantidade: ");

        if (quantidade <= 0) {

            printf("Quantidade invalida!\n");

            continue;
        }

        // Verifica se o produto ja esta no carrinho

        int posicaoProduto = -1;

        for (int i = 0; i < itens_carrinho(carrinho); i++) {

            if (carrinho->produto[i].codigo == p.codigo) {

                posicaoProduto = i;

                break;
            }
        }

        if (posicaoProduto == -1 &&
            itens_carrinho(carrinho) >= MAX_ITENS) {

            printf("O carrinho aceita no maximo %d tipos de produtos!\n",
                   MAX_ITENS);

            continue;
        }

        int quantidadeCarrinho = 0;

        if (posicaoProduto >= 0) {

            quantidadeCarrinho =
                carrinho->quantidade[posicaoProduto];
        }

        if (quantidade + quantidadeCarrinho > p.estoque) {

            printf("Estoque insuficiente! Disponivel: %d\n",
                   p.estoque);

            continue;
        }

        if (posicaoProduto == -1) {

            posicaoProduto = itens_carrinho(carrinho);

            carrinho->produto[posicaoProduto] = p;

            carrinho->quantidade[posicaoProduto] = quantidade;

        } else {

            carrinho->quantidade[posicaoProduto] += quantidade;
        }

        printf("Produto adicionado ao carrinho.\n");
    }

    if (itens_carrinho(carrinho) == 0) {

        printf("Carrinho vazio. Venda cancelada.\n");

        return;
    }

    // 3 - Desconto

    carrinho->subtotal = calculo_sub(carrinho);

    printf("\nSubtotal: R$ %.2f\n", carrinho->subtotal);

    do {

        carrinho->desconto =
            lerDouble("Desconto em porcentagem (0 a 100): ");

        if (carrinho->desconto < 0 ||
            carrinho->desconto > 100) {

            printf("Desconto invalido!\n");
        }

    } while (carrinho->desconto < 0 ||
             carrinho->desconto > 100);

    // 4 - Finalizar venda

    finalizar_vendas(carrinho);

    // 5 - Atualizar estoque

    for (int i = 0; i < itens_carrinho(carrinho); i++) {

        for (int j = 0; j < MAX_PRODUTOS; j++) {

            if (produto[j].codigo ==
                carrinho->produto[i].codigo) {

                produto[j].estoque -=
                    carrinho->quantidade[i];

                break;
            }
        }
    }
}

// ===================== PROGRAMA PRINCIPAL =====================

int main() {

    struct clientes cliente[MAX_CLIENTES] = {0};

    struct produtos produto[MAX_PRODUTOS] = {0};

    struct carrinhos carrinho = {0};

    int opcao;

    do {

        menu_inicial();

        opcao = lerInt("\nEscolha uma opcao: ");

        switch (opcao) {

            case 1: {

                int livre = -1;

                for (int i = 0; i < MAX_CLIENTES; i++) {

                    if (cliente[i].codigo == 0) {

                        livre = i;

                        break;
                    }
                }

                if (livre == -1) {

                    printf("\nLimite de clientes atingido!\n");

                    break;
                }

                struct clientes novo = cadastro_cliente();

                if (loc_cliente(novo.codigo, cliente).codigo != -1) {

                    printf("\nJa existe um cliente com esse codigo!\n");

                    break;
                }

                cliente[livre] = novo;

                printf("\nCliente cadastrado com sucesso! Codigo: %d\n",
                       novo.codigo);

                break;
            }

            case 2: {

                int livre = -1;

                for (int i = 0; i < MAX_PRODUTOS; i++) {

                    if (produto[i].codigo == 0) {

                        livre = i;

                        break;
                    }
                }

                if (livre == -1) {

                    printf("\nLimite de produtos atingido!\n");

                    break;
                }

                struct produtos novo = cadastro_produto();

                if (loc_produtos(novo.codigo, produto).codigo != -1) {

                    printf("\nJa existe um produto com esse codigo!\n");

                    break;
                }

                produto[livre] = novo;

                printf("\nProduto cadastrado com sucesso! Codigo: %d\n",
                       novo.codigo);

                break;
            }

            case 3:

                lista_clientes(cliente);

                break;

            case 4:

                lista_produtos(produto);

                break;

            case 5:

                efetuarvendas(cliente, produto, &carrinho);

                break;

            case 0:

                printf("\nFIM DO PROGRAMA!\n");

                break;

            default:

                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
