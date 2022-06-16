#include <dos.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X__SIZE_CLIENT 1000
#define X__SIZE_VEHICLES 1000
#define X__SIZE_SELLING_LOG 1000
#define SIZE__CODE_ALL 21
int i;
struct sEndereco
{
    char bairro[50], rua[100], numero[10], complemento[10], cep[15], cidade[50], estado[3];
};
typedef struct sEndereco tEndereco;
struct sCliente
{
    tEndereco endereco;
    char nome[50], codigo[SIZE__CODE_ALL], telefone[15];
};
typedef struct sCliente tCliente;
tCliente cliente[X__SIZE_CLIENT];
struct sCodigo
{
    char locacao[SIZE__CODE_ALL], cliente[SIZE__CODE_ALL], veiculo[SIZE__CODE_ALL];
};
typedef struct sCodigo tCodigo;
struct sLog
{
    tCodigo codigo;
    char preco[7], retirada[11], devolucao[11], devolucaotof[2], seguro[2], dias[4];
};
typedef struct sLog tLog;
tLog logLocacao[X__SIZE_SELLING_LOG];
struct sHardware
{
    char modelo[31], cor[13], placa[9], ocupacao[5];
};
typedef struct sHardware tHardware;
struct sVeiculo
{
    tHardware hardware;
    char diaria[7], codigo[SIZE__CODE_ALL], descricao[15], status[10];
};
typedef struct sVeiculo tVeiculo;
tVeiculo veiculo[X__SIZE_VEHICLES];
int pesquisarPorCodigoGlobal(int inpt)
{
    char code[SIZE__CODE_ALL], keep = 's';
    while (keep == 's')
    {
        printf("\n Busque o codigo:");
        gets(code);
        fflush(stdin);
        if (inpt == 0)
            for (i = 0; i < X__SIZE_CLIENT && strcmp(cliente[i].nome, "EOF") != 0; i++)
                if (strcasecmp(code, cliente[i].codigo) == 0)
                    return i;
        if (inpt == 1)
            for (i = 0; i < X__SIZE_SELLING_LOG && strcmp(logLocacao[i].devolucao, "EOF") != 0; i++)
                if (strcasecmp(code, logLocacao[i].codigo.locacao) == 0)
                    return i;
        if (inpt == 2)
            for (i = 0; i < X__SIZE_VEHICLES && strcmp(veiculo[i].descricao, "EOF") != 0; i++)
                if (strcasecmp(code, veiculo[i].codigo) == 0)
                    return i;
        printf("\n Codigo nao encontrado! Deseja buscar novamente? (s/n)");
        scanf(" %c", &keep);
        fflush(stdin);
    }
    return -1;
}
int pesquisarPorCodigoVeiculo(char code[])
{
    for (i = 0; i < X__SIZE_VEHICLES && strcmp(veiculo[i].descricao, "EOF") != 0; i++)
        if (strcasecmp(code, veiculo[i].codigo) == 0)
            return i;
    return -1;
}
void printCliente(tCliente p)
{
    printf("\n ******************** Cliente ********************");
    printf("\n\n Nome: %s", p.nome);
    printf("\n Tel: %s", p.telefone);
    printf("\n Codigo: %s", p.codigo);
    printf("\n Endereco:");
    printf("\n Rua %s, %s, %s", p.endereco.rua, p.endereco.numero, p.endereco.complemento);
    printf("\n %s, %s, %s", p.endereco.cidade, p.endereco.estado, p.endereco.cep);
    printf("\n");
}
void printVeiculo(tVeiculo q)
{
    printf("\n ***************** Veiculo *****************");
    printf("\n\n Modelo: %s", q.hardware.modelo);
    printf("\n Descricao: %s", q.descricao);
    printf("\n Codigo: %s", q.codigo);
    printf("\n Cor: %s, Ocupacao: %s", q.hardware.cor, q.hardware.ocupacao);
    printf("\n Diaria: %s, Placa: %s", q.diaria, q.hardware.placa);
    printf("\n Status: %s", q.status);
    printf("\n");
}
void printLog(tLog r)
{
    printf("\n ************* Log de vendas *************");
    printf("\n\n Codigo: %s", r.codigo.locacao);
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
void printTudo()
{
    int choice;
    printf("\n 1.Clientes\n 2.Logs\n 3.Veiculos\n Selecione o registro: ");
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
int fimDeVetorGlobal(int inp)
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
    char num[] = "0123456789";
    if (in == 0)
        codGerado[0] = num[rand() % 4];
    else if (in == 1)
        codGerado[0] = num[(rand() % 4) + 4];
    else if (in == 2)
        codGerado[0] = num[(rand() % 2) + 8];
    for (int i = 1; i < 5; i++)
        codGerado[i] = num[rand() % 10];
    codGerado[5] = '/';
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
    tCliente p;
    system("cls");
    printf("\n************** Incluir cliente **************\n");
    printf("\n\n Digite o nome: ");
    scanf(" %[^\n]", &p.nome);
    printf(" Cel: ");
    scanf(" %[^\n]", &p.telefone);
    printf(" Rua: ");
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
    geradorDeCodigoGlobal(p.codigo, 0);
    printf(" Codigo:%s", p.codigo);
    i = fimDeVetorGlobal(0);
    cliente[i] = p;
    strcpy(cliente[i + 1].nome, "EOF");
    printf("\n Cliente %s incluido.", p.codigo);
}
void devolucao(char inicio[11], char duracao[4], char fim[11])
{
    int temp[3] = {(inicio[6] - '0') * 1000 + (inicio[7] - '0') * 100 + (inicio[8] - '0') * 10 + (inicio[9] - '0'), (inicio[3] - '0') * 10 + (inicio[4] - '0'), (inicio[0] - '0') * 10 + (inicio[1] - '0')}, duracaoint;
    struct tm t = {.tm_year = temp[0] - 1900, .tm_mon = temp[1] - 1, .tm_mday = temp[2]};
    duracaoint = atoi(duracao);
    t.tm_mday += duracaoint;
    mktime(&t);
    strftime(fim, 11, "%d/%m/%Y", &t);
}
void calculaPreco(int point, char tofseguro[2], char fullduracao[4], char price[7])
{
    int diariaint, fullduracaoint;
    diariaint = atoi(veiculo[point].diaria);
    fullduracaoint = atoi(fullduracao);
    diariaint = diariaint * fullduracaoint;
    if (tofseguro[0] == 's')
        diariaint = diariaint + 50;
    itoa(diariaint, price, 10);
}
void addLog()
{
    tLog p;
    system("cls");
    printf("\n************** Incluir locacao **************");
    int verificadorDeVeiculo = 0, ponteiro = 0;
    while (verificadorDeVeiculo == 0)
    {
        printf("\n\n Digite o codigo do veiculo: ");
        scanf("%s", &p.codigo.veiculo);
        ponteiro = pesquisarPorCodigoVeiculo(p.codigo.veiculo);
        if (strcmp(veiculo[ponteiro].status, "Livre") == 0)
            verificadorDeVeiculo = 1;
        else
            printf(" O veiculo nao esta livre para locacao.\n");
    }
    printf(" O veiculo esta livre para locacao.\n");
    printf(" Codigo do cliente: ");
    scanf(" %[^\n]", &p.codigo.cliente);
    printf(" Digite a data de retirada (DD/MM/AAAA): ");
    scanf(" %[^\n]", &p.retirada);
    printf(" Digite quantos dias que o cliente deseja alugar: ");
    scanf(" %[^\n]", &p.dias);
    devolucao(p.retirada, p.dias, p.devolucao);
    printf(" Ele sera devolvido no dia: %s", p.devolucao);
    printf("\n O seguro esta incluido? (s/n): ");
    scanf(" %[^\n]", &p.seguro);
    calculaPreco(ponteiro, p.seguro, p.dias, p.preco);
    printf(" O cliente pagara: %s", p.preco);
    strcpy(p.devolucaotof, "N");
    geradorDeCodigoGlobal(p.codigo.locacao, 1);
    printf("\n Codigo: %s", p.codigo);
    i = fimDeVetorGlobal(1);
    logLocacao[i] = p;
    strcpy(veiculo[ponteiro].status, "Em uso");
    strcpy(logLocacao[i + 1].devolucao, "EOF");
    printf("\n Locacao %s incluida.", p.codigo.locacao);
}
void fimLog()
{
    system("cls");
    int logPointer, carPointer, tof1 = 0;
    printf("\n************** Finalizar locacao **************");
    while (tof1 == 0)
    {
        logPointer = pesquisarPorCodigoGlobal(1);
        if (logLocacao[logPointer].devolucaotof[0] == 'S')
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
    printf(" Por favor, cobre %s reais do cliente\n ", logLocacao[logPointer].preco);
    system("pause");
    strcpy(logLocacao[logPointer].devolucaotof, "S");
    carPointer = pesquisarPorCodigoVeiculo(logLocacao[logPointer].codigo.veiculo);
    strcpy(veiculo[carPointer].status, "Livre");
    printf("\n Devolucao concluida");
}
void addVeiculo()
{
    tVeiculo p;
    system("cls");
    printf("\n************** Incluir veiculo **************\n");
    printf("\n\n Digite o modelo: ");
    scanf(" %[^\n]", &p.hardware.modelo);
    printf(" Cor: ");
    scanf(" %[^\n]", &p.hardware.cor);
    printf(" Ocupacao: ");
    scanf(" %[^\n]", &p.hardware.ocupacao);
    printf(" Placa: ");
    scanf("%s", &p.hardware.placa);
    printf(" Valor da diaria: ");
    scanf(" %[^\n]", &p.diaria);
    printf(" Sua descricao: ");
    scanf(" %[^\n]", &p.descricao);
    geradorDeCodigoGlobal(p.codigo, 2);
    printf(" Codigo: %s", p.codigo);
    strcpy(p.status, "Livre");
    int i = fimDeVetorGlobal(2);
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
    printf("\n********************* Programa de fidelidade ************************\n");
    char code[SIZE__CODE_ALL];
    printf("\n\n Informe o codigo do cliente:");
    scanf("%s", &code);
    int total = printarContar(code) * 10;
    printf("\n Este cliente tem %d pontos", total);
    if (total >= 500)
        printf(", qualificando-o para o kit da LocaMais.");
}
void carregaDadosDosArquivos()
{
    FILE *pLerCliente = fopen("CLENTES.csv", "r"), *pLerLogLocacao = fopen("LOCACAO.csv", "r"), *pLerVeiculo = fopen("VEICULO.csv", "r");
    char type[150], value[150];
    tCliente client;
    tVeiculo vehicle;
    tLog registro;
    int outScan;
    i = 0;
    if (pLerCliente != NULL)
    {
        outScan = fscanf(pLerCliente, "%s %[^\n]", &type, &value);
        while (outScan != EOF)
        {
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(client.nome, "");
                strcpy(client.codigo, "");
                strcpy(client.telefone, "");
            }
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
            else if (strcasecmp(type, "FIM") == 0)
            {
                cliente[i] = client;
                i++;
            }
            outScan = fscanf(pLerCliente, "%s %[^\n]", &type, &value);
        }
        strcpy(cliente[i].nome, "EOF");
        fclose(pLerCliente);
    }
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
void escreverVetores()
{
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
        printf("\n\n 1. Incluir cliente");
        printf("\n 2. Pesquisar cliente por codigo");
        printf("\n 3. Incluir veiculo");
        printf("\n 4. Pesquisar veiculo por codigo");
        printf("\n 5. Gerar nova locacao");
        printf("\n 6. Pesquisar locacao por codigo");
        printf("\n 7. Determinar fim de locacao");
        printf("\n 8. Printar todo o registro");
        printf("\n 9. Programa de fidelidade");
        printf("\n 10. Encerrar ");
        printf("\n\n Digite sua opcao: ");
        scanf(" %d", &opcao);
        if (opcao >= 1 && opcao <= 10)
        {
            switchComandosInterface(opcao);
            printf("\n\n");
            system("pause");
        }
    }
    escreverVetores();
}