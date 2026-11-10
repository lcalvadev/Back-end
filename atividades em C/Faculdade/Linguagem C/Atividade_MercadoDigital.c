#include <stdio.h>
#include <string.h>

/* ===================== LIMITES DO SISTEMA ===================== */
#define MAX_CLIENTES 3
#define MAX_PRODUTOS 10
#define MAX_ITENS    3   /* tipos diferentes de produto no carrinho */

/* ===================== ESTRUTURAS ===================== */
struct telefones {
    char fixo[15];
    char movel[16];
};

struct clientes {
    int codigo;              /* 0 = posicao livre */
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
    int codigo;              /* 0 = posicao livre */
    char nome[20];
    struct modelos modelo;
    double valor;
    int estoque;
};

struct carrinhos {
    struct clientes cliente;
    struct produtos produto[MAX_ITENS];
    int quantidade[MAX_ITENS];   /* quantidade[i] pertence a produto[i] */
    double subtotal;
    double desconto;         /* em porcentagem */
    double total;
};

/* ===================== PROTOTIPOS ===================== */
void mostraMenuInicial();
struct clientes cadastrarCliente();
int geraCodigoCliente(double cpf);
void listarClientes(struct clientes cliente[MAX_CLIENTES]);
struct produtos cadastrarProduto();
int geraCodigoProduto(char nomeProduto[30]);
void listarProdutos(struct produtos produto[MAX_PRODUTOS]);
void efetuarVenda(struct clientes cliente[MAX_CLIENTES],
                  struct produtos produto[MAX_PRODUTOS],
                  struct carrinhos carrinho);
struct clientes localizaCliente(int codigo, struct clientes cliente[MAX_CLIENTES]);
struct produtos localizaProduto(int codigo, struct produtos produto[MAX_PRODUTOS]);
void finalizarVenda(struct carrinhos carrinho);
void listarCarrinho(struct carrinhos carrinho);
double calculaSubtotal(struct carrinhos carrinho);
double calculaTotal(double subtotal, double desconto);
int itensCarrinho(struct carrinhos carrinho);

/* ===================== FUNCOES AUXILIARES DE LEITURA ===================== */
/* converte uma letra minuscula em maiuscula (substitui o toupper) */
char maiuscula(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    return c;
}

void lerTexto(const char *msg, char *dest, int tam) {
    printf("%s", msg);
    if (fgets(dest, tam, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    int len = (int)strlen(dest);
    if (len > 0 && dest[len - 1] == '\n') {
        dest[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int lerInt(const char *msg) {
    char linha[64];
    int valor;
    while (1) {
        printf("%s", msg);
        if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
        if (sscanf(linha, "%d", &valor) == 1) return valor;
        printf("Entrada invalida! Digite um numero inteiro.\n");
    }
}

double lerDouble(const char *msg) {
    char linha[64];
    double valor;
    while (1) {
        printf("%s", msg);
        if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
        if (sscanf(linha, "%lf", &valor) == 1) return valor;
        printf("Entrada invalida! Digite um numero.\n");
    }
}

/* Le so os digitos e grava com a mascara. Ex: (11) 3210-1000 */
void lerTelefone(const char *msg, char *dest, int digitos) {
    char linha[64], d[16];
    int n;
    while (1) {
        printf("%s", msg);
        if (fgets(linha, sizeof(linha), stdin) == NULL) { dest[0] = '\0'; return; }
        n = 0;
        for (int i = 0; linha[i] != '\0' && n < 15; i++)
            if (linha[i] >= '0' && linha[i] <= '9') d[n++] = linha[i];
        d[n] = '\0';
        if (n == digitos) break;
        printf("Telefone invalido! Digite o DDD + %d digitos.\n", digitos - 2);
    }
    if (digitos == 10) sprintf(dest, "(%.2s) %.4s-%.4s", d, d + 2, d + 6);   /* fixo  */
    else               sprintf(dest, "(%.2s) %.5s-%.4s", d, d + 2, d + 7);   /* movel */
}

/* ===================== MENU ===================== */
void mostraMenuInicial() {
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Cadastrar produto\n");
    printf("3 - Listar clientes\n");
    printf("4 - Listar produtos\n");
    printf("5 - Efetuar compra\n");
    printf("0 - Sair do programa\n");
}

/* ===================== CLIENTES ===================== */
int geraCodigoCliente(double cpf) {
    /* CPF com 11 digitos / 10^5 = 6 primeiros digitos.
       Ex: 97734545610 -> 977345 | 03212345600 -> 32123 */
    return (int)(cpf / 100000.0);
}

struct clientes cadastrarCliente() {
    struct clientes c;
    memset(&c, 0, sizeof(c));

    printf("\n--- CADASTRO DE CLIENTE ---\n");

    do {
        lerTexto("Nome: ", c.nome, sizeof(c.nome));
        if (strlen(c.nome) == 0) printf("O nome nao pode ficar vazio!\n");
    } while (strlen(c.nome) == 0);

    do {
        c.cpf = lerDouble("CPF (somente numeros): ");
        if (c.cpf < 100000 || c.cpf >= 100000000000.0)
            printf("CPF invalido! Digite de 6 a 11 digitos, somente numeros.\n");
    } while (c.cpf < 100000 || c.cpf >= 100000000000.0);

    char linha[16];
    do {
        lerTexto("Sexo (M/F): ", linha, sizeof(linha));
        c.sexo = maiuscula(linha[0]);
        if (c.sexo != 'M' && c.sexo != 'F') printf("Sexo invalido! Digite M ou F.\n");
    } while (c.sexo != 'M' && c.sexo != 'F');

    lerTelefone("Telefone fixo (DDD + numero): ", c.tel.fixo, 10);
    lerTelefone("Telefone movel (DDD + numero): ", c.tel.movel, 11);

    c.codigo = geraCodigoCliente(c.cpf);
    return c;
}

void listarClientes(struct clientes cliente[MAX_CLIENTES]) {
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
    if (!achou) printf("Nenhum cliente cadastrado.\n");
}

struct clientes localizaCliente(int codigo, struct clientes cliente[MAX_CLIENTES]) {
    struct clientes nao;
    memset(&nao, 0, sizeof(nao));
    nao.codigo = -1; /* sinaliza "nao encontrado" */

    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (cliente[i].codigo > 0 && cliente[i].codigo == codigo)
            return cliente[i];
    }
    return nao;
}

/* ===================== PRODUTOS ===================== */
int geraCodigoProduto(char nomeProduto[30]) {
    /* Hash sobre os 4 caracteres recebidos (2 da marca + 2 do modelo):
       c1*31^3 + c2*31^2 + c3*31 + c4  (valores da tabela ASCII) */
    int hash = 0;
    for (int i = 0; i < 4 && nomeProduto[i] != '\0'; i++)
        hash = hash * 31 + maiuscula(nomeProduto[i]);
    return hash;
}

struct produtos cadastrarProduto() {
    struct produtos p;
    memset(&p, 0, sizeof(p));

    printf("\n--- CADASTRO DE PRODUTO ---\n");

    do {
        lerTexto("Nome do produto: ", p.nome, sizeof(p.nome));
        if (strlen(p.nome) == 0) printf("O nome nao pode ficar vazio!\n");
    } while (strlen(p.nome) == 0);

    do {
        lerTexto("Marca (minimo 2 caracteres): ", p.modelo.marca, sizeof(p.modelo.marca));
        if (strlen(p.modelo.marca) < 2) printf("Marca invalida!\n");
    } while (strlen(p.modelo.marca) < 2);

    do {
        lerTexto("Modelo (minimo 2 caracteres): ", p.modelo.modelo, sizeof(p.modelo.modelo));
        if (strlen(p.modelo.modelo) < 2) printf("Modelo invalido!\n");
    } while (strlen(p.modelo.modelo) < 2);

    do {
        p.valor = lerDouble("Valor do produto: R$ ");
        if (p.valor <= 0) printf("O valor deve ser maior que 0!\n");
    } while (p.valor <= 0);

    do {
        p.estoque = lerInt("Quantidade em estoque: ");
        if (p.estoque <= 0) printf("A quantidade deve ser maior que 0!\n");
    } while (p.estoque <= 0);

    /* chave = 2 primeiras letras da marca + 2 primeiras do modelo */
    char chave[30];
    chave[0] = p.modelo.marca[0];
    chave[1] = p.modelo.marca[1];
    chave[2] = p.modelo.modelo[0];
    chave[3] = p.modelo.modelo[1];
    chave[4] = '\0';

    p.codigo = geraCodigoProduto(chave);
    return p;
}

void listarProdutos(struct produtos produto[MAX_PRODUTOS]) {
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
    if (!achou) printf("Nenhum produto cadastrado.\n");
}

struct produtos localizaProduto(int codigo, struct produtos produto[MAX_PRODUTOS]) {
    struct produtos nao;
    memset(&nao, 0, sizeof(nao));
    nao.codigo = -1; /* sinaliza "nao encontrado" */

    for (int i = 0; i < MAX_PRODUTOS; i++) {
        if (produto[i].codigo > 0 && produto[i].codigo == codigo)
            return produto[i];
    }
    return nao;
}

/* ===================== CARRINHO / VENDA ===================== */
/* conta quantos tipos de produto ja estao no carrinho (codigo 0 = posicao livre) */
int itensCarrinho(struct carrinhos carrinho) {
    int n = 0;
    for (int i = 0; i < MAX_ITENS; i++)
        if (carrinho.produto[i].codigo > 0) n++;
    return n;
}

double calculaSubtotal(struct carrinhos carrinho) {
    double soma = 0;
    for (int i = 0; i < itensCarrinho(carrinho); i++)
        soma += carrinho.quantidade[i] * carrinho.produto[i].valor;
    return soma;
}

double calculaTotal(double subtotal, double desconto) {
    /* desconto em porcentagem. Ex: 1500 com 10 -> 1350 */
    return subtotal - (subtotal * desconto / 100.0);
}

void listarCarrinho(struct carrinhos carrinho) {
    printf("\n========== RESUMO DA COMPRA ==========\n");
    printf("Cliente: %s (codigo %d)\n", carrinho.cliente.nome, carrinho.cliente.codigo);

    for (int i = 0; i < itensCarrinho(carrinho); i++) {
        printf("\nProduto: %s (%s %s)\n", carrinho.produto[i].nome,
               carrinho.produto[i].modelo.marca, carrinho.produto[i].modelo.modelo);
        printf("Quantidade: %d x R$ %.2f = R$ %.2f\n", carrinho.quantidade[i],
               carrinho.produto[i].valor,
               carrinho.quantidade[i] * carrinho.produto[i].valor);
    }

    printf("\nSubtotal: R$ %.2f\n", carrinho.subtotal);
    printf("Desconto: %.2f%% (R$ %.2f)\n", carrinho.desconto,
           carrinho.subtotal - carrinho.total);
    printf("Total: R$ %.2f\n", carrinho.total);
}

void finalizarVenda(struct carrinhos carrinho) {
    carrinho.subtotal = calculaSubtotal(carrinho);
    carrinho.total = calculaTotal(carrinho.subtotal, carrinho.desconto);
    listarCarrinho(carrinho);
    printf("\nVenda finalizada com sucesso!\n");
}

void efetuarVenda(struct clientes cliente[MAX_CLIENTES],
                  struct produtos produto[MAX_PRODUTOS],
                  struct carrinhos carrinho) {
    printf("\n--- EFETUAR COMPRA ---\n");

    /* precisa ter ao menos 1 cliente e 1 produto */
    int temCliente = 0, temProduto = 0;
    for (int i = 0; i < MAX_CLIENTES; i++) if (cliente[i].codigo > 0) temCliente = 1;
    for (int i = 0; i < MAX_PRODUTOS; i++) if (produto[i].codigo > 0) temProduto = 1;

    if (!temCliente || !temProduto) {
        printf("Cadastre pelo menos um cliente e um produto antes de vender.\n");
        return;
    }

    /* inicializa o carrinho */
    memset(&carrinho, 0, sizeof(carrinho));

    /* 1) escolher o cliente */
    listarClientes(cliente);
    int cod = lerInt("\nDigite o codigo do cliente: ");
    struct clientes c = localizaCliente(cod, cliente);
    if (c.codigo == -1) {
        printf("Cliente nao encontrado!\n");
        return;
    }
    carrinho.cliente = c;
    printf("Cliente selecionado: %s\n", c.nome);

    /* 2) inserir produtos */
    while (1) {
        listarProdutos(produto);
        cod = lerInt("\nCodigo do produto (0 para finalizar a selecao): ");
        if (cod == 0) break;

        struct produtos p = localizaProduto(cod, produto);
        if (p.codigo == -1) {
            printf("Produto nao encontrado!\n");
            continue;
        }

        int qtd = lerInt("Quantidade: ");
        if (qtd <= 0) {
            printf("Quantidade invalida! Deve ser maior que 0.\n");
            continue;
        }

        /* o produto ja esta no carrinho? */
        int idx = -1;
        for (int i = 0; i < itensCarrinho(carrinho); i++) {
            if (carrinho.produto[i].codigo == p.codigo) { idx = i; break; }
        }

        if (idx == -1 && itensCarrinho(carrinho) >= MAX_ITENS) {
            printf("O carrinho aceita no maximo %d tipos de produto! "
                   "Voce ainda pode aumentar a quantidade de um item ja inserido.\n", MAX_ITENS);
            continue;
        }

        int jaNoCarrinho = (idx >= 0) ? carrinho.quantidade[idx] : 0;
        if (qtd + jaNoCarrinho > p.estoque) {
            printf("Estoque insuficiente! Disponivel: %d (ja no carrinho: %d).\n",
                   p.estoque, jaNoCarrinho);
            continue;
        }

        if (idx == -1) {
            idx = itensCarrinho(carrinho);
            carrinho.produto[idx] = p;
            carrinho.quantidade[idx] = qtd;
        } else {
            carrinho.quantidade[idx] += qtd;
        }
        printf("Produto adicionado ao carrinho.\n");
    }

    if (itensCarrinho(carrinho) == 0) {
        printf("Carrinho vazio. Venda cancelada.\n");
        return;
    }

    /* 3) desconto */
    carrinho.subtotal = calculaSubtotal(carrinho);
    printf("\nSubtotal: R$ %.2f\n", carrinho.subtotal);
    do {
        carrinho.desconto = lerDouble("Desconto em porcentagem (0 a 100): ");
        if (carrinho.desconto < 0 || carrinho.desconto > 100)
            printf("Desconto invalido!\n");
    } while (carrinho.desconto < 0 || carrinho.desconto > 100);

    /* 4) finaliza (calcula total e lista o carrinho) */
    finalizarVenda(carrinho);

    /* 5) baixa no estoque */
    for (int i = 0; i < itensCarrinho(carrinho); i++) {
        for (int j = 0; j < MAX_PRODUTOS; j++) {
            if (produto[j].codigo == carrinho.produto[i].codigo) {
                produto[j].estoque -= carrinho.quantidade[i];
                break;
            }
        }
    }
}

/* ===================== PROGRAMA PRINCIPAL ===================== */
int main() {
    struct clientes cliente[MAX_CLIENTES];
    struct produtos produto[MAX_PRODUTOS];
    struct carrinhos carrinho;

    memset(cliente, 0, sizeof(cliente));
    memset(produto, 0, sizeof(produto));
    memset(&carrinho, 0, sizeof(carrinho));

    int opcao;

    do {
        mostraMenuInicial();
        opcao = lerInt("\nEscolha uma opcao: ");

        switch (opcao) {

            case 1: { /* cadastrar cliente */
                int livre = -1;
                for (int i = 0; i < MAX_CLIENTES; i++)
                    if (cliente[i].codigo == 0) { livre = i; break; }

                if (livre == -1) {
                    printf("\nLimite de %d clientes atingido!\n", MAX_CLIENTES);
                    break;
                }

                struct clientes novo = cadastrarCliente();

                if (localizaCliente(novo.codigo, cliente).codigo != -1) {
                    printf("\nJa existe um cliente com o codigo %d! Cadastro cancelado.\n",
                           novo.codigo);
                    break;
                }

                cliente[livre] = novo;
                printf("\nCliente cadastrado com sucesso! Codigo: %d\n", novo.codigo);
                break;
            }

            case 2: { /* cadastrar produto */
                int livre = -1;
                for (int i = 0; i < MAX_PRODUTOS; i++)
                    if (produto[i].codigo == 0) { livre = i; break; }

                if (livre == -1) {
                    printf("\nLimite de %d produtos atingido!\n", MAX_PRODUTOS);
                    break;
                }

                struct produtos novo = cadastrarProduto();

                if (localizaProduto(novo.codigo, produto).codigo != -1) {
                    printf("\nJa existe um produto com o codigo %d! Cadastro cancelado.\n",
                           novo.codigo);
                    break;
                }

                produto[livre] = novo;
                printf("\nProduto cadastrado com sucesso! Codigo: %d\n", novo.codigo);
                break;
            }

            case 3:
                listarClientes(cliente);
                break;

            case 4:
                listarProdutos(produto);
                break;

            case 5:
                efetuarVenda(cliente, produto, carrinho);
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