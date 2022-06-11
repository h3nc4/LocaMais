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


/******************************** INFO IMPORTANTE *************************************

    cliente[k].nome sempre recebera EOF ao final do arquivo e vetor cliente
    logLocacao[k].devolucao sempre recebera EOF ao final do arquivo e vetor loglocacao
    veiculo[k].descricao sempre recebera EOF ao final do arquivo e vetor veiculo

***************************************************************************************/


/* Possiveis arquivos a serem usados
FILE *pLerCliente = fopen("CLENTES.csv", "r"),
     *pSalvarClientes = fopen("CLENTES.csv", "w"),
     *pLerLogLocacao = fopen("LOCACAO.csv", "r"),
     *pSalvarLogLocacao = fopen("LOCACAO.csv", "w"),
     *pLerVeiculo = fopen("VEICULO.csv", "r"),
     *pSalvarVeiculos = fopen("VEICULO.csv", "w");

    fclose(pLerCliente);
    fclose(pAdicionarCliente);
    fclose(pLogLocacao);
    fclose(pLerVeiculo);
    fclose(pAdicionarVeiculo);
    fclose(pSalvarVeiculos);

*/

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
    char retirada[11];
    char devolucao[11];
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
    char status[2];
};
typedef struct sVeiculo tVeiculo;
tVeiculo veiculo[X__SIZE_VEHICLES];

void switchComandosInterface(int p)
{
    fflush(stdin);
    if (p == 1)
        addCliente();
    else if (p == 2)
        printCliente(cliente[pesquisarPorCodigoCliente()]);
}

int pesquisarPorCodigoCliente()
{
    char code[21];
    printf("\n Busque o codigo:");
    gets(code);
    for (int i = 0; i < X__SIZE_CLIENT && strcmp(cliente[i].nome, "EOF") != 0; i++)
        if (strcasecmp(code, cliente[i].codigo) == 0)
            return i;
    return -1;
}

int fimDeArquivoGlobal(int inp)
{
    if (inp == 0)
        for (int i = 0; i < X__SIZE_CLIENT; i++)
            if (strcasecmp(cliente[i].nome, "EOF") == 0)
                return i;
    if (inp == 1)
        for (int i = 0; i < X__SIZE_SELLING_LOG; i++)
            if (strcasecmp(logLocacao[i].retirada, "EOF") == 0)
                return i;
    if (inp == 2)
        for (int i = 0; i < X__SIZE_VEHICLES; i++)
            if (strcasecmp(veiculo[i].hardware.modelo, "EOF") == 0)
                return i;
    return -1;
}

void geradorDeCodigoGlobal(char codGerado[], int in)
{
    time_t now = time('\0');
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
    codGerado[20] = '\0';
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

devolucao(char inicio[11], char duracao[4], char fim[11])
{
    // Inicializando ano em int
    int temp[3] = {(inicio[6] - '0') * 1000 + (inicio[7] - '0') * 100 + (inicio[8] - '0') * 10 + (inicio[9] - '0'),
     (inicio[3] - '0') * 10 + (inicio[4] - '0'), (inicio[0] - '0') * 10 + (inicio[1] - '0')};
    struct tm t = {.tm_year = temp[0] - 1900, .tm_mon = temp[1]-1, .tm_mday = temp[2]};
    // Mudar data
    t.tm_mday += 70;
    mktime(&t);
    // Escrever nova data formatada em string
    strftime(fim, 11, "%d/%m/%Y", &t);
}

addLog()
{
    // Criar tipo a ser preenchido
    tLog p;
    system("cls");
    // Preencher novo item
    printf("\n******* Incluir veiculo *******\n");
    printf("\n\nDigite a data de retirada (DD/MM/AAAA): ");
    scanf(" %[^\n]", &p.retirada);
    printf(" Digite os dias: ");
    scanf(" %[^\n]", &p.dias);
    devolucao(p.retirada, p.dias, p.devolucao);
    printf("\n Ele sera devolvido no dia: %s", p.devolucao);
    geradorDeCodigoGlobal(p.codigo.locacao, 1);
    printf("\n Codigo:%s", p.codigo);
    printf("\n O seguro esta incluido? (s/n): ");
    scanf(" %[^\n]", &p.seguro);
    printf(" Codigo do veiculo: ");
    scanf("%s", &p.codigo.veiculo);
    printf(" Codigo do cliente: ");
    scanf(" %[^\n]", &p.codigo.cliente);
    int i = fimDeArquivoGlobal(1);
    logLocacao[i] = p;
    strcpy(logLocacao[i + 1].retirada, "EOF");
    printf("\n Locacao %s incluida.", p.codigo.locacao);
}

addVeiculo()
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
    printf(" Codigo:%s", p.codigo);
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
    strcpy(veiculo[i + 1].hardware.modelo, "EOF");
    printf("\n Veiculo %s incluido.", p.codigo);
}

void printCliente(tCliente p)
{
    printf("\n ***** Cliente *****");
    printf("\n Nome:%s", p.nome);
    printf("\n Tel:%s", p.telefone);
    printf("\n Codigo:%s", p.codigo);
    printf("\n Endereco:");
    printf("\n Rua %s, %s, %s", p.endereco.rua, p.endereco.numero, p.endereco.complemento);
    printf("\n %s, %s, %s", p.endereco.cidade, p.endereco.estado, p.endereco.cep);
    printf("\n");
}

void carregaDadosDosArquivos()
{
    FILE *pLerCliente = fopen("CLENTES.csv", "r"),*pLerLogLocacao = fopen("LOCACAO.csv", "r"),*pLerVeiculo = fopen("VEICULO.csv", "r");
    tCliente client;
    tVeiculo vehicle;
    tLog registro;
    char leitura[150], escrita[150];
    int outputFscanf, i = 0;
    if (pLerCliente != '\0')
    {
        outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &leitura, &escrita);
        while (outputFscanf != "EOF")
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
                i++;// i++ para mudar de registro
            }
            outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &leitura, &escrita);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(cliente[i].nome, "EOF");
        fclose(pLerCliente);
    }
    if (pLerLogLocacao != '\0')
    {
        outputFscanf = fscanf(pLerLogLocacao, "%s %[^\n]", &leitura, &escrita);
        while (outputFscanf != "EOF")
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



                // Le fim
            else if (strcasecmp(leitura, "FIM") == 0)
            {
                logLocacao[i] = registro;
                i++;// i++ para mudar de registro
            }
            outputFscanf = fscanf(pLerLogLocacao, "%s %[^\n]", &leitura, &escrita);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(logLocacao[i].devolucao, "EOF");
        fclose(pLerLogLocacao);
    }
    if (pLerCliente != '\0')
    {
        outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &leitura, &escrita);
        while (outputFscanf != "EOF")
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





                // Le fim
            else if (strcasecmp(leitura, "FIM") == 0)
            {
                veiculo[i] = vehicle;
                i++;// i++ para mudar de registro
            }
            outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &leitura, &escrita);
        }
        // Ao final, escreve o fim do arquivo
        strcpy(veiculo[i].descricao, "EOF");
        fclose(pLerCliente);
    }
}

void escreverVetor()
{
    FILE *pSalvarClientes = fopen("CLENTES.csv", "w");
    if (pSalvarClientes != '\0')
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

    if (pSalvarLogLocacao != '\0')
    {
        for (int wCounter = 0; strcmp("EOF", logLocacao[wCounter].devolucao) != 0; wCounter++)
        {
            printf("\n %d %s", wCounter, logLocacao[wCounter].devolucao);
            fprintf(pSalvarLogLocacao, "INICIO\n");
            fprintf(pSalvarLogLocacao, "**Devolucao %s\n", logLocacao[wCounter].devolucao);
            fprintf(pSalvarLogLocacao, "**Seguro %s\n", logLocacao[wCounter].seguro);
            fprintf(pSalvarLogLocacao, "**Dias %s\n", logLocacao[wCounter].dias);
            fprintf(pSalvarLogLocacao, "**Retirada %s\n", logLocacao[wCounter].retirada);
            fprintf(pSalvarLogLocacao, "**Codigo %s\n", logLocacao[wCounter].codigo.locacao);
            fprintf(pSalvarLogLocacao, "**Cliente %s\n", logLocacao[wCounter].codigo.cliente);
            fprintf(pSalvarLogLocacao, "**Veiculo %s\n", logLocacao[wCounter].codigo.veiculo);
            fprintf(pSalvarLogLocacao, "FIM\n");
        }
        fclose(pSalvarLogLocacao);
    }
    FILE *pSalvarVeiculos = fopen("VEICULO.csv", "w");

    if (pSalvarVeiculos != '\0')
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
    srand((unsigned int)(time('\0')));
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
        printf("\n 9.Encerrar ");
        printf("\n\n Digite sua opcao : ");
        scanf(" %i", &opcao);
        if (opcao >= 1 && opcao <= 9)
        {
            switchComandosInterface(opcao);
            printf("\n\n");
            system("pause");
        }
    }
    escreverVetor();
}
