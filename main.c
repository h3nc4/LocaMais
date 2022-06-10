#include <conio.h>
#include <dos.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE_CLIENT 100
#define MAX_SIZE_VEHICLES 100
#define MAX_SIZE_SELLING_LOG 100
/* Possiveis arquivos a serem usados
FILE *pSalvarClientes = fopen("CLENTES.csv", "w"),
     *pLerCliente = fopen("CLENTES.csv", "r"),
     *pLogLocacao = fopen("LOCACAO.csv", "a"),
     *pAdicionarVeiculo = fopen("VEICULO.csv", "a"),
     *pLerVeiculo = fopen("VEICULO.csv", "r"),
     *pAlterarVeiculo = fopen("VEICULO.csv", "w");

    fclose(pLerCliente);
    fclose(pAdicionarCliente);
    fclose(pLogLocacao);
    fclose(pLerVeiculo);
    fclose(pAdicionarVeiculo);
    fclose(pAlterarVeiculo);*/

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
    char codigo[21];
    char telefone[15];
};
typedef struct sCliente tCliente;
tCliente cliente[MAX_SIZE_CLIENT];
struct sCliente iniCliente(char p1[], char p2[], char p3[], char p4[], char p5[], char p6[], char p7[], char p8[], char p9[], char p10[])
{
    tCliente n;
    strcpy(n.nome, p1);
    strcpy(n.telefone, p2);
    strcpy(n.codigo, p3);
    strcpy(n.endereco.rua, p4);
    strcpy(n.endereco.numero, p5);
    strcpy(n.endereco.complemento, p6);
    strcpy(n.endereco.bairro, p7);
    strcpy(n.endereco.cidade, p8);
    strcpy(n.endereco.estado, p9);
    strcpy(n.endereco.cep, p10);
    return n;
}
void switchComandos(int p)
{
    if (p == 1)
        addCliente();
    else if (p == 2)
        printCliente(cliente[pesquisarPorCodigo()]);
}

int pesquisarPorCodigo()
{
    char code[21];
    fflush(stdin);
    gets(code);
    for (int i = 0; i < MAX_SIZE_CLIENT && strcmp(cliente[i].nome, "EOF") != 0; i++)
        if (strcasecmp(code, cliente[i].codigo) == 0)
            return i;
    return -1;
}

int fimDoArquivo()
{
    for (int i = 0; i < MAX_SIZE_CLIENT; i++)
        if (strcasecmp(cliente[i].nome, "EOF") == 0)
            return i;
    return -1;
}

void geradorDeCodigo(char codGerado[])
{
    time_t now = time(NULL);
    struct tm *pt = localtime(&now);
    char num[] = "0123456789";
    for (int i = 0; i < 10; i++)
        codGerado[i] = num[rand() % 10];
    codGerado[10] = ((pt->tm_hour - (pt->tm_hour % 10)) / 10) + '0';
    codGerado[11] = (pt->tm_hour % 10) + '0';
    codGerado[12] = ((pt->tm_min - (pt->tm_min % 10))) / 10 + '0';
    codGerado[13] = (pt->tm_min % 10) + '0';
    codGerado[14] = ((pt->tm_sec - (pt->tm_sec % 10)) / 10) + '0';
    codGerado[15] = (pt->tm_sec % 10) + '0';
    codGerado[16] = '2';
    codGerado[17] = '0';
    codGerado[18] = ((pt->tm_year - 100 - (pt->tm_year % 10)) / 10) + '0';
    codGerado[19] = (pt->tm_year % 10) + '0';
    codGerado[20] = '\0';
}

void addCliente()
{
    tCliente p;
    system("cls");
    printf("\n** Incluir cliente ******-\n");
    printf("\n\nDigite o nome: ");
    scanf(" %[^\n]", &p.nome);
    printf("  cel: ");
    scanf(" %s", &p.telefone);
    geradorDeCodigo(p.codigo);
    printf(" Codigo:%s", p.codigo);
    printf("\n ENDERECO:");
    printf("\n rua: ");
    scanf(" %[^\n]", &p.endereco.rua);
    printf(" nro: ");
    scanf("%s", &p.endereco.numero);
    printf(" complemento: ");
    scanf(" %[^\n]", &p.endereco.complemento);
    printf(" bairro: ");
    scanf(" %[^\n]", &p.endereco.bairro);
    printf(" cidade: ");
    scanf(" %[^\n]", &p.endereco.cidade);
    printf(" estado: ");
    scanf("%s", &p.endereco.estado);
    printf(" cep: ");
    scanf("%s", &p.endereco.cep);
    int i = fimDoArquivo();
    cliente[i] = p;
    strcpy(cliente[i + 1].nome, "EOF");
    printf("\n Cliente %s incluido.", p.codigo);
}

void printCliente(tCliente p)
{
    printf("\n Cliente **********");
    printf("\n Nome:%s", p.nome);
    printf("\n Tel:%s", p.telefone);
    printf("\n Codigo:%s", p.codigo);
    printf("\n Endereco:");
    printf("\n Rua %s, %s, %s", p.endereco.rua, p.endereco.numero, p.endereco.complemento);
    printf("\n %s, %s, %s", p.endereco.cidade, p.endereco.estado, p.endereco.cep);
    printf("\n");
}

void carregaDadosDoArquivo()
{
    FILE *pLerCliente = fopen("CLENTES.csv", "r");
    tCliente contato;
    char p1[150];
    char p2[150];
    int outputFscanf, i = 0;
    if (pLerCliente != NULL)
    {
        outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &p1, &p2);
        while (outputFscanf != "EOF")
        {
            if (strcasecmp(p1, "inicio") == 0)
            {
                strcpy(contato.nome, "");
                strcpy(contato.codigo, "");
                strcpy(contato.telefone, "");
            }
            else if (strcasecmp(p1, "**nome") == 0)
                strcpy(contato.nome, p2);
            else if (strcasecmp(p1, "**telefone") == 0)
                strcpy(contato.telefone, p2);
            else if (strcasecmp(p1, "**codigo") == 0)
                strcpy(contato.codigo, p2);
            else if (strcasecmp(p1, "**rua") == 0)
                strcpy(contato.endereco.rua, p2);
            else if (strcasecmp(p1, "**nro") == 0)
                strcpy(contato.endereco.numero, p2);
            else if (strcasecmp(p1, "**comp") == 0)
                strcpy(contato.endereco.complemento, p2);
            else if (strcasecmp(p1, "**bairro") == 0)
                strcpy(contato.endereco.bairro, p2);
            else if (strcasecmp(p1, "**cidade") == 0)
                strcpy(contato.endereco.cidade, p2);
            else if (strcasecmp(p1, "**estado") == 0)
                strcpy(contato.endereco.estado, p2);
            else if (strcasecmp(p1, "**cep") == 0)
                strcpy(contato.endereco.cep, p2);
            else if (strcasecmp(p1, "fim") == 0)
            {
                cliente[i] = contato;
                i++;
            }
            outputFscanf = fscanf(pLerCliente, "%s %[^\n]", &p1, &p2);
        }
        strcpy(cliente[i].nome, "EOF");
        fclose(pLerCliente);
    }
}

void escreverVetor()
{
    FILE *pSalvarClientes = fopen("CLENTES.csv", "w");

    if (pSalvarClientes != NULL)
    {
        for (int i = 0; strcmp("EOF", cliente[i].nome) != 0; i++)
        {
            fprintf(pSalvarClientes, "inicio\n");
            fprintf(pSalvarClientes, "**Nome %s\n", cliente[i].nome);
            fprintf(pSalvarClientes, "**codigo %s\n", cliente[i].codigo);
            fprintf(pSalvarClientes, "**Telefone %s\n", cliente[i].telefone);
            fprintf(pSalvarClientes, "**Rua %s\n", cliente[i].endereco.rua);
            fprintf(pSalvarClientes, "**Nro %s\n", cliente[i].endereco.numero);
            fprintf(pSalvarClientes, "**Comp %s\n", cliente[i].endereco.complemento);
            fprintf(pSalvarClientes, "**Bairro %s\n", cliente[i].endereco.bairro);
            fprintf(pSalvarClientes, "**Cidade %s\n", cliente[i].endereco.cidade);
            fprintf(pSalvarClientes, "**Estado %s\n", cliente[i].endereco.estado);
            fprintf(pSalvarClientes, "**Cep %s\n", cliente[i].endereco.cep);
            fprintf(pSalvarClientes, "fim\n");
        }
        fclose(pSalvarClientes);
    }
}

main()
{
    srand((unsigned int)(time(NULL)));
    cliente[0] = iniCliente("Luquinhas", "31-99999-9999", "17409488241744112022", "rua da luz", "692", "casa", "Santa Lucia", "Belo Horizonte", "MG", "30.110-111");
    cliente[1] = iniCliente("Ana Claras", "31-99999-9999", "15811391221745382022", "rua da luz", "692", "casa", "Santa Lucia", "Belo Horizonte", "MG", "30.110-112");
    cliente[2] = iniCliente("Pedro Santos", "31-99999-9999", "08396876981745562022", "rua da luz", "692", "casa", "Santa Lucia", "Belo Horizonte", "MG", "30.110-113");
    cliente[3] = iniCliente("Theodoro", "31-99999-9999", "98494529411746172022", "rua da luz", "692", "casa", "Santa Lucia", "Belo Horizonte", "MG", "30.110-114");
    cliente[4] = iniCliente("Joaquim", "31-99999-9999", "13767741661746332022", "rua da luz", "692", "casa", "Santa Lucia", "Belo Horizonte", "MG", "30.110-115");
    cliente[5] = iniCliente("Henrique", "31-99999-9999", "71221327291746472022", "rua da felicidade", "1000", "101", "Ana lucia", "Belo Horizonte", "MG", "12.345-123");
    printf("sucesso");
    int opcao = 0;
    while (opcao != 9)
    {
        system("cls");
        printf("\n****** Cadastro de Clientes ********\n");
        printf("\n1.Incluir ");
        printf("\n2.Pesquisar por codigo");
        printf("\n9.Encerrar ");
        printf("\n\nDigite sua opcao : ");
        scanf(" %i", &opcao);
        if (opcao >= 1 && opcao <= 9)
        {
            switchComandos(opcao);
            printf("\n\n");
            system("pause");
        }
    }
    escreverVetor();
}
