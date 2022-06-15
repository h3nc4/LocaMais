#include <dos.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define X__SIZE_CLIENT 100
#define X__SIZE_VEHICLES 100
#define X__SIZE_SELLING_LOG 100
#define SIZE__CODE_ALL 21

// Estruturas do cliente.
struct sEndereco
{
    char bairro[50];
    char rua[100];
    char numero[10];
    char complemento[10];
    char cep[15];
    char cidade[50];
    char estado[3];
};
typedef struct sEndereco tEndereco;
struct sCliente
{
    tEndereco endereco;
    char nome[50];
    char codigo[SIZE__CODE_ALL];
    char telefone[15];
};
typedef struct sCliente tCliente;
tCliente cliente[X__SIZE_CLIENT];

// Estruturas do log de locacao.
struct sCodigo
{
    char locacao[SIZE__CODE_ALL];
    char cliente[SIZE__CODE_ALL];
    char veiculo[SIZE__CODE_ALL];
};
typedef struct sCodigo tCodigo;
struct sLog
{
    tCodigo codigo;
    char preco[7];
    char retirada[11];
    char devolucao[11];
    char devolucaotof[2];
    char seguro[2];
    char dias[4];
};
typedef struct sLog tLog;
tLog logLocacao[X__SIZE_SELLING_LOG];

// Estruturas do veiculo.
struct sHardware
{
    char modelo[31];
    char cor[13];
    char placa[9];
    char ocupacao[5];
};
typedef struct sHardware tHardware;
struct sVeiculo
{
    tHardware hardware;
    char diaria[7];
    char codigo[SIZE__CODE_ALL];
    char descricao[15];
    char status[10];
};
typedef struct sVeiculo tVeiculo;
tVeiculo veiculo[X__SIZE_VEHICLES];

int pesquisarPorCodigoGlobal(int inpt)
{
    char code[SIZE__CODE_ALL];
    printf("\n Busque o codigo:");
    gets(code);
    // Cliente
    if (inpt == 0)
        for (int i = 0; i < X__SIZE_CLIENT && strcmp(cliente[i].nome, "EOF") != 0; i++)
            if (strcasecmp(code, cliente[i].codigo) == 0)
                return i;
    // Locacao
    if (inpt == 1)
        for (int i = 0; i < X__SIZE_SELLING_LOG && strcmp(logLocacao[i].devolucao, "EOF") != 0; i++)
            if (strcasecmp(code, logLocacao[i].codigo.locacao) == 0)
                return i;
    // Veiculo
    if (inpt == 2)
        for (int i = 0; i < X__SIZE_VEHICLES && strcmp(veiculo[i].descricao, "EOF") != 0; i++)
            if (strcasecmp(code, veiculo[i].codigo) == 0)
                return i;
    return -1;
}

int pesquisarPorCodigoVeiculo(char code[])
{
    int r = -1;
    for (int i = 0; i < X__SIZE_VEHICLES && strcmp(veiculo[i].descricao, "EOF") != 0; i++)
        if (strcasecmp(code, veiculo[i].codigo) == 0)
        {
            r = i;
            i = X__SIZE_VEHICLES;
        }
    return r;
}
void printTudo()
{
    printf("\n Selecione o registro: \n 1.Clientes\n 2.Logs\n 3.Veiculos");
    int choice = 0;
    scanf("%d", &choice);
    if (choice == 1)
        for (int i = 0; strcmp("EOF", cliente[i].nome) != 0; i++)
            printCliente(cliente[i]);
    else if (choice == 2)
        for (int i = 0; strcmp("EOF", logLocacao[i].devolucao) != 0; i++)
            printLog(logLocacao[i]);
    else if (choice == 3)
        for (int i = 0; strcmp("EOF", veiculo[i].descricao) != 0; i++)
            printVeiculo(veiculo[i]);
}
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

void printVeiculo(tVeiculo q)
{
    printf("\n ***** Veiculo *****");
    printf("\n Modelo: %s", q.hardware.modelo);
    printf("\n Descricao: %s", q.descricao);
    printf("\n Codigo :%s", q.codigo);
    printf("\n Cor: %s, Ocupacao: %s", q.hardware.cor, q.hardware.ocupacao);
    printf("\n Diaria: %s, Placa: %s", q.diaria, q.hardware.placa);
    if (q.status == 'n')
        printf("\n Status: Em uso");
    else
        printf("\n Status: Livre");
    printf("\n");
}

void printLog(tLog r)
{
    printf("\n ***** Log de vendas *****");
    printf("\n Codigo: %s", r.codigo.locacao);
    printf("\n Cliente: %s", r.codigo.cliente);
    printf("\n Veiculo: %s", r.codigo.veiculo);
    printf("\n Rua %s, %s, %s", r.devolucao, r.retirada, r.dias);
    printf("\n Devolvido? %s", r.devolucaotof);
    if (r.seguro == 'n')
        printf("\n Seguro: Nao contratado");
    else
        printf("\n Seguro: Contratado");
    printf("\n");
}

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
        fidelilade();
}

int fimDeArquivoGlobal(int inp)
{
    if (inp == 0)
        for (int i = 0; i < X__SIZE_CLIENT; i++)
            if (strcasecmp(cliente[i].nome, "EOF") == 0)
                return i;
    if (inp == 1)
        for (int i = 0; i < X__SIZE_SELLING_LOG; i++)
            if (strcasecmp(logLocacao[i].devolucao, "EOF") == 0)
                return i;
    if (inp == 2)
        for (int i = 0; i < X__SIZE_VEHICLES; i++)
            if (strcasecmp(veiculo[i].hardware.modelo, "EOF") == 0)
                return i;
    return -1;
}

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
    int i = fimDeArquivoGlobal(0);
    cliente[i] = p;
    strcpy(cliente[i + 1].nome, "EOF");
    printf("\n Cliente %s incluido.", p.codigo);
}

void devolucao(char inicio[11], char duracao[4], char fim[11])
{
    // Inicializando ano em int
    int temp[3] = {(inicio[6] - '0') * 1000 + (inicio[7] - '0') * 100 + (inicio[8] - '0') * 10 + (inicio[9] - '0'),
                   (inicio[3] - '0') * 10 + (inicio[4] - '0'), (inicio[0] - '0') * 10 + (inicio[1] - '0')},
        duracaoint = 0;
    struct tm t = {.tm_year = temp[0] - 1900, .tm_mon = temp[1] - 1, .tm_mday = temp[2]};
    // Mudar data
    duracaoint = atoi(duracao);
    t.tm_mday += duracaoint;
    mktime(&t);
    // Escrever nova data formatada em string
    strftime(fim, 11, "%d/%m/%Y", &t);
}

void calculaPreco(char veic[SIZE__CODE_ALL], char tofseguro[2], char fullduracao[4], char price[7])
{
    int inew, iend = -1, diariaint, fullduracaoint;
    for (int inew = 0; inew < X__SIZE_VEHICLES && strcmp(veiculo[inew].descricao, "EOF") != 0; inew++)
        if (strcasecmp(veic, veiculo[inew].codigo) == 0)
        {
            iend = inew;
            inew = X__SIZE_SELLING_LOG;
        }
    veiculo[iend].diaria;
    diariaint = atoi(veiculo[iend].diaria);
    fullduracaoint = atoi(fullduracao);
    diariaint = diariaint * fullduracaoint;
    if (tofseguro[0] == 's')
        diariaint = diariaint + 50;
    itoa(diariaint, price, 7);
}

void addLog()
{
    // Criar tipo a ser preenchido
    tLog p;
    system("cls");
    // Preencher novo item
    printf("\n******* Incluir locacao *******");
    int verificadorDeVeiculo = 0;
    while (verificadorDeVeiculo == 0)
    {
        printf("\n Digite o codigo do veiculo: ");
        scanf("%s", &p.codigo.veiculo);
        if (strcmp(veiculo[pesquisarPorCodigoVeiculo(p.codigo.veiculo)].status, "Livre") == 0)
        {
            verificadorDeVeiculo = 1;
            strcpy(veiculo[pesquisarPorCodigoVeiculo(p.codigo.veiculo)].status, "Em uso");
        }
        else
            printf(" O veiculo nao esta livre para locacao.\n");
    }
    printf(" O veiculo esta livre para locacao.\n");
    strcpy(p.devolucaotof, "N");
    printf("\n\nDigite a data de retirada (DD/MM/AAAA): ");
    scanf(" %[^\n]", &p.retirada);
    printf(" Digite quantos dias que o cliente deseja alugar: ");
    scanf(" %[^\n]", &p.dias);
    devolucao(p.retirada, p.dias, p.devolucao);
    printf(" Ele sera devolvido no dia: %s", p.devolucao);
    geradorDeCodigoGlobal(p.codigo.locacao, 1);
    printf("\n Codigo: %s", p.codigo);
    printf("\n O seguro esta incluido? (s/n): ");
    scanf(" %[^\n]", &p.seguro);
    printf(" Codigo do veiculo: ");
    scanf("%s", &p.codigo.veiculo);
    calculaPreco(p.codigo.veiculo, p.seguro, p.dias, p.preco);
    printf(" O cliente pagara: %s", p.preco);
    printf("\n Codigo do cliente: ");
    scanf(" %[^\n]", &p.codigo.cliente);
    int i = fimDeArquivoGlobal(1);
    logLocacao[i] = p;
    strcpy(logLocacao[i + 1].devolucao, "EOF");
    printf("\n Locacao %s incluida.", p.codigo.locacao);
}

void fimLog()
{
    // Registra devolução
    system("cls");
    printf("\n******* Finalizar locacao *******");
    // Buscar log
    int logPointer, tof1 = 0;
    while (tof1 == 0)
    {
        logPointer = pesquisarPorCodigoGlobal(1);
        if (stcmp(logLocacao[logPointer].retirada, "S") != 0)
            printf("\n Esta devolucao ja ocorreu");
        else
            tof1 = 1;
    }
    printLog(logLocacao[logPointer]);
    printf("\n\n A data da entrega coincide com o esperado? (s/n)");
    char tof;
    scanf(" %c", &tof);
    if (tof == 'n')
    {
        printf(" Digite quantos dias que o cliente alugou: ");
        scanf(" %[^\n]", &logLocacao[logPointer].dias);
        calculaPreco(logLocacao[logPointer].codigo.veiculo, logLocacao[logPointer].seguro, logLocacao[logPointer].dias, logLocacao[logPointer].preco);
    }
    printf(" Por favor, cobre %s reais do cliente", logLocacao[logPointer].preco);
    system("pause");
    strcpy(logLocacao[logPointer].devolucaotof, "S");
    printf("\n Devolucao concluida");
}

void addVeiculo()
{
    // Criar tipo a ser preenchido
    tVeiculo p;
    system("cls");
    // Preencher novo item
    printf("\n******* Incluir veiculo *******\n");
    printf("\n\nDigite o modelo: ");
    scanf(" %[^\n]", &p.hardware.modelo);
    printf(" Cor: ");
    scanf(" %[^\n]", &p.hardware.cor);
    // Preencher codigo com funcao
    geradorDeCodigoGlobal(p.codigo, 2);
    printf(" Codigo: %s", p.codigo);
    strcpy(p.status, "Livre");
    printf("\n Ocupacao: ");
    scanf(" %[^\n]", &p.hardware.ocupacao);
    printf(" Placa: ");
    scanf("%s", &p.hardware.placa);
    printf(" Valor da diaria: ");
    scanf(" %[^\n]", &p.diaria);
    printf(" Sua descricao: ");
    scanf(" %[^\n]", &p.descricao);
    int i = fimDeArquivoGlobal(2);
    veiculo[i] = p;
    strcpy(veiculo[i + 1].descricao, "EOF");
    printf("\n Veiculo %s incluido.", p.codigo);
}

int printarContar(char cod[])
{
    int tot = 0;
    for (int c = 0; strcmp("EOF", logLocacao[c].devolucao) != 0; c++)
        if (strcmp(logLocacao[c].codigo.cliente, cod) == 0)
        {
            printLog(logLocacao[c]);
            tot++;
        }
}

void fidelidade()
{
    printf("\n******* Programa de fidelidade *******\n");
    char code[SIZE__CODE_ALL];
    printf("\n Informe o codigo do cliente:");
    scanf("%s", &code);
    int total = printarContar(code);
    printf("\n No total, o cliente realizou %d alugueis", total);
}

void carregaDadosDosArquivos()
{
    FILE *pLerCliente = fopen("CLENTES.csv", "r"), *pLerLogLocacao = fopen("LOCACAO.csv", "r"), *pLerVeiculo = fopen("VEICULO.csv", "r");
    tCliente client;
    tVeiculo vehicle;
    tLog registro;
    char leitura[150], escrita[150];
    int outputFscanf, i = 0;

    if (pLerCliente != NULL)
    {
        outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &leitura, &escrita);
        while (outputFscanf != EOF)
        {
            // Le o inicio de um registro
            if (strcasecmp(leitura, "INICIO") == 0)
            {
                strcpy(client.nome, "");
                strcpy(client.codigo, "");
                strcpy(client.telefone, "");
            }
            // Le nome
            else if (strcasecmp(leitura, "**Nome") == 0)
                strcpy(client.nome, escrita);
            // Telefone
            else if (strcasecmp(leitura, "**Telefone") == 0)
                strcpy(client.telefone, escrita);
            else if (strcasecmp(leitura, "**Codigo") == 0)
                strcpy(client.codigo, escrita);
            else if (strcasecmp(leitura, "**Rua") == 0)
                strcpy(client.endereco.rua, escrita);
            else if (strcasecmp(leitura, "**Nro") == 0)
                strcpy(client.endereco.numero, escrita);
            else if (strcasecmp(leitura, "**Comp") == 0)
                strcpy(client.endereco.complemento, escrita);
            else if (strcasecmp(leitura, "**Bairro") == 0)
                strcpy(client.endereco.bairro, escrita);
            else if (strcasecmp(leitura, "**Cidade") == 0)
                strcpy(client.endereco.cidade, escrita);
            else if (strcasecmp(leitura, "**Estado") == 0)
                strcpy(client.endereco.estado, escrita);
            else if (strcasecmp(leitura, "**Cep") == 0)
                strcpy(client.endereco.cep, escrita);

            // Le fim
            else if (strcasecmp(leitura, "FIM") == 0)
            {
                cliente[i] = client;
                i++; // i++ para mudar de registro
            }
            outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &leitura, &escrita);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(cliente[i].nome, "EOF");
        fclose(pLerCliente);
    }

    if (pLerLogLocacao != NULL)
    {
        outputFscanf = fscanf(pLerLogLocacao, "%s %[^\n]", &leitura, &escrita);
        while (outputFscanf != EOF)
        {
            // Le o inicio de um registro
            if (strcasecmp(leitura, "INICIO") == 0)
            {
                strcpy(registro.devolucao, "");
                strcpy(registro.seguro, "");
                strcpy(registro.dias, "");
            }
            // Le Devolucao
            else if (strcasecmp(leitura, "**Devolucao") == 0)
                strcpy(registro.devolucao, escrita);
            else if (strcasecmp(leitura, "**Seguro") == 0)
                strcpy(registro.seguro, escrita);
            else if (strcasecmp(leitura, "**Dias") == 0)
                strcpy(registro.dias, escrita);
            else if (strcasecmp(leitura, "**Retirada") == 0)
                strcpy(registro.retirada, escrita);
            else if (strcasecmp(leitura, "**Devolvido") == 0)
                strcpy(registro.devolucaotof, escrita);
            else if (strcasecmp(leitura, "**Codigo") == 0)
                strcpy(registro.codigo.locacao, escrita);
            else if (strcasecmp(leitura, "**Cliente") == 0)
                strcpy(registro.codigo.cliente, escrita);
            else if (strcasecmp(leitura, "**Veiculo") == 0)
                strcpy(registro.codigo.veiculo, escrita);
            else if (strcasecmp(leitura, "**Preco") == 0)
                strcpy(registro.preco, escrita);

            // Le fim
            else if (strcasecmp(leitura, "FIM") == 0)
            {
                logLocacao[i] = registro;
                i++; // i++ para mudar de registro
            }
            outputFscanf = fscanf(pLerLogLocacao, "%s %[^\n]", &leitura, &escrita);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(logLocacao[i].devolucao, "EOF");
        fclose(pLerLogLocacao);
    }

    if (pLerVeiculo != NULL)
    {
        outputFscanf = fscanf(pLerVeiculo, "%s %[^\n]", &leitura, &escrita);
        while (outputFscanf != EOF)
        {
            // Le o inicio de um registro
            if (strcasecmp(leitura, "INICIO") == 0)
            {
                strcpy(vehicle.descricao, "");
                strcpy(vehicle.codigo, "");
                strcpy(vehicle.status, "");
            }
            // Le descricao
            else if (strcasecmp(leitura, "**Descricao") == 0)
                strcpy(vehicle.descricao, escrita);
            else if (strcasecmp(leitura, "**Codigo") == 0)
                strcpy(vehicle.codigo, escrita);
            else if (strcasecmp(leitura, "**Status") == 0)
                strcpy(vehicle.status, escrita);
            else if (strcasecmp(leitura, "**Diaria") == 0)
                strcpy(vehicle.diaria, escrita);
            else if (strcasecmp(leitura, "**Placa") == 0)
                strcpy(vehicle.hardware.placa, escrita);
            else if (strcasecmp(leitura, "**Modelo") == 0)
                strcpy(vehicle.hardware.modelo, escrita);
            else if (strcasecmp(leitura, "**Ocupacao") == 0)
                strcpy(vehicle.hardware.ocupacao, escrita);
            else if (strcasecmp(leitura, "**Cor") == 0)
                strcpy(vehicle.hardware.cor, escrita);

            // Le fim
            else if (strcasecmp(leitura, "FIM") == 0)
            {
                veiculo[i] = vehicle;
                i++; // i++ para mudar de registro
            }
            outputFscanf = fscanf(pLerVeiculo, "%s %[^\n]", &leitura, &escrita);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(veiculo[i].descricao, "EOF");
        fclose(pLerVeiculo);
    }
}

void escreverVetor()
{
    FILE *pSalvarClientes = fopen("CLENTES.csv", "w");
    if (pSalvarClientes != NULL)
    {
        for (int wCounter = 0; strcmp("EOF", cliente[wCounter].nome) != 0; wCounter++)
        {
            printf("\n %d %s", wCounter, cliente[wCounter].nome);
            fprintf(pSalvarClientes, "INICIO\n");
            fprintf(pSalvarClientes, "**Nome %s\n", cliente[wCounter].nome);
            fprintf(pSalvarClientes, "**Codigo %s\n", cliente[wCounter].codigo);
            fprintf(pSalvarClientes, "**Telefone %s\n", cliente[wCounter].telefone);
            fprintf(pSalvarClientes, "**Rua %s\n", cliente[wCounter].endereco.rua);
            fprintf(pSalvarClientes, "**Nro %s\n", cliente[wCounter].endereco.numero);
            fprintf(pSalvarClientes, "**Comp %s\n", cliente[wCounter].endereco.complemento);
            fprintf(pSalvarClientes, "**Bairro %s\n", cliente[wCounter].endereco.bairro);
            fprintf(pSalvarClientes, "**Cidade %s\n", cliente[wCounter].endereco.cidade);
            fprintf(pSalvarClientes, "**Estado %s\n", cliente[wCounter].endereco.estado);
            fprintf(pSalvarClientes, "**Cep %s\n", cliente[wCounter].endereco.cep);
            fprintf(pSalvarClientes, "FIM\n");
        }
        fclose(pSalvarClientes);
    }
    FILE *pSalvarLogLocacao = fopen("LOCACAO.csv", "w");

    if (pSalvarLogLocacao != NULL)
    {
        for (int wCounter = 0; strcmp("EOF", logLocacao[wCounter].devolucao) != 0; wCounter++)
        {
            printf("\n %d %s", wCounter, logLocacao[wCounter].devolucao);
            fprintf(pSalvarLogLocacao, "INICIO\n");
            fprintf(pSalvarLogLocacao, "**Devolucao %s\n", logLocacao[wCounter].devolucao);
            fprintf(pSalvarLogLocacao, "**Seguro %s\n", logLocacao[wCounter].seguro);
            fprintf(pSalvarLogLocacao, "**Dias %s\n", logLocacao[wCounter].dias);
            fprintf(pSalvarLogLocacao, "**Retirada %s\n", logLocacao[wCounter].retirada);
            fprintf(pSalvarLogLocacao, "**Devolvido %s\n", logLocacao[wCounter].devolucaotof);
            fprintf(pSalvarLogLocacao, "**Codigo %s\n", logLocacao[wCounter].codigo.locacao);
            fprintf(pSalvarLogLocacao, "**Cliente %s\n", logLocacao[wCounter].codigo.cliente);
            fprintf(pSalvarLogLocacao, "**Veiculo %s\n", logLocacao[wCounter].codigo.veiculo);
            fprintf(pSalvarLogLocacao, "**Preco %s\n", logLocacao[wCounter].preco);
            fprintf(pSalvarLogLocacao, "FIM\n");
        }
        fclose(pSalvarLogLocacao);
    }
    FILE *pSalvarVeiculos = fopen("VEICULO.csv", "w");

    if (pSalvarVeiculos != NULL)
    {
        for (int wCounter = 0; strcmp("EOF", veiculo[wCounter].descricao) != 0; wCounter++)
        {
            printf("\n %d %s", wCounter, veiculo[wCounter].descricao);
            fprintf(pSalvarVeiculos, "INICIO\n");
            fprintf(pSalvarVeiculos, "**Descricao %s\n", veiculo[wCounter].descricao);
            fprintf(pSalvarVeiculos, "**Codigo %s\n", veiculo[wCounter].codigo);
            fprintf(pSalvarVeiculos, "**Status %s\n", veiculo[wCounter].status);
            fprintf(pSalvarVeiculos, "**Diaria %s\n", veiculo[wCounter].diaria);
            fprintf(pSalvarVeiculos, "**Placa %s\n", veiculo[wCounter].hardware.placa);
            fprintf(pSalvarVeiculos, "**Modelo %s\n", veiculo[wCounter].hardware.modelo);
            fprintf(pSalvarVeiculos, "**Ocupacao %s\n", veiculo[wCounter].hardware.ocupacao);
            fprintf(pSalvarVeiculos, "**Cor %s\n", veiculo[wCounter].hardware.cor);
            fprintf(pSalvarVeiculos, "FIM\n");
        }
        fclose(pSalvarVeiculos);
    }
}

main()
{
    srand((unsigned int)(time(NULL)));
    carregaDadosDosArquivos();
    int opcao = 0;
    while (opcao != 9)
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
        scanf(" %i", &opcao);
        if (opcao >= 1 && opcao <= 10)
        {
            switchComandosInterface(opcao);
            printf("\n\n");
            system("pause");
        }
    }
    escreverVetor();
}

/******************************** INFO IMPORTANTE *************************************

cliente[k].nome sempre recebera "EOF" ao final do arquivo e vetor cliente
logLocacao[k].devolucao sempre recebera "EOF" ao final do arquivo e vetor loglocacao
veiculo[k].descricao sempre recebera "EOF" ao final do arquivo e vetor veiculo

***************************************************************************************/
