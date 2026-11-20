#include <stdio.h>    
#include <string.h> //biblioteca para usar o stlen

// guarda os dois telefones do cliente
struct telefones {
    char fixo[15];      
    char movel[16];       
};

// guarda os dados de um cliente
struct clientes {
    int codigo;          // código do cliente: são os 6 primeiros dígitos do CPF 
    char nome[50];       
    double cpf;          
    char sexo;           
    struct telefones tel; 
};


// agrupa a marca e o modelo, que depois ficam dentro de cada produto
struct modelos {
    char marca[20];       
    char modelo[20];      
};

// guarda os dados de um produto
struct produtos {
    int codigo;           // código do produto: calculado pelo hash das 2 primeiras letras da marca e das 2 primeiras do modelo
    char nome[20];        
    double valor;         
    struct modelos modelo; 
};

// guarda a venda que está sendo feita no momento
struct carrinhos {
    struct clientes cliente;       // cliente para quem a venda está sendo feita
    struct produtos produto[3];    // até 3 tipos de produto diferentes no carrinho
    int quantidade[3];             // quantas unidades de cada produto; a posição é a mesma do vetor produto (quantidade[0] é do produto[0])
    double subtotal;               // soma de (quantidade x valor) de todos os itens, antes do desconto
    double desconto;               // desconto em porcentagem
    double total;                  // valor final a pagar: subtotal menos o desconto
};                                 // fim da struct carrinhos

// Protótipo avisa ao compilador que a função existe, antes de ela ser escrita mais abaixo.
// Assim o main e as outras funções podem chamá-la sem se importar com a ordem do arquivo.

void mostraMenuInicial();                                   // não recebe nada e não devolve nada: só mostra o menu na tela
struct clientes cadastrarCliente();                         // lê os dados de um cliente no teclado e devolve a struct pronta
int geraCodigoCliente(double cpf);                          // recebe o CPF e devolve o código do cliente (6 primeiros dígitos)
void listarClientes(struct clientes cliente[3]);            // recebe o vetor de clientes e mostra todos os cadastrados
struct produtos cadastrarProduto();                         // lê os dados de um produto no teclado e devolve a struct pronta
int geraCodigoProduto(char nomeProduto[30]);                // recebe as 4 letras e devolve o código do produto (hash)
void listarProdutos(struct produtos produto[10]);           // recebe o vetor de produtos e mostra todos os cadastrados
void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho); // monta a venda: escolhe o cliente e os produtos
struct clientes localizaCliente(int codigo, struct clientes cliente[3]);   // procura um cliente pelo código e devolve ele
struct produtos localizaProduto(int codigo, struct produtos produto[10]);  // procura um produto pelo código e devolve ele
void finalizarVenda(struct carrinhos carrinho);             // pede o desconto, calcula os valores e mostra os totais
void listarCarrinho(struct carrinhos carrinho);             // mostra o cliente e os itens que estão no carrinho
double calculaSubtotal(struct carrinhos carrinho);          // soma o valor dos itens do carrinho, sem desconto
double calculaTotal(double subtotal, double desconto);      // aplica o desconto ao subtotal e devolve o total


void mostraMenuInicial() {                                  // só mostra as opções do menu na tela; quem lê a opção digitada é o main

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

    // o CPF tem 11 dígitos: dividir por 100000 (5 zeros) tira os 5 últimos e deixa os 6 primeiros;
    // o (int) joga fora a parte decimal que sobra da divisão
    int codigo = (int)(cpf / 100000);

    return codigo;
}

struct clientes cadastrarCliente() {                         // lê os dados do teclado, confere cada um e devolve o cliente pronto

    struct clientes c = {0};                                 // cria o cliente com todos os campos zerados; ele vai sendo preenchido abaixo
    char cpf[20];                                            // CPF e telefones são lidos como texto para poder conferir, caractere por caractere, se só têm números
    char numeros[16];                                        // texto temporário que guarda os números do telefone antes de montar a máscara
    int valido;                                              // marcador: 1 se o que foi digitado está certo, 0 se está errado

    printf("\n--- CADASTRO DE CLIENTE ---\n");

    printf("Nome: ");
    scanf(" %49[^\n]", c.nome);                              // lê o nome inteiro, com espaços, até o Enter (o espaço antes do % ignora o Enter que sobrou da leitura anterior)

    // repete até o CPF ter exatamente 11 caracteres e todos serem números
    do {
        valido = 1;                                          // começa achando que está certo; qualquer erro abaixo muda para 0
        printf("CPF (11 numeros, sem pontos e tracos): ");
        scanf("%19s", cpf);                                  // lê o CPF como texto (no máximo 19 caracteres, para não passar do tamanho do vetor)

        if (strlen(cpf) != 11) {                             // CPF precisa ter 11 dígitos; qualquer outro tamanho deixa inválido
            valido = 0;
        }

        for (int i = 0; cpf[i] != '\0'; i++) {               // percorre cada caractere digitado, até chegar no fim do texto ('\0')
            if (cpf[i] < '0' || cpf[i] > '9') {              // se o caractere não estiver entre '0' e '9' (é letra, ponto, traço...), o CPF é inválido
                valido = 0;
            }
        }

        if (valido == 0) {
            printf("CPF invalido!\n");
        }
    } while (valido == 0);                                   // volta a pedir o CPF enquanto ele estiver inválido

    sscanf(cpf, "%lf", &c.cpf);                              // CPF já conferido: converte o texto em número (%lf = double) e guarda no campo cpf

    // só aceita M ou F (maiúsculo ou minúsculo); qualquer outra letra faz o programa perguntar de novo
    do {
        printf("Sexo (M/F): ");
        scanf(" %c", &c.sexo);                               // lê uma letra (o espaço antes do %c ignora o Enter que sobrou)

        if (c.sexo != 'M' && c.sexo != 'F' && c.sexo != 'm' && c.sexo != 'f') {
            printf("Sexo invalido!\n");
        }
    } while (c.sexo != 'M' && c.sexo != 'F' && c.sexo != 'm' && c.sexo != 'f');

    // repete até o fixo ter 10 números (2 do DDD + 8 do número)
    do {
        valido = 1;
        printf("Telefone fixo (10 numeros, DDD + numero): ");
        scanf("%15s", numeros);                              // lê o telefone como texto, sem espaços

        if (strlen(numeros) != 10) {                         // fixo precisa ter exatamente 10 dígitos
            valido = 0;
        }

        for (int i = 0; numeros[i] != '\0'; i++) {           // confere cada caractere, igual foi feito no CPF
            if (numeros[i] < '0' || numeros[i] > '9') {      // só aceita dígitos de 0 a 9
                valido = 0;
            }
        }

        if (valido == 0) {
            printf("Telefone invalido!\n");
        }
    } while (valido == 0);

    sprintf(c.tel.fixo, "(%.2s) %.4s-%.4s",                  // monta no campo fixo o texto com a máscara, no formato (11) 3210-1000
            numeros, numeros + 2, numeros + 6);              // %.2s pega 2 caracteres: os 2 do DDD, depois 4 a partir da posição 2 e 4 a partir da posição 6

    // repete até o móvel ter 11 números (2 do DDD + 9 do número)
    do {
        valido = 1;
        printf("Telefone movel (11 numeros, DDD + numero): ");
        scanf("%15s", numeros);                              // lê o celular como texto, sem espaços

        if (strlen(numeros) != 11) {                         // móvel precisa ter exatamente 11 dígitos
            valido = 0;
        }

        for (int i = 0; numeros[i] != '\0'; i++) {           // confere cada caractere
            if (numeros[i] < '0' || numeros[i] > '9') {      // só aceita dígitos de 0 a 9
                valido = 0;
            }
        }

        if (valido == 0) {
            printf("Telefone invalido!\n");
        }
    } while (valido == 0);

    sprintf(c.tel.movel, "(%.2s) %.5s-%.4s",                 // monta no campo movel o texto com a máscara, no formato (11) 98765-4321
            numeros, numeros + 2, numeros + 7);              // pega os 2 do DDD, 5 a partir da posição 2 e 4 a partir da posição 7

    c.codigo = geraCodigoCliente(c.cpf);                     // chama a função que gera o código do cliente a partir do CPF e guarda no campo codigo

    return c;                                                // devolve o cliente completo para quem chamou a função (o main guarda no vetor)
}

void listarClientes(struct clientes cliente[3]) {            // mostra os clientes cadastrados

    printf("\n--- CLIENTES CADASTRADOS ---\n");

    for (int i = 0; i < 3; i++) {                            // percorre as 3 posições do vetor

        if (cliente[i].codigo != 0) {                        // só mostra posições preenchidas: as vazias continuam com código 0

            printf("\nCodigo: %d\n", cliente[i].codigo);
            printf("Nome: %s\n", cliente[i].nome);
            printf("CPF: %.0f\n", cliente[i].cpf);           // %.0f mostra o número double sem casas decimais, ou seja, o CPF inteiro
            printf("Sexo: %c\n", cliente[i].sexo);
            printf("Telefone fixo: %s\n", cliente[i].tel.fixo);
            printf("Telefone movel: %s\n", cliente[i].tel.movel);
        }
    }
}

struct clientes localizaCliente(int codigo, struct clientes cliente[3]) {  // procura o cliente pelo código e devolve ele

    for (int i = 0; i < 3; i++) {                            // olha uma posição do vetor de cada vez

        if (cliente[i].codigo == codigo) {                   // achou o código procurado: devolve esse cliente e a função termina aqui
            return cliente[i];
        }
    }

    struct clientes vazio = {0};                             // se o laço terminou sem achar, cria um cliente zerado

    return vazio;                                            // devolve o cliente zerado; o código 0 é o sinal de "não encontrado"
}

// ===================== PRODUTOS =====================

int geraCodigoProduto(char nomeProduto[30]) {                // recebe 4 letras (2 da marca + 2 do modelo, ex.: "DEPR" para Dell Precision) e devolve o código

    // passo 1: cada letra vira o seu número da tabela ASCII (basta guardar o char em um int)
    int C1 = nomeProduto[0];                                 // 1ª letra (D = 68)
    int C2 = nomeProduto[1];                                 // 2ª letra (E = 69)
    int C3 = nomeProduto[2];                                 // 3ª letra (P = 80)
    int C4 = nomeProduto[3];                                 // 4ª letra (R = 82)

    // passo 2: cada número é multiplicado por uma potência de 31; as primeiras letras têm peso maior,
    // então trocar a ordem das letras gera um código diferente
    int parte1 = C1 * 31 * 31 * 31;                          // C1 x 31^3
    int parte2 = C2 * 31 * 31;                               // C2 x 31^2
    int parte3 = C3 * 31;                                    // C3 x 31^1
    int parte4 = C4;                                         // C4 x 31^0 (que vale 1, por isso não multiplica)

    // passo 3: a soma das 4 partes é o código do produto
    int hash = parte1 + parte2 + parte3 + parte4;

    return hash;
}

struct produtos cadastrarProduto() {                         // lê os dados do teclado, confere cada um e devolve o produto pronto

    struct produtos p = {0};                                 // cria o produto com todos os campos zerados; ele vai sendo preenchido abaixo
    char letras[30] = {0};                                   // guarda as 4 letras usadas no hash (2 da marca e 2 do modelo)

    printf("\n--- CADASTRO DE PRODUTO ---\n");

    printf("Nome do produto: ");
    scanf(" %19[^\n]", p.nome);                              // lê até 19 letras, com espaços, até o Enter

    // repete até a marca ter pelo menos 2 letras, porque o hash usa as 2 primeiras
    do {
        printf("Marca (minimo 2 letras): ");
        scanf(" %19[^\n]", p.modelo.marca);

        if (strlen(p.modelo.marca) < 2) {                    // com menos de 2 letras não dá para calcular o hash
            printf("Marca invalida!\n");
        }
    } while (strlen(p.modelo.marca) < 2);

    // repete até o modelo ter pelo menos 2 letras, porque o hash usa as 2 primeiras
    do {
        printf("Modelo (minimo 2 letras): ");
        scanf(" %19[^\n]", p.modelo.modelo);

        if (strlen(p.modelo.modelo) < 2) {                   // com menos de 2 letras não dá para calcular o hash
            printf("Modelo invalido!\n");
        }
    } while (strlen(p.modelo.modelo) < 2);

    // repete até o valor ser um número maior que zero
    do {
        printf("Valor: R$ ");

        if (scanf("%lf", &p.valor) != 1) {                   // o scanf devolve quantos valores conseguiu ler: 1 significa que leu um número; qualquer outra coisa significa que digitaram letra
            scanf("%*s");                                    // não era número: o %*s lê o texto digitado e joga fora, sem guardar (senão o scanf travaria no mesmo texto para sempre)
            p.valor = 0;                                     // coloca um valor inválido de propósito, para cair na mensagem de erro e repetir a pergunta
        }

        if (p.valor <= 0) {
            printf("Valor invalido!\n");
        }
    } while (p.valor <= 0);

    letras[0] = p.modelo.marca[0];                           // monta o texto de 4 letras para o hash: as 2 primeiras da marca...
    letras[1] = p.modelo.marca[1];
    letras[2] = p.modelo.modelo[0];                          // ...seguidas das 2 primeiras do modelo
    letras[3] = p.modelo.modelo[1];

    p.codigo = geraCodigoProduto(letras);                    // chama a função do hash com as 4 letras e guarda o código gerado

    return p;                                                // devolve o produto completo para quem chamou a função (o main guarda no vetor)
}

void listarProdutos(struct produtos produto[10]) {           // mostra os produtos cadastrados

    printf("\n--- PRODUTOS CADASTRADOS ---\n");

    for (int i = 0; i < 10; i++) {                           // percorre as 10 posições do vetor

        if (produto[i].codigo != 0) {                        // só mostra posições preenchidas: as vazias continuam com código 0

            printf("\nCodigo: %d\n", produto[i].codigo);
            printf("Nome: %s\n", produto[i].nome);
            printf("Marca: %s\n", produto[i].modelo.marca);
            printf("Modelo: %s\n", produto[i].modelo.modelo);
            printf("Valor: R$ %.2f\n", produto[i].valor);    // %.2f mostra o valor com 2 casas decimais, como dinheiro
        }
    }
}

struct produtos localizaProduto(int codigo, struct produtos produto[10]) {  // procura o produto pelo código e devolve ele

    for (int i = 0; i < 10; i++) {                           // olha uma posição do vetor de cada vez

        if (produto[i].codigo == codigo) {                   // achou o código procurado: devolve esse produto e a função termina aqui
            return produto[i];
        }
    }

    struct produtos vazio = {0};                             // se o laço terminou sem achar, cria um produto zerado

    return vazio;                                            // devolve o produto zerado; o código 0 é o sinal de "não encontrado"
}

// ===================== VENDA =====================

double calculaSubtotal(struct carrinhos carrinho) {          // soma o valor de todos os itens do carrinho, ainda sem o desconto

    double soma = 0;                                         // acumulador: começa em zero e vai recebendo o valor de cada item

    for (int i = 0; i < 3; i++) {                            // passa pelas 3 posições possíveis do carrinho
        soma += carrinho.quantidade[i] * carrinho.produto[i].valor;   // soma quantidade x valor unitário do item; posições vazias têm quantidade 0, então somam 0
    }

    return soma;
}

double calculaTotal(double subtotal, double desconto) {      // aplica o desconto percentual ao subtotal

    return subtotal - (subtotal * desconto / 100.0);         // calcula quanto vale o desconto (subtotal x desconto / 100) e tira do subtotal; com desconto 10 vira 10%
}

void listarCarrinho(struct carrinhos carrinho) {             // mostra o resumo do carrinho: cliente e itens

    printf("\n========== RESUMO DA COMPRA ==========\n");

    printf("Cliente: %s (codigo %d)\n",
           carrinho.cliente.nome,
           carrinho.cliente.codigo);

    for (int i = 0; i < 3; i++) {                            // passa pelas 3 posições possíveis do carrinho

        if (carrinho.quantidade[i] > 0) {                    // só mostra os itens que foram adicionados: posição vazia tem quantidade 0

            printf("\nProduto: %s (%s %s)\n",
                   carrinho.produto[i].nome,
                   carrinho.produto[i].modelo.marca,
                   carrinho.produto[i].modelo.modelo);

            printf("Valor unitario: R$ %.2f\n", carrinho.produto[i].valor);
            printf("Quantidade: %d\n", carrinho.quantidade[i]);
            printf("Total do item: R$ %.2f\n",
                   carrinho.quantidade[i] * carrinho.produto[i].valor);   // total só deste item: quantidade x valor unitário
        }
    }
}

void finalizarVenda(struct carrinhos carrinho) {             // fecha a venda: mostra o carrinho, pede o desconto e calcula os totais

    listarCarrinho(carrinho);                                // primeiro mostra o cliente e os itens, para quem está vendendo conferir

    // repete até o desconto ficar entre 0 e 100
    do {
        printf("\nDesconto em porcentagem (0 a 100, ex.: 10 para 10%%): ");   // dentro do printf, %% imprime o símbolo % (um % sozinho seria lido como formato)

        if (scanf("%lf", &carrinho.desconto) != 1) {         // o scanf devolve 1 quando leu um número; se devolveu outra coisa, digitaram letra
            scanf("%*s");                                    // descarta o texto digitado, sem guardar
            carrinho.desconto = -1;                          // desconto inválido de propósito, para cair na mensagem de erro e repetir a pergunta
        }

        if (carrinho.desconto < 0 || carrinho.desconto > 100) {   // desconto negativo aumentaria o preço e acima de 100% daria total negativo
            printf("Desconto invalido!\n");
        }
    } while (carrinho.desconto < 0 || carrinho.desconto > 100);

    carrinho.subtotal = calculaSubtotal(carrinho);           // soma dos itens, sem desconto, e guarda no carrinho

    carrinho.total = calculaTotal(carrinho.subtotal, carrinho.desconto);  // valor final já com o desconto aplicado, guardado no carrinho

    printf("\nSubtotal: R$ %.2f\n", carrinho.subtotal);
    printf("Desconto: %.2f%% (R$ %.2f)\n",                   // mostra o desconto em porcentagem e também em reais
           carrinho.desconto,
           carrinho.subtotal * carrinho.desconto / 100.0);   // valor do desconto em reais: subtotal x desconto / 100
    printf("Total: R$ %.2f\n", carrinho.total);

    printf("\nVenda finalizada!\n");
}

void efetuarVenda(struct clientes cliente[3], struct produtos produto[10], struct carrinhos carrinho) {  // monta a venda: escolhe o cliente e os produtos

    int codigo;                                              // código digitado pelo usuário (serve para o cliente e depois para os produtos)
    int quantidade;                                          // quantidade digitada de cada produto
    int item = 0;                                            // posição atual do carrinho (0, 1 ou 2); também conta quantos produtos já entraram
    struct produtos p;                                       // produto encontrado pelo código digitado, antes de ir para o carrinho

    printf("\n--- EFETUAR VENDA ---\n");

    listarClientes(cliente);                                 // mostra os clientes para o usuário saber qual código digitar

    printf("\nCodigo do cliente: ");
    if (scanf("%d", &codigo) != 1) {                         // o scanf devolve 1 quando leu um número inteiro; outra coisa significa que digitaram letra
        scanf("%*s");                                        // descarta o texto digitado, sem guardar
        codigo = 0;                                          // código 0 nunca existe de verdade, então cai em "cliente não encontrado"
    }

    carrinho.cliente = localizaCliente(codigo, cliente);     // busca o cliente pelo código e já coloca ele no carrinho

    if (carrinho.cliente.codigo == 0) {                      // se o cliente devolvido tem código 0, a busca não achou ninguém
        printf("\nCliente nao encontrado!\n");
        return;                                              // sai da função e volta ao menu, sem fazer a venda
    }

    while (item < 3) {                                       // repete enquanto o carrinho tem espaço (máximo 3 tipos de produto)

        listarProdutos(produto);                             // mostra os produtos para o usuário saber qual código digitar

        printf("\nCodigo do produto (0 para finalizar): ");
        if (scanf("%d", &codigo) != 1) {                     // o scanf devolve 1 quando leu um número inteiro; outra coisa significa que digitaram letra
            scanf("%*s");                                    // descarta o texto digitado, sem guardar
            codigo = -1;                                     // código -1 nunca existe, então cai em "produto não encontrado" (não pode ser 0, que significa finalizar)
        }

        if (codigo == 0) {
            break;                                           // digitou 0: sai do laço e segue para finalizar a venda
        }

        p = localizaProduto(codigo, produto);                // busca o produto pelo código digitado

        if (p.codigo == 0) {                                 // se o produto devolvido tem código 0, a busca não achou nada
            printf("\nProduto nao encontrado!\n");
            continue;                                        // pula o resto e volta ao início do laço para pedir outro código (sem ocupar posição do carrinho)
        }

        // repete até a quantidade ser um número maior que zero
        do {
            printf("Quantidade: ");

            if (scanf("%d", &quantidade) != 1) {             // caso o usuario não digitou um número
                scanf("%*s");                                // descarta o texto digitado, sem guardar
                quantidade = 0;                              // quantidade inválida de propósito, para cair na mensagem de erro e repetir a pergunta
            }

            if (quantidade <= 0) {                           // não faz sentido vender zero ou quantidade negativa
                printf("Quantidade invalida!\n");
            }
        } while (quantidade <= 0);

        carrinho.produto[item] = p;                          // coloca o produto encontrado na posição atual do carrinho
        carrinho.quantidade[item] = quantidade;              // guarda a quantidade na mesma posição, para produto e quantidade ficarem juntos

        item++;                                              // avança para a próxima posição livre do carrinho
    }

    if (item == 0) {                                         // se nenhum produto foi adicionado ao carrinho, imprime a mensagem e cancela a venda
        printf("\nCarrinho vazio. Venda cancelada.\n");
        return;
    }
    finalizarVenda(carrinho);                                // com ao menos 1 produto no carrinho, calcula e mostra os valores finais
}

// --------------------- Estrutura principal do programa ---------------------

int main() {

    struct clientes cliente[3] = {0};              // vetor de 3 clientes (o mínimo pedido), todos começando zerados
    struct produtos produto[10] = {0};            // vetor de 10 produtos (o mínimo pedido), todos começando zerados
    struct carrinhos carrinho = {0};             // o carrinho da venda, começando zerado

    int qtdClientes = 0;                  // quantos clientes já foram cadastrados; também é a próxima posição livre do vetor
    int qtdProdutos = 0;                  // quantos produtos já foram cadastrados; também é a próxima posição livre do vetor
    int opcao;                            // opção digitada no menu

    do {

        mostraMenuInicial();                                 // mostra o menu na tela a cada volta do laço

        if (scanf("%d", &opcao) != 1) {                      // o scanf devolve 1 quando leu um número inteiro; outra coisa significa que digitaram letra
            scanf("%*s");                                    // descarta o texto digitado, sem guardar
            opcao = -1;                                      // opção que não existe no menu, então cai em "Opcao invalida!" mais abaixo
        }

        if (opcao == 1) {

            if (qtdClientes < 3) {                           // se ainda tem espaço no vetor, cadastra o cliente na próxima posição livre
                cliente[qtdClientes] = cadastrarCliente();
                qtdClientes++;                               // e conta mais um cliente cadastrado
            } else {
                printf("\nLimite de clientes atingido!\n");  // vetor cheio: avisa o usuário em vez de gravar fora do vetor, o que quebraria o programa
            }

        } else if (opcao == 2) {

            if (qtdProdutos < 10) {                          // se ainda tem espaço no vetor, cadastra o produto na próxima posição livre
                produto[qtdProdutos] = cadastrarProduto();
                qtdProdutos++;                               // e conta mais um produto cadastrado
            } else {
                printf("\nLimite de produtos atingido!\n");  // vetor cheio: avisa o usuário em vez de gravar fora do vetor, o que quebraria o programa
            }

        } else if (opcao == 3) {

            listarClientes(cliente);                         // mostra todos os clientes cadastrados

        } else if (opcao == 4) {

            listarProdutos(produto);                         // mostra todos os produtos cadastrados

        } else if (opcao == 5) {

            efetuarVenda(cliente, produto, carrinho);        // inicia uma venda, usando os clientes e produtos cadastrados

        } else if (opcao != 0) {

            printf("\nOpcao invalida!\n");                   // qualquer número fora do menu (ou texto digitado) cai aqui; a opção 0 não entra, pois ela encerra o laço
        }

    } while (opcao != 0);                                    // volta ao menu enquanto a opção não for 0

    printf("\nFIM DO PROGRAMA!\n");

    return 0;                                                // avisa ao sistema que o programa terminou sem erro
}