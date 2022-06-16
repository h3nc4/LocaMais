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

#define X__SIZE_CLIENT 1000
#define X__SIZE_VEHICLES 1000
#define X__SIZE_SELLING_LOG 1000

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

    //

    // Fim da funcao

    //
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

    //

    // Fim da funcao

    //
}

//

/* Esta funcao printa o registro de um cliente especifico,
    ela recebe como entrada o ponteiro do cliente */

void printCliente(tCliente p)

{

    // Interface do usuario
    printf("\n ******************** Cliente ********************");
    printf("\n\n Nome: %s", p.nome);
    printf("\n Tel: %s", p.telefone);
    printf("\n Codigo: %s", p.codigo);
    printf("\n Endereco:");
    printf("\n Rua %s, %s, %s", p.endereco.rua, p.endereco.numero, p.endereco.complemento);
    printf("\n %s, %s, %s", p.endereco.cidade, p.endereco.estado, p.endereco.cep);
    printf("\n");

    //

    // Fim da funcao

    //
}

//

/* Esta funcao printa o registro de um veiculo especifico,
    ela recebe como entrada o ponteiro do veiculo */

void printVeiculo(tVeiculo q)

{

    // Interface do usuario
    printf("\n ***************** Veiculo *****************");
    printf("\n\n Modelo: %s", q.hardware.modelo);
    printf("\n Descricao: %s", q.descricao);
    printf("\n Codigo: %s", q.codigo);
    printf("\n Cor: %s, Ocupacao: %s", q.hardware.cor, q.hardware.ocupacao);
    printf("\n Diaria: %s, Placa: %s", q.diaria, q.hardware.placa);
    printf("\n Status: %s", q.status);
    printf("\n");

    //

    // Fim da funcao

    //
}

//

/* Esta funcao printa o registro de uma locacao especifica,
    ela recebe como entrada o ponteiro da locacao */

void printLog(tLog r)

{

    // Interface do usuario
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

    //

    // Fim da funcao

    //
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

    //

    // Fim da funcao

    //
}

//

/* Funcao auxiliar da interface de usuario,
   recebe como entrada um numero inteiro e designa a funcao correspondente */

void switchComandosInterface(int p)

{

    // Limpar teclado apos receber comando
    fflush(stdin);

    // Adicionar cliente
    if (p == 1)
        addCliente();

    // Buscar e printar registro de um cliente
    else if (p == 2)
        printCliente(cliente[pesquisarPorCodigoGlobal(0)]);

    // Adicionar veiculo
    else if (p == 3)
        addVeiculo();

    // Buscar e printar registro de um veiculo
    else if (p == 4)
        printVeiculo(veiculo[pesquisarPorCodigoGlobal(2)]);

    // Adicionar locacao
    else if (p == 5)
        addLog();

    // Buscar e printar registro de uma locacao
    else if (p == 6)
        printLog(logLocacao[pesquisarPorCodigoGlobal(1)]);

    // Declarar o fim de uma locacao
    else if (p == 7)
        fimLog();

    // Printar o registro completo de um tipo
    else if (p == 8)
        printTudo();

    // Printar todas as locacoes de um cliente e o eleger para o kit LocaMais
    else if (p == 9)
        fidelidade();

    //

    // Fim da funcao

    //
}

//

/* Esta funcao encontra o ponteiro final de um vetor e o retorna,
    ela recebe uma entrada inteira que define o vetor a ser varido */

int fimDeVetorGlobal(int inp)

{

    // 0 para cliente
    if (inp == 0)
        for (i = 0; i < X__SIZE_CLIENT; i++)
            if (strcasecmp(cliente[i].nome, "EOF") == 0)
                return i;

    // 1 para locacao
    if (inp == 1)
        for (i = 0; i < X__SIZE_SELLING_LOG; i++)
            if (strcasecmp(logLocacao[i].devolucao, "EOF") == 0)
                return i;

    // 2 para veiculo
    if (inp == 2)
        for (i = 0; i < X__SIZE_VEHICLES; i++)
            if (strcasecmp(veiculo[i].descricao, "EOF") == 0)
                return i;

    // Retorna -1 caso nada seja retornado
    return -1;

    //

    // Fim da funcao

    //
}

//

// Esta funcao gera codigos para todos os tipos, nela entram o codigo a ser gerado e o seu tipo

void geradorDeCodigoGlobal(char codGerado[], int in)

{

    // Inicializa data
    time_t now = time(NULL);

    // Inicializ estrutura da data
    struct tm *pt = localtime(&now);

    // esta string de caracteres numericos e usada para preencher numeros aleatorios
    char num[] = "0123456789";

    // 0 para locacao, dando como saida um numero de 0 a 3
    if (in == 0)
        codGerado[0] = num[rand() % 4];

    // 1 para locacao, dando como saida um numero de 4 a 7
    else if (in == 1)
        codGerado[0] = num[(rand() % 4) + 4];

    // 2 para locacao, dando como saida um numero de 8 a 9
    else if (in == 2)
        codGerado[0] = num[(rand() % 2) + 8];

    // Gera os proximos 4 numeros de forma totalmente aleatoria
    for (int i = 1; i < 5; i++)
        codGerado[i] = num[rand() % 10];

    // Formatacao
    codGerado[5] = '/';

    /*********** Os vetores a seguir sao preenchidos referente a diferenca do dia atual ao dia 1/1 ***********/
    codGerado[6] = ((pt->tm_yday - pt->tm_yday % 100) / 100) + '0';
    codGerado[7] = (pt->tm_yday - pt->tm_yday + pt->tm_yday % 100 - pt->tm_yday % 10) / 10 + '0';
    codGerado[8] = (pt->tm_yday % 10) + '0';
    /*********************************************************************************************************/

    // Formatacao
    codGerado[9] = '.';

    /********************************************** Hora atual **********************************************/
    codGerado[10] = (pt->tm_hour - pt->tm_hour % 10) / 10 + '0';
    codGerado[11] = pt->tm_hour % 10 + '0';
    /********************************************************************************************************/

    /*********************************************** Minutos ***********************************************/
    codGerado[12] = (pt->tm_min - pt->tm_min % 10) / 10 + '0';

    // Formatacao
    codGerado[13] = '.';

    codGerado[14] = pt->tm_min % 10 + '0';
    /********************************************************************************************************/

    /*********************************************** Segundos ***********************************************/
    codGerado[15] = (pt->tm_sec - pt->tm_sec % 10) / 10 + '0';
    codGerado[16] = pt->tm_sec % 10 + '0';
    /********************************************************************************************************/

    // Formatacao
    codGerado[17] = '-';

    /************************************************* Ano *************************************************/
    codGerado[18] = (pt->tm_year - 100 - pt->tm_year % 10) / 10 + '0';
    codGerado[19] = pt->tm_year % 10 + '0';
    /********************************************************************************************************/

    // Fim da string
    codGerado[20] = NULL;

    //

    // Fim da funcao

    //
}

//

// Esta funcao adiciona um cliente

void addCliente()

{

    // Criar tipo a ser preenchido
    tCliente p;
    system("cls");

    // Interface da nova locacao
    printf("\n************** Incluir cliente **************\n");

    /******* Preencher novo item atraves de inputs do usuario *******/

    // Sobre o nome
    printf("\n\n Digite o nome: ");
    scanf(" %[^\n]", &p.nome);

    // Sobre o telefone
    printf(" Cel: ");
    scanf(" %[^\n]", &p.telefone);

    // Sobre a rua
    printf(" Rua: ");
    scanf(" %[^\n]", &p.endereco.rua);

    // Sobre o numero da residencia
    printf(" Nro: ");
    scanf("%s", &p.endereco.numero);

    // Sobre o complemento
    printf(" Complemento: ");
    scanf(" %[^\n]", &p.endereco.complemento);

    // Sobre o bairro
    printf(" Bairro: ");
    scanf(" %[^\n]", &p.endereco.bairro);

    // Sobre a cidade
    printf(" Cidade: ");
    scanf(" %[^\n]", &p.endereco.cidade);

    // Sobre o estado, formato de dois caracteres
    printf(" Estado: ");
    scanf("%s", &p.endereco.estado);

    // Sobre o cep
    printf(" Cep: ");
    scanf("%s", &p.endereco.cep);

    /*********************** Fim dos inputs *********************/

    // Gera codigo do cliente
    geradorDeCodigoGlobal(p.codigo, 0);
    printf(" Codigo:%s", p.codigo);

    // Busca pelo ultimo ponteiro preenchido do vetor veiculo
    i = fimDeVetorGlobal(0);

    // Preenche este vetor com o tipo temporario
    cliente[i] = p;

    // Preenche o proximo vetor com "EOF"
    strcpy(cliente[i + 1].nome, "EOF");

    // Declara o sucesso da operacao ao usuario
    printf("\n Cliente %s incluido.", p.codigo);

    //

    // Fim da funcao

    //
}

//

// Calcula data da devolucao

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

    //

    // Fim da funcao

    //
}

//

// Calcula o preco de uma locacao

void calculaPreco(int point, char tofseguro[2], char fullduracao[4], char price[7])

{

    int diariaint,
        fullduracaoint;

    // Converte diaria para int
    diariaint = atoi(veiculo[point].diaria);

    // Converte a data para int
    fullduracaoint = atoi(fullduracao);

    // Calcula a o preco
    diariaint = diariaint * fullduracaoint;

    // Adiciona preco do seguro
    if (tofseguro[0] == 's')
        diariaint = diariaint + 50;

    // Converte o preco em int para string
    itoa(diariaint, price, 10);

    //

    // Fim da funcao

    //
}

//

// Esta funcao registra uma nova locacao

void addLog()

{

    // Criar tipo a ser preenchido
    tLog p;
    system("cls");

    // Interface da nova locacao
    printf("\n************** Incluir locacao **************");
    int verificadorDeVeiculo = 0,
        ponteiro = 0;

    // "while" prende o usuario a escolher um veiculo valido
    while (verificadorDeVeiculo == 0)
    {

        // Usuario digita o codigo do veiculo a ser alugado
        printf("\n\n Digite o codigo do veiculo: ");
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
    printf(" Codigo do cliente: ");
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
    i = fimDeVetorGlobal(1);

    // Preenche este vetor com o tipo temporario
    logLocacao[i] = p;

    // Caso o veiculo esteja livre, o atualiza
    strcpy(veiculo[ponteiro].status, "Em uso");

    // Preenche o proximo vetor com "EOF"
    strcpy(logLocacao[i + 1].devolucao, "EOF");

    // Declara o sucesso da operacao ao usuario
    printf("\n Locacao %s incluida.", p.codigo.locacao);

    //

    // Fim da funcao

    //
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
    printf("\n************** Finalizar locacao **************");

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
    printf(" Por favor, cobre %s reais do cliente\n ", logLocacao[logPointer].preco);

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

    //

    // Fim da funcao

    //
}

//

// Esta funcao adiciona um veiculo ao registro

void addVeiculo()

{

    // Criar tipo a ser preenchido
    tVeiculo p;
    system("cls");

    /******* Preencher novo item atraves de inputs do usuario *******/

    // Interface de usuario
    printf("\n************** Incluir veiculo **************\n");

    // Sobre o modelo
    printf("\n\n Digite o modelo: ");
    scanf(" %[^\n]", &p.hardware.modelo);

    // Sobre a cor
    printf(" Cor: ");
    scanf(" %[^\n]", &p.hardware.cor);

    // Sobre a ocupacao
    printf(" Ocupacao: ");
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
    int i = fimDeVetorGlobal(2);

    // Preenche este vetor com o tipo temporario
    veiculo[i] = p;

    // Preenche o proximo vetor com "EOF"
    strcpy(veiculo[i + 1].descricao, "EOF");

    // Declara sucesso ao usuario
    printf("\n Veiculo %s incluido.", p.codigo);

    //

    // Fim da funcao

    //
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

    //

    // Fim da funcao

    //
}

//

// Esta funcao printa todas as locacoes de um cliente e o seu total

void fidelidade()

{
    printf("\n******* Programa de fidelidade *******\n");
    char code[SIZE__CODE_ALL];

    // Usuario digita o codigo do cliente
    printf("\n\n Informe o codigo do cliente:");
    scanf("%s", &code);

    // Envia o codigo para a funcao anterior, printanto locacoes do cliente e retornando o seu total
    int total = printarContar(code) * 10;

    // Imprime o total de locacoes
    printf("\n Este cliente tem %d pontos", total);

    // Se o cliente tiver 500 pontos, declara sua qualificacao ao kit
    if (total >= 500)
        printf(", qualificando-o para o kit da LocaMais.");

    //

    // Fim da funcao

    //
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

    // Inicializa o ponteiro
    i = 0;

    // Se o arquivo existe
    if (pLerCliente != NULL)
    {

        // outScan le o retorno do scanf, testando assim se o arquivo chegou ao final
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

            // Estrutura nome
            else if (strcasecmp(type, "Nome") == 0)
                strcpy(client.nome, value);

            // Estrutura telefone
            else if (strcasecmp(type, "Telefone") == 0)
                strcpy(client.telefone, value);

            // Estrutura codigo
            else if (strcasecmp(type, "Codigo") == 0)
                strcpy(client.codigo, value);

            // Estrutura rua
            else if (strcasecmp(type, "Rua") == 0)
                strcpy(client.endereco.rua, value);

            // Estrutura numero
            else if (strcasecmp(type, "Nro") == 0)
                strcpy(client.endereco.numero, value);

            // Estrutura complemento
            else if (strcasecmp(type, "Comp") == 0)
                strcpy(client.endereco.complemento, value);

            // Estrutura bairro
            else if (strcasecmp(type, "Bairro") == 0)
                strcpy(client.endereco.bairro, value);

            // Estrutura cidade
            else if (strcasecmp(type, "Cidade") == 0)
                strcpy(client.endereco.cidade, value);

            // Estrutura estado
            else if (strcasecmp(type, "Estado") == 0)
                strcpy(client.endereco.estado, value);

            // Estrutura cep
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

            // outScan le o retorno do scanf, testando assim se o arquivo chegou ao final
            outScan = fscanf(pLerCliente, "%s %[^\n]", &type, &value);
        }

        // Ao final, escreve o fim do vetor
        strcpy(cliente[i].nome, "EOF");

        // Fecha o arquivo
        fclose(pLerCliente);
    }

    //
    //              OS PROXIMOS DOIS "IF" SAO EXATAMENTE IGUAIS AO PRIMEIRO, POREM PARA OUTROS VETORES
    //

    // Se o arquivo existe
    if (pLerLogLocacao != NULL)
    {

        // Inicializa o ponteiro
        i = 0;

        // outScan le o retorno do scanf, testando assim se o arquivo chegou ao final
        outScan = fscanf(pLerLogLocacao, "%s %[^\n]", &type, &value);

        // Enquanto o arquivo nao chega ao fim
        while (outScan != EOF)
        {

            // Le o inicio do registro no arquivo
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(registro.devolucao, "");
                strcpy(registro.seguro, "");
                strcpy(registro.dias, "");
            }

            /* Le cada uma das linhas em busca de sua respectiva variavel,
               definitivamente nao e o metodo mais eficiente */

            // Estrutura devolucao
            else if (strcasecmp(type, "Devolucao") == 0)
                strcpy(registro.devolucao, value);

            // Estrutura seguro
            else if (strcasecmp(type, "Seguro") == 0)
                strcpy(registro.seguro, value);

            // Estrutura dias
            else if (strcasecmp(type, "Dias") == 0)
                strcpy(registro.dias, value);

            // Estrutura retirada
            else if (strcasecmp(type, "Retirada") == 0)
                strcpy(registro.retirada, value);

            // Estrutura devolvido
            else if (strcasecmp(type, "Devolvido") == 0)
                strcpy(registro.devolucaotof, value);

            // Estrutura codigo
            else if (strcasecmp(type, "Codigo") == 0)
                strcpy(registro.codigo.locacao, value);

            // Estrutura cliente
            else if (strcasecmp(type, "Cliente") == 0)
                strcpy(registro.codigo.cliente, value);

            // Estrutura veiculo
            else if (strcasecmp(type, "Veiculo") == 0)
                strcpy(registro.codigo.veiculo, value);

            // Estrutura preco
            else if (strcasecmp(type, "Preco") == 0)
                strcpy(registro.preco, value);

            // Le fim do registro no arquivo
            else if (strcasecmp(type, "FIM") == 0)
            {

                // Passa do vetor temporario para o definitivo
                logLocacao[i] = registro;

                // i++ para mudar de registro no vetor
                i++;
            }

            // outScan le o retorno do scanf, testando assim se o arquivo chegou ao final
            outScan = fscanf(pLerLogLocacao, "%s %[^\n]", &type, &value);
        }

        // Ao final, escreve o fim do vetor
        strcpy(logLocacao[i].devolucao, "EOF");

        // Fecha o arquivo
        fclose(pLerLogLocacao);
    }

    // Se o arquivo existe
    if (pLerVeiculo != NULL)
    {

        // Inicializa o ponteiro
        i = 0;

        // outScan le o retorno do scanf, testando assim se o arquivo chegou ao final
        outScan = fscanf(pLerVeiculo, "%s %[^\n]", &type, &value);

        // Enquanto o arquivo nao chega ao fim
        while (outScan != EOF)
        {

            // Le o inicio do registro no arquivo
            if (strcasecmp(type, "INICIO") == 0)
            {
                strcpy(vehicle.descricao, "");
                strcpy(vehicle.codigo, "");
                strcpy(vehicle.status, "");
            }

            /* Le cada uma das linhas em busca de sua respectiva variavel,
               definitivamente nao e o metodo mais eficiente */

            // Estrutura descricao
            else if (strcasecmp(type, "Descricao") == 0)
                strcpy(vehicle.descricao, value);

            // Estrutura codigo
            else if (strcasecmp(type, "Codigo") == 0)
                strcpy(vehicle.codigo, value);

            // Estrutura status
            else if (strcasecmp(type, "Status") == 0)
                strcpy(vehicle.status, value);

            // Estrutura diaria
            else if (strcasecmp(type, "Diaria") == 0)
                strcpy(vehicle.diaria, value);

            // Estrutura placa
            else if (strcasecmp(type, "Placa") == 0)
                strcpy(vehicle.hardware.placa, value);

            // Estrutura modelo
            else if (strcasecmp(type, "Modelo") == 0)
                strcpy(vehicle.hardware.modelo, value);

            // Estrutura ocupacao
            else if (strcasecmp(type, "Ocupacao") == 0)
                strcpy(vehicle.hardware.ocupacao, value);

            // Estrutura cor
            else if (strcasecmp(type, "Cor") == 0)
                strcpy(vehicle.hardware.cor, value);

            // Le fim do registro no arquivo
            else if (strcasecmp(type, "FIM") == 0)
            {

                // Passa do vetor temporario para o definitivo
                veiculo[i] = vehicle;

                // i++ para mudar de registro no vetor
                i++;
            }

            // outScan le o retorno do scanf, testando assim se o arquivo chegou ao final

            outScan = fscanf(pLerVeiculo, "%s %[^\n]", &type, &value);
        }

        // Ao final, escreve o fim do vetor
        strcpy(veiculo[i].descricao, "EOF");

        // Fecha o arquivo
        fclose(pLerVeiculo);
    }

    //

    // Fim da funcao

    //
}

//

// Funcao escreve os vetores em arquivos ao finalizar o processo

void escreverVetores()

{
    // Arquivo
    FILE *pSalvarClientes = fopen("CLENTES.csv", "w"),
         *pSalvarLogLocacao = fopen("LOCACAO.csv", "w"),
         *pSalvarVeiculos = fopen("VEICULO.csv", "w");

    // Se o ponteiro existe

    if (pSalvarClientes != NULL)
    {

        /* "for" funciona como contador, inicializador e while da funcao,
            chegando ao fim quando encontra a string "EOF" no vetor */

        for (i = 0; strcmp("EOF", cliente[i].nome) != 0; i++)
        {

            // Le o inicio do registro no vetor
            fprintf(pSalvarClientes, "INICIO CLIENTE\n");

            // Escreve a estrutura nome
            fprintf(pSalvarClientes, "Nome %s\n", cliente[i].nome);

            // Escreve a estrutura codigo
            fprintf(pSalvarClientes, "Codigo %s\n", cliente[i].codigo);

            // Escreve a estrutura telefone
            fprintf(pSalvarClientes, "Telefone %s\n", cliente[i].telefone);

            // Escreve a estrutura rua
            fprintf(pSalvarClientes, "Rua %s\n", cliente[i].endereco.rua);

            // Escreve a estrutura numero
            fprintf(pSalvarClientes, "Nro %s\n", cliente[i].endereco.numero);

            // Escreve a estrutura complemento
            fprintf(pSalvarClientes, "Comp %s\n", cliente[i].endereco.complemento);

            // Escreve a estrutura bairro
            fprintf(pSalvarClientes, "Bairro %s\n", cliente[i].endereco.bairro);

            // Escreve a estrutura cidade
            fprintf(pSalvarClientes, "Cidade %s\n", cliente[i].endereco.cidade);

            // Escreve a estrutura estado
            fprintf(pSalvarClientes, "Estado %s\n", cliente[i].endereco.estado);

            // Escreve a estrutura cep
            fprintf(pSalvarClientes, "Cep %s\n", cliente[i].endereco.cep);

            // Le o fim do registro no vetor
            fprintf(pSalvarClientes, "FIM CLIENTE\n");
        }

        // Fecha o arquivo
        fclose(pSalvarClientes);
    }

    //
    //              OS PROXIMOS DOIS "IF" SAO EXATAMENTE IGUAIS AO PRIMEIRO, POREM PARA OUTROS VETORES
    //

    // Se o ponteiro existe

    if (pSalvarLogLocacao != NULL)
    {

        /* "for" funciona como contador, inicializador e while da funcao,
            chegando ao fim quando encontra a string "EOF" no vetor */

        for (i = 0; strcmp("EOF", logLocacao[i].devolucao) != 0; i++)
        {

            // Le o inicio do registro no vetor
            fprintf(pSalvarLogLocacao, "INICIO LOCACAO\n");

            // Escreve a estrutura devolucao
            fprintf(pSalvarLogLocacao, "Devolucao %s\n", logLocacao[i].devolucao);

            // Escreve a estrutura seguro
            fprintf(pSalvarLogLocacao, "Seguro %s\n", logLocacao[i].seguro);

            // Escreve a estrutura dias
            fprintf(pSalvarLogLocacao, "Dias %s\n", logLocacao[i].dias);

            // Escreve a estrutura retirada
            fprintf(pSalvarLogLocacao, "Retirada %s\n", logLocacao[i].retirada);

            // Escreve a estrutura devolvido
            fprintf(pSalvarLogLocacao, "Devolvido %s\n", logLocacao[i].devolucaotof);

            // Escreve a estrutura codigo
            fprintf(pSalvarLogLocacao, "Codigo %s\n", logLocacao[i].codigo.locacao);

            // Escreve a estrutura cliente
            fprintf(pSalvarLogLocacao, "Cliente %s\n", logLocacao[i].codigo.cliente);

            // Escreve a estrutura veiculo
            fprintf(pSalvarLogLocacao, "Veiculo %s\n", logLocacao[i].codigo.veiculo);

            // Escreve a estrutura preco
            fprintf(pSalvarLogLocacao, "Preco %s\n", logLocacao[i].preco);

            // Le o fim do registro no vetor
            fprintf(pSalvarLogLocacao, "FIM LOCACAO\n");
        }

        // Fecha o arquivo
        fclose(pSalvarLogLocacao);
    }

    // Se o ponteiro existe

    if (pSalvarVeiculos != NULL)
    {

        /* "for" funciona como contador, inicializador e while da funcao,
            chegando ao fim quando encontra a string "EOF" no vetor */

        for (i = 0; strcmp("EOF", veiculo[i].descricao) != 0; i++)
        {

            // Le o inicio do registro no vetor
            fprintf(pSalvarVeiculos, "INICIO VEICULO\n");

            // Escreve a estrutura descricao
            fprintf(pSalvarVeiculos, "Descricao %s\n", veiculo[i].descricao);

            // Escreve a estrutura codigo
            fprintf(pSalvarVeiculos, "Codigo %s\n", veiculo[i].codigo);

            // Escreve a estrutura status
            fprintf(pSalvarVeiculos, "Status %s\n", veiculo[i].status);

            // Escreve a estrutura diaria
            fprintf(pSalvarVeiculos, "Diaria %s\n", veiculo[i].diaria);

            // Escreve a estrutura placa
            fprintf(pSalvarVeiculos, "Placa %s\n", veiculo[i].hardware.placa);

            // Escreve a estrutura modelo
            fprintf(pSalvarVeiculos, "Modelo %s\n", veiculo[i].hardware.modelo);

            // Escreve a estrutura ocupacao
            fprintf(pSalvarVeiculos, "Ocupacao %s\n", veiculo[i].hardware.ocupacao);

            // Escreve a estrutura cor
            fprintf(pSalvarVeiculos, "Cor %s\n", veiculo[i].hardware.cor);

            // Le o fim do registro no vetor
            fprintf(pSalvarVeiculos, "FIM VEICULO\n");
        }

        // Fecha o arquivo
        fclose(pSalvarVeiculos);
    }

    //

    // Fim da funcao

    //
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

    // Decisao do usuario
    int opcao = 0;

    // "while" prende o usuario a escolher uma funcao valida
    while (opcao != 10)
    {
        system("cls");

        // Interface de usuario
        printf("\n************************ Cadastro de Clientes ************************\n");
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

            // Envia a escolha do usuario para a funcao tratar
            switchComandosInterface(opcao);
            printf("\n\n");
            system("pause");
        }
    }

    // Salva os vetores em arquivos
    escreverVetores();

    //

    // Fim da funcao

    //
}

//

/****************************         FIM DA FUNCAO PRINCIPAL         ****************************/

//

/*******************************************       FIM DO CODIGO       *******************************************/

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