//

/*****************  TRABALHO INTERDISCIPLINAR ENTRE FUNDAMENTOS DE ENGENHARIA DE SOFTWARE E AEDS I  *****************/

//

/****************************************  INICIO DO CODIGO  ****************************************/

//

/****************************         BIBLIOTECAS         ****************************/

// Usadas para definir data e hora

#include <dos.h>
#include <time.h>

// Usada para funcoes matematicas

#include <math.h>

// Usada para funcoes com strings

#include <string.h>

// Bibliotecas padroes

#include <stdio.h>
#include <stdlib.h>

/*************** Definicoes ******************/

// Definicoes de tamanhos para os vetores que carregam os arquivos

#define X__SIZE_CLIENT 100
#define X__SIZE_VEHICLES 100
#define X__SIZE_SELLING_LOG 100

// Definicao global para o tamanho dos codigos

#define SIZE__CODE_ALL 21

/********** Meu contador global ***********/

int i;

//

//

/****************************         ESTRUTURAS         ****************************/

// Estruturas do cliente.

struct sEndereco

{
    char bairro[50],
        rua[100],
        numero[10],
        complemento[10],
        cep[15],
        cidade[50],
        estado[3];
};

typedef struct sEndereco tEndereco;

struct sCliente

{
    tEndereco endereco;

    char nome[50],
        codigo[SIZE__CODE_ALL],
        telefone[15];
};

typedef struct sCliente tCliente;

tCliente cliente[X__SIZE_CLIENT];

// Estruturas do log de locacao.

struct sCodigo

{
    char locacao[SIZE__CODE_ALL],
        cliente[SIZE__CODE_ALL],
        veiculo[SIZE__CODE_ALL];
};

typedef struct sCodigo tCodigo;

struct sLog

{
    tCodigo codigo;

    char preco[7],
        retirada[11],
        devolucao[11],
        devolucaotof[2],
        seguro[2],
        dias[4];
};

typedef struct sLog tLog;

tLog logLocacao[X__SIZE_SELLING_LOG];

// Estruturas do veiculo.

struct sHardware

{
    char modelo[31],
        cor[13],
        placa[9],
        ocupacao[5];
};

typedef struct sHardware tHardware;

struct sVeiculo

{
    tHardware hardware;

    char diaria[7],
        codigo[SIZE__CODE_ALL],
        descricao[15],
        status[10];
};

typedef struct sVeiculo tVeiculo;

tVeiculo veiculo[X__SIZE_VEHICLES];

//

//

/****************************         FUNCOES         ****************************/

//

// Funcao retorna o ponteiro de um registro atraves do codigo, seja de pessoa, locacao ou veiculo
int pesquisarPorCodigoGlobal(int inpt)
{
    char code[SIZE__CODE_ALL],
        keep = 's';

    // 0 para cliente, 1 para locacao, 2 para veiculo
    while (keep == 's')
    {
        // Usuario insere o codigo
        printf("\n Busque o codigo:");
        gets(code);
        fflush(stdin);

        // Cliente
        if (inpt == 0)
            for (i = 0; i < X__SIZE_CLIENT && strcmp(cliente[i].nome, "EOF") != 0; i++)
                if (strcasecmp(code, cliente[i].codigo) == 0)
                    return i;

        // Locacao
        if (inpt == 1)
            for (i = 0; i < X__SIZE_SELLING_LOG && strcmp(logLocacao[i].devolucao, "EOF") != 0; i++)
                if (strcasecmp(code, logLocacao[i].codigo.locacao) == 0)
                    return i;

        // Veiculo
        if (inpt == 2)
            for (i = 0; i < X__SIZE_VEHICLES && strcmp(veiculo[i].descricao, "EOF") != 0; i++)
                if (strcasecmp(code, veiculo[i].codigo) == 0)
                    return i;

        // Caso nada seja retornado
        printf("\n Codigo nao encontrado! Deseja buscar novamente? (s/n)");
        scanf(" %c", &keep);
        fflush(stdin);
    }
    return -1;
}

//

/* Esta funcao precisou ser criada para que houvesse uma entrada com codigo em outras linhas,
    funciona da mesma forma que a anterior */
int pesquisarPorCodigoVeiculo(char code[])
{
    for (i = 0; i < X__SIZE_VEHICLES && strcmp(veiculo[i].descricao, "EOF") != 0; i++)
        if (strcasecmp(code, veiculo[i].codigo) == 0)
            return i;
    return -1;
}

//

// Printa todo o registro do tipo que o usuario desejar
void printTudo()
{
    int choice;
    // Informa o usuario sobre opcoes
    printf("\n 1.Clientes\n 2.Logs\n 3.Veiculos\n Selecione o registro: ");
    scanf("%d", &choice);
    system("cls");

    /* Estes "for" iniciam o ponteiro de um tipo e o terminam quando o tipo chegar em EOF, como
        inserem o print de cada funcao com um ponteiro diferente, acabam imprimindo todo o registro*/
    if (choice == 1)
        for (i = 0; strcmp("EOF", cliente[i].nome) != 0; i++)
            printCliente(cliente[i]);
    else if (choice == 2)
        for (i = 0; strcmp("EOF", logLocacao[i].devolucao) != 0; i++)
            printLog(logLocacao[i]);
    else if (choice == 3)
        for (i = 0; strcmp("EOF", veiculo[i].descricao) != 0; i++)
            printVeiculo(veiculo[i]);
}

//

void printCliente(tCliente p)
{
    printf("\n ***** Cliente *****");
    printf("\n Nome: %s", p.nome);
    printf("\n Tel: %s", p.telefone);
    printf("\n Codigo: %s", p.codigo);
    printf("\n Endereco:");
    printf("\n Rua %s, %s, %s", p.endereco.rua, p.endereco.numero, p.endereco.complemento);
    printf("\n %s, %s, %s", p.endereco.cidade, p.endereco.estado, p.endereco.cep);
    printf("\n");
}

//

void printVeiculo(tVeiculo q)
{
    printf("\n ***** Veiculo *****");
    printf("\n Modelo: %s", q.hardware.modelo);
    printf("\n Descricao: %s", q.descricao);
    printf("\n Codigo: %s", q.codigo);
    printf("\n Cor: %s, Ocupacao: %s", q.hardware.cor, q.hardware.ocupacao);
    printf("\n Diaria: %s, Placa: %s", q.diaria, q.hardware.placa);
    printf("\n Status: %s", q.status);
    printf("\n");
}

//

void printLog(tLog r)
{
    printf("\n ***** Log de vendas *****");
    printf("\n Codigo: %s", r.codigo.locacao);
    printf("\n Cliente: %s", r.codigo.cliente);
    printf("\n Veiculo: %s", r.codigo.veiculo);
    printf("\n Retirada: %s Devolucao: %s Dias: %s", r.retirada, r.devolucao, r.dias);
    printf("\n Devolvido? %s", r.devolucaotof);
    if (r.devolucaotof[0] == 'N')
        printf("\n Ainda nao pago, total esperado: %s", r.preco);
    else
        printf("\n Foram pagos %s reais", r.preco);
    if (r.seguro[0] == 'n')
        printf("\n Seguro nao contratado");
    else
        printf("\n Seguro Contratado");
    printf("\n");
}

//

void switchComandosInterface(int p)
{
    fflush(stdin);
    if (p == 1)
        addCliente();
    else if (p == 2)
        printCliente(cliente[pesquisarPorCodigoGlobal(0)]);
    else if (p == 3)
        addVeiculo();
    else if (p == 4)
        printVeiculo(veiculo[pesquisarPorCodigoGlobal(2)]);
    else if (p == 5)
        addLog();
    else if (p == 6)
        printLog(logLocacao[pesquisarPorCodigoGlobal(1)]);
    else if (p == 7)
        fimLog();
    else if (p == 8)
        printTudo();
    else if (p == 9)
        fidelidade();
}

//

int fimDeArquivoGlobal(int inp)
{
    if (inp == 0)
        for (i = 0; i < X__SIZE_CLIENT; i++)
            if (strcasecmp(cliente[i].nome, "EOF") == 0)
                return i;
    if (inp == 1)
        for (i = 0; i < X__SIZE_SELLING_LOG; i++)
            if (strcasecmp(logLocacao[i].devolucao, "EOF") == 0)
                return i;
    if (inp == 2)
        for (i = 0; i < X__SIZE_VEHICLES; i++)
            if (strcasecmp(veiculo[i].descricao, "EOF") == 0)
                return i;
    return -1;
}

//

void geradorDeCodigoGlobal(char codGerado[], int in)
{
    time_t now = time(NULL);
    struct tm *pt = localtime(&now);
    // esta string de caracteres numericos e usada para preencher numeros aleatorios
    char num[] = "0123456789";
    // clientes comecam com 0, log de locacao com 1 e veiculos com 2
    if (in == 0)
        codGerado[0] = num[rand() % 4];
    else if (in == 1)
        codGerado[0] = num[(rand() % 4) + 4];
    else if (in == 2)
        codGerado[0] = num[(rand() % 2) + 8];
    for (int i = 1; i < 5; i++)
        codGerado[i] = num[rand() % 10];
    codGerado[5] = '/';
    // tm_yday recebe os dias desde 1/1, portanto excluindo a necessidade de mês
    codGerado[6] = ((pt->tm_yday - pt->tm_yday % 100) / 100) + '0';
    codGerado[7] = (pt->tm_yday - pt->tm_yday + pt->tm_yday % 100 - pt->tm_yday % 10) / 10 + '0';
    codGerado[8] = (pt->tm_yday % 10) + '0';
    codGerado[9] = '.';
    codGerado[10] = (pt->tm_hour - pt->tm_hour % 10) / 10 + '0';
    codGerado[11] = pt->tm_hour % 10 + '0';
    codGerado[12] = (pt->tm_min - pt->tm_min % 10) / 10 + '0';
    codGerado[13] = '.';
    codGerado[14] = pt->tm_min % 10 + '0';
    codGerado[15] = (pt->tm_sec - pt->tm_sec % 10) / 10 + '0';
    codGerado[16] = pt->tm_sec % 10 + '0';
    codGerado[17] = '-';
    codGerado[18] = (pt->tm_year - 100 - pt->tm_year % 10) / 10 + '0';
    codGerado[19] = pt->tm_year % 10 + '0';
    codGerado[20] = NULL;
}

//

void addCliente()
{
    // Criar tipo a ser preenchido
    tCliente p;
    system("cls");
    // Preencher novo item
    printf("\n******* Incluir cliente *******\n");
    printf("\n\nDigite o nome: ");
    scanf(" %[^\n]", &p.nome);
    printf(" Cel: ");
    scanf(" %[^\n]", &p.telefone);
    geradorDeCodigoGlobal(p.codigo, 0);
    printf(" Codigo:%s", p.codigo);
    printf("\n *ENDERECO*");
    printf("\n Rua: ");
    scanf(" %[^\n]", &p.endereco.rua);
    printf(" Nro: ");
    scanf("%s", &p.endereco.numero);
    printf(" Complemento: ");
    scanf(" %[^\n]", &p.endereco.complemento);
    printf(" Bairro: ");
    scanf(" %[^\n]", &p.endereco.bairro);
    printf(" Cidade: ");
    scanf(" %[^\n]", &p.endereco.cidade);
    printf(" Estado: ");
    scanf("%s", &p.endereco.estado);
    printf(" Cep: ");
    scanf("%s", &p.endereco.cep);
    i = fimDeArquivoGlobal(0);
    cliente[i] = p;
    strcpy(cliente[i + 1].nome, "EOF");
    printf("\n Cliente %s incluido.", p.codigo);
}

//

void devolucao(char inicio[11], char duracao[4], char fim[11])
{

    // Inicializando ano em int
    int temp[3] = {(inicio[6] - '0') * 1000 + (inicio[7] - '0') * 100 + (inicio[8] - '0') * 10 + (inicio[9] - '0'),
                   (inicio[3] - '0') * 10 + (inicio[4] - '0'),
                   (inicio[0] - '0') * 10 + (inicio[1] - '0')},
        duracaoint;

    // Inicializando estrutura de tempo
    struct tm t = {.tm_year = temp[0] - 1900,
                   .tm_mon = temp[1] - 1,
                   .tm_mday = temp[2]};

    // Mudar data
    duracaoint = atoi(duracao);
    t.tm_mday += duracaoint;
    mktime(&t);

    // Escrever nova data formatada em string
    strftime(fim, 11, "%d/%m/%Y", &t);
}

//

// Calcula o preco de uma locacao
void calculaPreco(int point, char tofseguro[2], char fullduracao[4], char price[7])
{
    int diariaint,
        fullduracaoint;
    veiculo[point].diaria;
    diariaint = atoi(veiculo[point].diaria);
    fullduracaoint = atoi(fullduracao);
    diariaint = diariaint * fullduracaoint;
    if (tofseguro[0] == 's')
        diariaint = diariaint + 50;
    itoa(diariaint, price, 10);
}

//

// Esta funcao registra uma nova locacao
void addLog()
{

    // Criar tipo a ser preenchido
    tLog p;
    system("cls");

    // Interface da nova locacao
    printf("\n******* Incluir locacao *******");
    int verificadorDeVeiculo = 0,
        ponteiro = 0;

    // "while" prende o usuario a escolher um veiculo valido
    while (verificadorDeVeiculo == 0)
    {

        // Usuario digita o codigo do veiculo a ser alugado
        printf("\n Digite o codigo do veiculo: ");
        scanf("%s", &p.codigo.veiculo);

        // Verifica o status do veiculo desejado
        ponteiro = pesquisarPorCodigoVeiculo(p.codigo.veiculo);
        if (strcmp(veiculo[ponteiro].status, "Livre") == 0)
            verificadorDeVeiculo = 1;
        else
            printf(" O veiculo nao esta livre para locacao.\n");
    }
    /******* Preencher novo item atraves de inputs do usuario *******/

    // Informa ao usuario a disponibilidade positiva
    printf(" O veiculo esta livre para locacao.\n");

    // Scaneia o codigo do cliente que deseja realizar a locacao
    printf("\n Codigo do cliente: ");
    scanf(" %[^\n]", &p.codigo.cliente);

    // Data da retirada em formato DD/MM/AAAA
    printf(" Digite a data de retirada (DD/MM/AAAA): ");
    scanf(" %[^\n]", &p.retirada);

    // Dias esperados entre a retirada e devolucao
    printf(" Digite quantos dias que o cliente deseja alugar: ");
    scanf(" %[^\n]", &p.dias);

    // Funcao calcula a devolucao esperada do veiculo
    devolucao(p.retirada, p.dias, p.devolucao);
    printf(" Ele sera devolvido no dia: %s", p.devolucao);

    // Sobre o seguro de 50 RS
    printf("\n O seguro esta incluido? (s/n): ");
    scanf(" %[^\n]", &p.seguro);
    /*********************** Fim dos inputs *********************/

    // Calcula o preco esperado da locacao
    calculaPreco(ponteiro, p.seguro, p.dias, p.preco);
    printf(" O cliente pagara: %s", p.preco);

    // Define a devolucao como N, ja que a locacao acabou de ser feita
    strcpy(p.devolucaotof, "N");

    // Gera o codigo da locacao
    geradorDeCodigoGlobal(p.codigo.locacao, 1);
    printf("\n Codigo: %s", p.codigo);

    // Busca pelo ultimo ponteiro preenchido do vetor veiculo
    i = fimDeArquivoGlobal(1);

    // Preenche este vetor com o tipo temporario
    logLocacao[i] = p;

    // Caso o veiculo esteja livre, o atualiza
    strcpy(veiculo[ponteiro].status, "Em uso");

    // Preenche o proximo vetor com "EOF"
    strcpy(logLocacao[i + 1].devolucao, "EOF");

    // Declara o sucesso da operacao ao usuario
    printf("\n Locacao %s incluida.", p.codigo.locacao);
}

//

// Esta funcao registra a devolução de um veiculo, "dando baixa" em uma locacao
void fimLog()
{
    system("cls");
    int logPointer,
        carPointer,
        tof1 = 0;

    // Interface de usuario
    printf("\n******* Finalizar locacao *******");

    // While para caso a locacao ja esteja fechada
    while (tof1 == 0)
    {
        // Definir ponteiro da locacao desejada
        logPointer = pesquisarPorCodigoGlobal(1);

        // Informa ao usuario que a locacao ja foi totalmente concluida e o prende no while
        if (logLocacao[logPointer].devolucaotof[0] == 'S')
            printf("\n Esta devolucao ja ocorreu");
        else
            tof1 = 1;
        // Permite sair do while
    }

    // Informa o usuario sobre todos os detalhes da locacao
    printLog(logLocacao[logPointer]);

    /* Pergunta ao usuario se a data da entrega coincide com o esperado,
      isso sera importante nas linhas seguintes */
    printf("\n\n A data da entrega coincide com o esperado? (s/n)");
    char tof;
    scanf(" %c", &tof);

    // Caso a data nao coincida, calcula um novo preco
    if (tof == 'n')
    {
        printf(" Digite quantos dias que o cliente alugou: ");
        scanf(" %[^\n]", &logLocacao[logPointer].dias);

        // Calcula o novo preco
        calculaPreco(logPointer, logLocacao[logPointer].seguro, logLocacao[logPointer].dias, logLocacao[logPointer].preco);
    }

    // Apresenta ao usuario o preco final
    printf(" Por favor, cobre %s reais do cliente", logLocacao[logPointer].preco);

    // Segue apos a cobranca
    system("pause");

    // Escreve o fim da locacao
    strcpy(logLocacao[logPointer].devolucaotof, "S");

    /***** Escreve a volta do carro a locadora *****/

    // Busca pelo ponteiro do veiculo devolvido
    carPointer = pesquisarPorCodigoVeiculo(logLocacao[logPointer].codigo.veiculo);

    // Escreve a devolucao do veiculo
    strcpy(veiculo[carPointer].status, "Livre");

    /******************** Fim *********************/

    // Declara o sucesso da devolucao ao usuario
    printf("\n Devolucao concluida");
}

//

void addVeiculo()
{
    // Criar tipo a ser preenchido
    tVeiculo p;
    system("cls");

    /******* Preencher novo item atraves de inputs do usuario *******/

    // Interface de usuario
    printf("\n******* Incluir veiculo *******\n");

    // Sobre o modelo
    printf("\n\nDigite o modelo: ");
    scanf(" %[^\n]", &p.hardware.modelo);

    // Sobre a cor
    printf(" Cor: ");
    scanf(" %[^\n]", &p.hardware.cor);

    // Sobre a ocupacao
    printf("\n Ocupacao: ");
    scanf(" %[^\n]", &p.hardware.ocupacao);

    // Sobre a placa
    printf(" Placa: ");
    scanf("%s", &p.hardware.placa);

    // Sobre o valor do veiculo
    printf(" Valor da diaria: ");
    scanf(" %[^\n]", &p.diaria);

    // Sobre a descricao do veiculo
    printf(" Sua descricao: ");
    scanf(" %[^\n]", &p.descricao);

    /*********************** Fim dos inputs *********************/

    // Gerar e preencher codigo com funcao
    geradorDeCodigoGlobal(p.codigo, 2);
    printf(" Codigo: %s", p.codigo);

    // E obvio que um veiculo sera registrado como livre, portanto o faz automaticamente
    strcpy(p.status, "Livre");

    // Busca pelo ultimo ponteiro preenchido do vetor veiculo
    int i = fimDeArquivoGlobal(2);

    // Preenche este vetor com o tipo temporario
    veiculo[i] = p;

    // Preenche o proximo vetor com "EOF"
    strcpy(veiculo[i + 1].descricao, "EOF");

    // Declara sucesso ao usuario
    printf("\n Veiculo %s incluido.", p.codigo);
}

//

// Funcao recebe o codigo de um cliente, printa todos as suas locacoes e retorna o seu total
int printarContar(char cod[])
{
    i = 0;

    // c como ponteiro do vetor locacao
    for (int c = 0; strcmp("EOF", logLocacao[c].devolucao) != 0; c++)
        if (strcmp(logLocacao[c].codigo.cliente, cod) == 0)
        {
            // Printa as locacoes
            printLog(logLocacao[c]);

            // 'i' permite contar todas as locacoes do cliente
            i++;
        }
    return i;
}

//

// Esta funcao printa todas as locacoes de um cliente e o seu total

void fidelidade()
{
    printf("\n******* Programa de fidelidade *******\n");
    char code[SIZE__CODE_ALL];

    // Usuario digita o codigo do cliente
    printf("\n Informe o codigo do cliente:");
    scanf("%s", &code);

    // Envia o codigo para a funcao anterior, printanto locacoes do cliente e retornando o seu total
    int total = printarContar(code) * 10;

    // Imprime o total de locacoes
    printf("\n Este cliente tem %d pontos", total);

    // Se o cliente tiver 500 pontos, declara sua qualificacao ao kit
    if (total >= 500)
        printf(", qualificando-o para o kit da LocaMais.");
}

//

// Esta funcao carrega os dados dos arquivos em vetores

void carregaDadosDosArquivos()
{
    FILE *pLerCliente = fopen("CLENTES.csv", "r"),
         *pLerLogLocacao = fopen("LOCACAO.csv", "r"),
         *pLerVeiculo = fopen("VEICULO.csv", "r");

    // Estas strings receberao cada linha dos arquivos no fscanf
    char type[150],
        value[150];

    // Estas variaveis temporarias receberao as strings citadas acima
    tCliente client;
    tVeiculo vehicle;
    tLog registro;

    // outScan le o retorno do scanf, testando assim se o arquivo chegou ao final
    int outScan;
    i = 0;

    // Se o arquivo existe
    if (pLerCliente != NULL)
    {
        outScan = fscanf(pLerCliente, "%s %[^\n]", &type, &value);

        // Enquanto o arquivo nao chega ao fim
        while (outScan != EOF)
        {

            // Le o inicio do registro no arquivo
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(client.nome, "");
                strcpy(client.codigo, "");
                strcpy(client.telefone, "");
            }

            /* Le cada uma das linhas em busca de sua respectiva variavel,
               definitivamente nao e o metodo mais eficiente */
            else if (strcasecmp(type, "Nome") == 0)
                strcpy(client.nome, value);
            else if (strcasecmp(type, "Telefone") == 0)
                strcpy(client.telefone, value);
            else if (strcasecmp(type, "Codigo") == 0)
                strcpy(client.codigo, value);
            else if (strcasecmp(type, "Rua") == 0)
                strcpy(client.endereco.rua, value);
            else if (strcasecmp(type, "Nro") == 0)
                strcpy(client.endereco.numero, value);
            else if (strcasecmp(type, "Comp") == 0)
                strcpy(client.endereco.complemento, value);
            else if (strcasecmp(type, "Bairro") == 0)
                strcpy(client.endereco.bairro, value);
            else if (strcasecmp(type, "Cidade") == 0)
                strcpy(client.endereco.cidade, value);
            else if (strcasecmp(type, "Estado") == 0)
                strcpy(client.endereco.estado, value);
            else if (strcasecmp(type, "Cep") == 0)
                strcpy(client.endereco.cep, value);

            // Le fim do registro no arquivo
            else if (strcasecmp(type, "FIM") == 0)
            {

                // Passa do vetor temporario para o definitivo
                cliente[i] = client;

                // i++ para mudar de registro no vetor
                i++;
            }
            outScan = fscanf(pLerCliente, "%s %[^\n]", &type, &value);
        }

        // Ao final, escreve o fim do vetor
        strcpy(cliente[i].nome, "EOF");

        // Fecha o arquivo
        fclose(pLerCliente);
    }

    //              OS PROXIMOS DOIS "IF" SAO EXATAMENTE IGUAIS AO PRIMEIRO

    if (pLerLogLocacao != NULL)
    {
        i = 0;
        outScan = fscanf(pLerLogLocacao, "%s %[^\n]", &type, &value);
        while (outScan != EOF)
        {
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(registro.devolucao, "");
                strcpy(registro.seguro, "");
                strcpy(registro.dias, "");
            }
            else if (strcasecmp(type, "Devolucao") == 0)
                strcpy(registro.devolucao, value);
            else if (strcasecmp(type, "Seguro") == 0)
                strcpy(registro.seguro, value);
            else if (strcasecmp(type, "Dias") == 0)
                strcpy(registro.dias, value);
            else if (strcasecmp(type, "Retirada") == 0)
                strcpy(registro.retirada, value);
            else if (strcasecmp(type, "Devolvido") == 0)
                strcpy(registro.devolucaotof, value);
            else if (strcasecmp(type, "Codigo") == 0)
                strcpy(registro.codigo.locacao, value);
            else if (strcasecmp(type, "Cliente") == 0)
                strcpy(registro.codigo.cliente, value);
            else if (strcasecmp(type, "Veiculo") == 0)
                strcpy(registro.codigo.veiculo, value);
            else if (strcasecmp(type, "Preco") == 0)
                strcpy(registro.preco, value);
            else if (strcasecmp(type, "FIM") == 0)
            {
                logLocacao[i] = registro;
                i++;
            }
            outScan = fscanf(pLerLogLocacao, "%s %[^\n]", &type, &value);
        }
        strcpy(logLocacao[i].devolucao, "EOF");
        fclose(pLerLogLocacao);
    }

    if (pLerVeiculo != NULL)
    {
        i = 0;
        outScan = fscanf(pLerVeiculo, "%s %[^\n]", &type, &value);
        while (outScan != EOF)
        {
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(vehicle.descricao, "");
                strcpy(vehicle.codigo, "");
                strcpy(vehicle.status, "");
            }
            else if (strcasecmp(type, "Descricao") == 0)
                strcpy(vehicle.descricao, value);
            else if (strcasecmp(type, "Codigo") == 0)
                strcpy(vehicle.codigo, value);
            else if (strcasecmp(type, "Status") == 0)
                strcpy(vehicle.status, value);
            else if (strcasecmp(type, "Diaria") == 0)
                strcpy(vehicle.diaria, value);
            else if (strcasecmp(type, "Placa") == 0)
                strcpy(vehicle.hardware.placa, value);
            else if (strcasecmp(type, "Modelo") == 0)
                strcpy(vehicle.hardware.modelo, value);
            else if (strcasecmp(type, "Ocupacao") == 0)
                strcpy(vehicle.hardware.ocupacao, value);
            else if (strcasecmp(type, "Cor") == 0)
                strcpy(vehicle.hardware.cor, value);
            else if (strcasecmp(type, "FIM") == 0)
            {
                veiculo[i] = vehicle;
                i++;
            }
            outScan = fscanf(pLerVeiculo, "%s %[^\n]", &type, &value);
        }
        strcpy(veiculo[i].descricao, "EOF");
        fclose(pLerVeiculo);
    }
}

//

// Funcao escreve os vetores em arquivos ao finalizar o processo

void escreverVetores()
{
    // Arquivo
    FILE *pSalvarClientes = fopen("CLENTES.csv", "w"), *pSalvarLogLocacao = fopen("LOCACAO.csv", "w");
    if (pSalvarClientes != NULL)
    {
        for (i = 0; strcmp("EOF", cliente[i].nome) != 0; i++)
        {
            fprintf(pSalvarClientes, "INICIO CLIENTE\n");
            fprintf(pSalvarClientes, "Nome %s\n", cliente[i].nome);
            fprintf(pSalvarClientes, "Codigo %s\n", cliente[i].codigo);
            fprintf(pSalvarClientes, "Telefone %s\n", cliente[i].telefone);
            fprintf(pSalvarClientes, "Rua %s\n", cliente[i].endereco.rua);
            fprintf(pSalvarClientes, "Nro %s\n", cliente[i].endereco.numero);
            fprintf(pSalvarClientes, "Comp %s\n", cliente[i].endereco.complemento);
            fprintf(pSalvarClientes, "Bairro %s\n", cliente[i].endereco.bairro);
            fprintf(pSalvarClientes, "Cidade %s\n", cliente[i].endereco.cidade);
            fprintf(pSalvarClientes, "Estado %s\n", cliente[i].endereco.estado);
            fprintf(pSalvarClientes, "Cep %s\n", cliente[i].endereco.cep);
            fprintf(pSalvarClientes, "FIM CLIENTE\n");
        }
        fclose(pSalvarClientes);
    }
    
    // OS PROXIMOS IF SAO EXATAMENTE IGUAIS

    if (pSalvarLogLocacao != NULL)
    {
        for (i = 0; strcmp("EOF", logLocacao[i].devolucao) != 0; i++)
        {
            fprintf(pSalvarLogLocacao, "INICIO LOCACAO\n");
            fprintf(pSalvarLogLocacao, "Devolucao %s\n", logLocacao[i].devolucao);
            fprintf(pSalvarLogLocacao, "Seguro %s\n", logLocacao[i].seguro);
            fprintf(pSalvarLogLocacao, "Dias %s\n", logLocacao[i].dias);
            fprintf(pSalvarLogLocacao, "Retirada %s\n", logLocacao[i].retirada);
            fprintf(pSalvarLogLocacao, "Devolvido %s\n", logLocacao[i].devolucaotof);
            fprintf(pSalvarLogLocacao, "Codigo %s\n", logLocacao[i].codigo.locacao);
            fprintf(pSalvarLogLocacao, "Cliente %s\n", logLocacao[i].codigo.cliente);
            fprintf(pSalvarLogLocacao, "Veiculo %s\n", logLocacao[i].codigo.veiculo);
            fprintf(pSalvarLogLocacao, "Preco %s\n", logLocacao[i].preco);
            fprintf(pSalvarLogLocacao, "FIM LOCACAO\n");
        }
        fclose(pSalvarLogLocacao);
    }
    FILE *pSalvarVeiculos = fopen("VEICULO.csv", "w");

    if (pSalvarVeiculos != NULL)
    {
        for (i = 0; strcmp("EOF", veiculo[i].descricao) != 0; i++)
        {
            fprintf(pSalvarVeiculos, "INICIO VEICULO\n");
            fprintf(pSalvarVeiculos, "Descricao %s\n", veiculo[i].descricao);
            fprintf(pSalvarVeiculos, "Codigo %s\n", veiculo[i].codigo);
            fprintf(pSalvarVeiculos, "Status %s\n", veiculo[i].status);
            fprintf(pSalvarVeiculos, "Diaria %s\n", veiculo[i].diaria);
            fprintf(pSalvarVeiculos, "Placa %s\n", veiculo[i].hardware.placa);
            fprintf(pSalvarVeiculos, "Modelo %s\n", veiculo[i].hardware.modelo);
            fprintf(pSalvarVeiculos, "Ocupacao %s\n", veiculo[i].hardware.ocupacao);
            fprintf(pSalvarVeiculos, "Cor %s\n", veiculo[i].hardware.cor);
            fprintf(pSalvarVeiculos, "FIM VEICULO\n");
        }
        fclose(pSalvarVeiculos);
    }
}

//

//

//

//

/****************************         FUNCAO PRINCIPAL         ****************************/

//

main()
{
    // Inicializa seed para funcao time()
    srand((unsigned int)(time(0)));

    // Carrega os arquivos
    carregaDadosDosArquivos();

    // Interface de usuario
    int opcao = 0;
    while (opcao != 10)
    {
        system("cls");
        printf("\n ****** Cadastro de Clientes ********\n");
        printf("\n 1.Incluir cliente");
        printf("\n 2.Pesquisar cliente por codigo");
        printf("\n 3.Incluir veiculo");
        printf("\n 4.Pesquisar veiculo por codigo");
        printf("\n 5.Gerar nova locacao");
        printf("\n 6.Pesquisar locacao por codigo");
        printf("\n 7.Determinar fim de locacao");
        printf("\n 8.Printar todo o registro");
        printf("\n 9.Programa de fidelidade");
        printf("\n 10.Encerrar ");
        printf("\n\n Digite sua opcao : ");
        scanf(" %d", &opcao);
        if (opcao >= 1 && opcao <= 10)
        {
            // Envia a escolha do usuario para a funcao que a tratara
            switchComandosInterface(opcao);
            printf("\n\n");
            system("pause");
        }
    }

    // Salva os vetores em arquivos
    escreverVetores();
}

//

/****************************         FIM DA FUNCAO PRINCIPAL         ****************************/

//

/*******************************************         FIM DO CODIGO         *******************************************/

//

/******************************** INFO IMPORTANTE *************************************


Sendo k o ponteiro final,

cliente[k].nome sempre recebera "EOF" ao final do arquivo e vetor cliente
logLocacao[k].devolucao sempre recebera "EOF" ao final do arquivo e vetor loglocacao
veiculo[k].descricao sempre recebera "EOF" ao final do arquivo e vetor veiculo

----------------------Portanto sempre use-os para ler o mesmo---------------------------

//

***********************************************************************************************************************/

//
