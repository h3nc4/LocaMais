#include <stdio.h>
#include <time.h>

struct sEndereco
{
    char rua[100];
    char numero[10];
    char complemento[10];
    char bairro[50];
    char cidade[50];
    char estado[3];
    char cep[15];
};
typedef struct sEndereco tEndereco;
struct sCliente
{
    char nome[50];
    char telefone[15];
    char codigo[100];
    tEndereco endereco;
};
typedef struct sCliente tCliente;
tCliente cliente[100];

main()
{
    FILE *pLerCliente = fopen("CLENTES.csv", "r"),
         *pAdicionarCliente = fopen("CLENTES.csv", "a"),
         *pLogLocacao = fopen("LOCACAO.csv", "a"),
         *pAdicionarVeiculo = fopen("VEICULO.csv", "a"),
         *pLerVeiculo = fopen("VEICULO.csv", "r"),
         *pAlterarVeiculo = fopen("VEICULO.csv", "w");

    fclose(pLerCliente);
    fclose(pAdicionarCliente);
    fclose(pLogLocacao);
    fclose(pLerVeiculo);
    fclose(pAdicionarVeiculo);
    fclose(pAlterarVeiculo);
}