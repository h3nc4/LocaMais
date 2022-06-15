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

// Contador global
int i;

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

int pesquisarPorCodigoGlobal(int inpt)
{
    char code[SIZE__CODE_ALL];
    printf("\n Busque o codigo:");
    gets(code);
    while (i>=0)
    {
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
    printf("\n Codigo nao encontrado!");
    }
}

int pesquisarPorCodigoVeiculo(char code[])
{
    for (i = 0; i < X__SIZE_VEHICLES && strcmp(veiculo[i].descricao, "EOF") != 0; i++)
        if (strcasecmp(code, veiculo[i].codigo) == 0)
            return i;
    return -1;
}

void printTudo()
{
    printf("\n 1.Clientes\n 2.Logs\n 3.Veiculos\n Selecione o registro: ");
    int choice = 0;
    scanf("%d", &choice);
    system("cls");
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
    printf("\n Codigo: %s", q.codigo);
    printf("\n Cor: %s, Ocupacao: %s", q.hardware.cor, q.hardware.ocupacao);
    printf("\n Diaria: %s, Placa: %s", q.diaria, q.hardware.placa);
    printf("\n Status: %s", q.status);
    printf("\n");
}

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
    i = fimDeArquivoGlobal(0);
    cliente[i] = p;
    strcpy(cliente[i + 1].nome, "EOF");
    printf("\n Cliente %s incluido.", p.codigo);
}

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

void addLog()
{
    // Criar tipo a ser preenchido
    tLog p;
    system("cls");
    // Preencher novo item
    printf("\n******* Incluir locacao *******");
    int verificadorDeVeiculo = 0,
        ponteiro = 0;
    while (verificadorDeVeiculo == 0)
    {
        printf("\n Digite o codigo do veiculo: ");
        scanf("%s", &p.codigo.veiculo);
        ponteiro = pesquisarPorCodigoVeiculo(p.codigo.veiculo);
        if (strcmp(veiculo[ponteiro].status, "Livre") == 0)
        {
            verificadorDeVeiculo = 1;
            strcpy(veiculo[ponteiro].status, "Em uso");
        }
        else
            printf(" O veiculo nao esta livre para locacao.\n");
    }
    printf("\n veiculo n %d\n", ponteiro);
    printf(" O veiculo esta livre para locacao.\n");
    strcpy(p.devolucaotof, "N");
    printf(" Digite a data de retirada (DD/MM/AAAA): ");
    scanf(" %[^\n]", &p.retirada);
    printf(" Digite quantos dias que o cliente deseja alugar: ");
    scanf(" %[^\n]", &p.dias);
    devolucao(p.retirada, p.dias, p.devolucao);
    printf(" Ele sera devolvido no dia: %s", p.devolucao);
    geradorDeCodigoGlobal(p.codigo.locacao, 1);
    printf("\n Codigo: %s", p.codigo);
    printf("\n O seguro esta incluido? (s/n): ");
    scanf(" %[^\n]", &p.seguro);
    calculaPreco(ponteiro, p.seguro, p.dias, p.preco);
    printf(" O cliente pagara: %s", p.preco);
    printf("\n Codigo do cliente: ");
    scanf(" %[^\n]", &p.codigo.cliente);
    i = fimDeArquivoGlobal(1);
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
        if (strcmp(logLocacao[logPointer].retirada, "S") != 0)
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
        calculaPreco(logPointer, logLocacao[logPointer].seguro, logLocacao[logPointer].dias, logLocacao[logPointer].preco);
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
    i = 0;
    for (int c = 0; strcmp("EOF", logLocacao[c].devolucao) != 0; c++)
        if (strcmp(logLocacao[c].codigo.cliente, cod) == 0)
        {
            printLog(logLocacao[c]);
            i++;
        }
    return i;
}

void fidelidade()
{
    printf("\n******* Programa de fidelidade *******\n");
    char code[SIZE__CODE_ALL];
    printf("\n Informe o codigo do cliente:");
    scanf("%s", &code);
    int total = printarContar(code) * 10;
    printf("\n Este cliente tem %d pontos", total);
}

void carregaDadosDosArquivos()
{
    FILE *pLerCliente = fopen("CLENTES.csv", "r"),
         *pLerLogLocacao = fopen("LOCACAO.csv", "r"),
         *pLerVeiculo = fopen("VEICULO.csv", "r");
    tCliente client;
    tVeiculo vehicle;
    tLog registro;
    char type[150],
        value[150];
    int outScan;
    i = 0;
    if (pLerCliente != NULL)
    {
        outScan = fscanf(pLerCliente, "%s %[^\n]", &type, &value);
        while (outScan != EOF)
        {
            // Le o inicio de um registro
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(client.nome, "");
                strcpy(client.codigo, "");
                strcpy(client.telefone, "");
            }
            // Le nome
            else if (strcasecmp(type, "Nome") == 0)
                strcpy(client.nome, value);
            // Telefone
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

            // Le fim
            else if (strcasecmp(type, "FIM") == 0)
            {
                cliente[i] = client;
                i++; // i++ para mudar de registro
            }
            outScan = fscanf(pLerCliente, "%s %[^\n]", &type, &value);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(cliente[i].nome, "EOF");
        fclose(pLerCliente);
    }

    if (pLerLogLocacao != NULL)
    {
        i = 0;
        outScan = fscanf(pLerLogLocacao, "%s %[^\n]", &type, &value);
        while (outScan != EOF)
        {
            // Le o inicio de um registro
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(registro.devolucao, "");
                strcpy(registro.seguro, "");
                strcpy(registro.dias, "");
            }
            // Le Devolucao
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

            // Le fim
            else if (strcasecmp(type, "FIM") == 0)
            {
                logLocacao[i] = registro;
                i++; // i++ para mudar de registro
            }
            outScan = fscanf(pLerLogLocacao, "%s %[^\n]", &type, &value);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(logLocacao[i].devolucao, "EOF");
        fclose(pLerLogLocacao);
    }

    if (pLerVeiculo != NULL)
    {
        i = 0;
        outScan = fscanf(pLerVeiculo, "%s %[^\n]", &type, &value);
        while (outScan != EOF)
        {
            // Le o inicio de um registro
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(vehicle.descricao, "");
                strcpy(vehicle.codigo, "");
                strcpy(vehicle.status, "");
            }
            // Le descricao
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

            // Le fim
            else if (strcasecmp(type, "FIM") == 0)
            {
                veiculo[i] = vehicle;
                i++; // i++ para mudar de registro
            }
            outScan = fscanf(pLerVeiculo, "%s %[^\n]", &type, &value);
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
    FILE *pSalvarLogLocacao = fopen("LOCACAO.csv", "w");

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

main()
{
    srand((unsigned int)(time(0)));
    carregaDadosDosArquivos();
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
            switchComandosInterface(opcao);
            printf("\n\n");
            system("pause");
        }
    }
    printf("\n exeescreve");
    escreverVetor();
}

/******************************** INFO IMPORTANTE *************************************

cliente[k].nome sempre recebera "EOF" ao final do arquivo e vetor cliente
logLocacao[k].devolucao sempre recebera "EOF" ao final do arquivo e vetor loglocacao
veiculo[k].descricao sempre recebera "EOF" ao final do arquivo e vetor veiculo

***************************************************************************************/
